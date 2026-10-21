#!/usr/bin/env python3
"""
c_10_bateria.py -- Bateria amplia de transformaciones sobre BLOB1 y BLOB2.
Todo se evalua con "los 100% de los bytes son imprimibles" + score ingles.
"""
import numpy as np, string, itertools

DUMP = "/root/mrgarabato_analysis/run/stage3/wine__w7.bin"
d = open(DUMP, "rb").read()
B1 = np.frombuffer(d[0x227A0:0x22A00], np.uint8)
B2 = np.frombuffer(d[0x22A50:0x22BE0], np.uint8)

OK = np.zeros(256, bool); OK[0x20:0x7F] = True; OK[[0,10,13]] = True
ENG=[8.167,1.492,2.782,4.253,12.702,2.228,2.015,6.094,6.966,0.153,0.772,4.025,
     2.406,6.749,7.507,1.929,0.095,5.987,6.327,9.056,2.758,0.978,2.360,0.150,1.974,0.074]
W=np.full(256,0.004,np.float64)
for ch,f in zip(string.ascii_lowercase,ENG): W[ord(ch)]=f/100
W[ord(' ')]=0.17
BASE = W[0x20:0x7F].mean()

res=[]
def test(nm, p, minfrac=1.0):
    p=np.asarray(p,np.uint8)
    frac = OK[p].mean()
    if frac >= minfrac:
        sc = W[p].mean()/BASE
        res.append((frac, sc, nm, bytes(p)))

for BNAME, B in (("BLOB1", B1), ("BLOB2", B2)):
    n=len(B)
    print(f"\n{'#'*70}\n# {BNAME} ({n} bytes)\n{'#'*70}")
    res.clear()

    # (1) auto-transformaciones: p[i] = c[i] ^ c[i-k] / c[i] - c[i-k] / ...
    for k in range(1, n):
        x = B[:n-k]; y = B[k:]
        test(f"{BNAME} p=c[i]^c[i-{k}]", x ^ y)
        test(f"{BNAME} p=c[i]-c[i-{k}]", (x - y).astype(np.uint8))
        test(f"{BNAME} p=c[i]+c[i-{k}]", (x + y).astype(np.uint8))
        test(f"{BNAME} p=c[i]^c[i+{k}]", x ^ y)
    # con offset inicial k (los primeros k bytes = k key)
    for k in range(1, min(n, 64)):
        x = B[:n-k]; y = B[k:]
        for kk in range(256):
            test(f"{BNAME} p=(c[i]^c[i-{k}])^{kk}", x ^ y ^ kk, 0.9)

    # (2) claves indexadas por posicion
    i = np.arange(n, dtype=np.int32)
    for A in range(256):
        base = (A * i) & 255
        test(f"{BNAME} p=c^(A*i) A={A}", B ^ base)
        test(f"{BNAME} p=c^(A*i+A) A={A}", B ^ ((base + A) & 255))
        test(f"{BNAME} p=c-(A*i) A={A}", (B - base).astype(np.uint8))
    # indices con增长率 doubling / fibonacci
    for name, seq in (("fib", None), ("pow2", None), ("lcg", None)):
        pass

    # (3) permutaciones de bits (8! = 40320) + constante
    perms = list(itertools.permutations(range(8)))
    vals = np.unique(B)
    def permute(v, p):
        r = 0
        for i in range(8):
            r |= ((v >> i) & 1) << p[i]
        return r
    LUT = np.array([[permute(v, p) for v in range(256)] for p in perms], np.uint8)  # 40320x256
    M = LUT[:, vals]                     # 40320 x nvals
    mx = M.max(axis=1); mn = M.min(axis=1)
    span = mx - mn
    good = np.where(span <= 94)[0]
    # para esos, comprobar si existe offset tal que todo caiga en [0x20,0x7E]
    for gi in good:
        m = M[gi]; off = (0x20 - int(m.min())) & 255
        if int(m.max()) + off <= 0x7E:
            test(f"{BNAME} bitperm {perms[gi]} +{off}", LUT[gi][B])
    print(f"  (permutaciones de bits: {len(good)} con span<=94, "
          f"{len(res)} candidatos totales tras testear)")

    res.sort(key=lambda t: (-t[0], -t[1]))
    print(f"  --> {len(res)} candidatos")
    for frac, sc, nm, pt in res[:20]:
        print(f"   frac={frac:.2f} score={sc:.2f}  {nm}")
        print(f"       {pt[:120]!r}")
