#!/usr/bin/env python3
"""Localiza la tabla de handlers y el bucle de dispatch del interprete VM
que vive en RVA 0xE3C000-0xF8A8A4."""
import sys, collections
from capstone import *
from capstone.x86 import *

img = open("mem_bypass.bin", "rb").read()
BASE = 0x140000000
LO, HI = 0xE3C000, 0xF8A8A4
md = Cs(CS_ARCH_X86, CS_MODE_64); md.detail = True

# 1) buscar saltos indirectos con escala 8 (accesos a tabla de handlers)
cands = []
for i in md.disasm(img[LO:HI], BASE + LO):
    if i.id in (X86_INS_JMP, X86_INS_CALL) and i.bytes[0] == 0xFF:
        for op in i.operands:
            if op.type == X86_OP_MEM and op.mem.scale == 8:
                cands.append((i.address, i.mnemonic, i.op_str, op.mem.base, op.mem.index))
                break
print(f"[*] saltos/llamadas indirectos con escala 8: {len(cands)}")
for a, mn, ops, base, idx in cands[:30]:
    print("   0x%x  %-5s %s" % (a, mn, ops))

# 2) buscar el bucle tipico: movzx opcode + acceso a tabla
print("\n[*] instrucciones de lectura de opcode (movzx/mov byte) seguidas de salto:")
reads = collections.Counter()
for i in md.disasm(img[LO:HI], BASE + LO):
    if i.id in (X86_INS_MOVZX, X86_INS_MOV):
        for op in i.operands:
            if op.type == X86_OP_MEM and op.mem.scale in (1,) and i.mnemonic.startswith("movzx"):
                reads[i.address] += 1
print("   candidatos movzx: %d" % len(reads))

# 3)去找 las zonas con mas actividad: dispatchers tienen mucha densidad de saltos
print("\n[*] zonas de alta densidad de saltos (posibles dispatch loops):")
jumps = collections.Counter()
for i in md.disasm(img[LO:HI], BASE + LO):
    if i.id in (X86_INS_JMP, X86_INS_CALL):
        jumps[i.address >> 10] += 1
for page, n in jumps.most_common(15):
    print("   pagina 0x%x  %d saltos/llamadas" % (BASE + (page << 10), n))

# 4)范围内 buscar el patron clasico:  lea reg,[tabla] ; ... ; jmp [reg+reg*8]
print("\n[*] busqueda de tabla de handlers: secuencia de 8 bytes alineados "
      "que apunten dentro del rango del interprete")
tbl = {}
for off in range(LO, HI, 8):
    v = int.from_bytes(img[off:off + 8], "little")
    if LO + BASE <= v < HI + BASE:
        tbl.setdefault(BASE + off, []).append(v)
print("   punteros validos a zona de handlers: %d en %d posiciones" %
      (sum(len(v) for v in tbl.values()), len(tbl)))
best = sorted(tbl.items(), key=lambda z: -len(z[1]))[:15]
for addr, targets in best:
    print("   0x%x -> %d entradas  ej: %s" % (addr, len(targets),
          ", ".join("0x%x" % t for t in targets[:5])))