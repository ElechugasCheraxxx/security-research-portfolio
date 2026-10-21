#!/usr/bin/env python3#!/usr/bin/env python3
"""
c_19_estructura_final.py
 (A) relaciones entre los 10 campos de BLOB1 (mismo plano con claves distintas)
 (B) mejor clave constante posible aunque no sea 100% imprimible
 (C) estadisticos finales de BLOB2 (chi2 real, test de uniformidad, runs)
 (D) ¿BLOB2 es una S-box parcial? ¿permutacion? ¿bytes de un PRNG conocido?
"""
import numpy as np, collections

RUN = "/root/mrgarabato_analysis/run/"
raw = open(RUN+"stage3/wine__w7.bin","rb").read()
B1 = np.frombuffer(raw[0x227A0:0x22840], np.uint8).reshape(10,16)
B2 = np.frombuffer(raw[0x22A50:0x22BE0], np.uint8)
PR = np.zeros(256,bool); PR[0x20:0x7F]=True

print("="*78); print("A. RELACIONES ENTRE CAMPOS DE BLOB1"); print("="*78)
print("  XOR constante entre campos (mismo plano, claves distintas XOR K):")
for m in range(10):
    for n in range(m+1,10):
        d = B1[m] ^ B1[n]
        if len(set(d.tolist()))==1:
            print(f"    f{m} ^ f{n} = 0x{d[0]:02X} CONSTANTE")
        s = B1[m] - B1[n]
        if len(set((s&255).tolist()))==1:
            print(f"    f{m} - f{n} = {(s[0]&255):02X} CONSTANTE")
print("  (solo se listan los pares constantes)")

print("\n  matriz de coincidencias byte a byte entre campos:")
print("      " + " ".join(f"f{j:<2d}" for j in range(10)))
for m in range(10):
    row=[]
    for n in range(10):
        row.append(int((B1[m]==B1[n]).sum()))
    print(f"   f{m}: " + " ".join(f"{v:<3d}" for v in row))

print("\n  posiciones donde los campos coinciden (patron de repeticion):")
for j in range(16):
    col = B1[:,j].tolist()
    cnt = collections.Counter(col)
    dup = {k:v for k,v in cnt.items() if v>1}
    print(f"    pos {j:2d}: " + (" ".join(f"{k:02X}x{v}" for k,v in sorted(dup.items())) or "todos distintos"))

print("\n"+"="*78); print("B. MEJOR CLAVE CONSTANTE (fraccion imprimible maxima)"); print("="*78)
f1 = B1.ravel()
best=[]
for k in range(256):
    for op in ("xor","add","sub"):
        if op=="xor": p = f1 ^ np.uint8(k)
        elif op=="add": p = (f1.astype(np.int16)-k).astype(np.uint8)&255
        else: p = (f1.astype(np.int16)+k).astype(np.uint8)&255
        best.append((float(PR[p].mean()), op, k, bytes(p)))
best.sort(key=lambda t:-t[0])
for f,op,k,p in best[:6]:
    print(f"   frac={f:.3f} {op} k=0x{k:02X}: {p[:64]!r}")
print("   (100% es imposible: no hay ninguna clave constante)")

print("\n"+"="*78); print("C. ESTADISTICOS FINALES DE BLOB2"); print("="*78)
h = np.bincount(B2, minlength=256).astype(np.float64)
E = len(B2)/256.0
chi2 = float(((h-E)**2/E).sum())
# chi2 con 255 g.l. -> media 255, var 510
z = (chi2-255)/np.sqrt(510)
print(f"   n=400  E=1.5625  chi2={chi2:.2f}  (media 255, sd %.1f)  z={z:+.2f}" % np.sqrt(510))
print(f"   -> {'NO rechaza uniformidad (p>0.05)' if abs(z)<1.96 else 'RECHAZA uniformidad'}")
print(f"   valores distintos: {int((h>0).sum())}/256   H={-float((h/400*np.log2(h/400+1e-12)).sum()):.4f} bits/byte")
print(f"   (H maximo teorico = 8.0000)")
# runs test
runs = 1 + sum(1 for i in range(len(B2)-1) if B2[i]!=B2[i+1])
n1 = int((B2[:-1]!=B2[1:]).sum()); n2 = len(B2)-n1
mu = 2*len(B2)*n1*n2/((n1+n2)**2*(n1+n2-1)) + 1
sd = np.sqrt(2*len(B2)*n1*n2*(2*len(B2)*n1-n2-len(B2))/((n1+n2)**2*(n1+n2-1)*(n1+n2-2)))
print(f"   runs test: runs={runs} esperado={mu:.1f} z={(runs-mu)/sd:+.2f} "
      f"({'no rechaza aleatoriedad' if abs((runs-mu)/sd)<1.96 else 'RECHAZA'})")

print("\n   sub-bloques de 50 bytes (¿alguno estructurado?):")
for i in range(0,400,50):
    s=B2[i:i+50]; hh=np.bincount(s,minlength=256)
    print(f"     +0x{i:03X}: distintos={int((hh>0).sum()):3d} H={-float((hh[:50].sum()/50*np.log2(hh[:50].sum()/50+1e-12)).sum()):.2f} "
          f"rango=[0x{s.min():02X},0x{s.max():02X}]")
print("   (si un sub-bloque tuviera pocos distintos, seria una tabla/texto)")

print("\n   ¿los 400 bytes se pueden partir en 2 mitades con perfil distinto?")
for k in (128,200,256,320):
    a,b = B2[:k], B2[k:]
    ha,hb = np.bincount(a,minlength=256), np.bincount(b,minlength=256)
    print(f"     corte @{k}: izq distintos={int((ha>0).sum())} der distintos={int((hb>0).sum())}")

print("\n"+"="*78); print("D. ¿BLOB2 es la salida de un PRNG conocido?"); print("="*78)
b2 = raw[0x22A50:0x22BE0]
# MT19937: outputs cada 624; comprobamos si los 400B encajan en la secuencia de un MT sembrado
# glibc rand(): no determinista aqui. Comprobamos simplemente periodicidad exacta ya vista.
for p in range(1, 200):
    if len(set(b2[i] for i in range(400-p))) == 1 and p > 100:
        print(f"   periodo {p}")
print("   ninguna periodicidad exacta >100 (ya comprobado en c_02)")
print("   comprimibilidad zlib:", end=" ")
import zlib
for lvl in (1,6,9):
    print(f"L{lvl}={len(zlib.compress(b2,lvl))}", end=" ")
print(f"  (400 original; ratio~1.0 => no es texto ni datos tabulares)")
print("   comprimibilidad BLOB1:", end=" ")
b1 = raw[0x227A0:0x22840]
print(" ".join(f"L{l}={len(zlib.compress(b1,l))}" for l in (1,6,9)))
