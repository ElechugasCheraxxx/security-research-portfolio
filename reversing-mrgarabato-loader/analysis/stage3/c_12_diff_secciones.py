#!/usr/bin/env python3
"""
c_12_diff_secciones.py -- Compara artefactos de .w7/ (en disco vs en memoria).
Si uno es la version cifrada en reposo y otro la descifrada, el XOR de ambos
en la zona de .rdata da el keystream del desempaquetador.
"""
import os, numpy as np, hashlib

RUN = "/root/mrgarabato_analysis/run/"
F = {
 "wine__w7.bin (memoria)":      RUN+"stage3/wine__w7.bin",
 "seccion_completa.bin":        RUN+"stage3/seccion_completa.bin",
 "w7_cifrado_7.79MB.bin":       RUN+"stage3/w7_cifrado_7.79MB.bin",
 "wine_unpacked.exe (payload)": RUN+"stage3/wine_unpacked.exe",
 "seccion_post_run.bin":        RUN+"stage3/seccion_post_run.bin",
}
data = {}
for k, p in F.items():
    if not os.path.exists(p): print("falta", k); continue
    b = open(p, "rb").read()
    data[k] = b
    z = b.count(0)
    print(f"{k:30s} {len(b):9d} B  md5={hashlib.md5(b).hexdigest()[:16]}  ceros={z} ({z/len(b)*100:.1f}%)")

print("\n--- ¿son identicos? ---")
ks = list(data)
for i in range(len(ks)):
    for j in range(i+1, len(ks)):
        a, b = data[ks[i]], data[ks[j]]
        n = min(len(a), len(b))
        eq = sum(1 for x, y in zip(a[:n], b[:n]) if x == y)
        print(f"  {ks[i][:26]:28s} vs {ks[j][:26]:28s}: {eq}/{n} = {eq/n*100:.2f}% iguales")

BLOB1_OFF, BLOB2_OFF = 0x227A0, 0x22A50
print("\n--- bytes en la zona de los blobs en cada artefacto ---")
for k, b in data.items():
    for nm, off, ln in (("BLOB1", BLOB1_OFF, 16), ("BLOB2", BLOB2_OFF, 16)):
        seg = b[off:off+ln]
        asc = "".join(chr(c) if 32 <= c < 127 else "." for c in seg)
        print(f"  {k:30s} {nm} @0x{off:X}: {seg.hex(' ')}  {asc}")

# ¿algun par da algo legible en la zona .rdata?
print("\n--- XOR entre pares en la zona 0x21000-0x23000 : ¿aparece texto? ---")
def printable_frac(x):
    return float(((x >= 0x20) & (x <= 0x7E)).mean())
for i in range(len(ks)):
    for j in range(i+1, len(ks)):
        a = np.frombuffer(data[ks[i]][0x21000:0x23000], np.uint8).astype(np.int16)
        b = np.frombuffer(data[ks[j]][0x21000:0x23000], np.uint8).astype(np.int16)
        for nm, x in (("xor", a ^ b), ("sub", (a - b) & 255)):
            pf = printable_frac(x.astype(np.uint8))
            if pf > 0.5:
                s = bytes(x.astype(np.uint8))
                print(f"  {ks[i][:24]:26s} {nm} {ks[j][:24]:26s} imprimible={pf:.2f}")
                print(f"     {s[:200]!r}")
