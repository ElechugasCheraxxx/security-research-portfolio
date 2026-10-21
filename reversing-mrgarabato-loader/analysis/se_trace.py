#!/usr/bin/env python3
"""se_trace.py — traza de APIs y cola de ejecucion, para ver DONDE se detiene
el stub del protector bajo speakeasy.

Resultados previos:
  - PC 0x140d88535 (EP, zona "cifrada") -> 0x140f53dd1 (zona clara)
  - 3,1 M instrucciones
  - solo 1,19 MB escritos, y todos a la pagina de stack 0x12f0000 (99% ceros)
    => NO hubo destino de desempaquetado
"""
import os
import sys
import time
import collections
import json

import speakeasy

HERE = os.path.dirname(os.path.abspath(__file__))
TARGET = sys.argv[1] if len(sys.argv) > 1 else \
    os.path.join(HERE, 'wineprefix/drive_c/work/MrGarabato-LoaderAdvanced.exe')
BUDGET = float(sys.argv[2]) if len(sys.argv) > 2 else 90.0

IBASE = 0x140000000
SEC_VA = IBASE + 0x825000
SEC_END = SEC_VA + 0x76E000
CLEAR = IBASE + 0xE36000

api_log = []
tail = collections.deque(maxlen=3000)
n = [0]
uniq_pages = collections.Counter()


def on_api(se_obj, fname, params, retv):
    api_log.append((fname, len(params)))
    return False


def on_code(se_obj, va, size, ctx=None):
    n[0] += 1
    tail.append(va)
    uniq_pages[va >> 16] += 1
    if n[0] > 20_000_000:
        se.stop()
    return False


se = speakeasy.Speakeasy()
mod = se.load_module(TARGET)
se.add_api_hook(on_api)
se.add_code_hook(on_code)

t0 = time.time()
try:
    try:
        se.run_module(mod, timeout=BUDGET)
    except TypeError:
        se.run_module(mod)
except Exception as e:
    print(f"[*] run_module: {type(e).__name__}: {e}")
print(f"[*] {n[0]:,} instrucciones en {time.time()-t0:.1f}s")
print(f"[*] PC final 0x{se.get_pc():x}")

print(f"\n[*] APIs llamadas: {len(api_log)}")
cnt = collections.Counter(f for f, _ in api_log)
for f, c in cnt.most_common(40):
    print(f"    {c:>5}x  {f}")
if not api_log:
    print("    NINGUNA API llamada -> el stub no llega a la frontera de OS")

print(f"\n[*] paginas de codigo mas ejecutadas (64 KB):")
for pg, c in uniq_pages.most_common(15):
    zone = ('.w7/ cifrado' if SEC_VA <= pg < CLEAR else
            '.w7/ claro' if CLEAR <= pg < SEC_END else 'fuera')
    print(f"    0x{pg:012x}  {c:>8} muestras   [{zone}]")

print(f"\n[*] ultimas {tail.maxlen} direcciones ejecutadas (cola):")
seq = list(tail)
# resumir en runs
runs = []
for va in seq:
    if runs and va - runs[-1][0] <= 16:
        runs[-1][1] = va
        runs[-1][2] += 1
    else:
        runs.append([va, va, 1])
print(f"    {len(runs)} tramos consecutivos")
for a, b, c in runs[-40:]:
    zone = ('CIFRADO' if SEC_VA <= a < CLEAR else
            'CLARO' if CLEAR <= a < SEC_END else 'fuera')
    print(f"      0x{a:x}..0x{b:x}  x{c:<5} [{zone}]")

# donde se paso de cifrado a claro
cross = [i for i in range(1, len(seq)) if (seq[i-1] < CLEAR) != (seq[i] < CLEAR)]
if cross:
    print(f"\n[*] cruces cifrado<->claro en la cola: {len(cross)}")
    for i in cross[:6]:
        print(f"      0x{seq[i-1]:x} -> 0x{seq[i]:x}")

json.dump({'apis': [f for f, _ in api_log], 'instr': n[0]},
          open(os.path.join(HERE, 'stage3', 'se_trace.json'), 'w'), indent=1)
print(f"\n[*] stage3/se_trace.json escrito")