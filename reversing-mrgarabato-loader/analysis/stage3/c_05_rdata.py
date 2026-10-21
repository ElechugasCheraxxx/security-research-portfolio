#!/usr/bin/env python3
"""c_05_rdata.py -- Vuelca y clasifica toda la zona .rdata 0x21700-0x22C00."""
import collections, math, struct

d = open("/root/mrgarabato_analysis/run/stage3/wine__w7.bin", "rb").read()
LO, HI = 0x21700, 0x22C00

def kind(b):
    if all(x == 0 for x in b): return "ZERO"
    if all(32 <= x < 127 for x in b): return "ANSI"
    # printable con huecos
    pr = sum(1 for x in b if 32 <= x < 127 or x in (0,10,13,9))
    if pr >= len(b)*0.85: return "ANSI~"
    # UTF-16LE?
    if len(b) % 2 == 0:
        w = [b[i] | (b[i+1] << 8) for i in range(0, len(b), 2)]
        if all((x < 0x80 and (x == 0 or 32 <= x < 127)) for x in w): return "W16"
        if all((0x20 <= x < 0x7F) or x in (0x0A, 0x0D) for x in w): return "W16"
    # punteros 8 bytes
    if len(b) % 8 == 0:
        vals = [struct.unpack_from("<Q", b, i)[0] for i in range(0, len(b), 8)]
        if all(0x140000000 <= v < 0x140800000 for v in vals): return "PTR64"
    return "BIN "

print("Mapa de la zona .rdata (bloques de 16 bytes, tipo):")
seg = []
for off in range(LO, HI, 16):
    seg.append((off, kind(d[off:off+16])))
# colapsar
i = 0
while i < len(seg):
    j = i
    while j+1 < len(seg) and seg[j+1][1] == seg[i][1]: j += 1
    a, bb = seg[i][0], seg[j][0]+16
    print(f"  0x{a:06X}-0x{bb-1:06X} ({bb-a:5d} B)  {seg[i][1]}")
    i = j+1

print("\n\n--- volcado legible 0x21700-0x22C00 ---")
for off in range(LO, HI, 16):
    b = d[off:off+16]
    if all(x == 0 for x in b): continue
    asc = "".join(chr(x) if 32 <= x < 127 else "." for x in b)
    print(f"  {off:06x}: {b.hex(' '):<47}  {asc}")
