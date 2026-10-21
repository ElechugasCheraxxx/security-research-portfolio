#!/usr/bin/env python3
"""
w_05_keystream.py -- ATAQUE DE TEXTO CONOCIDO.

Hecho: w7_cifrado_7.79MB.bin tiene entropia 8.000 (cifrado) en el primer 80 %,
wine__w7.bin tiene el MISMO rango en claro (entropia 5.5-7.1). Si el
"cifrado" es un XOR con clave, el XOR de ambos ficheros da el flujo de claves
y con el se puede descifrar el resto.

Este script:
  1. mide cuanto difieren los dos ficheros y si comparten estructura
  2. extrae el flujo de claves del tramo descifrado
  3. busca su periodo (autocorrelacion / indice de coincidencia)
  4. intenta el descifrado completo
"""
import os, collections
import numpy as np

HERE = os.path.dirname(os.path.abspath(__file__))
C = np.frombuffer(open(os.path.join(HERE, "w7_cifrado_7.79MB.bin"), "rb").read(), np.uint8)
W = np.frombuffer(open(os.path.join(HERE, "wine__w7.bin"), "rb").read(), np.uint8)
D = np.frombuffer(open(os.path.join(HERE, "descifrado_6M.bin"), "rb").read(), np.uint8)
S = np.frombuffer(open(os.path.join(HERE, "stage3_code.bin"), "rb").read(), np.uint8)
N = min(len(C), len(W))
print("w7_cifrado=%d  wine__w7=%d  descifrado_6M=%d  stage3_code=%d" %
      (len(C), len(W), len(D), len(S)))

# ---- 1. cuanto difieren ----
diff = (C[:N] != W[:N])
print("bytes distintos entre w7_cifrado y wine__w7: %d / %d (%.2f%%)" %
      (int(diff.sum()), N, 100.0 * diff.sum() / N))
# runs de "igual"
runs = []
i = 0
eq = ~diff
while i < N:
    if eq[i]:
        j = i
        while j < N and eq[j]:
            j += 1
        runs.append((i, j - i))
        i = j
    else:
        i += 1
big = [r for r in runs if r[1] >= 4096]
print("tramos >= 4 KB donde los dos ficheros son IDENTICOS: %d" % len(big))
tot = sum(r[1] for r in big)
print("  bytes: %d (%.2f%% del fichero)" % (tot, 100.0 * tot / N))
if big:
    big.sort(key=lambda x: -x[1])
    for lo, ln in big[:12]:
        print("    %08x  %8d B" % (lo, ln))
    # agrupar en regiones contiguas
    print("\n  regiones iguales (agregando tramos separados por < 256 B):")
    agg = []
    for lo, ln in sorted(big):
        if agg and lo - (agg[-1][0] + agg[-1][1]) < 256:
            agg[-1][1] = max(agg[-1][1], lo + ln - agg[-1][0])
        else:
            agg.append([lo, ln])
    for lo, ln in agg:
        if ln >= 4096:
            print("    %08x..%08x  %8d B (%.2f%%)" % (lo, lo + ln, ln, 100.0 * ln / N))

# ---- 2. flujo de claves en el tramo descifrado ----
print()
print("=" * 90)
print("FLUJO DE CLAVES = w7_cifrado XOR wine__w7   (tramo 0..0x70000, el 'claro')")
print("=" * 90)
ks = (C[:0x70000] ^ W[:0x70000])
h = collections.Counter(ks.tolist())
print("bytes distintos en el flujo de claves: %d / 256" % len(h))
print("top-10:", h.most_common(10))
ent = 0.0
n = len(ks)
for c in h.values():
    p = c / n
    ent -= p * np.log2(p)
print("entropia del flujo de claves: %.4f bits/byte (8.0 = aleatorio)" % ent)

# ---- 3. periodo: indice de coincidencia para lags 1..4096 ----
print("\nbuscando periodo del flujo de claves (IC y bytes iguales a cada lag):")
kss = ks[:200000]
best = []
for lag in range(1, 4097):
    if lag >= len(kss):
        break
    a = kss[:-lag]; b = kss[lag:]
    eqpct = float((a == b).mean())
    best.append((eqpct, lag))
best.sort(reverse=True)
print("  top-20 lags por % de bytes iguales:")
for pct, lag in best[:20]:
    print("     lag %5d : %6.3f %%   (azar = %.3f %%)" % (lag, 100 * pct, 100.0 / 256))

# ---- 4. comparar con stage3_code.bin ----
print()
print("=" * 90)
print("COMPARACION con stage3_code.bin (la 'region clara del disco')")
print("=" * 90)
m = min(len(S), len(W))
common = 0
for k in (16, 64, 256, 4096):
    nblk = 0
    hs = set()
    for i in range(0, m - k, k):
        hs.add(S[i:i + k].tobytes())
    hit = 0
    for i in range(0, m - k, k):
        if W[i:i + k].tobytes() in hs:
            hit += 1
    print("  bloques de %5d B de stage3_code presentes en wine__w7 en la MISMA posicion: %d"
          % (k, hit))
    common += hit
# prefijos comunes
cp = 0
while cp < m and S[cp] == W[cp]:
    cp += 1
print("  prefijo comun exacto: %d bytes" % cp)
# ¿esta stage3_code en wine__w7 en otro offset?
for probe in (0x10000, 0x20000, 0x40000, 0x70000, 0x100000):
    if S[0:64].tobytes() in open(os.path.join(HERE, "wine__w7.bin"), "rb").read():
        print("  los primeros 64 B de stage3_code.bin occuren en wine__w7 (offset ignorado)")
        break
raw_w = open(os.path.join(HERE, "wine__w7.bin"), "rb").read()
i = raw_w.find(S[0:64].tobytes())
print("  stage3_code[0:64] en wine__w7 @ %s" % (("%08x" % i) if i >= 0 else "NO"))
i = raw_w.find(S[0x10000:0x10000 + 64].tobytes())
print("  stage3_code[0x10000:+64] en wine__w7 @ %s" % (("%08x" % i) if i >= 0 else "NO"))
