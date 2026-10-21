#!/usr/bin/env python3
"""
c_14_blob2.py -- Caracterizacion exhaustiva de BLOB2 (400 B @0x22A50)
+ busqueda de tablas criptograficas conocidas
+ relaciones cruzadas BLOB1/BLOB2.
"""
import numpy as np, collections, struct, itertools, hashlib, zlib, binascii

RUN = "/root/mrgarabato_analysis/run/stage3/"
raw = open(RUN+"wine__w7.bin", "rb").read()
B1 = np.frombuffer(raw[0x227A0:0x22840], np.uint8)
B2 = np.frombuffer(raw[0x22A50:0x22BE0], np.uint8)

print("="*78); print("1. CONTEXTO AMPLIO DE BLOB2"); print("="*78)
for off in range(0x22A00, 0x22C40, 16):
    b = raw[off:off+16]
    mark = ""
    if off == 0x22A50: mark = "  <<< BLOB2 empieza"
    if off == 0x22BE0: mark = "  <<< BLOB2 acaba (400 B)"
    asc = "".join(chr(c) if 32 <= c < 127 else "." for c in b)
    print(f"  {off:06x}: {b.hex(' '):<47} {asc}{mark}")

print("="*78); print("2. ESTRUCTURA / SUBESTRUCTURAS"); print("="*78)
for step in (1,2,3,4,5,8,16):
    for off in range(step):
        s = B2[off::step]
        u = np.unique(s)
        ent = -float((np.bincount(s,minlength=256)/len(s) *
                      np.log2(np.bincount(s,minlength=256)/len(s)+1e-12)).sum())
        print(f"  B2[{off}::{step}]  n={len(s):3d} distintos={len(u):3d} H={ent:.2f} "
              f"rango=[0x{u.min():02X},0x{u.max():02X}]")
    print()

print("  dwords de BLOB2 con MSB=0 (posibles indices/ punteros pequenos):")
cnt=0
for i in range(0, 400, 4):
    v = struct.unpack_from("<I", raw, 0x22A50+i)[0]
    if v < 0x10000:
        print(f"    +0x{i:03X} = {v} (0x{v:X})"); cnt+=1
print(f"    total {cnt}/100")

print("="*78); print("3. CONCENTRACION DE VALORES (ventanas deslizantes)"); print("="*78)
h = collections.Counter(B2.tolist())
print("  0xDB=%d  0x24=%d  (0xDB^0x24=0x%02X)" % (h[0xDB], h[0x24], 0xDB^0x24))
best = []
for v, c in h.most_common(8):
    pos = [i for i, x in enumerate(B2.tolist()) if x == v]
    # ventana mas densa
    runs = []
    for p in pos:
        if runs and p == runs[-1][-1]+1: runs[-1].append(p)
        else: runs.append([p])
    r = max(runs, key=len)
    print(f"  valor 0x{v:02X}: {c} veces; run mas largo {len(r)} en +0x{r[0]:03X}")
    best.append((len(r), v, r[0]))
# prueba: en la ventana 0x22B08-0x22B66, ¿que otros valores hay?
print("  valores en la ventana +0xB8..+0x116:")
w = collections.Counter(B2[0xB8:0x116].tolist())
print("   ", sorted((f"0x{k:02X}:{v}" for k, v in w.items()), key=lambda s: -int(s.split(':')[1]))[:12])

print("="*78); print("4. ¿TABLA CRIPTOGRAFICA CONOCIDA?"); print("="*78)
def aes_sbox():
    p=q=1; sbox=[0]*256
    while True:
        p = p ^ ((p<<1)&0xFF) ^ (0x1B if p&0x80 else 0)
        q ^= q<<1; q ^= q<<2; q ^= q<<4; q &= 0xFF
        if q&0x80: q ^= 0x09
        x = q ^ ((q<<1)|(q>>7)) ^ ((q<<2)|(q>>6)) ^ ((q<<3)|(q>>5)) ^ ((q<<4)|(q>>4))
        sbox[p] = (x ^ 0x63) & 0xFF
        if p == 1: break
    sbox[0]=0x63
    return bytes(sbox)
SB = aes_sbox(); ISB = bytes(SB.index(i) for i in range(256))

TABLAS = {
 "AES S-box": SB, "AES S-box inversa": ISB,
 "sigma ChaCha/Salsa": b"expand 32-byte k",
 "sigma ChaCha/Salsa 2": b"expand 16-byte k",
 "RC4 identity": bytes(range(256)),
 "b64 alphabet": b"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/",
 "b64url alphabet": b"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_",
 "TEA delta LE": struct.pack("<I", 0x9E3779B9),
 "TEA delta BE": struct.pack(">I", 0x9E3779B9),
 "MD5 IV LE": bytes.fromhex("0123456789abcdeffedcba9876543210"),
 "MD5 T[0] LE": struct.pack("<I", 0xd76aa478),
 "AES rcon": bytes([0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80,0x1b,0x36]),
 "SHA256 K[0] BE": bytes.fromhex("428a2f98"), "SHA256 K[0] LE": struct.pack("<I",0x428a2f98),
 "AES Te0[0]": struct.pack("<I",0xc66363a5), "AES Td0[0]": struct.pack("<I",0x51f4a750),
}
# tablas CRC
for nm, poly in (("CRC32",0x04C11DB7), ("CRC32C",0x82F63B78), ("CRC32K",0x741B8CD7),
                 ("CRC32Q",0x814141AB)):
    t=[]
    for i in range(256):
        c=i
        for _ in range(8): c = (c>>1) ^ (poly if c&1 else 0)
        t.append(c)
    TABLAS[nm+" (LE dwords)"] = b"".join(struct.pack("<I",x) for x in t)
    TABLAS[nm+" (BE dwords)"] = b"".join(struct.pack(">I",x) for x in t)
    TABLAS[nm+" (bytes)"] = bytes(t)

for nm, t in TABLAS.items():
    hit = raw.find(t)
    if hit >= 0: print(f"  ENCONTRADO: {nm} en el volcado @0x{hit:X}")
    hit2 = B2.tobytes().find(t)
    if hit2 >= 0: print(f"  ENCONTRADO dentro de BLOB2: {nm} @+0x{hit2:X}")
print("  (sin salida = ninguna de esas tablas aparece)")

print("="*78); print("5. ¿BLOB2 es una permutacion parcial / precalculado?"); print("="*78)
v = B2.tolist()
print("  ¿los 400 valores son únicos?", len(set(v)) == 400)
print("  ¿algún valor se repite >= 3 veces?", [k for k,c in collections.Counter(v).items() if c>=3])
# ¿los 400 valores son un subconjunto structured?
print("  sorted/unsorted? la entrada esta ordenada:", all(v[i] <= v[i+1] for i in range(399)))
# bytes faltantes
falt = [x for x in range(256) if x not in set(v)]
print(f"  faltan {len(falt)} de 256: {falt[:40]}")

print("="*78); print("6. RELACIONES CRUZADAS BLOB1 / BLOB2"); print("="*78)
b1 = B1.tobytes(); b2 = B2.tobytes()
for off in range(0, 400-160):
    seg = b2[off:off+160]
    if all(32 <= x < 127 for x in (bytes(a^b for a,b in zip(b1,seg)))):
        print(f"  B1 XOR B2[+0x{off:X}] = 100% imprimible:", bytes(a^b for a,b in zip(b1,seg)))
print("  (vacio = ninguna)")
# B2 vs B1 escalado
print("  md5 B1=%s  md5 B2=%s" % (hashlib.md5(b1).hexdigest(), hashlib.md5(b2).hexdigest()))

print("="*78); print("7. ¿BLOB2 comprime / es flujo conocido?"); print("="*78)
print("  zlib header:", b2[:2].hex(), " gzip:", b2[:3].hex())
print("  chi2/u =", float(((np.bincount(B2,minlength=256)-400/256)**2).sum()/(400/256)))
print("  runs de bytes iguales consecutivos:", sum(1 for i in range(399) if b2[i]==b2[i+1]))
