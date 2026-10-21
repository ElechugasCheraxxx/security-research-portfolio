#!/usr/bin/env python3
"""
c_08_rampas.py -- Familia de keystreams posicionales (rampas) sobre ambos blobs.
Modelos:  p[i] = c[i] ^ k(i) ; p[i] = (c[i] + k(i))%256 ; p[i] = (c[i] - k(i))%256
con k(i) = (a + b*i) % 256  (i global o i reiniciado cada 16 bytes)
"""
import itertools, string

DUMP = "/root/mrgarabato_analysis/run/stage3/wine__w7.bin"
d = open(DUMP, "rb").read()
B1 = d[0x227A0:0x22A00]
B2 = d[0x22A50:0x22BE0]
PR = set(range(0x20, 0x7F)) | {0x00, 0x0A, 0x0D}

ENG = [8.167,1.492,2.782,4.253,12.702,2.228,2.015,6.094,6.966,0.153,0.772,4.025,
       2.406,6.749,7.507,1.929,0.095,5.987,6.327,9.056,2.758,0.978,2.360,0.150,
       1.974,0.074]
FRQ = {}
for ch, f in zip(string.ascii_lowercase, ENG): FRQ[ord(ch)] = f/100
FRQ[ord(' ')] = 0.17
TOT = sum(FRQ.values())

def score(pt):
    if not all(b in PR for b in pt): return None
    s = 0.0
    for b in pt:
        s += FRQ.get(b, 0.004)
    return s/len(pt)/ (TOT/95)      # ~1.0 = distribucion inglesa

def decrypt(c, a, b, op, restart, span):
    out = bytearray()
    for i, x in enumerate(c):
        j = (i % span) if restart else i
        k = (a + b*j) & 0xFF
        if op == 'xor':  out.append(x ^ k)
        elif op == 'add':out.append((x - k) & 0xFF)   # c = p + k
        else:            out.append((x + k) & 0xFF)   # c = p - k
    return bytes(out)

def run(name, blob, spans=(16, None)):
    hits = []
    for restart in (False, True):
        for span in spans:
            ss = span if restart else None
            if restart and ss is None: continue
            for op in ('xor','add','sub'):
                for a in range(256):
                    for b in range(256):
                        pt = decrypt(blob, a, b, op, restart, ss)
                        sc = score(pt)
                        if sc and sc > 0.55:
                            hits.append((sc, name, op, "rampa" if restart else "global",
                                         a, b, span, pt))
    hits.sort(reverse=True)
    print(f"\n### {name}: {len(hits)} candidatos (score>0.55)")
    for h in hits[:25]:
        sc, nm, op, mode, a, b, span, pt = h
        print(f"  score={sc:.3f} {op:4s} {mode:6s} a=0x{a:02X} b={b} span={span}")
        print(f"     {pt!r}")

run("BLOB1", B1)
run("BLOB2", B2)

# --- variante concreta del informe: plain[i] = cipher[i] ^ (0x53+i) ---
print("\n### prueba directa 0x53+i")
for nm, blob in (("BLOB1", B1), ("BLOB2", B2)):
    for a in range(256):
        pt = bytes(blob[i] ^ ((a + i) & 0xFF) for i in range(len(blob)))
        sc = score(pt)
        if sc and sc > 0.9:
            print(f"  {nm} a=0x{a:02X} score={sc:.2f} {pt[:80]!r}")
