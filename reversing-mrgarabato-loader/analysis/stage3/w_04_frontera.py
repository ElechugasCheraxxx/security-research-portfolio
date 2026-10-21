#!/usr/bin/env python3
"""
w_04_frontera.py -- Localiza las fronteras reales de "claro / cifrado" con
ventanas deslizantes de 4 KB y 64 KB, sobre todos los artefactos candidatos.
Ademas: donde caen las cadenas clave dentro de cada uno.
"""
import os, re, collections
import numpy as np

HERE = os.path.dirname(os.path.abspath(__file__))
CAND = ["wine__w7.bin", "wine_unpacked.exe", "descifrado_6M.bin",
        "w7_cifrado_7.79MB.bin", "stage3_code.bin", "stage3_code.exe",
        "mem_loader.bin", "unpacked_loader.exe"]


def ent(blk):
    c = np.bincount(blk, minlength=256).astype(np.float64)
    p = c[c > 0] / len(blk)
    return float(-(p * np.log2(p)).sum())


def chi2n(blk):
    c = np.bincount(blk, minlength=256).astype(np.float64)
    return float(((c * 255.0 / len(blk) - 1.0) ** 2).sum())


ANCHORS = [b"MRGARABATO", b"/Auth/api/neural_login.php", b"MiDriver",
           b"WinDivert", b"Waiting for emulator", b"Injection Process",
           b"PhoneHx", b"HD-Player.exe", b"hwid_affected", b"NeuralAuth"]

for f in CAND:
    p = os.path.join(HERE, f)
    if not os.path.exists(p):
        continue
    a = np.frombuffer(open(p, "rb").read(), np.uint8)
    raw = open(p, "rb").read()
    N = len(a)
    print("=" * 110)
    print("%s  %d bytes" % (f, N))
    # ventanas deslizantes de 64 KB, paso 64 KB
    B = 1 << 16
    prof = [(lo, ent(a[lo:lo + B]), chi2n(a[lo:lo + B])) for lo in range(0, N, B)]
    H = np.array([x[1] for x in prof])
    C = np.array([x[2] for x in prof])
    hi = H >= 7.5
    # bloques contiguos de alta entropia
    runs = []
    st = None
    for i, v in enumerate(hi):
        if v and st is None:
            st = i
        elif not v and st is not None:
            runs.append((st * B, i * B)); st = None
    if st is not None:
        runs.append((st * B, len(hi) * B))
    lowruns = []
    st = None
    for i, v in enumerate(hi):
        if not v and st is None:
            st = i
        elif v and st is not None:
            lowruns.append((st * B, i * B)); st = None
    if st is not None:
        lowruns.append((st * B, len(hi) * B))
    print("  entropia: min=%.3f max=%.3f media=%.3f" % (H.min(), H.max(), H.mean()))
    print("  ventanas 64K con entropia <7.5 (posible texto plano): %d / %d  = %.1f%%"
          % (len(hi) - int(hi.sum()), len(hi), 100.0 * (len(hi) - hi.sum()) / len(hi)))
    print(" Runs BAJA entropia (claro), >0: ")
    for lo, hi2 in lowruns:
        if hi2 - lo >= 0x1000:
            seg = a[lo:hi2]
            print("    %08x..%08x  %8d B (%6.2f%%)  entropa media %.3f  nul%% %.3f ascii%% %.3f"
                  % (lo, hi2, hi2 - lo, 100.0 * (hi2 - lo) / N,
                     ent(seg), float((seg == 0).mean()),
                     float(((seg >= 32) & (seg < 127)).mean())))
    if len(lowruns) == 0 or all(b - a_ < 0x1000 for a_, b in lowruns):
        print("    (ninguno >= 4 KB)")
    # perfil de entropia en 64 bloques iguales para ver el degradado
    print("  entropia por octil (64 bloques iguales de %.0f KB):" % (N / 64 / 1024))
    segs = []
    for k in range(64):
        lo = k * N // 64
        hi2 = (k + 1) * N // 64
        segs.append(ent(a[lo:hi2]))
    print("   " + " ".join("%.2f" % s for s in segs))
    # anclas
    hits = []
    for s in ANCHORS:
        i = raw.find(s)
        j = raw.find(s, i + 1) if i >= 0 else -1
        if i >= 0:
            hits.append((s.decode(errors="replace"), i, j))
    if hits:
        print("  ANCLAS:")
        for s, i, j in hits:
            extra = " (+%d)" % j if j >= 0 else ""
            print("    %-32s @ %08x%s" % (s, i, extra))
    else:
        print("  ANCLAS: ninguna encontrada")
    print()
