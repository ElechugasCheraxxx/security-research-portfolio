#!/usr/bin/env python3
"""speakeasy: emulacion de Windows. Venv aislado (speakeasy exige unicorn 1.0.2)."""
import sys, json, collections

import speakeasy

target = sys.argv[1] if len(sys.argv) > 1 else "unpacked_bypass.exe"
timeout = int(sys.argv[2]) if len(sys.argv) > 2 else 120

print(f"[*] speakeasy sobre {target} (timeout {timeout}s)", flush=True)
se = speakeasy.Speakeasy()

try:
    mod = se.load_module(target)
except Exception as e:
    print(f"[!] load_module fallo: {type(e).__name__}: {e}")
    sys.exit(1)

print(f"[+] modulo: base=0x{mod.get_base():x} ep=0x{mod.ep:x} arch={mod.arch} "
      f"ptr={mod.get_ptr_size()} imagen=0x{mod.get_image_size():x}")

# hooks para capturar comportamiento
api_calls = collections.Counter()
dropped = []
dumps = []


def api_hook(ctx, api, argv, retv):
    try:
        api_calls[api] += 1
    except Exception:
        pass


try:
    se.run_module(mod, timeout=timeout)
    print("[+] emulacion terminada")
except Exception as e:
    print(f"[!] run_module: {type(e).__name__}: {e}")

# ---- informe
try:
    rep = se.get_report()
    print(f"\n[+] informe: {len(rep)} entradas")
    with open("speakeasy_report.json", "w") as f:
        json.dump(rep, f, indent=1, default=str)
    kinds = collections.Counter(r.get("event") or r.get("kind") or "?" for r in rep)
    print("    tipos de evento:", dict(kinds))
    for r in rep[:30]:
        ev = r.get("event") or r.get("kind")
        d = r.get("desc") or r.get("api") or ""
        print(f"      [{ev}] {str(d)[:100]}")
except Exception as e:
    print(f"[!] get_report: {type(e).__name__}: {e}")

# ---- imports dinamicos resueltos en runtime (clave: el binario resuelve por hash)
try:
    dyn = se.get_dyn_imports()
    print(f"\n[+] imports dinamicos: {len(dyn or [])}")
    for d in sorted(dyn or [])[:60]:
        print("   ", d if isinstance(d, str) else str(d)[:120])
except Exception as e:
    print(f"[!] get_dyn_imports: {e}")

# ---- ficheros soltados
try:
    for f in se.get_dropped_files() or []:
        dropped.append(f)
        print(f"\n[+] FICHERO SOLTADO: {f}")
except Exception as e:
    print(f"[!] get_dropped_files: {e}")

# ---- volcados de memoria
try:
    for m in se.get_memory_dumps() or []:
        print(f"[+] volcado de memoria: {m}")
except Exception as e:
    pass

# ---- mapa de memoria (¿se mapearon las secciones grandes?)
try:
    mm = se.get_mem_maps()
    print(f"\n[+] regiones de memoria mapeadas: {len(mm)}")
    for m in list(mm)[:15]:
        print("   ", str(m)[:120])
except Exception as e:
    print(f"[!] get_mem_maps: {e}")

print("\n[+] fin")