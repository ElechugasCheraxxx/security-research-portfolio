#!/usr/bin/env python3
"""
c_04_bruteforce_pos.py
Clave posicional de 16 bytes: fuerza bruta por posicion usando la restriccion
"todos los bytes descifrados son ASCII imprimible".

Modelos probados (clave k[0..15], el mismo para los 10 campos):
  XOR   c = p ^ k        ->  p = c ^ k
  ADD   c = (p + k)%256  ->  p = (c - k)%256
  SUB   c = (p - k)%256  ->  p = (c + k)%256
  ROT   c = (p - k)%256  rot-left  (k = rotacion)
"""
import itertools, sys

d = open("/root/mrgarabato_analysis/run/stage3/wine__w7.bin", "rb").read()
b1 = d[0x227A0:0x227A0+160]
F = [b1[i*16:(i+1)*16] for i in range(10)]

PR = set(range(0x20, 0x7F))          # ASCII imprimible
PR_NUL = PR | {0x00}

def cand_xor(pos, ok):
    return [k for k in range(256) if all((F[i][pos] ^ k) in ok for i in range(10))]
def cand_sub(pos, ok):               # p = c + k
    return [k for k in range(256) if all((F[i][pos] + k) & 0xFF in ok for i in range(10))]
def cand_add(pos, ok):               # p = c - k
    return [k for k in range(256) if all((F[i][pos] - k) & 0xFF in ok for i in range(10))]
def cand_rot(pos, ok):
    out=[]
    for r in range(256):
        okall=True
        for i in range(10):
            v=F[i][pos]
            v=((v<<r)|(v>>(8-r)))&0xFF if r else v
            if v not in ok:
                okall=False; break
        if okall: out.append(r)
    return out

MODELS = [("XOR", cand_xor), ("ADD(c-k)", cand_add), ("SUB(c+k)", cand_sub), ("ROL", cand_rot)]

for okname, ok in (("imprimible", PR), ("imprimible+NUL", PR_NUL)):
    print("="*78)
    print(f"RESTRICCION: {okname}")
    print("="*78)
    for mname, fn in MODELS:
        per = [fn(p, ok) for p in range(16)]
        tot = 1
        for c in per: tot *= max(1, len(c))
        sizes = "/".join(str(len(c)) for c in per)
        flag = "  <== VIABLE" if all(per) and tot < 10**9 else ""
        print(f"\n  {mname:8s} candidatos por posicion: {sizes}   (combinaciones={tot}){flag}")
        if all(per):
            for p in range(16):
                chars = "".join(chr(F[i][p]^0) if False else "" for i in range(0))
            # descifrado con las primeras candidatas
            for combo in itertools.islice(itertools.product(*per), 12):
                key = bytes(combo)
                pt = bytes(F[i][p] ^ key[p] if mname=="XOR" else
                           (F[i][p] - key[p]) & 0xFF if mname=="ADD(c-k)" else
                           (F[i][p] + key[p]) & 0xFF if mname=="SUB(c+k)" else
                           (lambda v,r: ((v<<r)|(v>>(8-r)))&0xFF if r else v)(F[i][p], key[p])
                           for i in range(10) for p in range(16))
                print(f"      key={key.hex()}  ->  {pt!r}")
    print()
