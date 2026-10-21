#!/usr/bin/env python3
"""Recuperacion de CFG con angr sobre el PE desempaquetado.
CFGFast reconstruye funciones pese a junk-instructions y predicados opacos."""
import sys, time, logging
import angr_shim                      # inyecta PEStubs antes de angr

path = sys.argv[1] if len(sys.argv) > 1 else "unpacked_bypass.exe"
t0 = time.time()
p = angr_shim.load(path)
print(f"[1] cargado  entry=0x{p.entry:x}  ({time.time()-t0:.1f}s)", flush=True)

print("[2] CFGFast ...", flush=True)
cfg = p.analyses.CFGFast(normalize=True, data_references=True)
funcs = list(cfg.kb.functions.values())
print(f"    funciones: {len(funcs)}  ({time.time()-t0:.1f}s)", flush=True)

funcs = [f for f in funcs if f.size > 0]
funcs.sort(key=lambda f: f.size, reverse=True)

BASE = 0x140000000
def zona(a):
    r = a - BASE
    if 0x1000 <= r < 0x18000: return ".text"
    if 0x23000 <= r < 0x80b000: return ".7f"
    if 0x81c000 <= r < 0xf8a8a4: return ".3q"
    return "otros"

from collections import Counter
c = Counter(zona(f.addr) for f in funcs)
print("    reparto por seccion:", dict(c))

print("\n[3] 20 funciones mas grandes:")
for f in funcs[:20]:
    print(f"    0x{f.addr:012x} [{zona(f.addr):5}] {f.size:>7} B  {f.name}")

with open("angr_funcs.txt", "w") as fh:
    for f in funcs:
        fh.write("0x%x %d %s\n" % (f.addr, f.size, f.name))
print(f"\n[+] {len(funcs)} funciones -> angr_funcs.txt")

# funciones que tocan las cadenas clave
KEY = {0x19f70:"C2 mrgarabato.com", 0x1a208:"HD-Player.exe", 0x1a218:"MEmu.exe",
       0x1a1f0:"Checking Update", 0x1a280:"Injection Process", 0x19f28:"token"}
print("\n[4] funciones cuyo cuerpo contiene literales clave:")
for f in funcs:
    try:
        blk = bytes(p.loader.memory.load(f.addr, min(f.size, 0x30000)))
    except Exception:
        continue
    found = [v for k, v in KEY.items() if p.loader.memory.load(k + BASE, 40)[:0] == b"" and
             (BASE + k).to_bytes(8, "little") in blk]
    if found:
        print(f"    0x{f.addr:012x} [{zona(f.addr):5}] {f.size:>7} B -> {', '.join(found)}")