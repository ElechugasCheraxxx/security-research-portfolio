#!/usr/bin/env python3
"""
s1_disasm_lineal.py -- Barrido lineal de desensamblado con capstone sobre el
blob de stage3. Guarda un volcado compacto de todas las instrucciones en un
formato binario legible (offset, tam, bytes, id_mnem, grupo) para reutilizar en
fases posteriores sin volver a desensamblar.

Salidas:
  instrs.bin   -- registro compacto (ver formato abajo)
  s1_stats.txt -- estadisticas del barrido
  s1_lineal.txt-- muestra humana de las primeras N instrucciones
"""
import sys, os, json, struct, collections
from capstone import Cs, CS_ARCH_X86, CS_MODE_64

HERE = os.path.dirname(os.path.abspath(__file__))
BLOB = os.path.join(HERE, "stage3_code.bin")

data = open(BLOB, "rb").read()
N = len(data)

md = Cs(CS_ARCH_X86, CS_MODE_64)
md.detail = True
md.skipdata = True   # permite seguir mas alla de una instruccion invalida


class Rec:
    __slots__ = ("off", "size", "mnem", "op1", "op2", "grp")


recs = []
nsynth = 0
mdet = md.disasm(data, 0)
for ins in mdet:
    r = Rec()
    r.off = ins.address
    r.size = ins.size
    o1 = o2 = ""
    if ins.id == 0:            # pseudo-instruccion sintetica de SKIPDATA
        nsynth += 1
        r.mnem = ".byte"
    else:
        r.mnem = ins.mnemonic
        if ins.op_str:
            parts = ins.op_str.split(",", 1)
            o1 = parts[0].strip()
            o2 = parts[1].strip() if len(parts) > 1 else ""
    r.op1 = o1
    r.op2 = o2
    recs.append(r)

print("instrucciones:", len(recs), " sinteticas(.byte):", nsynth)

# cobertura lineal
covered = sum(r.size for r in recs)
print("bytes cubiertos:", covered, "de", N, "=> %.2f%%" % (100.0 * covered / N))

# histograma de mnemonicos
hist = collections.Counter(r.mnem for r in recs)
with open(os.path.join(HERE, "s1_stats.txt"), "w") as f:
    f.write("total instr: %d\n" % len(recs))
    f.write("bytes cubiertos: %d / %d (%.2f%%)\n\n" % (covered, N, 100.0 * covered / N))
    f.write("%-12s %8s %7s\n" % ("MNEM", "COUNT", "PCT"))
    for m, c in hist.most_common(80):
        f.write("%-12s %8d %6.2f%%\n" % (m, c, 100.0 * c / len(recs)))

# volcado de texto de las primeras 400 instrucciones
with open(os.path.join(HERE, "s1_lineal.txt"), "w") as f:
    for r in recs[:400]:
        f.write("%08x  %-8s %-30s\n" % (r.off, r.mnem, (r.op1 + (", " + r.op2 if r.op2 else ""))[:30]))

# registro compacto: cabecera + registros de tam variable
# formato por instruccion: <off:u32><size:u8><mnemid:u8><op1id:u16><op2id:u16>
mnems = sorted(hist)
midx = {m: i for i, m in enumerate(mnems)}

# ops vocabulary
opvocab = {}
def opid(s):
    i = opvocab.get(s)
    if i is None:
        i = len(opvocab)
        opvocab[s] = i
    return i

with open(os.path.join(HERE, "instrs.bin"), "wb") as f:
    f.write(b"STG3IN1")
    f.write(struct.pack("<II", len(recs), N))
    f.write(struct.pack("<H", len(mnems)))
    for m in mnems:
        f.write(m.encode() + b"\0")
    f.write(struct.pack("<I", len(opvocab)))
    pass
    # segunda pasada para escribir ops
    for r in recs:
        f.write(struct.pack("<IHHII", r.off, r.size, midx[r.mnem], opid(r.op1), opid(r.op2)))
    for s, i in opvocab.items():
        f.write(s.encode() + b"\0")

# offsets donde el barrido lineal resbalo (instruccion invalida)
with open(os.path.join(HERE, "s1_desync.txt"), "w") as f:
    for r in recs:
        if r.mnem == ".byte":
            f.write("%08x %s\n" % (r.off, data[r.off:r.off+8].hex()))

print("escrito instrs.bin  ops vocab:", len(opvocab))