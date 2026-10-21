#!/usr/bin/env python3
"""
c_11_rango_clave.py -- Restricciones FUERTES que impone el rango del cifrado.

Hecho: los bytes del BLOB1 viven en [0xB0,0xFF] U {0x8E,0x8F,0x00}.
Si el cifrado es  c = (p + k) mod 256  con p ASCII imprimible:
    para TODOS los p:  c >= 0xB0  =>  k >= 0xB0 - 0x20 = 0x90   (para el p minimo)
                       c >= 0xB0  =>  k >= 0xB0 - 0x7E = 0x32   (para el p maximo)
    y sin desbordamiento: k <= 0xFF - 0x20 = 0xDF
    => k debe caer en [0x90, 0xDF].
Lo mismo por posicion. Se交的 con la restriccion "los 10 campos descifran a imprimible".
"""
import numpy as np, string

DUMP = "/root/mrgarabato_analysis/run/stage3/wine__w7.bin"
d = open(DUMP, "rb").read()
B = np.frombuffer(d[0x227A0:0x22840], np.uint8).reshape(10, 16)   # 10 campos x 16 bytes
print("BLOB1 =", B.shape, " bytes totales", B.size)

PR = np.zeros(256, bool); PR[0x20:0x7F] = True

print("\n" + "="*76)
print("A) ADD  c = (p + k) mod 256 ;  k restringido a [0x90,0xDF] por el rango")
print("="*76)
sols = []
for j in range(16):
    col = B[:, j].astype(np.int32)
    cand = [k for k in range(0x90, 0xE0) if PR[((col - k) & 255).astype(np.uint8)].all()]
    sols.append(cand)
    print(f"  pos {j:2d}  ({len(cand):2d} k): " + " ".join(f"{k:02X}" for k in cand[:24]))
tot = 1
for c in sols: tot *= max(1, len(c))
print(f"  -> combinaciones = {tot:.3g}")
if all(sols):
    ENG=[8.167,1.492,2.782,4.253,12.702,2.228,2.015,6.094,6.966,0.153,0.772,4.025,
         2.406,6.749,7.507,1.929,0.095,5.987,6.327,9.056,2.758,0.978,2.360,0.150,1.974,0.074]
    W=np.full(256,0.004)
    for ch,f in zip(string.ascii_lowercase,ENG): W[ord(ch)]=f/100
    W[ord(' ')]=0.17
    base=W[0x20:0x7F].mean()
    import itertools
    scored=[]
    for combo in itertools.islice(itertools.product(*sols), 2_000_000):
        p = (B.astype(np.int32) - np.array(combo, np.int32)) & 255
        sc = W[p].mean()/base
        scored.append((sc, combo, bytes(p.astype(np.uint8).ravel())))
    scored.sort(key=lambda t:-t[0])
    print(f"  evaluados {len(scored)}; top:")
    for sc, combo, pt in scored[:8]:
        print(f"    score={sc:.3f} key={bytes(combo).hex()}  {pt!r}")

print("\n" + "="*76)
print("B) XOR  c = p ^ k  : ¿existe k por posicion con los 10 imprimibles Y c>=0xB0?")
print("="*76)
for j in range(16):
    col = B[:, j]
    allk = [k for k in range(256) if PR[col ^ np.uint8(k)].all()]
    print(f"  pos {j:2d}: {len(allk):3d} k -> {' '.join(f'{k:02X}' for k in allk[:16])}"
          + ("   <-- VACIO" if not allk else ""))

print("\n" + "="*76)
print("C) ¿Existe clave de longitud L (cualquiera) tal que el plano sea ANCHO?")
print("   Para p ancho, los bytes IMPARES del plano son 0. Con clave periodica de")
print("   longitud L, c[i] en las posiciones i==j (mod L) con j impar seria = k[j],")
print("   luego todos iguales. Se comprueba para todo L.")
print("="*76)
flat = B.ravel()
for L in [16, 32, 48, 64, 80, 96, 128, 160]:
    bad = 0
    for j in range(L):
        col = flat[j::L]
        if len(set(col.tolist())) > 1: bad += 1
    print(f"  L={L:4d}: {bad}/{L} posiciones con valores distintos "
          f"({'INCOMPATIBLE con plano ancho' if bad else 'compatible'})")

print("\n" + "="*76)
print("D) Histograma: ¿la forma es compatible con texto tras clave constante?")
print("="*76)
h = np.bincount(flat, minlength=256)
ENG=[8.167,1.492,2.782,4.253,12.702,2.228,2.015,6.094,6.966,0.153,0.772,4.025,
     2.406,6.749,7.507,1.929,0.095,5.987,6.327,9.056,2.758,0.978,2.360,0.150,1.974,0.074]
E=np.zeros(256); E[0x20]=0.17
for ch,f in zip(string.ascii_lowercase,ENG): E[ord(ch)]=f/100
def chi(vals):
    n=len(vals); k=len(set(vals.tolist()))
    if k==0: return 0
    e=n/k
    return float((( np.bincount(vals,minlength=256)[np.unique(vals)] - e)**2).sum()/e), k
best=[]
for k in range(256):
    for nm, tr in (("xor", lambda v,k: v ^ k), ("add", lambda v,k: (v - k) & 255)):
        p = tr(flat.copy(), k).astype(np.uint8)
        if not PR[p].all(): continue
        c,kk = chi(p); best.append((c, nm, k, bytes(p)))
best.sort()
print(f"  solo {len(best)} claves constantes dan 100% imprimible")
for c, nm, k, p in best[:5]:
    print(f"    chi2={c:.1f} {nm} k=0x{k:02X} {p[:64]!r}")
print("  (referencia: chi2/u ~1 es uniforme; texto ingles da >>10 con k'Ã³mo de tamano)")

print("\n" + "="*76)
print("E) Proyecciones del byte: ¿alguna da un alfabeto pequeno?")
print("="*76)
for nm, f in (("c & 0x0F", lambda v: v & 0x0F), ("c & 0x1F", lambda v: v & 0x1F),
              ("c & 0x3F", lambda v: v & 0x3F), ("c & 0x4F", lambda v: v & 0x4F),
              ("c & 0x7F", lambda v: v & 0x7F), ("c - 0xB0", lambda v: (v - 0xB0) & 255),
              ("c >> 4", lambda v: v >> 4), ("c >> 3", lambda v: v >> 3),
              ("~c", lambda v: (~v) & 255), ("bitrev", lambda v: np.array(
                  [int(f"{x:08b}"[::-1],2) for x in v], np.uint8))):
    t = f(flat.copy())
    u, cnt = np.unique(t, return_counts=True)
    ent = -float((cnt/cnt.sum() * np.log2(cnt/cnt.sum())).sum())
    print(f"  {nm:10s}: distintos={len(u):3d}  entropia={ent:.2f} bits  "
          f"max_freq={cnt.max()}  rango=[{u.min()},{u.max()}]")
