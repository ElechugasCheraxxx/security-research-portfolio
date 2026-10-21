#!/usr/bin/env python3
"""Emulador del stub del empaquetador del loader, sobre Unicorn.

Objetivo: ejecutar solo la etapa de desempaquetado y volcar las secciones
descifradas. No emula Windows: intercepta cualquier salto fuera de la imagen
y lo trata como una llamada a API, devolviendo un valor plausible.
"""
import sys, struct, collections
import pefile
from unicorn import *
from unicorn.x86_const import *
from capstone import Cs, CS_ARCH_X86, CS_MODE_64

PE = sys.argv[1] if len(sys.argv) > 1 else "stage_run/loader.exe"
OUT = sys.argv[2] if len(sys.argv) > 2 else "stage_run/emu_out"

pe = pefile.PE(PE)
IB = pe.OPTIONAL_HEADER.ImageBase
SIZE = pe.OPTIONAL_HEADER.SizeOfImage
EP = pe.OPTIONAL_HEADER.AddressOfEntryPoint

print("[*] %s" % PE)
print("[*] imagebase=0x%x  SizeOfImage=0x%x (%d B)  entry RVA=0x%x VA=0x%x"
      % (IB, SIZE, SIZE, EP, IB + EP))

# ---------------------------------------------------------------- memoria
uc = Uc(UC_ARCH_X86, UC_MODE_64)
uc.mem_map(IB, (SIZE + 0xFFF) & ~0xFFF)

# cabeceras
hdr = pe.__data__[:pe.OPTIONAL_HEADER.SizeOfHeaders]
uc.mem_write(IB, hdr)

# secciones
print("[*] secciones:")
for s in pe.sections:
    name = s.Name.rstrip(b"\0").decode("ascii", "replace")
    va = IB + s.VirtualAddress
    vs = max(s.Misc_VirtualSize, s.SizeOfRawData)
    data = s.get_data() if s.SizeOfRawData else b""
    if data:
        uc.mem_write(va, data[:vs])
    print("    %-9s VA=0x%012x vsize=%-9d raw=%-9d %s"
          % (name, va, s.Misc_VirtualSize, s.SizeOfRawData,
             "datos" if s.SizeOfRawData else "VACIA (se rellena al desempaquetar)"))

# pila
STACK_BASE = 0x7FF000000000
STACK_SIZE = 0x200000
uc.mem_map(STACK_BASE, STACK_SIZE)
RSP = STACK_BASE + STACK_SIZE - 0x4000

# zona de hilos / TEB / PEB
TEB = 0x7FFD00000000
PEB = 0x7FFD00001000
uc.mem_map(TEB & ~0xFFF, 0x4000)
# Layout del PEB en x64 (offsets reales, no los de x86):
#   0x02 BeingDebugged    -> 0 = "no hay depurador"
#   0x08 Mutant
#   0x10 ImageBaseAddress -> ES la que usa el empaquetador para el OEP
#   0x18 Ldr
#   0x20 ProcessParameters
uc.mem_write(PEB + 0x02, b"\x00")                      # BeingDebugged
uc.mem_write(PEB + 0x10, struct.pack("<Q", IB))         # ImageBaseAddress
uc.mem_write(TEB + 0x30, struct.pack("<Q", PEB))

# --- lista de modulos sintetica -------------------------------------------
# El empaquetador resuelve APIs por hash recorriendo
# PEB->Ldr->InMemoryOrderModuleList; con la lista vacia no encuentra nada y
# 'call rax' salta a basura. Cada export apunta a un trampolin unico para
# poder registrar a que API llama.
TRAMP_BASE = 0x30000000000
TRAMP_SIZE = 0x10000
uc.mem_map(TRAMP_BASE, TRAMP_SIZE)
uc.mem_write(TRAMP_BASE, b"\xc3" * TRAMP_SIZE)

import fake_modules as FM

tramp = {}
def _mk(names):
    return list(names)

NTDLL_EXPORTS = [
    "NtAllocateVirtualMemory", "NtProtectVirtualMemory", "NtFreeVirtualMemory",
    "NtQueryInformationProcess", "NtSetInformationThread", "NtClose",
    "NtQuerySystemInformation", "NtCreateSection", "NtMapViewOfSection",
    "NtUnmapViewOfSection", "NtRaiseHardError", "NtCreateThread",
    "NtResumeThread", "NtSuspendThread", "NtQueueApcThread",
    "RtlAddFunctionTableEntry", "RtlDeleteFunctionTableEntry",
    "RtlLookupFunctionEntry", "RtlVirtualUnwind", "RtlGetVersion",
    "LdrLoadDll", "LdrGetProcedureAddress", "LdrGetDllHandle",
    "NtOpenProcess", "NtReadVirtualMemory", "NtWriteVirtualMemory",
    "NtCreateFile", "NtWriteFile", "NtReadFile", "NtDeviceIoControlFile",
    "NtQueryVirtualMemory", "NtFlushInstructionCache",
]
KERNEL32_EXPORTS = [
    "VirtualProtect", "VirtualAlloc", "VirtualAllocEx", "VirtualFree",
    "GetProcAddress", "LoadLibraryA", "LoadLibraryW", "GetModuleHandleA",
    "IsDebuggerPresent", "VirtualQuery", "GetSystemInfo", "CreateFileA",
    "WriteFile", "ReadFile", "CloseHandle", "GetFileSize", "CreateProcessA",
    "GetModuleHandleW", "GetCurrentProcess", "HeapAlloc", "HeapFree",
    "GetProcessHeap", "GetLastError", "SetLastError", "ExitProcess",
    "GetModuleFileNameA", "GetModuleFileNameW", "GetTickCount", "Sleep",
]
USER32_EXPORTS = [
    "CreateWindowExA", "CreateWindowExW", "MessageBoxA", "FindWindowA",
    "GetForegroundWindow", "GetDesktopWindow", "ShowWindow", "GetSystemMetrics",
]

ntdll_e = _mk(NTDLL_EXPORTS)
k32_e   = _mk(KERNEL32_EXPORTS)
u32_e   = _mk(USER32_EXPORTS)

MOD_BASE = 0x20000000000
mods = [
    FM.FakeModule(uc, MOD_BASE,          "ntdll.dll",    ntdll_e),
    FM.FakeModule(uc, MOD_BASE + 0x10000, "kernel32.dll", k32_e),
    FM.FakeModule(uc, MOD_BASE + 0x20000, "user32.dll",   u32_e),
]
for m in mods:
    tramp.update(m.stubs)
FM.build_module_list(uc, PEB, 0x7FFD00002000, mods)
print("[*] modulos sinteticos: %d exports" % len(tramp))
print("[*] rango de stubs: 0x%x .. 0x%x" % (min(tramp), max(tramp)))

uc.reg_write(UC_X86_REG_RSP, RSP)
# En x64 el PEB se localiza con 'mov rax, gs:[0x60]' (en x86 es fs:[0x30]).
# Hay que fijar la BASE del segmento GS, no la de FS.
#   TEB -> GS:[0x00] ; PEB -> GS:[0x60] ; TEB.ProcessEnvironmentBlock -> PEB
try:
    uc.msr_write(0xC0000101, TEB)     # IA32_GS_BASE
    uc.mem_write(TEB + 0x60, struct.pack("<Q", PEB))
    print("[*] GS:[0x60] -> PEB  (0x%x)" % PEB)
except Exception as e:
    print("[!] no se pudo fijar IA32_GS_BASE: %s" % e)
try:
    uc.msr_write(0xC0000100, TEB)     # IA32_FS_BASE (por si acaso)
except Exception:
    pass
# Base del segmento FS (IA32_FS_BASE): 'mov rax, fs:[0x30]' llega al TEB,
# que es como el empaquetador localiza el PEB.
try:
    uc.msr_write(0xC0000100, TEB)
except Exception as e:
    print("[!] no se pudo fijar IA32_FS_BASE: %s" % e)

cs = Cs(CS_ARCH_X86, CS_MODE_64)
cs.detail = False

IMAGE_LO, IMAGE_HI = IB, IB + SIZE
outside = collections.Counter()
trace_out = []
insn_count = [0]
MAX_INSN = 3_000_000
ring = collections.deque(maxlen=60)   # ultimas instrucciones antes del fallo
rva_fixes = []

X86_REG_BY_ENUM = {
    0: UC_X86_REG_RAX, 1: UC_X86_REG_RCX, 2: UC_X86_REG_RDX,
    3: UC_X86_REG_RBX, 4: UC_X86_REG_RSP, 5: UC_X86_REG_RBP,
    6: UC_X86_REG_RSI, 7: UC_X86_REG_RDI,
}

def hook_code(uc, addr, size, user):
    insn_count[0] += 1
    if insn_count[0] > MAX_INSN:
        print("[!] limite de instrucciones alcanzado")
        uc.emu_stop()
        return
    code = bytes(uc.mem_read(addr, size))

    # El stub resuelve el OEP como RVA y salta sin sumar la base: es la
    # dependencia que el cargador de Windows resuelve. Si una transferencia
    # indirecta apunta a un valor del rango de RVAs, se le suma ImageBase.
    if size >= 2 and code[0] == 0xFF:
        op = code[1]
        modrm = op & 0x38
        if modrm in (0x10, 0x18) and size >= 3:   # call/jmp r/m64
            mod = (code[2] >> 6) & 3
            rm = code[2] & 7
            if mod == 3 and rm in X86_REG_BY_ENUM:
                reg = X86_REG_BY_ENUM[rm]
                val = uc.reg_read(reg)
                if 0 < val < SIZE:
                    fixed = val + IB
                    uc.reg_write(reg, fixed)
                    if len(rva_fixes) < 20:
                        rva_fixes.append((addr, code.hex(), val, fixed))
                    if IMAGE_LO <= fixed < IMAGE_HI:
                        return

    ring.append((addr, size, code,
                 uc.reg_read(UC_X86_REG_RAX), uc.reg_read(UC_X86_REG_RDX),
                 uc.reg_read(UC_X86_REG_RCX), uc.reg_read(UC_X86_REG_RBX),
                 uc.reg_read(UC_X86_REG_RSI), uc.reg_read(UC_X86_REG_RDI),
                 uc.reg_read(UC_X86_REG_RSP)))
    # salto fuera de la imagen => llamada a API
    if not (IMAGE_LO <= addr < IMAGE_HI):
        name = "api_0x%x" % addr
        outside[addr] += 1
        if len(trace_out) < 200:
            trace_out.append(addr)
        # simulamos: devolvemos 0 y comprobamos si la devuelve el stub
        rsp = uc.reg_read(UC_X86_REG_RSP)
        try:
            ret = struct.unpack("<Q", uc.mem_read(rsp, 8))[0]
        except UcError:
            ret = 0
        if ret and not (IMAGE_LO <= ret < IMAGE_HI):
            # el stub continua dentro de la imagen: nada que hacer
            pass
        uc.emu_stop()
        return

def hook_mem_invalid(uc, access, address, size, value, user):
    # cualquier acceso fuera de lo mapeado: lo tratamos como API/lectura
    if access in (UC_MEM_READ_UNMAPPED, UC_MEM_WRITE_UNMAPPED):
        if 0x500000000000 <= address < 0x600000000000 or True:
            try:
                uc.mem_map(address & ~0xFFF, 0x1000)
                return True
            except UcError:
                return False
    return False

uc.hook_add(UC_HOOK_CODE, hook_code, begin=IMAGE_LO, end=IMAGE_HI)

api_calls = []
def hook_api(uc, addr, size, user):
    name = tramp.get(addr)
    if name is None:
        return
    api_calls.append(name)
    if len(api_calls) <= 60:
        print("    API -> %s" % name)

uc.hook_add(UC_HOOK_CODE, hook_api, begin=MOD_BASE, end=MOD_BASE + 0x40000)

uc.hook_add(UC_HOOK_MEM_READ_UNMAPPED | UC_HOOK_MEM_WRITE_UNMAPPED, hook_mem_invalid)

print("[*] arrancando emulacion desde el entry (RVA 0x%x)..." % EP)
try:
    uc.emu_start(IB + EP, 0, count=MAX_INSN)
except UcError as e:
    rip = uc.reg_read(UC_X86_REG_RIP)
    print("[!] UcError %s en RIP=0x%x  RVA=0x%x  (insn=%d)"
          % (e, rip, rip - IB, insn_count[0]))

rip = uc.reg_read(UC_X86_REG_RIP)
print("[*] RIP final = 0x%x (RVA 0x%x)" % (rip, rip - IB))
print("[*] instrucciones emuladas: %d" % insn_count[0])
print("[*] destinos fuera de la imagen: %d unicos" % len(outside))
for a, c in outside.most_common(10):
    print("    0x%012x  x%d" % (a, c))
if rva_fixes:
    print("[*] RVAs convertidas a absolutas: %d" % len(rva_fixes))
    for addr, hx, v, f in rva_fixes[:10]:
        print("    @0x%x  %s  %x -> %x" % (addr, hx, v, f))

print()
print("[*] ultimas %d instrucciones antes del fallo:" % len(ring))
for ent in ring:
    addr, size, code = ent[0], ent[1], ent[2]
    rax, rdx, rcx, rbx, rsi, rdi, rsp = ent[3:]
    try:
        d0 = cs.disasm(code, addr)
        txt = (d0[0].mnemonic + " " + d0[0].op_str) if d0 else "(?)"
    except Exception:
        txt = "(?)"
    inside = "IMG" if IMAGE_LO <= addr < IMAGE_HI else "OUT"
    print("    %s %012x rva=%08x %-30s %-22s rax=%016x rdx=%012x rcx=%016x rbx=%012x"
          % (inside, addr, addr - IB, txt, code.hex(), rax, rdx, rcx, rbx))

# ------------------------------------------------------------ volcar
print("[*] volcando imagen emulada...")
img = bytes(uc.mem_read(IB, SIZE))
open(OUT + ".image.bin", "wb").write(img)

# buscar cadenas conocidas en la imagen emulada
import re
for needle in [b"Checking Update", b"14ddg0941cvah", b"34dbbmddg71c",
               b"update_url", b"MRGARABATO"]:
    i = img.find(needle)
    print("    %-20s %s" % (needle.decode(), ("en RVA 0x%x" % i) if i >= 0 else "NO"))