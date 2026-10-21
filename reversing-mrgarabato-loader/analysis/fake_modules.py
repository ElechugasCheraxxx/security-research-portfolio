#!/usr/bin/env python3
"""Construye una lista de modulos PEB sintetica con tabla de exports real.

El empaquetador resuelve APIs recorriendo
    PEB -> Ldr -> InMemoryOrderModuleList
y comparando el hash de cada nombre de export. Con la lista vacia no
encuentra nada y 'call rax' salta a basura.

Aqui se generan modulos PE minimos pero estructuralmente validos, con su
IMAGE_EXPORT_DIRECTORY, y se encadenan en la lista.
"""
import struct

#偏移 de las estructuras en x64
OFF_LDR              = 0x18   # PEB->Ldr
OFF_INMEMORY_FLINK   = 0x20   # PDR_LDR_DATA_TABLE_ENTRY.InMemoryOrderLinks.Flink
OFF_INMEMORY_BLINK   = 0x28
OFF_DLLBASE          = 0x30
OFF_ENTRYPOINT       = 0x38
OFF_SIZE_OF_IMAGE    = 0x40
OFF_FULL_DLLNAME     = 0x48   # UNICODE_STRING (16 B) + buffer
OFF_BASE_DLLNAME     = 0x58

LIST_ENTRY_SIZE = 0x10

class FakeModule:
    def __init__(self, uc, base, name, exports):
        self.uc = uc
        self.base = base
        self.name = name
        self.exports = exports          # {nombre: stub_rva_relativo_al_modulo}
        self.entry = 0
        self.size = 0
        self.stubs = {}                  # VA de stub -> nombre
        self._build()

    def _build(self):
        uc = self.uc
        names = sorted(self.exports if isinstance(self.exports, (list, tuple))
                       else self.exports.keys())
        n = len(names)

        # disposicion dentro del modulo
        EXPORT_RVA = 0x1000
        HEAD_END   = 0x28
        func_rva   = EXPORT_RVA + HEAD_END
        name_rva   = func_rva + 4 * n
        ord_rva    = name_rva + 4 * n
        strs_rva   = (ord_rva + 2 * n + 15) & ~15
        cur = strs_rva
        name_offsets = []
        for nm in names:
            name_offsets.append(cur)
            cur += len(nm.encode()) + 1
        cur = (cur + 15) & ~15
        STUBS_RVA = cur                      # los stubs van dentro del modulo
        cur += 0x10 * n

        SIZE = 0x8000
        if SIZE < cur + 0x1000:
            SIZE = (cur + 0x1000 + 0xFFF) & ~0xFFF
        uc.mem_map(self.base, SIZE)
        self.size = SIZE

        # --- stubs: un 'ret' por export ---
        for i, nm in enumerate(names):
            stub = STUBS_RVA + 0x10 * i
            uc.mem_write(self.base + stub, b"\xc3")
            self.stubs[self.base + stub] = nm

        # --- PE minimo ---
        dos = bytearray(0x80)
        struct.pack_into('<H', dos, 0, 0x5A4D)
        struct.pack_into('<I', dos, 0x3C, 0x80)
        uc.mem_write(self.base, bytes(dos))

        pe = bytearray(0x200)
        struct.pack_into('<I', pe, 0, 0x00004550)
        struct.pack_into('<H', pe, 4, 0x8664)
        struct.pack_into('<H', pe, 16, 0x210E)
        struct.pack_into('<H', pe, 18, 0x2102)
        opt_off = 24
        struct.pack_into('<H', pe, opt_off + 0, 0x20B)
        struct.pack_into('<I', pe, opt_off + 16, 0x1000)          # EP (RVA)
        struct.pack_into('<Q', pe, opt_off + 24, self.base)       # ImageBase
        struct.pack_into('<I', pe, opt_off + 56, 0x1000)          # SectionAlignment
        struct.pack_into('<I', pe, opt_off + 60, 0x200)           # FileAlignment
        struct.pack_into('<H', pe, opt_off + 68, 1)               # NATIVE
        struct.pack_into('<H', pe, opt_off + 70, 0x8160)
        struct.pack_into('<Q', pe, opt_off + 108, SIZE)           # SizeOfImage
        struct.pack_into('<I', pe, opt_off + 108 - 4, 16)         # NumberOfRvaAndSizes
        dd_off = opt_off + 112
        struct.pack_into('<II', pe, dd_off + 0 * 8, EXPORT_RVA, cur - EXPORT_RVA)
        uc.mem_write(self.base + 0x80, bytes(pe))

        # --- IMAGE_EXPORT_DIRECTORY ---
        exp = bytearray(cur - EXPORT_RVA)
        struct.pack_into('<I', exp, 0x0C, 0)             # Name RVA (no critico)
        struct.pack_into('<I', exp, 0x10, 1)             # Base
        struct.pack_into('<I', exp, 0x14, n)             # NumberOfFunctions
        struct.pack_into('<I', exp, 0x18, n)             # NumberOfNames
        struct.pack_into('<I', exp, 0x1C, func_rva)
        struct.pack_into('<I', exp, 0x20, name_rva)
        struct.pack_into('<I', exp, 0x24, ord_rva)
        for i, nm in enumerate(names):
            struct.pack_into('<I', exp, (func_rva - EXPORT_RVA) + 4 * i, STUBS_RVA + 0x10 * i)
            struct.pack_into('<I', exp, (name_rva - EXPORT_RVA) + 4 * i, name_offsets[i])
            struct.pack_into('<H', exp, (ord_rva  - EXPORT_RVA) + 2 * i, i)
            enc = nm.encode() + b"\0"
            o = name_offsets[i] - EXPORT_RVA
            exp[o:o + len(enc)] = enc
        uc.mem_write(self.base + EXPORT_RVA, bytes(exp))

    def get(self, name):
        return self.base + self.exports[name]


def build_module_list(uc, peb, talloc, modules):
    """Enlaza los FakeModule en PEB.Ldr.InMemoryOrderModuleList."""
    ldr = peb + OFF_LDR
    # PEB->Ldr debe apuntar a la estructura: sin esto el empaquetador lee
    # NULL y no encuentra ningun modulo.
    uc.mem_write(peb + OFF_LDR, struct.pack('<Q', ldr))
    entries = []
    for i, m in enumerate(modules):
        e = talloc + i * 0x100
        m.entry = e
        entries.append(e)

    for i, (m, e) in enumerate(zip(modules, entries)):
        nxt = entries[i + 1] if i + 1 < len(entries) else ldr + OFF_INMEMORY_FLINK
        prv = entries[i - 1] if i > 0 else ldr + OFF_INMEMORY_BLINK
        uc.mem_write(e + OFF_INMEMORY_FLINK, struct.pack('<Q', nxt))
        uc.mem_write(e + OFF_INMEMORY_BLINK, struct.pack('<Q', prv))
        uc.mem_write(e + OFF_DLLBASE,       struct.pack('<Q', m.base))
        uc.mem_write(e + OFF_ENTRYPOINT,    struct.pack('<Q', m.base + 0x1000))
        uc.mem_write(e + OFF_SIZE_OF_IMAGE, struct.pack('<I', m.size))

        nb = m.name.encode('utf-16-le') + b"\0\0"
        buf = e + 0x70
        uc.mem_write(buf, nb)
        us = struct.pack('<HHI', len(nb) - 2, len(nb), 0) + struct.pack('<Q', buf)
        uc.mem_write(e + OFF_FULL_DLLNAME, us)
        uc.mem_write(e + OFF_BASE_DLLNAME, us)

    head = ldr + OFF_INMEMORY_FLINK
    uc.mem_write(head, struct.pack('<Q', entries[0] if entries else 0))
    uc.mem_write(ldr + OFF_INMEMORY_BLINK,
                 struct.pack('<Q', entries[-1] if entries else 0))
    return entries