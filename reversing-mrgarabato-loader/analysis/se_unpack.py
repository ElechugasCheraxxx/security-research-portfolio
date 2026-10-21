#!/usr/bin/env python3
"""se_unpack.py — speakeasy contra el loader protegido: ejecutar el stub del
protector y detectar si los 6,2 MB cifrados se descifran en runtime.

Seccion .w7/ = 7,79 MB:
    0x000000 .. 0x611000   6,07 MB  CIFRADO   (chi2/255 ~ 0,9-1,0)
    0x611000 .. 0x76E000   1,33 MB  x86-64 en claro (chi2/255 ~ 257-920)

Metodo:
  - Mide ANTES y DESPUES con ventanas EXACTAMENTE iguales (mismo offset, mismo
    tamano), que es la unica forma honesta de detectar un cambio.
  - Instrumenta con hooks de escritura para saber si alguien toca la zona
    cifrada, y con un code hook para ver hasta donde llega la ejecucion.
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
SEC_RVA = 0x825000
SEC_SIZE = 0x76E000
CLEAR_OFF = 0x611000
SEC_VA = IBASE + SEC_RVA
WIN = 0x20000                      # ventana de medida, IDENTICA antes y despues

# (etiqueta, offset en la seccion) -- mismas ventanas en ambas pasadas
PROBES = [
    ('cifrado 0.0M', 0x000000),
    ('cifrado 1.0M', 0x100000),
    ('cifrado 2.0M', 0x200000),
    ('cifrado 3.0M', 0x300000),
    ('cifrado 4.0M', 0x400000),
    ('cifrado 5.0M', 0x500000),
    ('cifrado 6.0M', 0x5F0000),
    ('borde cifrado', CLEAR_OFF - WIN),
    ('claro 6.2M',   CLEAR_OFF),
    ('claro final',  SEC_SIZE - WIN),
]


def chi2_255(buf):
    """chi2/255 normalizado. ~1 = uniforme (cifrado). >5 = con estructura."""
    n = len(buf)
    if n == 0:
        return 0.0
    exp = n / 256.0
    c = collections.Counter(buf)
    return sum((c.get(i, 0) - exp) ** 2 / exp for i in range(256)) / 255.0


def measure(se):
    out = {}
    for label, off in PROBES:
        va = SEC_VA + off
        try:
            out[label] = chi2_255(bytes(se.mem_read(va, WIN)))
        except Exception:
            out[label] = None
    return out


def show(tag, vals):
    print(f"  [{tag}]")
    for label, off in PROBES:
        v = vals[label]
        if v is None:
            print(f"    {label:<14} 0x{SEC_VA+off:x}   no legible")
        else:
            verdict = 'cifrado' if v < 3 else 'ESTRUCTURA'
            print(f"    {label:<14} 0x{SEC_VA+off:x}   chi2/255={v:>9.3f}   {verdict}")


se = speakeasy.Speakeasy()
print(f"[*] cargando {TARGET}")
mod = se.load_module(TARGET)
print(f"[*] base 0x{mod.get_base():x}   EP 0x{mod.ep:x}")
print(f"[*] seccion .w7/  VA 0x{SEC_VA:x} .. 0x{SEC_VA+SEC_SIZE:x}")
print(f"[*] cifrado 0x{SEC_VA:x}..0x{SEC_VA+CLEAR_OFF:x} ({CLEAR_OFF} B)")
print(f"[*] en claro 0x{SEC_VA+CLEAR_OFF:x}..0x{SEC_VA+SEC_SIZE:x}")

# ---- instrumentacion ----
writes = collections.Counter()
instr_count = [0]
hot = collections.Counter()


def on_write(se_obj, access, va, size, value, ctx=None):
    """se invoca en cada escritura a memoria."""
    if SEC_VA <= va < SEC_VA + CLEAR_OFF:
        writes['zona_cifrada'] += 1
    elif SEC_VA + CLEAR_OFF <= va < SEC_VA + SEC_SIZE:
        writes['zona_clara'] += 1
    else:
        writes['otra'] += 1
    return False


def on_code(se_obj, va, size, ctx=None):
    instr_count[0] += 1
    if instr_count[0] % 4096 == 0:
        hot[va >> 16] += 1
    if instr_count[0] > 40_000_000:
        se.stop()
    return False


se.add_mem_write_hook(on_write)
se.add_code_hook(on_code)

print("\n[*] medicion ANTES (ventanas de 128 KB):")
before = measure(se)
show('antes', before)

print(f"\n[*] ejecutando run_module() con presupuesto {BUDGET:.0f}s ...")
t0 = time.time()
try:
    se.run_module(mod, timeout=BUDGET)
except TypeError:
    try:
        se.run_module(mod)
    except Exception as e:
        print(f"[*] run_module fallo: {type(e).__name__}: {e}")
except Exception as e:
    print(f"[*] run_module termino: {type(e).__name__}: {e}")
elapsed = time.time() - t0
print(f"[*] elapsed {elapsed:.1f}s   instrucciones {instr_count[0]:,}")

print(f"\n[*] escrituras a memoria:")
for k, v in writes.most_common():
    print(f"    {k:<16} {v:>10,}")

if hot:
    print(f"\n[*] paginas mas calientes (64 KB) — donde se ejecuta:")
    for page, c in hot.most_common(8):
        print(f"    0x{page<<16:x}   {c:>8}")

print("\n[*] medicion DESPUES (mismas ventanas):")
after = measure(se)
show('despues', after)

print("\n[*] DELTA (unica forma valida de detectar descifrado):")
changed = []
for label, off in PROBES:
    b, a = before[label], after[label]
    if b is None or a is None:
        print(f"    {label:<14} no comparable")
        continue
    d = a - b
    verdict = 'SIN CAMBIO'
    if b < 3 <= a:
        verdict = '*** SE HA DESCIFRADO ***'
        changed.append(label)
    elif abs(d) > 2:
        verdict = 'ha cambiado'
    print(f"    {label:<14} {b:>9.3f} -> {a:>9.3f}   delta {d:>+9.3f}   {verdict}")

print(f"\n[*] PC final: 0x{se.get_pc():x}")

# volcado
for name, va, size in (('seccion_completa', SEC_VA, SEC_SIZE),):
    try:
        buf = bytes(se.mem_read(va, size))
        out = os.path.join(HERE, 'stage3', name + '.bin')
        open(out, 'wb').write(buf)
        print(f"[+] {out}  ({len(buf):,} B)")
    except Exception as e:
        print(f"[-] volcado fallo: {e}")

if changed:
    print(f"\n[+] zonas descifradas: {changed}")
else:
    print("\n[-] NINGUNA zona cifrada cambio: el stub no llego a descifrar")
    print("    => o speakeasy no emula una API que el stub necesita,")
    print("       o hay anti-emulacion en el stub.")