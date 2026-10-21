#!/usr/bin/env python3
"""
c_09_busqueda.py -- Busca el plaintext/keystream de los blobs dentro del propio volcado
y en los otros artefactos (mem_*.bin, unpacked_loader.exe, etc.)
"""
import os, glob, struct
import numpy as np

RUN = "/root/mrgarabato_analysis/run/"
DUMP = RUN+"stage3/wine__w7.bin"
d = open(DUMP, "rb").read()
B1 = d[0x227A0:0x22A00]
B2 = d[0x22A50:0x22BE0]

# keystream候选 si el plano es ASCII ancho: los bytes PARES / IMPARES son el keystream
KS_EVEN = bytes(B1[0::2]); KS_ODD = bytes(B1[1::2])

OTRAS = [RUN+"stage3/wine_unpacked.exe", RUN+"loader_solo_text.exe",
         RUN+"mem_loader.bin", RUN+"mem_check.bin", RUN+"unpacked_loader.exe",
         RUN+"stage3/stage3_code.bin", RUN+"stage3/stage3_code.exe",
         RUN+"stage3/seccion_completa.bin", RUN+"stage3/w7_cifrado_7.79MB.bin",
         RUN+"stage3/instrs.bin", RUN+"stage3/mapa_offsets.json",
         RUN+"stage3/wine_strings.txt", RUN+"stage3/driver_strings.txt"]
OTRAS = [p for p in OTRAS if os.path.exists(p)]

PATS = {
    "BLOB1 completo (160)": B1,
    "BLOB1 64B":           B1[:64],
    "BLOB1 32B":           B1[:32],
    "BLOB1 16B (campo0)":  B1[:16],
    "BLOB2 completo (400)":B2,
    "BLOB2 64B":           B2[:64],
    "BLOB2 16B":           B2[:16],
    "keystream PAR(80)":   KS_EVEN,
    "keystream IMP(80)":   KS_ODD,
}

print("=== busqueda dentro del propio volcado ===")
for nm, p in PATS.items():
    hits=[]; st=0
    while len(hits)<8:
        i=d.find(p, st)
        if i<0: break
        hits.append(i); st=i+1
    print(f"  {nm:22s}: {[hex(h) for h in hits]}")

print("\n=== busqueda en otros artefactos ===")
for f in OTRAS:
    try: b = open(f,"rb").read()
    except Exception as e: print(f"  {f}: {e}"); continue
    res=[]
    for nm, p in PATS.items():
        i = b.find(p)
        if i >= 0: res.append(f"{nm}@0x{i:X}")
    print(f"  {os.path.basename(f):28s} ({len(b)} B): " + (", ".join(res) if res else "nada"))

# ---- ¿los 8 bytes 'cola compartida' ec b1 c5 d9 c7  en algun sitio? ----
print("\n=== motifs recurrentes ===")
for nm, p in (("cola ecb1c5d9c7", bytes.fromhex("ecb1c5d9c7")),
              ("cola 8ec4da", bytes.fromhex("8ec4da")),
              ("campo f8==f9", B1[7*16:8*16])):
    hits=[]; st=0
    while len(hits)<12:
        i=d.find(p, st)
        if i<0: break
        hits.append(i); st=i+1
    print(f"  {nm:16s}: {len(hits)} hits -> {[hex(h) for h in hits]}")
