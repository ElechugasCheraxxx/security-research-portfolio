#!/usr/bin/env python3
"""se_where.py — DONDE escribe el loader al desempaquetar.

Resultado previo (se_unpack.py): el stub ejecuta 3,7 M instrucciones, no toca
NI un byte de la zona cifrada de .w7/, y escribe 218.769 bytes FUERA de la
seccion. Ese "fuera" es el destino: hay que localizarlo.

Aqui se bucketean las escrituras por pagina de 64 KB y se identifica la region
grande recien escrita, que es donde vive el payload desempaquetado.
"""
import os
import sys
import time
import collections

import speakeasy

HERE = os.path.dirname(os.path.abspath(__file__))
TARGET = sys.argv[1] if len(sys.argv) > 1 else \
    os.path.join(HERE, 'wineprefix/drive_c/work/MrGarabato-LoaderAdvanced.exe')
BUDGET = float(sys.argv[2]) if len(sys.argv) > 2 else 120.0

IBASE = 0x140000000
SEC_VA = IBASE + 0x825000
SEC_END = SEC_VA + 0x76E000
PAGE = 0x10000

se = speakeasy.Speakeasy()
mod = se.load_module(TARGET)
print(f"[*] base 0x{mod.get_base():x}  EP 0x{mod.ep:x}")

w_pages = collections.Counter()      # paginas destino, por numero de escrituras
w_bytes = collections.Counter()      # paginas destino, por bytes escritos
first_seen = {}
pc_start = [None]
pc_hot = collections.Counter()
n = [0]
big_writes = []                       # escrituras individuales grandes


def on_write(se_obj, access, va, size, value, ctx=None):
    pg = va & ~(PAGE - 1)
    w_pages[pg] += 1
    w_bytes[pg] += size
    if pg not in first_seen:
        first_seen[pg] = va
    if size >= 0x1000:
        big_writes.append((va, size))
    return False


def on_code(se_obj, va, size, ctx=None):
    n[0] += 1
    if pc_start[0] is None:
        pc_start[0] = va
    if n[0] % 2048 == 0:
        pc_hot[va >> 16] += 1
    if n[0] > 40_000_000:
        se.stop()
    return False


se.add_mem_write_hook(on_write)
se.add_code_hook(on_code)

t0 = time.time()
try:
    try:
        se.run_module(mod, timeout=BUDGET)
    except TypeError:
        se.run_module(mod)      # esta version no acepta timeout kwarg
except Exception as e:
    print(f"[*] run_module: {type(e).__name__}: {e}")
print(f"[*] {n[0]:,} instrucciones en {time.time()-t0:.1f}s")
print(f"[*] PC inicial "
      f"{'0x%x' % pc_start[0] if pc_start[0] else 'n/d'}"
      f"   PC final 0x{se.get_pc():x}")

print(f"\n[*] escrituras por pagina (64 KB), top 20 por bytes:")
tot = sum(w_bytes.values())
print(f"    total escrito: {tot:,} B en {len(w_pages)} paginas")
for pg, b in w_bytes.most_common(20):
    inside = SEC_VA <= pg < SEC_END
    # leer la pagina para medir su estructura
    try:
        buf = bytes(se.mem_read(pg, PAGE))
        cnt = collections.Counter(buf)
        exp = PAGE / 256.0
        chi = sum((cnt.get(i, 0) - exp) ** 2 / exp for i in range(256)) / 255.0
        mark = 'EN .w7/' if inside else ''
        print(f"    0x{pg:012x}  {b:>10,} B  escr={w_pages[pg]:>7}  "
              f"chi2/255={chi:>9.2f}  {'zeros=' + str(cnt.get(0,0)*100//PAGE) + '%':<10} {mark}")
    except Exception as e:
        print(f"    0x{pg:012x}  {b:>10,} B  escr={w_pages[pg]:>7}  no legible")

if big_writes:
    big_writes.sort(key=lambda x: -x[1])
    print(f"\n[*] escrituras individuales >= 4 KB: {len(big_writes)}")
    for va, size in big_writes[:15]:
        print(f"    0x{va:012x}  {size:,} B")

# el mapa completo de memoria ayuda a ver regiones grandes mapeadas
try:
    maps = se.get_mem_maps()
    big = sorted([m for m in maps if m.get('size', 0) >= 0x100000],
                 key=lambda m: -m['size'])
    print(f"\n[*] regiones mapeadas >= 1 MB: {len(big)}")
    for m in big[:15]:
        print(f"    0x{m['start']:016x}-0x{m['end']:016x}  {m['size']:>12,} B  {m.get('prot','')}")
except Exception as e:
    print(f"[-] get_mem_maps fallo: {e}")

# volcado de las paginas mas escritas
outdir = os.path.join(HERE, 'stage3', 'destinos')
os.makedirs(outdir, exist_ok=True)
print(f"\n[*] volcando las 8 paginas mas escritas:")
for pg, b in w_bytes.most_common(8):
    try:
        buf = bytes(se.mem_read(pg, PAGE))
        p = os.path.join(outdir, f'pag_{pg:012x}.bin')
        open(p, 'wb').write(buf)
        nz = sum(1 for x in buf if x)
        print(f"    0x{pg:012x} -> {p}  ({nz*100//PAGE}% no nulos)")
    except Exception as e:
        print(f"    0x{pg:012x}: {e}")