#!/usr/bin/env python3
"""Reconstruye el flujo de instrucciones del dispatcher usando como anclas
las direcciones que la traza de ejecucion demuestra como realmente ejecutadas."""
import re, collections, sys
from capstone import *
from capstone.x86 import *

BASE = 0x140000000
img = open("mem_bypass.bin", "rb").read()
md = Cs(CS_ARCH_X86, CS_MODE_64)
md.detail = True

# 1) recoger direcciones ejecutadas de la traza
pat = re.compile(rb'\bret=([0-9a-f]{9,16})\b')
hist = collections.Counter()
with open("run3.relay", "rb") as f:
    for line in f:
        m = pat.search(line)
        if m:
            a = int(m.group(1), 16)
            if BASE <= a < BASE + len(img):
                hist[a] += 1

anchors = sorted(hist)
print(f"[*] {len(anchors)} direcciones ejecutadas (anclas)")
by_zone = collections.Counter()
for a in anchors:
    r = a - BASE
    by_zone["text" if r < 0x18000 else ("7f" if r < 0x81b000 else
            ("zzc" if r < 0x81c000 else ("3q" if r < 0xf8a8a4 else "rsrc")))] += 1
print("    reparto:", dict(by_zone))

# 2) para cada ancla, alinear hacia atras hasta un limite de instruccion
#    y desensamblar hacia adelante contando los pasos realistas
def disasm_from(off, n=24):
    out = []
    for i in md.disasm(img[off:off + 15 * n], BASE + off, count=n):
        out.append(i)
    return out

print("\n[*] desensamblado alineado en las 12 anclas mas calientes:\n")
for a, cnt in hist.most_common(12):
    off = a - BASE
    print(f"--- 0x{a:x} (RVA 0x{off:x}) ejecutado {cnt} veces ---")
    ins = disasm_from(off, 18)
    for i in ins:
        mark = ""
        if i.id == X86_INS_RET:                       mark = "   <== RET"
        if i.id == X86_INS_JMP and i.bytes[0] == 0xFF: mark = "   <== DISPATCH"
        for op in i.operands:
            if op.type == X86_OP_MEM and op.mem.scale in (8, 4):
                mark = mark or "   <- tabla"
        print("    0x%x  %-26s %-8s %s%s" % (i.address, i.bytes.hex(), i.mnemonic, i.op_str, mark))
    print()