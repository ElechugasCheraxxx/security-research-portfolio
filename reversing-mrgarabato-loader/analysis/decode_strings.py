#!/usr/bin/env python3
"""Descifrador de cadenas del payload.

Cifrado descubierto:  plain[i] = cipher[i] ^ (0x53 + i)
El indice corre de forma continua a lo largo de la cadena (verificado:
1b15071200190b1f  -> 'HARDWARE'
071d1e0e163c2531  -> '\\ACPI\\DS'  continuando en i=8)
"""
import sys, re

KEY0 = 0x53


def dec(blob: bytes, start_index: int = 0, key0: int = KEY0) -> bytes:
    return bytes(b ^ ((key0 + start_index + i) & 0xFF) for i, b in enumerate(blob))


def show(label, blob, idx=0):
    p = dec(blob, idx)
    txt = "".join(chr(c) if 32 <= c < 127 else ("\\0" if c == 0 else ".") for c in p)
    print("  %-34s -> %s" % (label, txt))
    return p


img = open(sys.argv[1] if len(sys.argv) > 1 else "mem_bypass.bin", "rb").read()

print("=" * 78)
print("VERIFICACION")
print("=" * 78)
print("  0x1a470 =", dec(img[0x1a470:0x1a478]).decode("latin1"))
print("  0x1a478 (continuando i=8) =", dec(img[0x1a478:0x1a480], 8).decode("latin1"))
whole = dec(img[0x1a470:0x1a480])
print("  bloque completo 0x1a470-0x1a480 =", whole.decode("latin1"))

print()
print("=" * 78)
print("CADENAS DESCIFRADAS (resto de la region 0x1a2e0-0x1a600)")
print("=" * 78)
# las cadenas codificadas ocupan posiciones contiguas; se decodifica todo
seg = img[0x1a2e0:0x1a600]
dec_all = dec(seg)
for m in re.finditer(rb'[\x20-\x7e]{4,}', dec_all):
    print("  0x%x  %s" % (0x1a2e0 + m.start(), m.group().decode("latin1")))

print()
print("=" * 78)
print("TODAS las cadenas del binario en claro+descifrado (region .rdata extendida)")
print("=" * 78)
for start, end in [(0x1a460, 0x1a700), (0x19e00, 0x19f00)]:
    print(f"--- 0x{start:x}-0x{end:x} ---")
    for m in re.finditer(rb'[\x20-\x7e]{4,}', dec(img[start:end])):
        print("  0x%x  %s" % (start + m.start(), m.group().decode("latin1")))