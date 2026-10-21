#!/usr/bin/env python3
"""se_smoke.py — prueba de humo: ¿puede speakeasy cargar y arrancar el loader?"""
import sys, time, traceback
import speakeasy

TARGET = sys.argv[1] if len(sys.argv) > 1 else \
    'wineprefix/drive_c/work/MrGarabato-LoaderAdvanced.exe'

se = speakeasy.Speakeasy()
print(f"cargando {TARGET} ...", flush=True)
try:
    mod = se.load_module(TARGET)
except Exception as e:
    print(f"  load_module fallo: {e}")
    traceback.print_exc()
    sys.exit(1)

print(f"  base     = 0x{mod.get_base():x}")
print(f"  ep       = 0x{mod.get_ep():x}")
print(f"  secciones = {len(mod.get_sections()) if hasattr(mod,'get_sections') else '?'}")

# mapa de memoria inicial
try:
    maps = se.mem_map()
except Exception:
    maps = None
print(f"  regiones mapeadas = {len(maps) if maps else 0}")
if maps:
    for m in sorted(maps, key=lambda x: x['start'])[:12]:
        print(f"    0x{m['start']:016x}-0x{m['end']:016x}  {m['size']:>12}  {m.get('prot','')}")

print("ejecutando 8 s desde el EP ...", flush=True)
t0 = time.time()
try:
    se.run(mod.get_ep(), timeout=8)
except Exception as e:
    print(f"  run() termino con: {type(e).__name__}: {e}")
print(f"  tiempo real: {time.time()-t0:.1f}s")

# dopo
try:
    maps2 = se.mem_map()
    print(f"  regiones tras ejecutar = {len(maps2)}")
    big = sorted([m for m in maps2 if m['size'] > 0x100000], key=lambda x:-x['size'])
    print(f"  regiones >1MB tras ejecutar: {len(big)}")
    for m in big[:10]:
        print(f"    0x{m['start']:016x}  {m['size']:>12}  prot={m.get('prot','')}")
except Exception as e:
    print(f"  mem_map fallo: {e}")
