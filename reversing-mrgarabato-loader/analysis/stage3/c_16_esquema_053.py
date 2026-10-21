#!/usr/bin/env python3
"""
c_16_esquema_053.py -- Valida el esquema de ofuscacion de cadenas
   plain[i] = cipher[i] ^ ((0x53 + idx + i) & 0xFF)
contra las cadenas YA descifradas por el analisis previo, y luego lo aplica
a BLOB1 y BLOB2.
"""
import numpy as np, string

RUN = "/root/mrgarabato_analysis/run/"
raw = open(RUN+"stage3/wine__w7.bin","rb").read()
img = open(RUN+"loader_solo_text.exe","rb").read()

def dec(buf, idx, key0=0x53):
    b = np.frombuffer(buf, np.uint8).astype(np.int32)
    i = np.arange(len(b))
    return bytes((b ^ ((key0 + idx + i) & 255)).astype(np.uint8))

print("="*78); print("1. VALIDACION: cadenas conocidas de strings_decodificadas.txt"); print("="*78)
lineas = [l.split() for l in open(RUN+"strings_decodificadas.txt") if l.strip()][:6]
print(lineas)
for off, idx, txt in [(0x00d033,0,"ollydbg.exe"), (0x00d074,0,"ProcessHacker.exe"),
                      (0x00d0c3,0,"tcpview.exe"), (0x00d463,0,"ImmunityDebugger.exe")]:
    for base, nm in ((raw,"dump"), (img,"img")):
        got = dec(base[off:off+len(txt)+2], idx)
        ok = "OK " if txt.encode() in got else "-- "
        print(f"  {nm:5s} 0x{off:06X} idx={idx}: {got!r}   {ok}{txt}")

print("\n  ¿coincide dump<->img en esos offsets?",
      all(raw[o:o+12]==img[o+0x1200:o+0x1200+12] for o in (0xd033,0xd074,0xd0c3)))

print("\n"+"="*78); print("2. BARRIDO DEL ESQUEMA 0x53+i SOBRE BLOB1 Y BLOB2"); print("="*78)
OK = set(range(0x20,0x7F)) | {0,9,10,13}
for nm, off, ln in (("BLOB1",0x227A0,160), ("BLOB2",0x22A50,400)):
    b = raw[off:off+ln]
    best=None
    for idx in range(256):
        for k0 in (0x53,):
            p = dec(b, idx, k0)
            f = sum(1 for x in p if x in OK)/ln
            if best is None or f>best[0]: best=(f,idx,p)
    f,idx,p = best
    print(f"  {nm}: mejor idx={idx} frac_imprimible={f:.3f}")
    print(f"     {p[:64]!r}")
    print(f"     {p[64:128]!r}" if ln>64 else "")

print("\n  mismo barrido pero solo exigiendo que el primer byte sea imprimible:")
for nm, off, ln in (("BLOB1",0x227A0,160),("BLOB2",0x22A50,400)):
    b = raw[off:off+ln]
    idxs = [i for i in range(256) if (b[0] ^ ((0x53+i) & 255)) in OK]
    print(f"  {nm}: idx validos = {idxs}")
    for i in idxs[:3]:
        print(f"     idx={i}: {dec(b,i)[:32]!r}")

print("\n"+"="*78); print("3. ¿Y con el indice i contado desde el FINAL o por campo?"); print("="*78)
def dec2(buf, idx, key0=0x53, per=16, rev=False):
    b = np.frombuffer(buf, np.uint8).astype(np.int32)
    n=len(b); i=np.arange(n)
    j = (i % per) if per else i
    if rev: j = per-1-j
    return bytes((b ^ ((key0 + idx + j) & 255)).astype(np.uint8))
for per in (8,16,32,None):
    for rev in (False,True):
        hits=[]
        for idx in range(256):
            p=dec2(raw[0x227A0:0x22840], idx, per=per, rev=rev)
            f=sum(1 for x in p if x in OK)/160
            if f>0.9: hits.append((idx,f,p))
        if hits:
            print(f"  per={per} rev={rev}: {len(hits)} idx -> {[(h[0],round(h[1],2)) for h in hits[:6]]}")
            print(f"      {hits[0][2][:48]!r}")
print("  (vacio = ninguna variante sirve)")
