#!/usr/bin/env python3
"""Descompila todas las funciones de .text del LoaderAdvanced con rz-ghidra.
Hace UN solo analisis y luego pd:g por funcion (mucho mas rapido que
re-analizar en cada inicio candidato)."""
import sys, os, time
import r2pipe

path   = sys.argv[1]
lo     = int(sys.argv[2], 16)
hi     = int(sys.argv[3], 16)
outdir = sys.argv[4]
os.makedirs(outdir, exist_ok=True)

img  = open(path, "rb").read()
BASE = 0x140000000

PROLOGS = [bytes.fromhex(p) for p in
           ("48895c2408", "48894c2408", "488b5c2408", "4053", "4055", "4883ec",
            "4c8bdc", "488bec", "554889e5", "4154", "4155", "4156", "4157")]
cands = sorted({i for i in range(lo, hi - 16)
                for p in PROLOGS if img[i:i + len(p)] == p})
print("[+] %d inicios candidatos" % len(cands), flush=True)

r2 = r2pipe.open(path, flags=["-e", "bin.relocs.apply=true", "-e", "scr.color=0", "-2"])
r2.cmd("e scr.color=0")
r2.cmd("e asm.arch=x86")
r2.cmd("e asm.bits=64")
t0 = time.time()
r2.cmd("e anal.timeout=120")
print("[*] analizando .text ...", flush=True)
for i, a in enumerate(cands):
    if i % 40 == 0:
        r2.cmd("af @ 0x%x" % (BASE + a))
print("[*] analisis: %.1f s" % (time.time() - t0), flush=True)

fns = {}
fl = r2.cmdj("aflj") or []
for f in fl:
    a = f["addr"]
    if BASE + lo <= a < BASE + hi:
        fns[a] = f
print("[+] %d funciones detectadas" % len(fns), flush=True)

results = []
fail = 0
for a in sorted(fns):
    try:
        r2.cmd("s 0x%x" % a)
        dec = r2.cmd("pd:g").strip()
        if not dec or dec.startswith("WARN") or "No function" in dec:
            fail += 1
            continue
        size = fns[a].get("size", 0)
        fn = os.path.join(outdir, "fcn_%x.c" % (a - BASE))
        with open(fn, "w") as fh:
            fh.write("/* RVA 0x%x  tam %d B  addr 0x%x */\n\n" % (a - BASE, size, a))
            fh.write(dec + "\n")
        results.append((a - BASE, size, len(dec)))
    except Exception:
        fail += 1
print("[+] descompiladas: %d  fallidas: %d -> %s" % (len(results), fail, outdir), flush=True)
r2.quit()