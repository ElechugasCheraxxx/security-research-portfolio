#!/usr/bin/env python3
"""c_02_estructura.py -- Caracterizacion estadistica + mapa PE del volcado."""
import struct, math, collections

DUMP = "/root/mrgarabato_analysis/run/stage3/wine__w7.bin"
d = open(DUMP, "rb").read()
b1 = d[0x227A0:0x227A0+160]
b2 = d[0x22A50:0x22A50+400]

# ---------------- 1. PE ----------------
print("="*70); print("1. ESTRUCTURA PE DEL VOLCADO"); print("="*70)
print("magic primeros 4:", d[:4])
e_lfanew = struct.unpack_from("<I", d, 0x3C)[0]
print("e_lfanew = 0x%X" % e_lfanew)
sig = d[e_lfanew:e_lfanew+4]
print("firma PE:", sig)
if sig == b"PE\0\0":
    coff = e_lfanew+4
    machine, nsec, tds, psym, nsym, optsz, chars = struct.unpack_from("<HHIIIHH", d, coff)
    print(f"machine=0x{machine:04X} nsec={nsec} optsz={optsz} chars=0x{chars:04X}")
    opt = coff+20
    magic = struct.unpack_from("<H", d, opt)[0]
    print("opt magic = 0x%04X (%s)" % (magic, "PE32" if magic==0x10B else "PE32+" if magic==0x20B else "?"))
    imgbase = struct.unpack_from("<I", d, opt+28)[0] if magic==0x10B else struct.unpack_from("<Q", d, opt+24)[0]
    print("ImageBase = 0x%X" % imgbase)
    secoff = opt+optsz
    print(f"{'name':10s} {'VSz':>10s} {'VAddr':>10s} {'RawSz':>10s} {'RawPtr':>10s} {'Chars':>10s}")
    secs=[]
    for i in range(nsec):
        o = secoff+i*40
        nm = d[o:o+8].rstrip(b"\0").decode("latin1")
        vsz, va, rsz, rp = struct.unpack_from("<IIII", d, o+8)
        ch = struct.unpack_from("<I", d, o+36)[0]
        secs.append((nm,vsz,va,rsz,rp,ch))
        print(f"{nm:10s} {vsz:10d} 0x{va:08X} {rsz:10d} 0x{rp:08X} 0x{ch:08X}")
    for tag,off in (("BLOB1",0x227A0),("BLOB2",0x22A50)):
        for nm,vsz,va,rsz,rp,ch in secs:
            if va <= off < va+max(vsz,rsz):
                print(f"  {tag} @0x{off:X} -> seccion {nm}  (fileoff 0x{rp+off-va:X}, "
                      f"VA 0x{imgbase+off:X})")
    # data directories
    if magic==0x10B:
        ddir = opt+96
    else:
        ddir = opt+112
    names=["EXPORT","IMPORT","RESOURCE","EXCEPTION","SECURITY","BASERELOC","DEBUG",
           "ARCH","GLOBALPTR","TLS","LOADCFG","BOUNDIMP","IAT","DELAYIMP","CLR","RES"]
    print("  data dirs (RVA, size):")
    for i in range(min(16,(optsz-96)//8)):
        r,s = struct.unpack_from("<II", d, ddir+i*8)
        if r or s: print(f"    {names[i]:11s} rva=0x{r:08X} sz=0x{s:X}")

# ---------------- 2. histograma / estructura de b1 ----------------
print(); print("="*70); print("2. BLOB1 -- histogramas y estructura"); print("="*70)
h = collections.Counter(b1)
print("bytes distintos: %d  (min 0x%02X max 0x%02X)" % (len(h), min(b1), max(b1)))
print("valores < 0xB0 y != 0x00:", [(hex(k),v) for k,v in sorted(h.items()) if k < 0xB0 and k != 0])
print("histograma:")
for lo in range(0xB0, 0x100, 8):
    row = " ".join("%02X:%-2d"%(v,h.get(v,0)) for v in range(lo,lo+8))
    print("  ", row)

def entropy(b):
    c=collections.Counter(b); n=len(b)
    return -sum(v/n*math.log2(v/n) for v in c.values())
def chi2_uniform(b):
    n=len(b); k=len(set(b)); e=n/k
    return sum((b.count(x)-e)**2 for x in set(b))/e, k

print("\nsubconjuntos:")
for nm, sub in (("160 full", b1), ("pares(80)", b1[0::2]), ("impares(80)", b1[1::2]),
                ("cols 0-7 (8x20)", b"".join(b1[i*16+j] for i in range(10) for j in range(8)))):
    ch, k = chi2_uniform(sub)
    print(f"  {nm:14s} n={len(sub):3d} distintos={k:3d} H={entropy(sub):.3f} chi2/u={ch:.2f}")

def autocorr(seq, maxp=80):
    n=len(seq); best=[]
    for p in range(1, maxp+1):
        m=n-p
        eq=sum(1 for i in range(m) if seq[i]==seq[i+p])
        best.append((eq/m, p))
    best.sort(reverse=True)
    return best[:6]
print("\nautocorrelacion 160 full :", [(f"P{p}={r:.3f}") for r,p in autocorr(b1)])
print("autocorrelacion pares(80):", [(f"P{p}={r:.3f}") for r,p in autocorr(b1[0::2])])
print("autocorrelacion impares  :", [(f"P{p}={r:.3f}") for r,p in autocorr(b1[1::2])])

# ---------------- 3. paridad de bytes por posicion ----------------
print(); print("="*70); print("3. BLOB1 -- patron de bits"); print("="*70)
for b in range(8):
    cnt = sum(1 for x in b1 if (x>>b)&1)
    print(f"  bit{b}: {cnt}/160  ({cnt/160*100:.1f}%)")

# ---------------- 4. blob2 ----------------
print(); print("="*70); print("4. BLOB2 -- estructura"); print("="*70)
h2 = collections.Counter(b2)
print("distintos: %d / 256   rango 0x%02X-0x%02X   H=%.3f" % (len(h2), min(b2), max(b2), entropy(b2)))
ch,k = chi2_uniform(b2); print("chi2/u=%.3f (n=400, k=%d)"%(ch,k))
print("faltan %d valores de 0..255" % (256-len(h2)))
print("top 15:", [(hex(a),n) for a,n in h2.most_common(15)])
print("0xdb count=%d  0x24 count=%d  0xdb^0x24=0x%02X" % (b2.count(0xdb), b2.count(0x24), 0xdb^0x24))
for p in range(1, 81):
    m=len(b2)-p
    eq=sum(1 for i in range(m) if b2[i]==b2[i+p])
    if eq/m > 0.05: print(f"  autocorr P{p} = {eq/m:.3f}")
print("(autocorr >5% listada arriba; si vacia = aperiodica)")

# dwords / words
print("\ndwords no nulos con MSB 0 (posibles punteros):")
for i in range(0,400,4):
    v = struct.unpack_from("<I", b2, i)[0]
    if 0x400000 <= v <= 0x7FFFFFFF:
        print(f"   +0x{i:03X} -> 0x{v:08X}")
print("words en rango 0x20-0x7E consecutively:")
i=0
while i < 396:
    v=struct.unpack_from("<H", b2, i)[0]
    if 0x20 <= v <= 0x7E:
        j=i; s=""
        while j<396:
            v2=struct.unpack_from("<H",b2,j)[0]
            if 0x20<=v2<=0x7E: s+=chr(v2); j+=2
            else: break
        if len(s)>=4: print(f"   +0x{i:03X}: {s!r}")
        i=j if j>i else i+1
    else: i+=1
