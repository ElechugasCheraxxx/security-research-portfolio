#!/usr/bin/env python3
"""Decodifica las cadenas construidas en pila de fcn.140012290 (RVA 0x12290),
que enumera procesos buscando nombres de maquinas virtuales."""
import re, struct

KEY0 = 0x53


def dec(data, idx0=0):
    return bytes(b ^ ((KEY0 + idx0 + i) & 0xFF) for i, b in enumerate(data))


src = open("decomp_text/fcn_12290.c").read()
img = open("mem_bypass.bin", "rb").read()

# 1) los literales inmediatos: _var_20h = 0xAAAABBBB; _var_18h = 0xCCCCDDDDEEEE
pairs = re.findall(r"_var_20h = (0x[0-9a-f]+);\s*\n\s*_var_18h = ([^;]+);", src)
n = int(re.search(r"while \(uVar2 < (0x[0-9a-f]+)\)", src).group(1), 16)

print("=" * 70)
print("CADENAS QUE fcn.140012290 BUSCA EN LOS PROCESOS")
print("=" * 70)

for a, b in pairs:
    va = int(a, 16)
    raw = struct.pack("<Q", va)          # 8 bytes little-endian
    vb = b.strip()
    # CONCAT26(uStack_1a, 0x...) o literal simple
    m = re.search(r"0x([0-9a-f]+)", vb)
    vb_i = int(m.group(1), 16)
    raw2 = vb_i.to_bytes(8, "little")
    total = raw + raw2
    # trim: la longitud real es n-8 bytes del segundo immediate (el 0x10 es basura de ancho)
    extra = n - 8
    blob = raw + raw2[:extra]
    plain = dec(blob)
    txt = "".join(chr(c) if 32 <= c < 127 else "." for c in plain)
    print("   %-22s  <- %s %s" % (txt, a, vb))

# 2) la que viene de memoria: *0x14001a440
for addr in (0x1a440, 0x1a448):
    raw = img[addr:addr + 24]
    print("\n   desde memoria 0x%x (len 17):" % (0x140000000 + addr))
    print("     %s" % dec(raw[:17]).decode("latin1", "replace"))

# 3) volcar tambien las otras dos funciones de chequeo por si tienen listas
for f in ("decomp_text/fcn_f1e0.c", "decomp_text/fcn_ee70.c", "decomp_text/fcn_ee80.c",
          "decomp_text/fcn_120f0.c"):
    try:
        s = open(f).read()
    except FileNotFoundError:
        continue
    m = re.search(r"_var_20h = \*(0x[0-9a-f]+);", s)
    if m:
        a = int(m.group(1), 16) - 0x140000000
        ln = re.search(r"while \(uVar2 < (0x[0-9a-f]+)\)", s)
        L = int(ln.group(1), 16) if ln else 16
        print("\n   %s -> %s" % (f, dec(img[a:a + L]).decode("latin1", "replace")))