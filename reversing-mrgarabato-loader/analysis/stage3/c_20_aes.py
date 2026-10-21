#!/usr/bin/env python3
"""
c_20_aes.py -- BLOB2 como texto cifrado con AES (400 = 25 bloques de 16)
Prueba TODOS los candidatos de clave: los 10 campos de 16 bytes de BLOB1,
las 141 cadenas de la zona .rdata, y claves derivadas. Modos ECB y CBC (IV=0).
Criterio: el primer bloque descifrado debe ser imprimible / empezar por texto.
"""
import numpy as np, re, itertools
from Crypto.Cipher import AES
from Crypto.Util import Counter

RUN = "/root/mrgarabato_analysis/run/"
raw = open(RUN+"stage3/wine__w7.bin","rb").read()
B1 = raw[0x227A0:0x22840]
B2 = raw[0x22A50:0x22BE0]
assert len(B2) == 400 and len(B2) % 16 == 0

def printable(x): return sum(1 for c in x if 32 <= c < 127)/max(1,len(x))
def wide(x):
    try: s = x.decode("utf-16-le")
    except Exception: return 0.0, ""
    return sum(1 for c in s if 32 <= ord(c) < 127)/max(1,len(s)), s

claves = []
for i in range(10):
    claves.append(("BLOB1.f%d"%i, B1[i*16:(i+1)*16]))
for i in range(25):
    claves.append(("BLOB2.bloque%d"%i, B2[i*16:(i+1)*16]))

# cadenas de la zona .rdata
cadenas = set()
for m in re.finditer(rb"[\x20-\x7e]{4,}", raw[0x21700:0x22C00]):
    cadenas.add(m.group())
    if len(m.group()) >= 16: claves.append(("rdata:%r"%m.group()[:20], m.group()[:16]))
    if len(m.group()) >= 32: claves.append(("rdata32:%r"%m.group()[:20], m.group()[:32]))
    if len(m.group()) >= 8:  claves.append(("rdata8:%r"%m.group()[:14], m.group()[:8].ljust(16,b'\0')))
CAD = ["APP_SECRET","app_secret","OWNER_ID","MrGarabato","PhoneHx","Ignyx","NeuralAuth/1.0",
       "7RobSZuyx23L677ulvLD1Cq","YX9Y0KWPU6","Nf7D?!r+WMtb3Z&s3_","MRGARABATO",
       "neural_login.php","14ddg0941cvah.exe","34dbbmddg71c.exe","token","FreeFire"]
for c in CAD:
    claves.append(("lit:"+c, c.encode()[:16].ljust(16,b'\0')))
    claves.append(("lit16:"+c, c.encode()[:16]))
print("claves candidatas:", len(claves))

hits=[]
for nm, k in claves:
    if len(k) not in (16,24,32): continue
    # ECB
    try:
        pt = AES.new(k, AES.MODE_ECB).decrypt(B2)
    except Exception: continue
    f = printable(pt[:16]); fw, s = wide(pt[:32])
    if f > 0.7 or fw > 0.7:
        hits.append((max(f,fw), f"ECB {nm}", pt))
    # CBC IV=0
    try:
        pt = AES.new(k, AES.MODE_CBC, iv=b"\0"*16).decrypt(B2)
    except Exception: continue
    f = printable(pt[:16]); fw, s = wide(pt[:32])
    if f > 0.7 or fw > 0.7:
        hits.append((max(f,fw), f"CBC0 {nm}", pt))
    # CTR con nonce 0
    try:
        ctr = Counter.new(128, initial_value=0)
        pt = AES.new(k, AES.MODE_CTR, counter=ctr).decrypt(B2)
    except Exception: continue
    f = printable(pt[:16]); fw, s = wide(pt[:32])
    if f > 0.7 or fw > 0.7:
        hits.append((max(f,fw), f"CTR {nm}", pt))

print(f"\nresultados con >70% imprimible en el primer bloque: {len(hits)}")
for h in hits[:20]:
    print(f"  {h[0]:.2f} {h[1]}: {h[2][:48]!r}")

# crib: buscar 'http', 'https', '.exe', 'Auth' en los primeros 64 bytes de cada descifrado
print("\ncrib-drag sobre los primeros 32 bytes de TODOS los descifrados (ECB):")
found=0
for nm,k in claves:
    if len(k) not in (16,24,32): continue
    try: pt = AES.new(k, AES.MODE_ECB).decrypt(B2)
    except Exception: continue
    for crib in (b"http", b"HTTP", b".exe", b"Auth", b"14dd", b"34db", b"\\14", b"pack", b"Mrg"):
        if crib in pt[:32]:
            print(f"   {nm}: {crib!r} en {pt[:32]!r}"); found+=1
print(f"  ({found} coincidencias)")
print("\nCONCLUSION: si no hay lineas -> BLOB2 no es AES con ninguna clave candidata")
