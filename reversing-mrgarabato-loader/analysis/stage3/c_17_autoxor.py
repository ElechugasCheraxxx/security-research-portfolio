#!/usr/bin/env python3
"""
c_17_autoxor.py -- Busca una clave para BLOB1 dentro del propio binario y demas
artefactos: prueba XOR / ADD / SUB de BLOB1 contra TODAS las posiciones del
volcado (y de las imagenes derivadas), exigiendo 100% ASCII imprimible.
"""
import numpy as np, os, hashlib

RUN = "/root/mrgarabato_analysis/run/"
B1 = np.frombuffer(open(RUN+"stage3/wine__w7.bin","rb").read()[0x227A0:0x22840], np.uint8)
B2 = np.frombuffer(open(RUN+"stage3/wine__w7.bin","rb").read()[0x22A50:0x22BE0], np.uint8)

PR = np.zeros(256, bool); PR[0x20:0x7F] = True

def search(cand, blob, name):
    """Devuelve offsets donde cand XOR blob (o +- ) es todo imprimible."""
    n = len(cand); m = len(blob)
    good = np.ones(n-m+1, dtype=bool)
    for j in range(m):
        seg = cand[j:j+n-m+1]
        for op, x in (("xor", seg ^ blob[j]), ("sub", (seg - blob[j]).astype(np.uint8)),
                      ("add", (seg + blob[j]).astype(np.uint8))):
            ok = PR[x]
            if op == "xor": good &= ok
            else:
                # acumulamos aparte
                pass
    res = {}
    for op in ("xor","add","sub"):
        good = np.ones(n-m+1, dtype=bool)
        for j in range(m):
            seg = cand[j:j+n-m+1].astype(np.int16)
            bj = int(blob[j])
            if op == "xor":  x = (seg ^ bj).astype(np.uint8)
            elif op == "sub":x = ((seg - bj) & 255).astype(np.uint8)
            else:            x = ((seg + bj) & 255).astype(np.uint8)
            good &= PR[x]
        idx = np.nonzero(good)[0]
        res[op] = idx
        if len(idx):
            print(f"    {name} {op}: {len(idx)} offsets -> {idx[:8].tolist()}")
            for o in idx[:4]:
                seg = cand[o:o+m].astype(np.int16)
                if op == "xor":   out = bytes((seg ^ blob).astype(np.uint8))
                elif op == "sub": out = bytes(((seg - blob) & 255).astype(np.uint8))
                else:             out = bytes(((seg + blob) & 255).astype(np.uint8))
                print(f"        @0x{o:X}: {out!r}")
    return res

FILES = [RUN+"stage3/wine__w7.bin", RUN+"stage3/seccion_completa.bin",
         RUN+"stage3/wine_unpacked.exe", RUN+"loader_solo_text.exe",
         RUN+"mem_loader.bin", RUN+"stage3/instrs.bin"]
for f in FILES:
    if not os.path.exists(f): continue
    data = np.frombuffer(open(f,"rb").read(), np.uint8)
    if len(data) < 600: continue
    print(f"\n== {os.path.basename(f)} ({len(data)} B) ==")
    for nm, blob in (("BLOB1", B1), ("BLOB2", B2[:160])):
        search(data, blob, nm)
print("\n(vacio en todos = no hay clave de ese tipo en los artefactos)")
