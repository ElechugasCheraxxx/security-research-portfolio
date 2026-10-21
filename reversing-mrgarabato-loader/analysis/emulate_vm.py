#!/usr/bin/env python3
"""
emulate_vm.py -- emulador x86-64 (unicorn) para el binario MrGarabato.

Objetivo: ejecutar el binario en emulacion, descubrir a donde salta el
EntryPoint real y trazar el "dispatch" del interprete/protector.

Uso:
    python3 emulate_vm.py probe EP            # arranca en el EP y sigue el flujo
    python3 emulate_vm.py trace 0xADDR N      # traza N pasos desde una direccion
    python3 emulate_vm.py full                # mapea APIs y corre mas lejos

"""
import sys, os, struct, collections, argparse

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)

# unicorn 2.x importa pkg_resources (que setuptools>=84 ya no instala).
# Si no esta, se usa la copia vendorizada de pip.
try:
    import pkg_resources  # noqa: F401
except ModuleNotFoundError:  # pragma: no cover
    import glob
    for _c in glob.glob("/usr/lib/python3*/site-packages/pip/_vendor"):
        sys.path.append(_c)

from unicorn import *
from unicorn.x86_const import *
from capstone import *

BASE   = 0x140000000
IMAGE  = os.path.join(HERE, "mem_bypass.bin")
SIZE_OF_IMAGE = 0xF94000

# regiones de la imagen (offset == RVA)
SEC = {
    '.text':  (0x1000,   0x162DC),
    '.rdata': (0x18000,  0x7AFC),
    '.data':  (0x20000,  0x1188),
    '.pdata': (0x22000,  0xEE8),
    '.7f':    (0x23000,  0x7F7D93),
    '.zzc':   (0x81B000, 0xE00),
    '.3q-':   (0x81C000, 0x76E8A4),
    '.rsrc':  (0xF8B000, 0x8E48),
}
# las dos mitades de .3q- segun el analisis previo (NO asumir: se recalcula)
M_DENSE_LO, M_DENSE_HI = 0x81C000, 0xE3C000     # entropia ~7.99  (cifrado)
M_CODE_LO,  M_CODE_HI  = 0xE3C000, 0xF8A8A4     # entropia ~7.0   (codigo real)

STACK_TOP  = 0x0007FFF0000000
STACK_SIZE = 0x20000
TEB_ADDR   = 0x0007FF7000000
PEB_ADDR   = 0x0007FF7001000
HEAP_ADDR  = 0x0000050000000
HEAP_SIZE  = 0x200000
STUB_BASE  = 0x0007700000000          # paginas de stub para APIs
STUB_SIZE  = 0x10000
GDT_ADDR   = 0x0007FF6000000

md = Cs(CS_ARCH_X86, CS_MODE_64)
md.detail = True


def region(rva):
    for n, (a, s) in SEC.items():
        if a <= rva < a + s:
            return n
    return "?"


def half(rva):
    if M_DENSE_LO <= rva < M_DENSE_HI:
        return "DENSE(7.99)"
    if M_CODE_LO <= rva < M_CODE_HI:
        return "CODE(7.0)"
    return ""


# --------------------------------------------------------------------------
# stubs de API: cada API tiene una direccion unica dentro de STUB_BASE
# --------------------------------------------------------------------------
class ApiBook:
    def __init__(self):
        self.by_addr = {}
        self.n = 0
        self.calls = []
        self.unknown = collections.Counter()

    def alloc(self, name):
        a = STUB_BASE + self.n * 0x10
        self.n += 1
        self.by_addr[a] = name
        return a

    def get(self, addr):
        return self.by_addr.get(addr)


# APIs conocidas (resueltas en el rango tipico de un Windows x64 emulado)
KNOWN_APIS = [
    # ntdll
    "NtQueryInformationProcess", "NtQuerySystemInformation", "NtSetInformationThread",
    "NtOpenFile", "NtCreateSection", "NtMapViewOfSection", "NtUnmapViewOfSection",
    "NtClose", "NtProtectVirtualMemory", "NtRaiseHardError", "NtQueryVirtualMemory",
    "RtlUnwindEx", "RtlGetVersion", "RtlInitUnicodeString", "RtlAdjustPrivilege",
    "NtAllocateVirtualMemory", "NtFreeVirtualMemory", "NtReadVirtualMemory",
    "NtWriteVirtualMemory", "NtCreateThreadEx", "NtResumeThread", "NtDelayExecution",
    "NtQueryObject", "NtDeviceIoControlFile", "NtCreateFile", "NtQueryAttributesFile",
    "NtGetContextThread", "NtSetContextThread", "NtQueueApcThread",
    # kernel32
    "LocalAlloc", "LocalFree", "GlobalAlloc", "GlobalFree", "HeapAlloc", "HeapFree",
    "GetModuleFileNameW", "ExitProcess", "LoadLibraryA", "LoadLibraryW",
    "GetModuleHandleA", "GetModuleHandleW", "GetProcAddress", "VirtualAlloc",
    "VirtualProtect", "VirtualFree", "CreateFileW", "CreateFileA", "ReadFile",
    "WriteFile", "CloseHandle", "GetLastError", "SetLastError", "GetCurrentProcess",
    "GetCurrentThread", "GetCurrentProcessId", "GetCurrentThreadId",
    "GetTickCount", "QueryPerformanceCounter", "Sleep", "CreateThread",
    "WaitForSingleObject", "SleepEx", "TlsAlloc", "TlsGetValue", "TlsSetValue",
    "IsDebuggerPresent", "CheckRemoteDebuggerPresent", "OutputDebugStringA",
    "CreateToolhelp32Snapshot", "Process32First", "Process32Next",
    "Module32First", "Module32Next", "GetCurrentDirectoryA", "GetTempPathA",
    "MultiByteToWideChar", "WideCharToMultiByte", "lstrlenA", "lstrcpyA",
    "CreateFileMappingA", "MapViewOfFile", "UnmapViewOfFile", "FlushInstructionCache",
    "GetSystemInfo", "GetNativeSystemInfo", "GetVersionExW", "RtlUnwind",
    # user32
    "MessageBoxA", "MessageBoxW", "FindWindowA", "FindWindowW",
    # advapi32/shell32
    "RegOpenKeyExW", "RegQueryValueExW", "RegSetValueExW", "RegCloseKey",
    "ShellExecuteA", "ShellExecuteW",
]

# valores de retorno plausibles
RET_VAL = {
    "IsDebuggerPresent": 0,
    "CheckRemoteDebuggerPresent": 1,
    "GetCurrentProcess": 0xFFFFFFFFFFFFFFFF,
    "GetCurrentThread": 0xFFFFFFFFFFFFFFFE,
    "GetCurrentProcessId": 0x1234,
    "GetCurrentThreadId": 0x1235,
    "GetTickCount": 0x11223344,
    "GetLastError": 0,
    "NtQueryInformationProcess": 0,
    "NtQuerySystemInformation": 0,
    "NtSetInformationThread": 0,
    "NtClose": 0,
    "NtRaiseHardError": 0,
}


class VMEmu:
    def __init__(self, verbose=False, maxsteps=2_000_000):
        self.img = open(IMAGE, "rb").read()
        self.uc = Uc(UC_ARCH_X86, UC_MODE_64)
        self.api = ApiBook()
        self.verbose = verbose
        self.maxsteps = maxsteps
        self.rip_hist = collections.Counter()
        self.jmps = []             # transiciones lejanas registradas
        self.log = []
        self.unmapped_log = []
        self.mod_pages = set()
        self._setup()

    # ---------------- mapeo ----------------
    def _setup(self):
        uc = self.uc
        # imagen (alineada a 4 KB)
        sz = (SIZE_OF_IMAGE + 0xFFF) & ~0xFFF
        uc.mem_map(BASE, sz)
        uc.mem_write(BASE, self.img[:SIZE_OF_IMAGE])
        # stack
        uc.mem_map(STACK_TOP - STACK_SIZE, STACK_SIZE)
        # heap / zona de asignaciones
        uc.mem_map(HEAP_ADDR, HEAP_SIZE)
        # stubs
        uc.mem_map(STUB_BASE, STUB_SIZE)
        # TEB/PEB
        uc.mem_map(TEB_ADDR, 0x10000)
        # GDT
        uc.mem_map(GDT_ADDR, 0x1000)

        # stubs 'ret' para toda la pagina por defecto
        uc.mem_write(STUB_BASE, b"\xc3" * STUB_SIZE)

        #登记表 de APIs conocidas -> direcciones unicas
        for name in KNOWN_APIS:
            self.api.alloc(name)

        # PE ->adir de cada API
        for k, name in enumerate(KNOWN_APIS):
            self.api.by_addr[STUB_BASE + k * 0x10] = name

        # inicializa registros (Windows x64)
        uc.reg_write(UC_X86_REG_RSP, STACK_TOP - 0x100)
        uc.reg_write(UC_X86_REG_RBP, STACK_TOP - 0x100)
        uc.reg_write(UC_X86_REG_RCX, 0)
        uc.reg_write(UC_X86_REG_RDX, STACK_TOP - 0x100)   # PEB en rcx cuando hay marco
        uc.reg_write(UC_X86_REG_RAX, STACK_TOP - 0x28)  # retorno al stub de salida
        uc.reg_write(UC_X86_REG_EFLAGS, 0x202)

        # TEB/PEB minimos
        teb = bytearray(0x100)
        struct.pack_into("<Q", teb, 0x30, PEB_ADDR)       # TEB.ProcessEnvironmentBlock
        struct.pack_into("<Q", teb, 0x18, TEB_ADDR)       # TEB.Self
        struct.pack_into("<Q", teb, 0x00, 0)              # TEB.ExceptionList
        uc.mem_write(TEB_ADDR, bytes(teb))
        peb = bytearray(0x100)
        struct.pack_into("<Q", peb, 0x10, 0x1234)         # PEB.ImageBaseAddress
        uc.mem_write(PEB_ADDR, bytes(peb))

        # GDT con entrada FS
        self._setup_gdt()

        uc.hook_add(UC_HOOK_CODE, self._hook_code)
        uc.hook_add(UC_HOOK_MEM_UNMAPPED, self._hook_unmapped)
        uc.hook_add(UC_HOOK_MEM_INVALID, self._hook_unmapped)

    def _setup_gdt(self):
        uc = self.uc
        def ent(base, limit, access, flags):
            d = bytearray(8)
            d[0] = limit & 0xFF
            d[1] = (limit >> 8) & 0xFF
            d[2] = base & 0xFF
            d[3] = (base >> 8) & 0xFF
            d[4] = (base >> 16) & 0xFF
            d[5] = access
            d[6] = ((limit >> 16) & 0x0F) | (flags << 4)
            d[7] = (base >> 24) & 0xFF
            return bytes(d)
        gdt = bytearray(0x100)
        gdt[0:8] = b"\x00" * 8
        gdt[8:16] = ent(0, 0xFFFFF, 0x9A, 0xC)     # selector 0x08 code64
        gdt[16:24] = ent(0, 0xFFFFF, 0x92, 0xC)    # selector 0x10 data
        gdt[24:32] = ent(TEB_ADDR, 0xFFF, 0xF2, 0x4)   # selector 0x18 -> TEB (FS)
        uc.mem_write(GDT_ADDR, bytes(gdt))
        uc.reg_write(UC_X86_REG_GDTR, (0, GDT_ADDR, 8 * 8 - 1, 0))
        uc.reg_write(UC_X86_REG_CS, 0x08)
        uc.reg_write(UC_X86_REG_DS, 0x10)
        uc.reg_write(UC_X86_REG_ES, 0x10)
        uc.reg_write(UC_X86_REG_SS, 0x10)
        uc.reg_write(UC_X86_REG_FS, 0x18)
        uc.reg_write(UC_X86_REG_GS, 0x10)

    # ---------------- hooks ----------------
    def _hook_code(self, uc, addr, size, _):
        self.steps += 1
        self.rip_hist[addr] += 1
        if STUB_BASE <= addr < STUB_BASE + STUB_SIZE:
            self._do_api(uc, addr)
        elif addr in self.mod_pages:
            # entrada en un "modulo" simulado: tratar como API desconocida
            self._do_api(uc, addr)

    def _do_api(self, uc, addr):
        name = self.api.get(addr)
        if name is None:
            name = "mod+0x%x" % (addr & 0xFFF)
            self.api.unknown[addr] += 1
        # argumentos: RCX,RDX,R8,R9  (abi Microsoft x64)
        args = [uc.reg_read(r) for r in
                (UC_X86_REG_RCX, UC_X86_REG_RDX, UC_X86_REG_R8, UC_X86_REG_R9)]
        rv = RET_VAL.get(name, 0x1000)
        if name in ("VirtualAlloc", "NtAllocateVirtualMemory", "LocalAlloc",
                    "GlobalAlloc", "HeapAlloc", "CreateFileMappingA"):
            # reserva memoria real en HEAP para que no explote
            try:
                addr_alloc = HEAP_ADDR + (self.heap_off & ~0xFFF)
                self.heap_off += 0x1000
                if rv > 0x1000:
                    size = min(rv, 0x100000)
                    size = (size + 0xFFF) & ~0xFFF
                    try:
                        uc.mem_map(addr_alloc, size)
                    except UcError:
                        pass
                rv = addr_alloc
            except Exception:
                rv = HEAP_ADDR
        if name in ("GetModuleHandleA", "GetModuleHandleW", "LoadLibraryA",
                    "LoadLibraryW", "GetModuleFileNameW"):
            rv = BASE
        if name == "GetProcAddress":
            rv = STUB_BASE + 0x1000     # stub generico
        rsp = uc.reg_read(UC_X86_REG_RSP)
        ret = struct.unpack("<Q", bytes(uc.mem_read(rsp, 8)))[0]
        # argumentos: RCX,RDX,R8,R9  (abi Microsoft x64)
        args = [uc.reg_read(r) for r in
                (UC_X86_REG_RCX, UC_X86_REG_RDX, UC_X86_REG_R8, UC_X86_REG_R9)]
        self.calls_log.append((name, ret, args, rv))
        uc.reg_write(UC_X86_REG_RAX, rv & 0xFFFFFFFFFFFFFFFF)
        uc.reg_write(UC_X86_REG_RSP, rsp + 8)
        uc.reg_write(UC_X86_REG_RIP, ret)

    def _hook_unmapped(self, uc, access, addr, size, value, _):
        """Auto-mapea cualquier pagina no mapeada (asi el emulador no se muere).
        Si la pagina cae en un 'modulo' (base de DLL) se rellena con stubs ret."""
        page = addr & ~0xFFF
        self.unmapped_log.append((uc.reg_read(UC_X86_REG_RIP), access, addr))
        if len(self.unmapped_log) < 4000:
            try:
                uc.mem_map(page, 0x1000)
            except UcError:
                return False
            # si parece una pagina de modulo (base 0x6fffff.... / 0x7ff....),pon stubs
            base = page >> 32
            if base in (0x6fffff, 0x7fffff, 0x7ffe, 0x7ffd, 0x00007ff):
                uc.mem_write(page, b"\xc3" * 0x1000)
                self.mod_pages.add(page)
            return True
        return False

    # ---------------- ejecucion ----------------
    def run(self, start, count=100000, until=None, seq=False):
        self.steps = 0
        self.calls_log = []
        self.heap_off = 0
        self.seq = []
        if seq:
            self.uc.hook_add(UC_HOOK_CODE, self._hook_seq)
        self.uc.reg_write(UC_X86_REG_RIP, start)
        err = None
        try:
            self.uc.emu_start(start, until or 0, count=count)
        except UcError as e:
            err = f"{e}  (rip=0x{self.uc.reg_read(UC_X86_REG_RIP):x})"
        return err

    def _hook_seq(self, uc, addr, size, _):
        self.seq.append(addr)

    @staticmethod
    def transitions(seq):
        """Colapsa la secuencia a transiciones (solo cuando cambia RIP)."""
        out = []
        prev = None
        for a in seq:
            if a != prev:
                out.append(a)
                prev = a
        return out

    def loops(self, seq, maxlen=4000):
        """Detecta bucles: busca el prefijo periodico mas largo de la traza."""
        t = self.transitions(seq)
        res = []
        seen = {}
        for i, a in enumerate(t):
            if a in seen:
                j = seen[a]
                res.append((j, i, t[j:i]))
                if len(res) > 60:
                    break
            else:
                seen[a] = i
        return res, t


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("cmd")
    ap.add_argument("args", nargs="*")
    a = ap.parse_args()

    emu = VMEmu()
    if a.cmd == "probe":
        ep = int(a.args[0], 16) if a.args else 0x960917
        n = int(a.args[1], 16) if len(a.args) > 1 else 20000
        print(f"[*] arrancando en 0x{ep:x} durante {n} pasos")
        err = emu.run(BASE + ep, count=n)
        rip = emu.uc.reg_read(UC_X86_REG_RIP)
        print(f"[*] fin: {err}   RIP=0x{rip:x}  pasos={emu.steps}")
        print(f"[*] APIs llamadas: {len(emu.calls_log)}")
        for c in emu.calls_log[:40]:
            print("    ", c[0], "ret=%x" % c[1], [hex(x) for x in c[2]])
        print("\n[*] top 30 RIP:")
        for addr, cnt in emu.rip_hist.most_common(30):
            r = addr - BASE
            print("   0x%012x [%-8s %-11s] x%d" % (addr, region(r) if BASE <= addr < BASE + SIZE_OF_IMAGE else "ext",
                                                  half(r), cnt))
    elif a.cmd == "trace":
        start = int(a.args[0], 16)
        n = int(a.args[1]) if len(a.args) > 1 else 5000
        err = emu.run(start, count=n)
        print(f"[*] {err}")
        for addr, cnt in emu.rip_hist.most_common(40):
            r = addr - BASE
            print("   0x%012x [%-8s %-11s] x%d" % (addr, region(r) if BASE <= addr < BASE + SIZE_OF_IMAGE else "ext",
                                                  half(r), cnt))
    else:
        ap.print_help()


if __name__ == "__main__":
    main()