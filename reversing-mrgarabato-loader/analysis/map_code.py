#!/usr/bin/env python3
"""Mapea que regiones de la imagen son codigo real descifrado frente a
bloques aun cifrados, usando Capstone como metrica de 'code-likeness'."""
import sys
from capstone import *

img = open(sys.argv[1], "rb").read()
BASE = 0x140000000
md = Cs(CS_ARCH_X86, CS_MODE_64)
md.skipdata = True

CH = 0x1000
regions = [("text", 0x1000, 0x18000), ("7 f", 0x23000, 0x80B000)]

for name, lo, hi in regions:
    print(f"=== seccion {name} (0x{lo:x}-0x{hi:x}) ===")
    prev = None
    for off in range(lo, hi, CH):
        blk = img[off:off + CH]
        if not any(blk):
            state = "vacio"
        else:
            # ratio de bytes que forman instrucciones con operands coherentes
            good = bad = 0
            for i in md.disasm(blk, BASE + off):
                if i.id == 0:
                    bad += len(i.bytes)
                else:
                    good += len(i.bytes)
            r = good / max(1, good + bad)
            state = "codigo" if r > 0.75 else ("mixto" if r > 0.45 else "cifrado")
        if state != prev:
            print(f"   0x{BASE+off:012x}  ->  {state}")
            prev = state
    print()

# donde acaba el codigo limpio en .7 f ?
print("=== barrido fino del inicio de .7 f ===")
lo, hi = 0x23000, 0x30000
run = []
for off in range(lo, hi, 0x200):
    blk = img[off:off + 0x200]
    good = bad = 0
    for i in md.disasm(blk, BASE + off):
        good += 0 if i.id == 0 else len(i.bytes)
        bad += len(i.bytes) if i.id == 0 else 0
    r = good / max(1, good + bad)
    run.append((off, r))
lim = [o for o, r in run if r > 0.7]
if lim:
    print(f"   codigo limpio continuo: 0x{BASE+min(lim):x} .. 0x{BASE+max(lim)+0x200:x}"
          f"  ({max(lim)+0x200-min(lim)} bytes)")