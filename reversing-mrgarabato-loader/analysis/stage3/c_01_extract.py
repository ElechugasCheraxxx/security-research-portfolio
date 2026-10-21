#!/usr/bin/env python3
"""c_01_extract.py -- Extrae y verifica los dos blobs objetivo del volcado."""
import os, hashlib, json

DUMP = "/root/mrgarabato_analysis/run/stage3/wine__w7.bin"
OUT  = "/root/mrgarabato_analysis/run/stage3"

data = open(DUMP, "rb").read()
print(f"dump size = {len(data)} (0x{len(data):X})")
print(f"md5  = {hashlib.md5(data).hexdigest()}")
print(f"sha1 = {hashlib.sha1(data).hexdigest()}")

B1_OFF, B1_LEN = 0x0227A0, 160
B2_OFF, B2_LEN = 0x022A50, 400

b1 = data[B1_OFF:B1_OFF+B1_LEN]
b2 = data[B2_OFF:B2_OFF+B2_LEN]
assert len(b1) == B1_LEN and len(b2) == B2_LEN

open(f"{OUT}/c_blob1_160.bin", "wb").write(b1)
open(f"{OUT}/c_blob2_400.bin", "wb").write(b2)

# ---- dump hex del blob1 tal y como lo dio el enunciado ----
ESPERADO = """
f0: e0 ed e6 d7 f9 f9 f5 e3 e1 f9 ef b0 fa d8 c4 00
f1: c1 f1 e6 f9 e2 ea fa ff d3 fd fe f5 fa d2 8f c7
f2: c0 ed e6 df f9 eb e9 ff f8 e8 f2 ec b1 c5 d9 c7
f3: f9 fb f0 f4 f8 e0 ea ff e9 ea f8 ec b1 c5 d9 c7
f4: db fb fa fd d2 e0 e9 f6 f4 ee f8 ec b1 c5 d9 c7
f5: fb e0 e1 e6 f3 fd fb ef fc fb f8 ec b1 c5 d9 c7
f6: da f9 f8 e3 f9 f1 ed e3 df f9 ff eb f8 c7 c4 d0
f7: e3 e6 fa f5 c8 f9 f7 fb f7 e5 e7 fb ed 8e c4 da
f8: c3 e6 fa f5 f2 eb ea d2 fa ff f6 fb ed 8e c4 da
f9: f9 fb f0 f4 f8 e0 fa f5 f5 e8 ef f1 f3 8e c4 da
"""
esperado = bytearray()
for line in ESPERADO.strip().splitlines():
    esperado += bytes.fromhex(line.split(":", 1)[1].strip())

print("\n[blob1] coincide con el hex del enunciado:", bytes(esperado) == b1)
print("[blob1] md5 =", hashlib.md5(b1).hexdigest())
for i in range(10):
    row = b1[i*16:(i+1)*16]
    print(f"  f{i}: " + " ".join(f"{x:02x}" for x in row))

print("\n[blob2] md5 =", hashlib.md5(b2).hexdigest())
for i in range(0, 400, 16):
    row = b2[i:i+16]
    print(f"  {B2_OFF+i:06x}: " + " ".join(f"{x:02x}" for x in row))

# ---- contexto de las zonas ----
def ctx(off, antes=0x60, despues=0x60):
    a = max(0, off-antes); z = min(len(data), off+despues)
    return data[a:z], a

for name, off, ln in (("BLOB1", B1_OFF, B1_LEN), ("BLOB2", B2_OFF, B2_LEN)):
    win, base = ctx(off)
    print(f"\n===== contexto {name} @0x{off:X} (ventana base 0x{base:X}) =====")
    for i in range(0, len(win), 16):
        row = win[i:i+16]
        asc = "".join(chr(c) if 32 <= c < 127 else "." for c in row)
        mark = "  <<<" if base+i <= off < base+i+16 else ""
        print(f"  {base+i:06x}: " + " ".join(f"{c:02x}" for c in row).ljust(48) + " " + asc + mark)

# ---- mapa de ceros/nonceros alrededor ----
print("\n===== mapa de bytes nulos en 0x021700-0x022C00 =====")
region = data[0x21700:0x22C00]
i = 0
while i < len(region):
    if region[i] == 0:
        j = i
        while j < len(region) and region[j] == 0: j += 1
        if j - i >= 8:
            print(f"  zeros 0x{0x21700+i:06x}-0x{0x21700+j-1:06x}  ({j-i} B)")
        i = j
    else:
        i += 1
