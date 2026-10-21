#!/usr/bin/env python3
"""
w_02_regiones.py -- Clasificacion de regiones del volcado de Wine por densidad.

Herramientas por bloque de 512 KB (y refinado a 64 KB / 4 KB):
  * chi2/255 : la metrica del enunciado (bytes iguales / bytes distintos)
  * entropia Shannon (bits/byte)
  * fraccion de bytes NUL
  * fraccion de bytes imprimibles ASCII
  * fraccion de `.byte` (zonas que capstone NO desensambla)
  * fraccion de instrucciones de E/S de puerto (in/out/ins/outs) y de
    instrucciones privilegiadas (cli/sti/hlt/wait) -- indicadores clasicos de
    que lo que se esta desensamblando NO es codigo.
"""
import os, sys, json, collections
import numpy as np

HERE = os.path.dirname(os.path.abspath(__file__))
BLOB = os.path.join(HERE, "wine__w7.bin")
data = open(BLOB, "rb").read()
N = len(data)

z = np.load(os.path.join(HERE, "w_cache.npz"))
off, size, mid, tgt = z["off"], z["size"], z["mid"], z["tgt"]
mnems = [str(x) for x in z["mnems"]]
MID = {m: i for i, m in enumerate(mnems)}
PORT = set(i for i, m in enumerate(mnems)
           if m in ("in", "out", "insb", "insd", "insw", "outsb", "outsd", "outsw"))
PRIV = set(i for i, m in enumerate(mnems)
           if m in ("cli", "sti", "hlt", "wait"))
BYTE = MID[".byte"]
CALLRET = set(MID[m] for m in ("ret", "retf", "retfq") if m in MID)

arr = np.frombuffer(data, np.uint8)
print("blob %d bytes (%.3f MB)\n" % (N, N / 1e6))


def chi2(block):
    c = np.bincount(block, minlength=256).astype(np.float64)
    c *= 255.0 / max(len(block), 1)
    return float(((c - 1.0) ** 2).sum())


def entropy(block):
    c = np.bincount(block, minlength=256).astype(np.float64)
    p = c[c > 0] / len(block)
    return float(-(p * np.log2(p)).sum())


def region_table(bs, label):
    rows = []
    n = (N + bs - 1) // bs
    # pre-indexa instrucciones por bloque para contar por bloque
    ib = off // bs
    for b in range(n):
        lo = b * bs
        hi = min((b + 1) * bs, N)
        blk = arr[lo:hi]
        sel = np.nonzero((ib == b))[0]
        tot = len(sel)
        nb = int((mid[sel] == BYTE).sum())
        port = int(np.isin(mid[sel], list(PORT)).sum()) if PORT else 0
        priv = int(np.isin(mid[sel], list(PRIV)).sum()) if PRIV else 0
        cr = int(np.isin(mid[sel], list(CALLRET)).sum()) if CALLRET else 0
        rows.append(dict(
            off=lo, size=hi - lo,
            chi2=round(chi2(blk), 1),
            ent=round(entropy(blk), 3),
            nul=round(float((blk == 0).sum()) / len(blk), 4),
            pri=round(float(((blk >= 32) & (blk < 127)).sum()) / len(blk), 4),
            instr=tot,
            pct_byte=round(100.0 * nb / max(tot, 1), 2),
            pct_port=round(100.0 * port / max(tot, 1), 2),
            pct_priv=round(100.0 * priv / max(tot, 1), 2),
            instr_per_kb=round(tot * 1024.0 / (hi - lo), 1),
            pct_ret=round(100.0 * cr / max(tot, 1), 2),
        ))
    return rows


print("=" * 120)
print("PERFIL POR 512 KB (chi2/255 : ~1 = uniforme/cifrado, >74 = texto plano)")
print("=" * 120)
r512 = region_table(1 << 19, "512K")
print("%-9s %-9s %-7s %-7s %-7s %-8s %-8s %-8s %-8s %-7s" %
      ("offset", "chi2", "entrop", "nul%", "ascii%", "instr", "i/KB", "%byte", "%port", "%ret"))
for r in r512:
    print("%08x %9.1f %7.3f %7.3f %7.3f %8d %8.1f %8.2f %8.2f %7.2f" %
          (r["off"], r["chi2"], r["ent"], r["nul"], r["pri"], r["instr"],
           r["instr_per_kb"], r["pct_byte"], r["pct_port"], r["pct_ret"]))

print()
print("=" * 120)
print("PERFIL POR 64 KB")
print("=" * 120)
r64 = region_table(1 << 16, "64K")
print("%-9s %-9s %-7s %-7s %-7s %-8s %-8s %-8s %-8s %-7s" %
      ("offset", "chi2", "entrop", "nul%", "ascii%", "instr", "i/KB", "%byte", "%port", "%ret"))
for r in r64:
    print("%08x %9.1f %7.3f %7.3f %7.3f %8d %8.1f %8.2f %8.2f %7.2f" %
          (r["off"], r["chi2"], r["ent"], r["nul"], r["pri"], r["instr"],
           r["instr_per_kb"], r["pct_byte"], r["pct_port"], r["pct_ret"]))

# ---- distribucion de chi2 en ventanas deslizantes de 512 KB ----
W = 1 << 19
w = N - W + 1
step = 4096
vals = []
cs = np.cumsum(arr.astype(np.int64))
# histogramas acumuladas para velocidad
print()
print("=" * 120)
print("HISTOGRAMA chi2/255 en ventanas deslizantes de 512 KB (paso 4 KB)")
print("=" * 120)
hs = []
pos = 0
CH = 256
# histograma acumulado por bloques de 4096 para no recalcular
blk = arr[:(N // 4096) * 4096].reshape(-1, 4096)
hb = np.stack([np.bincount(x, minlength=256) for x in blk])  # (nblk,256)
hb = np.vstack([hb, np.zeros((1, 256), np.int64)])
cum = np.cumsum(hb, axis=0)
k = 0
for s in range(0, N - W + 1, step):
    b0 = s // 4096
    b1 = (s + W) // 4096
    c = cum[b1 + 1] - cum[b0]
    c = c * (255.0 / W)
    v = float(((c - 1.0) ** 2).sum())
    hs.append((s, v))
hs = np.array(hs)
bins = [0, 1, 2, 5, 10, 20, 50, 74, 100, 150, 250, 500, 1500, 6000, 20000, 1e9]
h = np.histogram(hs[:, 1], bins=bins)[0]
for i in range(len(bins) - 1):
    print("   chi2 %8.0f .. %8.0f : %5d ventanas (%5.1f%%)" %
          (bins[i], bins[i + 1], h[i], 100.0 * h[i] / len(hs)))

json.dump({"per_512k": r512, "per_64k": r64,
           "ventanas": [[int(a), round(float(b), 1)] for a, b in hs]},
          open(os.path.join(HERE, "w_regiones.json"), "w"), indent=1)
print("\nescrito w_regiones.json")
