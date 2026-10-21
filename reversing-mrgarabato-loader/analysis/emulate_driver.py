#!/usr/bin/env python3
"""Emulacion de DriverEntry del driver iQVW64E.SYS con Unicorn.

Objetivo: la tabla de despacho de IOCTL NO existe como constante en el fichero.
Se construye en runtime en el BSS de .data (6 MB). La unica forma de obtener
los codigos IOCTL reales es ejecutar la inicializacion y leer la tabla ya
construida.

Esto NO carga el driver en ningun kernel: es emulacion pura de用户 x64 en
memoria de proceso, con los imports de ntoskrnl sustituidos por stubs que
devuelven punteros de un heap ficticio. No se toca ningun kernel real.

Tambien evita el problema de que la tabla se inicialice leyendo entradas de
teclado, raton o fichero: no se ejecuta codigo ajeno a la inicializacion.
"""
import struct
import sys
from unicorn import (Uc, UcError, UC_ARCH_X86, UC_MODE_64, UC_HOOK_CODE,
                     UC_HOOK_MEM_INVALID, UC_PROT_ALL)
from unicorn.x86_const import UC_X86_REG_RIP, UC_X86_REG_RSP, UC_X86_REG_RAX, \
    UC_X86_REG_RCX, UC_X86_REG_RDX, UC_X86_REG_R8, UC_X86_REG_R9, \
    UC_X86_REG_R10, UC_X86_REG_R11

PE = "c2_descargas/payload_embebido.exe"

STACK_BASE = 0x7FFFF0000000
STACK_SIZE = 0x200000
OBJ_BASE = 0x7FFFF8000000          # DRIVER_OBJECT ficticio
OBJ_SIZE = 0x1000
HEAP_BASE = 0x0000004000000000      # heap ficticio para punteros devueltos
HEAP_SIZE = 0x2000000
STUB_BASE = 0x70000000              # codigo de los stubs
STUB_SLOT = 0x10
STUB_SIZE = 0x20000

# funciones que deben devolver un puntero utilizable
RET_PTR = {
    "IoCreateDevice", "IoCreateSymbolicLink", "IoAllocateMdl",
    "MmMapLockedPagesSpecifyCache", "ExAllocatePoolWithTag",
    "ZwCreateFile", "ZwOpenFile", "IoGetDeviceObjectPointer",
    "IoRegisterDeviceInterface", "ZwCreateKey", "ZwOpenKey",
    "PsCreateSystemThread", "ZwCreateSection", "MmAllocateContiguousMemory",
}
# funciones que deben devolver 0 (STATUS_SUCCESS) y siguen con exito
RET_ZERO = {
    "DbgPrint", "IoDeleteDevice", "IoDeleteSymbolicLink", "KeInitializeEvent",
    "InitializeCriticalSectionAndSpinCount", "InitializeSListHead",
    "InitializeCriticalSectionEx", "ObReferenceObject", "ZwEnumerateValueKey",
    "ZwQueryValueKey", "IoBuildSynchronousFsdRequest", "IofCallDriver",
    "IoGetDeviceInterfaces", "ZwQuerySystemInformation", "RtlInitUnicodeString",
}


def rva2off(d, secs, r):
    for va, ptr, raw, vsz in secs:
        if va <= r < va + max(raw, vsz):
            return ptr + (r - va)
    return None


def parse_pe(path):
    d = open(path, "rb").read()
    e = struct.unpack_from("<I", d, 0x3C)[0]
    nsec = struct.unpack_from("<H", d, e + 6)[0]
    so = struct.unpack_from("<H", d, e + 20)[0]
    sox = e + 24 + so
    opt = e + 24
    imgbase = struct.unpack_from("<Q", d, opt + 24)[0]
    sizeofimg = struct.unpack_from("<I", d, opt + 56)[0]
    entry = struct.unpack_from("<I", d, opt + 16)[0]
    secs = []
    for i in range(nsec):
        o = sox + 40 * i
        va = struct.unpack_from("<I", d, o + 12)[0]
        vsz = struct.unpack_from("<I", d, o + 8)[0]
        raw = struct.unpack_from("<I", d, o + 16)[0]
        ptr = struct.unpack_from("<I", d, o + 20)[0]
        secs.append((va, ptr, raw, vsz))
    return d, e, imgbase, sizeofimg, entry, secs


def parse_imports(d, secs):
    """Devuelve {nombre_funcion: rva_de_su_slot_en_la_IAT}."""
    out = {}

    def o2r(f):
        for va, ptr, raw, _ in secs:
            if ptr <= f < ptr + raw:
                return va + (f - ptr)
        return None

    e = struct.unpack_from("<I", d, 0x3C)[0]
    dd = e + 24 + 0x78          # IMAGE_DIRECTORY_ENTRY_IMPORT (PE32+: DD en opt+0x70, indice 1)
    imp_rva = struct.unpack_from("<I", d, dd)[0]
    o = rva2off(d, secs, imp_rva)
    if o is None:
        return out
    iat = struct.unpack_from("<I", d, e + 24 + 0xD0)[0]   # DD indice 12 = IAT
    while True:
        oft = struct.unpack_from("<I", d, o)[0]
        name_rva = struct.unpack_from("<I", d, o + 12)[0]
        ft = struct.unpack_from("<I", d, o + 16)[0]
        if oft == 0 and ft == 0:
            break
        t = rva2off(d, secs, oft)
        i = 0
        while True:
            w = struct.unpack_from("<Q", d, t)[0]
            if w == 0:
                break
            if not (w >> 63):
                hn = rva2off(d, secs, w & 0x7FFFFFFF)
                nm = d[hn + 2:d.index(b"\x00", hn + 2)].decode("latin1")
                out[nm] = ft + i * 8
            t += 8
            i += 1
        o += 20
    return out


def main():
    d, e, imgbase, sizeofimg, entry, secs = parse_pe(PE)
    imports = parse_imports(d, secs)
    print("PE: ImageBase=0x%x SizeOfImage=0x%x Entry=0x%x  imports=%d"
          % (imgbase, sizeofimg, entry, len(imports)))

    uc = Uc(UC_ARCH_X86, UC_MODE_64)
    img_sz = ((sizeofimg + 0xFFF) & ~0xFFF)
    uc.mem_map(imgbase, img_sz, UC_PROT_ALL)
    # cabeceras
    uc.mem_write(imgbase, d[:0x1000])
    # secciones
    for va, ptr, raw, vsz in secs:
        if raw:
            uc.mem_write(imgbase + va, d[ptr:ptr + raw])
        if vsz > raw:                       # BSS a cero
            uc.mem_write(imgbase + va + raw, b"\x00" * (vsz - raw))

    uc.mem_map(STACK_BASE, STACK_SIZE, UC_PROT_ALL)
    uc.mem_map(OBJ_BASE, OBJ_SIZE, UC_PROT_ALL)
    uc.mem_map(HEAP_BASE, HEAP_SIZE, UC_PROT_ALL)
    uc.mem_map(STUB_BASE, STUB_SIZE, UC_PROT_ALL)

    # stub: un 'ret' por cada slot
    for i in range(STUB_SIZE // STUB_SLOT):
        uc.mem_write(STUB_BASE + i * STUB_SLOT, b"\xc3")

    # mapear cada slot de la IAT a su stub
    stub_of = {}
    n = 0
    for nm, rva in sorted(imports.items(), key=lambda x: x[1]):
        addr = STUB_BASE + n * STUB_SLOT
        uc.mem_write(imgbase + rva, struct.pack("<Q", addr))
        stub_of[addr] = nm
        n += 1

    heap_ptr = [HEAP_BASE + 0x1000]
    calls = {}

    def heap_alloc():
        p = heap_ptr[0]
        heap_ptr[0] += 0x1000
        if heap_ptr[0] >= HEAP_BASE + HEAP_SIZE:
            heap_ptr[0] = HEAP_BASE + 0x1000
        return p

    def on_code(uc_, addr, size, _):
        nm = stub_of.get(addr)
        if nm is None:
            return
        calls[nm] = calls.get(nm, 0) + 1
        rsp = uc_.reg_read(UC_X86_REG_RSP)
        ret = struct.unpack("<Q", uc_.mem_read(rsp, 8))[0]
        if nm in RET_PTR:
            rax = heap_alloc()
        elif nm in RET_ZERO:
            rax = 0
        else:
            rax = 0
        uc_.reg_write(UC_X86_REG_RAX, rax)
        uc_.reg_write(UC_X86_REG_RSP, rsp + 8)
        uc_.reg_write(UC_X86_REG_RIP, ret)

    def on_invalid(uc_, access, addr, size, value, _):
        # lecturas fuera de rango -> devolver 0 sin romper la ejecucion
        try:
            uc_.mem_map(addr & ~0xFFF, 0x1000, UC_PROT_ALL)
            return True
        except UcError:
            return False

    uc.hook_add(UC_HOOK_CODE, on_code, begin=STUB_BASE, end=STUB_BASE + STUB_SIZE)
    uc.hook_add(UC_HOOK_MEM_INVALID, on_invalid)

    # preparar la llamada a DriverEntry
    sp = STACK_BASE + STACK_SIZE - 0x2000
    uc.reg_write(UC_X86_REG_RSP, sp)
    uc.reg_write(UC_X86_REG_RCX, OBJ_BASE)        # DRIVER_OBJECT*
    uc.reg_write(UC_X86_REG_RDX, 0)               # RegistryPath
    uc.reg_write(UC_X86_REG_RAX, imgbase + entry)

    print("ejecutando DriverEntry (0x%x) ..." % (imgbase + entry))
    LIMIT = 4_000_000
    try:
        uc.emu_start(imgbase + entry, 0, count=LIMIT)
        print("se detuvo en RIP=0x%x" % uc.reg_read(UC_X86_REG_RIP))
    except UcError as ex:
        print("UcError tras %s" % ex)

    print("\nllamadas a imports durante la inicializacion:")
    for nm, c in sorted(calls.items(), key=lambda x: -x[1]):
        print("   %-34s x%d" % (nm, c))

    # volcar los objetos que DriverEntry dejo en el DRIVER_OBJECT
    obj = bytes(uc.mem_read(OBJ_BASE, 0x100))
    print("\nDRIVER_OBJECT tras DriverEntry:")
    for off, name in ((0x68, "DriverUnload"), (0x70, "MajorFunction[0]  CREATE"),
                      (0x78, "MajorFunction[1]  CREATE_NAMED"),
                      (0x80, "MajorFunction[2]  CLOSE"),
                      (0x88, "MajorFunction[3]  READ"),
                      (0x90, "MajorFunction[4]  WRITE"),
                      (0x98, "MajorFunction[5]  QUERY_INFORMATION"),
                      (0xE0, "MajorFunction[11] DEVICE_CONTROL"),
                      (0xE8, "MajorFunction[12]  DEVICE_CLEANUP")):
        v = struct.unpack_from("<Q", obj, off)[0]
        r = v - imgbase if imgbase <= v < imgbase + sizeofimg else None
        tag = ""
        if r is not None and 0 < r < sizeofimg:
            tag = "  -> RVA 0x%05x" % r
        print("   +0x%02x %-32s = 0x%016x%s" % (off, name, v, tag))

    # buscar la tabla de IOCTL en el BSS
    print("\nbuscando tabla de IOCTL en el BSS (entradas de stride 0x40, handler en +0x38)...")
    lo = imgbase + 0x7000
    hi = imgbase + 0x5D0000
    blob = bytes(uc.mem_read(lo, hi - lo))
    hits = []
    for i in range(0, len(blob) - 0x40, 4):
        code = struct.unpack_from("<I", blob, i)[0]
        if (code >> 16) != 0x9B0C:
            continue
        h = struct.unpack_from("<Q", blob, i + 0x38)[0]
        r = h - imgbase
        if 0x1000 <= r < 0x6000:
            hits.append((lo - imgbase + i, code, r))
    seen = set()
    print("\n  %-10s %-12s %-10s %-12s %-9s %s" % ("RVA tabla", "IOCTL", "DeviceType", "Function", "Method", "handler RVA"))
    for rva, code, h in hits:
        key = (code, h)
        if key in seen:
            continue
        seen.add(key)
        print("  0x%08x  0x%08X   0x%04X     0x%03X       %-9d 0x%04x"
              % (rva, code, code >> 16, (code >> 2) & 0xFFF, code & 3, h))
    if not hits:
        print("  (ninguna entrada con DeviceType 0x9B0C encontrada en el BSS)")

    # volcar el BSS entero para analisis posterior
    open("emu_bss.bin", "wb").write(blob)
    print("\nBSS volcado -> emu_bss.bin (%d B)" % len(blob))


if __name__ == "__main__":
    main()