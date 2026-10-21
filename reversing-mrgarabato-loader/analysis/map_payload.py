#!/usr/bin/env python3
"""Mapeo estructural fino de la seccion .3q- (el payload) del binario desempaquetado.
Divide por entropia y analiza la distribucion de bytes de cada region para
distinguir codigo x86 real, datos comprimidos y material cifrado."""
import math, collections, sys, re
from capstone import Cs, CS_ARCH_X86, CS_MODE_64

img = open(sys.argv[1] if len(sys.argv) > 1 else "mem_bypass.bin", "rb").read()
BASE = 0x140000000
START, SIZE = 0x81C000, 0x76E8A4
blob = img[START:START + SIZE]
md = Cs(CS_ARCH_X86, CS_MODE_64); md.skipdata = True


def ent(b):
    if not b:
        return 0.0
    c = collections.Counter(b)
    n = len(b)
    return -sum((v / n) * math.log2(v / n) for v in c.values())


def rexfrac(b):
    return sum(1 for x in b if 0x40 <= x <= 0x4F) / max(1, len(b))


def zerof(b):
    return b.count(0) / max(1, len(b))


CH = 0x4000
print("RVA        entropia  REX%%   0x00%%  lectura")
print("-" * 64)
regions = []
for off in range(0, SIZE, CH):
    blk = blob[off:off + CH]
    e, r, z = ent(blk), rexfrac(blk) * 100, zerof(blk) * 100
    if e > 7.90:
        kind = "CIFRADO/ALEATORIO"
    elif e > 7.20:
        kind = "comprimido denso"
    elif e > 6.20:
        kind = "comprimido / mixto"
    elif r > 4.5:
        kind = "CODIGO x86-64"
    else:
        kind = "datos/tablas"
    regions.append((off, e, r, z, kind))
    if off < 0x20000 or off % 0x20000 == 0 or off > SIZE - 0x80000:
        print("0x%06x   %.3f    %5.2f  %5.2f   %s" % (START + off, e, r, z, kind))

# agrupar regiones contiguas del mismo tipo
print("\n" + "=" * 64)
print("SEGMENTOS HOMOGENEOS")
print("=" * 64)
runs = []
cur = None
for off, e, r, z, kind in regions:
    if cur is None or cur[2] != kind:
        if cur:
            runs.append(cur)
        cur = [off, off + CH, kind, []]
    cur[1] = off + CH
    cur[3].append(e)
if cur:
    runs.append(cur)

for s, e, kind, es in runs:
    if e - s < 0x8000:
        continue
    print("  0x%06x - 0x%06x  (%.2f MB)  %-22s ent=%.3f"
          % (BASE + s, BASE + e, (e - s) / 1048576, kind, sum(es) / len(es)))

# REX por region global (cabecera vs cola)
print("\n" + "=" * 64)
print("ANALISIS POR BLOQUE (inicio vs final de la seccion)")
print("=" * 64)
for name, s, e in [("inicio 0x0-0x100000", 0, 0x100000),
                   ("medio  0x500000-0x600000", 0x500000, 0x600000),
                   ("final 0x660000-0x76E8A4", 0x660000, SIZE)]:
    b = blob[s:e]
    if not b:
        continue
    print("  %-24s ent=%.3f  REX=%.2f%%  0x00=%.2f%%  tam=%.1f MB"
          % (name, ent(b), rexfrac(b) * 100, zerof(b) * 100, len(b) / 1048576))

# carve: buscar firmas de ficheros embebidos en TODO el blob
print("\n" + "=" * 64)
print("CARVE: firmas de ficheros embebidos")
print("=" * 64)
SIGS = {
    "MZ/PE":      b"MZ",
    "PNG":        b"\x89PNG\r\n\x1a\n",
    "ZIP/APK/JAR": b"PK\x03\x04",
    "RAR":        b"Rar!\x1a\x07",
    "7z":         b"7z\xbc\xaf\x27\x1c",
    "CAB":        b"MSCF",
    "GZIP":       b"\x1f\x8b\x08",
    "BZ2":        b"BZh",
    "XZ":         b"\xfd7zXZ\x00",
    "ZSTD":       b"\x28\xb5\x2f\xfd",
    "LZ4":        b"\x04\x22\x4d\x18",
    "ELF":        b"\x7fELF",
    "PDF":        b"%PDF",
    "SQLITE":     b"SQLite format 3",
    "MZ+PE valido": b"MZ\x90\x00",
}
for name, sig in SIGS.items():
    pos = []
    start = 0
    while True:
        i = blob.find(sig, start)
        if i < 0:
            break
        pos.append(i)
        start = i + 1
    if pos:
        print("  %-14s %d hits  primeros: %s"
              % (name, len(pos), ", ".join("0x%x" % (BASE + START + p) for p in pos[:6])))
    else:
        print("  %-14s 0" % name)