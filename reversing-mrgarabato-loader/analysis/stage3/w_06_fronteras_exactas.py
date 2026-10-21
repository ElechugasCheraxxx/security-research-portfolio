#!/usr/bin/env python3
"""
w_06_fronteras_exactas.py -- Delimita con precision las regiones de
wine__w7.bin y dice que hay en cada una.

Criterio:
  entropia < 6.95 y  %nul > 1,5 %   -> CODIGO x86-64 en claro
                                    (0x00 muy frequente, REX, y la
                                     distribucion tipica de codigo)
  entropia 6,95..7,30                 -> ROPC/DATOS (cadenas, tablas, .rdata)
  entropia > 7,80                     -> OPACO (cifrado o comprimido)
"""
import os, sys, collections, re
import numpy as np

HERE = os.path.dirname(os.path.abspath(__file__))
BLOB = os.path.join(HERE, "wine__w7.bin")
raw = open(BLOB, "rb").read()
a = np.frombuffer(raw, np.uint8)
N = len(a)
B = 1 << 12
print("wine__w7.bin  %d bytes  (%d bloques de 4 KB)\n" % (N, N // B))

rows = []
for lo in range(0, N, B):
    blk = a[lo:lo + B]
    c = np.bincount(blk, minlength=256).astype(np.float64)
    p = c[c > 0] / len(blk)
    H = float(-(p * np.log2(p)).sum())
    nul = float((blk == 0).mean())
    pri = float(((blk >= 32) & (blk < 127)).mean())
    ch2 = float((((c * 255.0 / len(blk)) - 1.0) ** 2).sum())
    if H < 6.95 and nul > 0.015:
        k = "COD"
    elif H > 7.80:
        k = "OPA"
    else:
        k = "DAT"
    rows.append((lo, H, nul, pri, ch2, k))

def runs_of(k):
    out = []
    st = None
    for i, r in enumerate(rows):
        if r[5] == k and st is None:
            st = i
        elif r[5] != k and st is not None:
            out.append((st * B, i * B, i - st)); st = None
    if st is not None:
        out.append((st * B, len(rows) * B, len(rows) - st))
    return out

print("RESUMEN POR CLASE (bloques de 4 KB):")
for k, name in (("COD", "CODIGO en claro"), ("DAT", "DATOS/ROPC"), ("OPA", "OPACO")):
    tot = sum((hi - lo) for lo, hi, n in runs_of(k))
    print("  %-14s %10d B  (%5.2f%%)  bloques: %4d" %
          (name, tot, 100.0 * tot / N, sum(n for lo, hi, n in runs_of(k))))
print()
print("REGIONES CONTIGUAS (>= 8 KB):")
for k, name in (("COD", "CODIGO"), ("DAT", "DATOS "), ("OPA", "OPACO")):
    for lo, hi, n in runs_of(k):
        if hi - lo < 8192:
            continue
        seg = rows[lo // B:(hi // B)]
        Hm = sum(r[1] for r in seg) / len(seg)
        nulm = sum(r[2] for r in seg) / len(seg)
        c2 = sum(r[4] for r in seg) / len(seg)
        print("  %s %08x..%08x  %9d B (%5.2f%%)  %3d bloques  H=%.3f nul=%.3f chi2/255=%.1f"
              % (name, lo, hi, hi - lo, 100.0 * (hi - lo) / N, n, Hm, nulm, c2))
print()
print("TRANSICIONES (bloques donde cambia la clase):")
prev = None
for i, r in enumerate(rows):
    if prev is not None and r[5] != prev[5]:
        print("  %08x : %s -> %s   (H %.3f -> %.3f, nul %.4f -> %.4f)"
              % (r[0], prev[5], r[5], rows[i - 1][1], r[1], rows[i - 1][2], r[2]))
    prev = r

# ---------------- contenido de cada region ----------------
print()
print("=" * 90)
print("CONTENIDO")
print("=" * 90)
# cadenas largas en la region opaca: si fuera "cifrado" no habria ninguna
def strscan(lo, hi, minlen=8):
    out = []
    i = lo
    cur = bytearray()
    start = lo
    while i < hi:
        c = raw[i]
        if 32 <= c < 127:
            if not cur:
                start = i
            cur.append(c)
        else:
            if len(cur) >= minlen:
                out.append((start, bytes(cur).decode()))
            cur = bytearray()
        i += 1
    if len(cur) >= minlen:
        out.append((start, bytes(cur).decode()))
    return out

for lo, hi, n in runs_of("OPA"):
    if hi - lo < 65536:
        continue
    ss = strscan(lo, min(lo + 2 * 1024 * 1024, hi))
    ss.sort(key=lambda x: -len(x[1]))
    print("  OPA %08x..%08x (%d B): %d cadenas >=8 en los primeros 2 MB; mejores:"
          % (lo, hi, hi - lo, len(ss)))
    for o, s in ss[:6]:
        print("      %08x  %s" % (o, s[:90]))
    if not ss:
        print("      (ninguna cadena imprimible >= 8 -> compatible con cifrado/compresion)")
    # magicos
    for mg in (b"PK\x03\x04", b"\x1f\x8b", b"\xfd7zXZ", b"7z\xbc\xaf",
               b"MZ", b"\x4d\x5a", b"BZh", b"\x78\x9c", b"\x78\x01"):
        p = raw.find(mg, lo, min(lo + 4 * 1024 * 1024, hi))
        if p >= 0:
            print("      magico %r @ %08x" % (mg, p))
    break

print()
for lo, hi, n in runs_of("DAT"):
    if hi - lo < 65536:
        continue
    ss = strscan(lo, hi)
    ss.sort(key=lambda x: -len(x[1]))
    print("  DAT %08x..%08x (%d B): %d cadenas >=8 ; mejores:" % (lo, hi, hi - lo, len(ss)))
    for o, s in ss[:12]:
        print("      %08x  %s" % (o, s[:100]))
    print()

print()
print("CADENAS SIGNIFICATIVAS en todo el fichero (>= 12 chars imprimibles):")
ss = strscan(0, N, 12)
KEY = re.compile(r"(MRGARABATO|Auth|hwid|token|expired|WinDivert|MiDriver|PhoneHx|"
                 r"emulator|Injection|HD-Player|MEmu|neural|status|last_login|"
                 r"Microsoft|sc create|\.php|\.dll|\.sys|runtime|dotnet|https?://)", re.I)
hits = [(o, s) for o, s in ss if KEY.search(s)]
print("  %d cadenas con patron clave" % len(hits))
for o, s in hits[:80]:
    print("    %08x  %s" % (o, s[:120]))
