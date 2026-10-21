#!/usr/bin/env python3
"""
c_18_prng.py -- ExHAUSTIVO sobre generadores de keystream de 1 byte:
   (a) LCG   k[i] = (A*k[i-1] + C) mod 256     (256^3 = 16.7M combinaciones)
   (b) LFSR8 k[i] = (k[i-1] >> 1) ^ (-(k[i-1]&1) & POLY)
para XOR, ADD y SUB sobre BLOB1 y BLOB2.
Ademas: periodo P (cualquiera) con 100% imprimible; RC4 con claves candidatas;
transformaciones encadenadas sobre los 160 bytes correctos.
"""
import numpy as np, itertools, sys

RUN = "/root/mrgarabato_analysis/run/"
raw = open(RUN+"stage3/wine__w7.bin","rb").read()
B1 = np.frombuffer(raw[0x227A0:0x22840], np.uint8)
B2 = np.frombuffer(raw[0x22A50:0x22BE0], np.uint8)
PR = np.zeros(256, bool); PR[0x20:0x7F] = True; PR[[0,9,10,13]] = True
PRs = np.zeros(256, bool); PRs[0x20:0x7F] = True   # sin NUL

A_ = np.arange(256, dtype=np.uint8)[:, None, None]
C_ = np.arange(256, dtype=np.uint8)[None, :, None]
S_ = np.arange(256, dtype=np.uint8)[None, None, :]
np.broadcast_to(A_, (256,256,256))

def lcg_scan(blob, ops=("xor","add","sub"), nbytes=40, label=""):
    k0 = np.broadcast_to(S_, (256,256,256)).astype(np.uint8).copy()
    alive = np.ones((256,256,256), bool)
    hits = []
    n = min(nbytes, len(blob))
    for t in range(n):
        # genera k_t para los que siguen vivos
        st = k0.astype(np.uint16)
        ks = ((A_.astype(np.uint16)*st + C_.astype(np.uint16)) & 255).astype(np.uint8)
        cb = np.uint8(blob[t])
        good = np.zeros_like(alive)
        for op in ops:
            if   op == "xor": x = ks ^ cb
            elif op == "add": x = (cb.astype(np.int16) - ks.astype(np.int16)).astype(np.uint8) & 255
            else:             x = (cb.astype(np.int16) + ks.astype(np.int16)).astype(np.uint8) & 255
            good |= (PRs[x] & alive)
        alive = good
        # avanza el estado
        k0 = ((A_.astype(np.uint8)*k0 + C_.astype(np.uint8)).astype(np.uint8))
        if not alive.any():
            break
    idx = np.argwhere(alive)
    print(f"  LCG {label}: {len(idx)}o byte(s) sobreviven tras {t+1} bytes")
    return idx

def gen_lcg(seed, A, C, n):
    out = np.empty(n, np.uint8); s = seed
    for i in range(n):
        s = (A*s + C) & 255; out[i] = s
    return out

def lfsr_scan(blob, nbytes=40):
    alive = np.ones((256,255), bool)  # (seed, poly)
    poly = np.arange(1,256, dtype=np.uint8)[None,:]
    st = np.broadcast_to(np.arange(256,dtype=np.uint8)[:,None], (256,255)).copy()
    n = min(nbytes, len(blob))
    for t in range(n):
        lsb = (st & 1).astype(bool)
        ks = ((st >> 1) ^ (lsb * poly)).astype(np.uint8)
        cb = np.uint8(blob[t])
        good = np.zeros_like(alive)
        for op in ("xor","add","sub"):
            if   op == "xor": x = ks ^ cb
            elif op == "add": x = (cb.astype(np.int16)-ks.astype(np.int16)).astype(np.uint8)&255
            else:             x = (cb.astype(np.int16)+ks.astype(np.int16)).astype(np.uint8)&255
            good |= (PRs[x] & alive)
        alive = good
        lsb = (st & 1).astype(bool)
        st = ((st >> 1) ^ (lsb * poly)).astype(np.uint8)
        if not alive.any(): break
    idx = np.argwhere(alive)
    print(f"  LFSR8: {len(idx)}o byte sobrevive tras {t+1}")
    return idx

print("="*78); print("A. LCG de 1 byte (exhaustivo A,C,seed = 256^3)"); print("="*78)
for nm, blob in (("BLOB1", B1), ("BLOB2", B2)):
    idx = lcg_scan(blob, nbytes=40, label=nm)
    if len(idx):
        for (s,a,c) in idx[:20]:
            k = gen_lcg(int(s), int(a), int(c), len(blob))
            for op in ("xor","add","sub"):
                if op=="xor": p = blob ^ k
                elif op=="add": p = ((blob.astype(np.int16)-k.astype(np.int16))&255).astype(np.uint8)
                else: p = ((blob.astype(np.int16)+k.astype(np.int16))&255).astype(np.uint8)
                f = PR[p].mean()
                if f > 0.9:
                    print(f"    seed=0x{s:02X} A=0x{a:02X} C=0x{c:02X} {op} frac={f:.3f} {bytes(p)!r}")

print("="*78); print("B. LFSR de 8 bits (exhaustivo poly,seed)"); print("="*78)
for nm, blob in (("BLOB1", B1), ("BLOB2", B2)):
    idx = lfsr_scan(blob, nbytes=40)
    if len(idx):
        for (s,pl) in idx[:20]:
            st=int(s); k=np.empty(len(blob),np.uint8)
            for i in range(len(blob)):
                st = (st>>1) ^ ((0xFF if st&1 else 0) & int(pl)); k[i]=st
            for op in ("xor","add","sub"):
                if op=="xor": p = blob ^ k
                elif op=="add": p = ((blob.astype(np.int16)-k.astype(np.int16))&255).astype(np.uint8)
                else: p = ((blob.astype(np.int16)+k.astype(np.int16))&255).astype(np.uint8)
                f = PR[p].mean()
                if f > 0.9:
                    print(f"    seed=0x{s:02X} poly=0x{pl:02X} {op} frac={f:.3f} {bytes(p)!r}")

print("="*78); print("C. CLAVE PERIODICA DE LONGITUD P (XOR/ADD/SUB, 100% imprimible)"); print("="*78)
for P in (8,10,12,16,20,24,32,40,48,64,80,160):
    n=len(B1)
    if n % P: 
        pass
    for op in ("xor","add","sub"):
        viable = True; tot=1
        for j in range(P):
            col = B1[j::P]
            if len(col) < 2:
                cand = [k for k in range(256)]
            else:
                ci = col.astype(np.int16)
                if op=="xor":   cand=[k for k in range(256) if PRs[(ci^k).astype(np.uint8)].all()]
                elif op=="add": cand=[k for k in range(256) if PRs[((ci-k)&255).astype(np.uint8)].all()]
                else:           cand=[k for k in range(256) if PRs[((ci+k)&255).astype(np.uint8)].all()]
            if not cand: viable=False; break
            tot *= len(cand)
        if viable:
            print(f"  P={P:3d} {op:4s}: VIABLE, {tot} combinaciones")
print("  (solo se listan los P con solucion)")

print("="*78); print("D. TRANSFORMACIONES ENCADENADAS (160 bytes correctos)"); print("="*78)
def show(nm, p):
    f = PR[np.frombuffer(bytes(p), np.uint8)].mean()
    if f > 0.85: print(f"   {f:.2f} {nm}: {bytes(p)!r}")
for k in range(1, 40):
    x=B1[:160-k]; y=B1[k:]
    show(f"p=c[i]^c[i-{k}]", bytes(x^y))
    show(f"p=(c[i]-c[i-{k}])&255", bytes(((x.astype(np.int16)-y.astype(np.int16))&255).astype(np.uint8)))
    show(f"p=(c[i]+c[i-{k}])&255", bytes(((x.astype(np.int16)+y.astype(np.int16))&255).astype(np.uint8)))
print("  (vacio = ninguna cadena de 16+ bytes da texto)")

print("="*78); print("E. RC4 CON CLAVES CANDIDATAS"); print("="*78)
def rc4(key, n):
    S=list(range(256)); j=0; out=bytearray()
    for i in range(256):
        j=(j+S[i]+key[i%len(key)])&255; S[i],S[j]=S[j],S[i]
    i=j=0
    for _ in range(n):
        i=(i+1)&255; j=(j+S[i])&255; S[i],S[j]=S[j],S[i]
        out.append(S[(S[i]+S[j])&255])
    return bytes(out)
CLAVES = ["APP_SECRET","OWNER_ID","MrGarabato","urus_bypass","YourApplication","PhoneHx",
          "Ignyx","NeuralAuth/1.0","7RobSZuyx23L677ulvLD1Cq","YX9Y0KWPU6","Nf7D?!r+WMtb3Z&s3_",
          "PhoneHx\\MrGarabato","SOFTWARE\\Microsoft\\PhoneHx\\MrGarabato","MRGARABATO",
          "neural_login.php","token","app_secret","14ddg0941cvah.exe","34dbbmddg71c.exe",
          "SecurityHx","FakeLag","panel","FreeFire","MrGarabato-LoaderAdvanced"]
CLAVES += ["APP_SECRET","app_secret","owner_id","Subscription","neural_auth"]
best=[]
for nm, blob in (("BLOB1",B1),("BLOB2",B2)):
    for k in CLAVES:
        kk=k.encode('latin1','ignore')
        ks=rc4(kk,len(blob))
        for op in ("xor","add","sub"):
            if op=="xor": p=blob^np.frombuffer(ks,np.uint8)
            elif op=="add": p=((blob.astype(np.int16)-np.frombuffer(ks,np.int8).astype(np.int16))&255).astype(np.uint8)
            else: p=((blob.astype(np.int16)+np.frombuffer(ks,np.int8).astype(np.int16))&255).astype(np.uint8)
            f=PR[p].mean()
            if f>0.5:
                print(f"  {nm} clave={k!r} {op} frac={f:.2f} {bytes(p[:64])!r}")
                best.append(f)
print("  (vacio = ninguna clave candidata funciona)")
