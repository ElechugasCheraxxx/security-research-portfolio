#!/usr/bin/env python3
"""
w_03_contraste.py -- Contrasta el perfil de densidad entre los tres artefactos
candidatos para comprobar cual corresponde al perfil citado en el encargo
(0M:15635  0,5M:74  1M:221 ... 7M:5207).

Calcula varias normalizaciones de chi-cuadrado para no depender de la que
usara el otro agente:
   A) chi2 = sum((c_i - L/256)^2) / L          -> media 255 para datos uniformes
   B) A / 255                                   -> media 1
   C) sum((c_i - L/256)^2)                      -> media 255^2
Ademas entropia Shannon y cociente de bytes iguales.
"""
import os, sys
import numpy as np

HERE = os.path.dirname(os.path.abspath(__file__))
FILES = ["wine__w7.bin", "w7_cifrado_7.79MB.bin", "seccion_completa.bin",
         "stage3_code.bin"]


def prof(path, bs=1 << 19):
    a = np.frombuffer(open(path, "rb").read(), np.uint8)
    N = len(a)
    out = []
    for lo in range(0, N, bs):
        blk = a[lo:lo + bs]
        L = len(blk)
        c = np.bincount(blk, minlength=256).astype(np.float64)
        e = L / 256.0
        s2 = float(((c - e) ** 2).sum())
        p = c[c > 0] / L
        H = float(-(p * np.log2(p)).sum())
        out.append((lo, s2, s2 / 255.0, s2 * 255.0 / L ** 0 * 0 + s2, H,
                    float((blk == blk[0]).sum()) / L))
    return out


TARGET = [15635, 74, 221, 221, 220, 222, 219, 218, 216, 147, 243, 293, 74, 1510, 5207]
print("PERFIL CITADO EN EL ENCARGO (15 ventanas de 512 KB):")
print(TARGET)
print()
for f in FILES:
    p = os.path.join(HERE, f)
    if not os.path.exists(p):
        continue
    r = prof(p)
    print("=" * 100)
    print("%s  (%d bytes)" % (f, os.path.getsize(p)))
    print("  %-9s %12s %10s %8s %8s" % ("off", "A=sum(..)^2", "B=A/255", "entrop", "igual%"))
    for lo, s2, b, _, H, eq in r:
        mark = ""
        if lo // (1 << 19) < len(TARGET):
            k = int(lo // (1 << 19))
            d = abs(b - TARGET[k]) / max(TARGET[k], 1)
            d2 = abs(s2 - TARGET[k]) / max(TARGET[k], 1)
            mark = "   <-- citado=%d  (d%%B=%.2f d%%A=%.2f)" % (TARGET[k], d, d2)
        print("  %08x %12.1f %10.2f %8.3f %8.4f%s" % (lo, s2, b, H, eq, mark))
    print()
