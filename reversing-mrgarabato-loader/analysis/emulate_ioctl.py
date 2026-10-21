#!/usr/bin/env python3
"""Fase 2 de la emulacion: construir el contexto del dispositivo y conducir
los IOCTL de iQVW64E.SYS.

Lo que quedo claro en la fase 1 (emulate_driver.py):
  MajorFunction[11] = IRP_MJ_DEVICE_CONTROL -> RVA 0x1150
  Ese handler NO lee el IoControlCode del IRP, sino del DeviceExtension:
      mov rax,[rdx+0xB8]   ; DeviceObject->DeviceExtension
      mov edx,[rax+0x18]   ; extension->IoControlCode
      mov rcx,[rax+0x20]   ; extension->contexto (debe ser != NULL)

Por tanto no hace falta fabricar un IRP completo: basta un DeviceObject cuyo
DeviceExtension tenga el IOCTL en +0x18 y un contexto valido en +0x20.

Se ejecuta primero IRP_MJ_CREATE (RVA 0x1090), que es donde el driver
construye el contexto del dispositivo y la tabla de despacho. Despues se
dispara cada uno de los cuatro IOCTL y se registra a que funciones llega.
"""
import struct
import sys
from unicorn import (Uc, UcError, UC_ARCH_X86, UC_MODE_64, UC_HOOK_CODE,
                     UC_HOOK_MEM_INVALID, UC_PROT_ALL)
from unicorn.x86_const import (UC_X86_REG_RIP, UC_X86_REG_RSP, UC_X86_REG_RAX,
                               UC_X86_REG_RCX, UC_X86_REG_RDX, UC_X86_REG_R8,
                               UC_X86_REG_R9)

PE = "c2_descargas/payload_embebido.exe"
STACK_BASE, STACK_SIZE = 0x7FFFF0000000, 0x200000
OBJ_BASE, OBJ_SIZE = 0x7FFFF8000000, 0x1000
HEAP_BASE, HEAP_SIZE = 0x0000004000000000, 0x4000000
STUB_BASE, STUB_SLOT, STUB_SIZE = 0x70000000, 0x10, 0x20000
DEVOBJ_BASE, DEVOBJ_SIZE = 0x7FFFF9000000, 0x1000
DEVEXT_BASE, DEVEXT_SIZE = 0x7FFFFA000000, 0x4000
IRP_BASE, IRP_SIZE = 0x7FFFFB000000, 0x1000

IOCTLS = {0x80862007: "CREATE?/handler 0x13C0",
          0x8086200B: "handler 0x1A60",
          0x8086200F: "handler 0x1330",
          0x80862013: "handler 0x3FA0"}

RET_PTR = {"IoCreateDevice", "IoCreateSymbolicLink", "IoAllocateMdl",
           "MmMapLockedPagesSpecifyCache", "ExAllocatePoolWithTag",
           "ZwCreateFile", "ZwOpenFile", "IoGetDeviceObjectPointer",
           "IoRegisterDeviceInterface", "ZwCreateKey", "ZwOpenKey",
           "PsCreateSystemThread", "ZwCreateSection", "MmAllocateContiguousMemory",
           "ObReferenceObject"}


def rva2off(secs, r):
    for va, ptr, raw, vsz in secs:
        if va <= r < va + max(raw, vsz):
            return ptr + (r - va)
    return None


def parse(path):
    d = open(path, "rb").read()
    e = struct.unpack_from("<I", d, 0x3C)[0]
    nsec = struct.unpack_from("<H", d, e + 6)[0]
    sox = e + 24 + struct.unpack_from("<H", d, e + 20)[0]
    opt = e + 24
    imgbase = struct.unpack_from("<Q", d, opt + 24)[0]
    sizeofimg = struct.unpack_from("<I", d, opt + 56)[0]
    entry = struct.unpack_from("<I", d, opt + 16)[0]
    secs = []
    for i in range(nsec):
        o = sox + 40 * i
        secs.append((struct.unpack_from("<I", d, o + 12)[0],
                     struct.unpack_from("<I", d, o + 20)[0],
                     struct.unpack_from("<I", d, o + 16)[0],
                     struct.unpack_from("<I", d, o + 8)[0]))
    imp = struct.unpack_from("<I", d, opt + 0x78)[0]
    imports = {}
    o = rva2off(secs, imp)
    while o is not None:
        oft = struct.unpack_from("<I", d, o)[0]
        ft = struct.unpack_from("<I", d, o + 16)[0]
        if oft == 0 and ft == 0:
            break
        t = rva2off(secs, oft)
        i = 0
        while True:
            w = struct.unpack_from("<Q", d, t)[0]
            if w == 0:
                break
            if not (w >> 63):
                hn = rva2off(secs, w & 0x7FFFFFFF)
                imports[d[hn + 2:d.index(b"\x00", hn + 2)].decode("latin1")] = ft + i * 8
            t += 8
            i += 1
        o += 20
    return d, imgbase, sizeofimg, entry, secs, imports


class Emu:
    def __init__(self):
        self.d, self.imgbase, self.sizeofimg, self.entry, self.secs, self.imports = parse(PE)
        self.uc = Uc(UC_ARCH_X86, UC_MODE_64)
        u = self.uc
        u.mem_map(self.imgbase, (self.sizeofimg + 0xFFF) & ~0xFFF, UC_PROT_ALL)
        u.mem_write(self.imgbase, self.d[:0x1000])
        for va, ptr, raw, vsz in self.secs:
            if raw:
                u.mem_write(self.imgbase + va, self.d[ptr:ptr + raw])
            if vsz > raw:
                u.mem_write(self.imgbase + va + raw, b"\x00" * (vsz - raw))
        u.mem_map(STACK_BASE, STACK_SIZE, UC_PROT_ALL)
        u.mem_map(OBJ_BASE, OBJ_SIZE, UC_PROT_ALL)
        u.mem_map(HEAP_BASE, HEAP_SIZE, UC_PROT_ALL)
        u.mem_map(STUB_BASE, STUB_SIZE, UC_PROT_ALL)
        u.mem_map(DEVOBJ_BASE, DEVOBJ_SIZE, UC_PROT_ALL)
        u.mem_map(DEVEXT_BASE, DEVEXT_SIZE, UC_PROT_ALL)
        u.mem_map(IRP_BASE, IRP_SIZE, UC_PROT_ALL)
        for i in range(STUB_SIZE // STUB_SLOT):
            u.mem_write(STUB_BASE + i * STUB_SLOT, b"\xc3")
        self.stub_of = {}
        for n, (nm, rva) in enumerate(sorted(self.imports.items(), key=lambda x: x[1])):
            a = STUB_BASE + n * STUB_SLOT
            u.mem_write(self.imgbase + rva, struct.pack("<Q", a))
            self.stub_of[a] = nm
        self.heap = [HEAP_BASE + 0x2000]
        self.calls = {}
        self.trace = []
        u.hook_add(UC_HOOK_CODE, self.on_code, begin=STUB_BASE, end=STUB_BASE + STUB_SIZE)
        u.hook_add(UC_HOOK_MEM_INVALID, self.on_invalid)

    def on_invalid(self, uc_, access, addr, size, value, _):
        try:
            uc_.mem_map(addr & ~0xFFF, 0x1000, UC_PROT_ALL)
            return True
        except UcError:
            return False

    def on_code(self, uc_, addr, size, _):
        nm = self.stub_of.get(addr)
        if nm is None:
            return
        self.calls[nm] = self.calls.get(nm, 0) + 1
        rsp = uc_.reg_read(UC_X86_REG_RSP)
        ret = struct.unpack("<Q", uc_.mem_read(rsp, 8))[0]
        rax = 0
        if nm in RET_PTR:
            rax = self.heap[0]
            self.heap[0] += 0x1000
            if self.heap[0] >= HEAP_BASE + HEAP_SIZE:
                self.heap[0] = HEAP_BASE + 0x2000
        uc_.reg_write(UC_X86_REG_RAX, rax)
        uc_.reg_write(UC_X86_REG_RSP, rsp + 8)
        uc_.reg_write(UC_X86_REG_RIP, ret)

    def run_at(self, rva, rcx, rdx=0, r8=0, count=3_000_000, trace=False):
        u = self.uc
        sp = STACK_BASE + STACK_SIZE - 0x4000
        u.reg_write(UC_X86_REG_RSP, sp)
        u.reg_write(UC_X86_REG_RCX, rcx)
        u.reg_write(UC_X86_REG_RDX, rdx)
        u.reg_write(UC_X86_REG_R8, r8)
        u.reg_write(UC_X86_REG_RAX, self.imgbase + rva)
        self.trace = []
        if trace:
            def tr(uc_, addr, size, _):
                if STUB_BASE <= addr < STUB_BASE + STUB_SIZE:
                    self.trace.append(("IMPORT", self.stub_of.get(addr, "?")))
                else:
                    self.trace.append(("CODE", addr - self.imgbase))
            h = u.hook_add(UC_HOOK_CODE, tr)
            try:
                u.emu_start(self.imgbase + rva, 0, count=count)
            finally:
                u.hook_del(h)
        else:
            try:
                u.emu_start(self.imgbase + rva, 0, count=count)
            except UcError as ex:
                pass
        return u.reg_read(UC_X86_REG_RAX)

    def read(self, addr, n):
        return bytes(self.uc.mem_read(addr, n))


def main():
    e = Emu()
    print("fase 2: construir contexto y conducir IOCTL\n")

    # 1) DriverEntry
    e.run_at(e.entry, OBJ_BASE)
    obj = e.read(OBJ_BASE, 0x100)
    def mfo(off):
        v = struct.unpack_from("<Q", obj, off)[0]
        return v - e.imgbase if e.imgbase <= v < e.imgbase + e.sizeofimg else None
    print("handlers registrados en el DRIVER_OBJECT:")
    for off, nm in ((0x68, "DriverUnload"), (0x70, "CREATE"),
                    (0x80, "CLOSE"), (0xE0, "DEVICE_CONTROL")):
        r = mfo(off)
        print("   %-16s RVA 0x%s" % (nm, ("%04x" % r) if r else "?"))

    # 2) IRP_MJ_CREATE: donde se inicializa el contexto del dispositivo
    print("\n--- ejecutando IRP_MJ_CREATE (RVA 0x%04x) ---" % mfo(0x70))
    before = e.calls.get("IoCreateDevice", 0)
    e.run_at(mfo(0x70), DEVOBJ_BASE, IRP_BASE)
    print("   IoCreateDevice llamadas: %d -> %d" % (before, e.calls.get("IoCreateDevice", 0)))

    # localizar el DeviceObject real devuelto por IoCreateDevice: el stub lo
    # entrega desde el heap ficticio. Tomamos el ultimo asignado.
    dev = None
    for cand in sorted({HEAP_BASE + 0x2000 + i * 0x1000 for i in range(8)}, reverse=True):
        if e.calls.get("IoCreateDevice", 0) and cand <= HEAP_BASE + 0x2000 + (e.calls["IoCreateDevice"] - 1) * 0x1000:
            dev = cand
            break
    dev = dev or DEVOBJ_BASE
    print("   DeviceObject del driver: 0x%x" % dev)

    # Enlazar DeviceObject -> DeviceExtension y rellenar el contexto que el
    # handler de DEVICE_CONTROL lee: +0x18 = IoControlCode, +0x20 = contexto.
    ext = DEVEXT_BASE
    ctx = HEAP_BASE + 0x300000
    e.uc.mem_write(dev + 0xB8, struct.pack("<Q", ext))
    # el handler hace mov rax,[rdx+0xB8] con rdx=IRP: el IRP guarda aqui
    # un puntero a la estructura de contexto con el IoControlCode en +0x18
    e.uc.mem_write(IRP_BASE + 0xB8, struct.pack("<Q", ext))
    e.uc.mem_write(ext + 0x18, struct.pack("<I", 0))
    e.uc.mem_write(ext + 0x20, struct.pack("<Q", ctx))
    e.uc.mem_write(ext + 0x28, struct.pack("<Q", dev))
    e.uc.mem_write(ext + 0x30, struct.pack("<Q", IRP_BASE))
    # verificar lectura
    rb_ext = struct.unpack("<Q", e.read(IRP_BASE + 0xB8, 8))[0]
    rb_ctx = struct.unpack("<Q", e.read(rb_ext + 0x20, 8))[0] if rb_ext else 0
    print("   verificacion: IRP+0xB8 = 0x%x  -> ext+0x18 = 0x%08X  ext+0x20 = 0x%x"
          % (rb_ext, struct.unpack("<I", e.read(rb_ext + 0x18, 4))[0], rb_ctx))

    # 2b) recorrer los FunctionId (1..7) del IOCTL 0x8086200B: su handler
    #     (RVA 0x1a60) lee el FunctionId del contexto en [rcx] y salta por una
    #     tabla de 7 casos. Con FunctionId=0 cae en la rama por defecto.
    print("\n--- IOCTL 0x8086200B: recorrer FunctionId 1..7 ---")
    PRIM = {0x2030, 0x258d, 0x2a0f, 0x38b0, 0x3980, 0x3a00, 0x3b20, 0x354b}
    for fid in range(1, 8):
        e.uc.mem_write(ext + 0x18, struct.pack("<I", 0x8086200B))
        e.uc.mem_write(ctx, struct.pack("<I", fid))
        before = dict(e.calls)
        e.run_at(mfo(0xE0), dev, IRP_BASE, trace=True)
        codes = sorted({a for k, a in e.trace if k == "CODE"})
        delta = {k: v - before.get(k, 0) for k, v in e.calls.items()
                 if v > before.get(k, 0) and k not in ("IofCompleteRequest", "DbgPrint")}
        hit = PRIM & set(codes)
        print("\n   FunctionId %d" % fid)
        print("      imports: %s" % (", ".join(sorted(delta)) or "ninguno"))
        print("      recorre: %s" % (" -> ".join("0x%x" % c for c in codes[26:50]) or "(solo prologo)"))
        print("      >>> toca el subsistema NAL/mapeo: %s"
              % (", ".join("0x%04x" % h for h in sorted(hit)) if hit else "no"))

    # 3) disparar el resto de IOCTL
    print("\n--- resto de IOCTL (contexto limpio) ---")
    for code, note in sorted(IOCTLS.items()):
        e.uc.mem_write(ext + 0x18, struct.pack("<I", code))
        before = dict(e.calls)
        e.run_at(mfo(0xE0), DEVOBJ_BASE, IRP_BASE, trace=True)
        delta = {k: v - before.get(k, 0) for k, v in e.calls.items() if v > before.get(k, 0)}
        imports = [k for k in delta if k not in ("DbgPrint",)]
        codes = sorted({a for k, a in e.trace if k == "CODE"})
        print("\n   IOCTL 0x%08X  (%s)" % (code, note))
        print("      imports invocados: %s" % (", ".join(sorted(imports)) or "ninguno"))
        print("      funciones .text recorridas: %s"
              % (" -> ".join("0x%x" % c for c in codes[:60]) or "ninguna"))
        prim = [c for c in codes if c in (0x2030, 0x258d)]
        print("      >>> ALCANZA LA PRIMITIVA DE MAPEO: %s"
              % ("SI, en 0x%04x" % prim[0] if prim else "no"))


def self_heap_end(e):
    return e.heap[0] + 0x100000


if __name__ == "__main__":
    main()