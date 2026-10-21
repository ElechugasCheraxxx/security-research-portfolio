#!/usr/bin/env python3
"""Vuelca la lista de funciones de .text detectada por r2 (un solo analisis)."""
import sys, time, json
import r2pipe

path = sys.argv[1]
lo = int(sys.argv[2], 16); hi = int(sys.argv[3], 16)
BASE = 0x140000000
img = open(path, "rb").read()
PROLOGS = [bytes.fromhex(p) for p in
           ("48895c2408", "48894c2408", "488b5c2408", "4053", "4055", "4883ec",
            "4c8bdc", "488bec", "554889e5", "4154", "4155", "4156", "4157")]
cands = sorted({i for i in range(lo, hi - 16) for p in PROLOGS if img[i:i + len(p)] == p})
r2 = r2pipe.open(path, flags=["-e", "bin.relocs.apply=true", "-e", "scr.color=0", "-2"])
r2.cmd("e scr.color=0"); r2.cmd("e anal.timeout=120")
t0 = time.time()
for i, a in enumerate(cands):
    if i % 40 == 0:
        r2.cmd("af @ 0x%x" % (BASE + a))
fl = r2.cmdj("aflj") or []
fns = sorted((f["addr"], f.get("size", 0), f.get("nbbs", 0)) for f in fl
             if BASE + lo <= f["addr"] < BASE + hi)
print("[+] %d funciones en %.1f s" % (len(fns), time.time() - t0))
with open("fns_loader.json", "w") as f:
    json.dump([[a, s, n] for a, s, n in fns], f)
for a, s, n in fns:
    print("  0x%06x  %6d B  %3d bbs" % (a - BASE, s, n))
r2.quit()