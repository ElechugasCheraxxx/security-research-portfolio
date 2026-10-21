#!/usr/bin/env python3
"""
c_08b_rampas_np.py -- Familia de rampas, vectorizada con numpy.
p[i] = c[i] OP ((a + b*j) & 255),  j = i (global) o j = i % span (reinicio)
"""
import numpy as np, string

DUMP = "/root/mrgarabato_analysis/run/stage3/wine__w7.bin"
d = open(DUMP, "rb").read()
BLOBS = {"BLOB1": d[0x227A0:0x22A00], "BLOB2": d[0x22A50:0x22BE0]}

OK = np.zeros(256, bool); OK[0x20:0x7F] = True; OK[[0,10,13]] = True
ENG = [8.167,1.492,2.782,4.253,12.702,2.228,2.015,6.094,6.966,0.153,0.772,4.025,
       2.406,6.749,7.507,1.929,0.095,5.987,6.327,9.056,2.758,0.978,2.360,0.150,
       1.974,0.074]
W = np.full(256, 0.004, np.float64)
for ch, f in zip(string.ascii_lowercase, ENG): W[ord(ch)] = f/100
W[ord(' ')] = 0.17

def run(name, blob):
    c = np.frombuffer(blob, np.uint8).astype(np.int32)
    n = len(c)
    ii = np.arange(n)
    best = []
    for span, restart in ((16, True), (32, True), (None, False)):
        j = (ii % span) if restart else ii
        for b in range(256):
            bs = (b*j) & 255
            for a in range(256):
                k = (bs + a) & 255
                for op in range(3):
                    if   op == 0: p = c ^ k
                    elif op == 1: p = (c - k) & 255
                    else:          p = (c + k) & 255
                    if not OK[p].all(): continue
                    sc = W[p].mean() / (W[0x20:0x7F].mean())
                    best.append((float(sc), op, a, b, span, restart, bytes(p)))
    best.sort(key=lambda t: -t[0])
    print(f"\n### {name}  ({len(best)} candidatos imprimibles)")
    opn = {0:"XOR",1:"c=p+k",2:"c=p-k"}
    for sc, op, a, b, span, restart, pt in best[:30]:
        print(f"  score={sc:.3f} {opn[op]:7s} a=0x{a:02X} b={b:3d} span={span} restart={restart}")
        print(f"     {pt!r}")

for nm, bl in BLOBS.items():
    run(nm, bl)
