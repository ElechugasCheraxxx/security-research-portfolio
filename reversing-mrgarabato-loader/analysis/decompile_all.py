#!/usr/bin/env python3
"""Descompila en lote las funciones de la zona de codigo limpio usando
rz-ghidra (backend del decompilador de Ghidra dentro de rizin)."""
import sys, os
import r2pipe

path   = sys.argv[1]
lo     = int(sys.argv[2], 16)
hi     = int(sys.argv[3], 16)
outdir = sys.argv[4]
os.makedirs(outdir, exist_ok=True)

img  = open(path, "rb").read()
BASE = 0x140000000

PROLOGS = [
    bytes.fromhex("48895c2408"), bytes.fromhex("48894c2408"),
    bytes.fromhex("488b5c2408"), bytes.fromhex("4053"), bytes.fromhex("4055"),
    bytes.fromhex("4883ec"),     bytes.fromhex("4c8bdc"),
    bytes.fromhex("488bec"),     bytes.fromhex("554889e5"),
]
cands = {i for i in range(lo, hi - 16)
         for p in PROLOGS if img[i:i + len(p)] == p}
print(f"[+] {len(cands)} posibles inicios de funcion en 0x{BASE+lo:x}-0x{BASE+hi:x}", flush=True)

r2 = r2pipe.open(path, flags=["-e", "bin.relocs.apply=true"])
r2.cmd("e scr.color=0")
r2.cmd("e anal.timeout=90")

results = []
fail = 0
for a in sorted(cands):
    try:
        r2.cmd("s 0x%x" % (BASE + a))
        r2.cmd("af-")
        r2.cmd("af")
        info = r2.cmdj("afij") or []
        if not info:
            continue
        meta = info[0]
        size = int(meta.get("size", 0) or 0)
        if size < 16:
            continue
        dec = r2.cmd("pd:g").strip()
        if not dec or dec.startswith("WARN") or "No function" in dec:
            fail += 1
            continue
        fn = os.path.join(outdir, "fcn_%x.c" % a)
        with open(fn, "w") as fh:
            fh.write("/* RVA 0x%x  tam %d B  addr 0x%x */\n\n" % (a, size, BASE + a))
            fh.write(dec + "\n")
        results.append((a, size, len(dec)))
    except Exception:
        fail += 1

results.sort(key=lambda t: -t[2])
print(f"[+] descompiladas: {len(results)}   fallidas: {fail}   -> {outdir}\n")
print("  %-12s %8s %10s" % ("RVA", "tam", "chars"))
for a, s, l in results[:35]:
    print("  0x%08x %8d %10d" % (a, s, l))
r2.quit()