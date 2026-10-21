#!/usr/bin/env python3
"""
c_13_keystream_packer.py -- Recupera el keystream del desempaquetador
   K[i] = memoria[i] XOR disco[i]
sobre 7.79 MB, y lo analiza (periodo, distribucion, si es rampa).
Ademas: el XOR de un par de ficheros con regions conocidas en claro.
"""
import numpy as np, collections

RUN = "/root/mrgarabato_analysis/run/stage3/"
mem = np.frombuffer(open(RUN+"wine__w7.bin","rb").read(), np.uint8)
dsk = np.frombuffer(open(RUN+"seccion_completa.bin","rb").read(), np.uint8)
n = min(len(mem), len(dsk))
K = mem[:n] ^ dsk[:n]
print("keystream recuperado:", n, "bytes")
h = np.bincount(K, minlength=256)
nz = np.nonzero(h)[0]
print("valores distintos:", len(nz), " rango:", hex(nz.min()), hex(nz.max()))
ent = -float((h/h.sum()*np.log2(h/h.sum() + 1e-12)).sum())
print("entropia: %.4f bits/byte" % ent)
print("top-10:", [(hex(v), int(h[v])) for v in np.argsort(-h)[:10]])
print("chi2/u = %.3f" % (float(((h - n/256)**2).sum() / (n/256)) / 1.0))

def ac(seq, maxp=4096, step=1):
    seq = seq.astype(np.int32)
    best = []
    for p in range(1, maxp, step):
        m = len(seq)-p
        if m <= 0: break
        # coincidecia exacta (no correlacion) para detectar repeticion literal
        best.append((float((seq[:m] == seq[p:]).mean()), p))
    best.sort(reverse=True)
    return best[:8]

print("\nautocorrelacion EXACTA del keystream (top):", [(f"P{p}", f"{r:.4f}") for r,p in ac(K, 2048, 1)])
print("primeros 64 bytes del keystream:", K[:64].hex())
print("bytes 0x20000-0x20040:", K[0x20000:0x20040].hex())

# ¿los primeros 4 bytes del empaquetado son los de una clave known?
print("\n¿el keystream es una rampa? k[i]=(a+b*i)&255")
for b in range(256):
    a = int(K[0])
    pred = (a + b*np.arange(4096)) & 255
    if (pred == K[:4096]).all():
        print("   SI: a=0x%02X b=%d" % (a, b))

# ¿keystream constante?
top = np.argsort(-h)[:5]
for v in top:
    frac = h[v]/n
    print(f"  valor 0x{v:02X}: {h[v]} ({frac*100:.2f}%)")

# ¿el keystream aparece dentro del propio volcado?
raw = open(RUN+"wine__w7.bin","rb").read()
k32 = K[:32].tobytes()
print("\n¿los primeros 32 bytes del keystream estan en el volcado? ->", raw.find(k32))
print("¿estan en disco? ->", open(RUN+"seccion_completa.bin","rb").read().find(k32))
