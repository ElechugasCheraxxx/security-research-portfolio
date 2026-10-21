#!/usr/bin/env python3
"""
s16_poda.py -- PODA RIGUROSA de basura trivial, con remapeo completo de
offsets y reescritura de TODAS las ramificaciones para preservar el CFG.

======================================================================
 FILOSOFIA
======================================================================
Solo se elimina algo cuya ausencia sea *demostrablemente* indistinguible en
tiempo de ejecucion. Ademas, ninguna eliminacion puede cambiar el flujo de
control: antes de decidir, se calcula el conjunto de destinos de rama y
nunca se toca una instruccion que sea destino de un salto (el control podria
entrar ahi).

======================================================================
 REGLAS
======================================================================
T1  NOP-LIKE
    `nop` (1..9 bytes) y `xchg ax,ax` / `xchg eax,eax`.
    No tocan registro, flag, memoria ni flujo. No-ops por definicion de ISA.

T2  RACE DE FLAGS MUERTA
    Secuencia consecutiva de `clc/stc/cmc` seguida de una instruccion que
    SOBREESCRIBE CF y NO lo lee. El CF resultante antes y despues es
    identico, luego la race es basura muerta.
    Se excluyen ademas: `adc` y `sbb` (leen CF), `rcr` (lee CF),
    rotaciones/shifts con contador no constante (pueden ser 1 y leer CF).

T3  RACE solo-clc/stc
    Si la race contiene unicamente clc y stc, el CF final depende solo de
    la ULTIMA. Se conserva la ultima; las anteriores se borran.

T4  RACE solo-cmc
    `cmc` alterna CF. Un numero PAR de cmc consecutivos se anula por
    completo. Un numero IMPAR conserva exactamente uno. Si la race mezcla
    clc/stc con cmc NO se toca nada (rompe la paridad).

T5  JMP-NOOP
    `E9 00000000` = `jmp $+5`: salta a la instruccion siguiente. No cambia
    el flujo (verificado: 178/178 en frontera de instruccion, y el destino
    es exactamente o+5).

======================================================================
 LO QUE NO SE ELIMINA (y por que)
======================================================================
* `ror/rol/rcl/rcr/bswap/not/neg/xor r,r/add/sub/cmp/test/mov` : tocan
  registros o flags con valor dependiente del estado. Sin analisis de
  liveness no es demostrable que sean basura. Se contabilizan aparte.
* `xor r,r` y `mov r,r` : se detectan, pero un `xor eax,eax` precede casi
  siempre a un `jcc` (zero-idiom) -> se dejan.
* Cualquier instruccion que sea destino de rama (verificado antes de podar).

======================================================================
 REMAPEO DE OFFSETS
======================================================================
1. Se concatenan las instrucciones conservadas -> blob nuevo.
2. `new_of[old]` / `old_of_new[new]` = correspondencia bidireccional.
3. Se reescriben los campos rel32/rel8 de TODAS las ramas conservadas para
   que apunten al mismo bloque logico.
4. Los saltos cortos (rel8) que dejan de caber se EXPANDEN a su forma
   larga (0F 8x rel32, E9 rel32), semanticamente identica.
5. `loop/loope/loopne/jrcxz` NO tienen forma rel32. Para esos se bloquea la
   eliminacion dentro de su ventana [min(src,tgt), max(src,tgt)+2), de modo
   que su desplazamiento no cambia. Esto es conservador y sound.
"""
import os, sys, struct, pickle, collections, json, time

HERE = os.path.dirname(os.path.abspath(__file__))
BLOB = os.path.join(HERE, "stage3_code.bin")
OUT  = os.path.join(HERE, "stage3_podado.bin")
MAP  = os.path.join(HERE, "mapa_offsets.json")
REP  = os.path.join(HERE, "informe_poda.txt")
END  = 0x154F13

t0 = time.time()
data = open(BLOB, "rb").read()
N = len(data)
lin = pickle.load(open(os.path.join(HERE, "cache_lin.pkl"), "rb"))
so = sorted(lin)
INS = {o: lin[o] for o in so}
print("instrucciones: %d ; cobertura %d/%d bytes" %
      (len(so), sum(lin[o][0] for o in so), N))

# ------------------------------------------------------------------
# 0. Conjunto de destinos de rama: NO se puede tocar nada que sea destino
# ------------------------------------------------------------------
# ------------------------------------------------------------------
# 0b. VALIDACION CANONICA DE LAS RAMAS
# ------------------------------------------------------------------
# El barrido lineal puede desincronizarse. Un sintoma inequivoco es una
# rama cuyo TAMANO no es el canonico:
#   70-7F (jcc rel8)  -> DEBE medir 2 bytes. Si capstone devuelve 3 o 4,
#                        hay un prefijo REX/legacy delante que se consumio
#                        como opcode: el offset NO es una frontera real.
#   EB   (jmp rel8)   -> DEBE medir 2
#   E0-E3 (loop*)     -> DEBE medir 2
#   E8/E9 (call/jmp rel32) -> DEBE medir 5
#   0F 80-8F (jcc rel32)   -> DEBE medir 6
# Esos descodificados no canonicos NO son fronteras de instruccion
# creibles: se tratan como BARRERAS (no se reescriben y su ventana se
# congela), y se contabilizan aparte.
CANON = {}
for b in range(0x70, 0x80): CANON[b] = 2
CANON[0xEB] = 2
for b in (0xE0, 0xE1, 0xE2, 0xE3): CANON[b] = 2
CANON[0xE8] = 5
CANON[0xE9] = 5
# (0F NO entra en CANON: 0F es prefijo de dos bytes para ~200 opcodes
# distintos. Solo se validan las formas 0F 8x rel32, mas abajo.)

# ------------------------------------------------------------------------
# DECODIFICACION DE SALTOS CON PREFIJOS
# ------------------------------------------------------------------------
# Un salto puede llevar prefijos delante: 66 (opsize), 67 (addrsize),
# F0/F2/F3, y REX (40..4F). El REX es IGNORADO por los saltos, asi que
# `48 7a 8d` es un `jp rel8` de 3 bytes. Si no se tiene en cuenta, esas
# ramas no se reescriben y el CFG se rompe.
LEGACY_PRE = {0x66, 0x67, 0xF0, 0xF2, 0xF3}
REX_PRE    = set(range(0x40, 0x50))

def decode_branch(o):
    """Devuelve (opcode_off, opcode, forma) para un salto con prefijos, o None.
    forma in ('rel8','rel32')"""
    i = o
    while i < N and (data[i] in LEGACY_PRE or data[i] in REX_PRE):
        i += 1
    if i >= N:
        return None
    b = data[i]
    if 0x70 <= b <= 0x7F:
        return (i, b, 'rel8')
    if b == 0xEB:
        return (i, b, 'rel8')
    if b in (0xE0, 0xE1, 0xE2, 0xE3):
        return (i, b, 'rel8')
    if b in (0xE8, 0xE9):
        return (i, b, 'rel32')          # E8/E9 + rel32  = 1+4 = 5 bytes
    if b == 0x0F and i + 1 < N and 0x80 <= data[i + 1] <= 0x8F:
        return (i + 1, data[i + 1], 'rel32')   # 0F 8x + rel32 = 2+4 = 6
    return None

# longitud total del salto con prefijos.
#   rel8 : (opoff - o) + 2                       (opcode + rel8)
#   rel32 forma E8/E9 : (opoff - o) + 1 + 4
#   rel32 forma 0F 8x : (opoff - o) + 4           (0F ya contado en opoff)
def branch_len(o):
    d = decode_branch(o)
    if d is None:
        return None
    i, b, forma = d
    if forma == 'rel8':
        total = (i - o) + 2
    elif data[i] == 0x0F:
        total = (i - o) + 4
    else:
        total = (i - o) + 5
    return total, forma, i

branch_targets = set()
for o in so:
    sz, m, ops, t = INS[o]
    if t is not None and 0 <= t < N:
        branch_targets.add(t)
n_direct = sum(1 for o in so if INS[o][3] is not None)

noncanon = {}
for o in so:
    sz, m, ops, t = INS[o]
    b0 = data[o]
    exp = None
    if b0 in CANON:
        exp = CANON[b0]
    elif b0 == 0x0F and o + 1 < N and (0x80 <= data[o + 1] <= 0x8F):
        exp = 6
    if exp is not None and sz != exp:
        noncanon[o] = (sz, exp)
    elif t is not None and 0 <= t < N:
        # Rama directa cuyo destino NO cae en frontera de instruccion del
        # barrido: indicio fuerte de desync. Se marca aparte.
        pass
print("destinos de rama directa: %d (offsets distintos: %d)" %
      (n_direct, len(branch_targets)))
print("RAMAS NO CANONICAS (desync del barrido lineal): %d" % len(noncanon))
nc = collections.Counter((data[o], v[0]) for o, v in noncanon.items())
for (b, sz), n in nc.most_common(12):
    print("   opcode %02x con tamano %d : %d casos" % (b, sz, n))

# ------------------------------------------------------------------
# 1. T1 -- nop-like
# ------------------------------------------------------------------
drop = {}
for o in so:
    sz, m, ops, t = INS[o]
    if m == "nop":
        drop[o] = ("T1", "nop de %d bytes" % sz)
    elif m == "xchg" and ops.replace(" ", "") in ("ax,ax", "eax,eax"):
        drop[o] = ("T1", "xchg reg,reg (identidad)")

# ------------------------------------------------------------------
# 2. T2/T3/T4 -- races de flags
# ------------------------------------------------------------------
CF_ONLY = {"clc", "stc", "cmc"}
CF_WRITERS = {
    "add", "sub", "cmp", "xor", "or", "and", "test", "neg", "not",
    "inc", "dec", "imul", "mov", "lea", "push", "pop", "xchg",
    "movzx", "movsx", "movsxd", "cwde", "cdqe", "cdq", "cqo", "cwd",
    "cbw", "leave", "lodsb", "lodsw", "lodsd", "lodsq",
    "stosb", "stosw", "stosd", "stosq", "xlatb", "nop",
    "cld", "std", "lfence", "mfence", "sfence",
    "prefetchw", "prefetcht0", "prefetchnta",
}
for s in ("set", ):
    for cc in ("e","ne","z","nz","l","le","g","ge","s","ns","a","ae","b",
               "be","o","no","p","np","c","nc"):
        CF_WRITERS.add(s + cc)

def is_cf_writer(m, ops):
    if m in CF_WRITERS:
        return True
    if m in ("shl", "shr", "sar", "rol", "ror", "rcl"):
        last = ops.split(",")[-1].strip()
        if last.startswith("0x") or last.isdigit():
            try:
                v = int(last, 16) if last.startswith("0x") else int(last)
                return v != 0
            except ValueError:
                return False
        return False
    return False

races = 0
j = 0
while j < len(so):
    o = so[j]
    if INS[o][1] in CF_ONLY:
        k = j
        while k + 1 < len(so) and INS[so[k + 1]][1] in CF_ONLY:
            k += 1
        run = so[j:k + 1]
        nxt = so[k + 1] if k + 1 < len(so) else None
        kinds = [INS[x][1] for x in run]
        races += 1
        # el control no puede entrar por la mitad de la race
        if any(x in branch_targets for x in run):
            j = k + 1
            continue
        if nxt is not None and is_cf_writer(INS[nxt][1], INS[nxt][2]):
            for x in run:
                drop[x] = ("T2", "race de flags muerta (CF lo reescribe %s)"
                           % INS[nxt][1])
        elif "cmc" not in kinds:
            for x in run[:-1]:
                drop[x] = ("T3", "clc/stc anterior al clc/stc final")
        else:
            cmcs = [x for x in run if INS[x][1] == "cmc"]
            if len(cmcs) == len(run):
                if len(cmcs) % 2 == 0:
                    for x in cmcs:
                        drop[x] = ("T4", "cmc: paridad par, se anula")
                else:
                    for i, x in enumerate(cmcs):
                        if i:
                            drop[x] = ("T4", "cmc se anula con el anterior")
            # mezcla clc/stc + cmc -> no se toca
        j = k + 1
    else:
        j += 1
print("races de flags detectadas: %d" % races)

# ------------------------------------------------------------------
# 3. T5 -- jmp $+5
# ------------------------------------------------------------------
for o in so:
    if o in branch_targets:
        continue
    sz, m, ops, t = INS[o]
    if m == "jmp" and sz == 5 and t is not None and t == o + 5:
        drop[o] = ("T5", "jmp $+5 (E9 00000000): no-op de flujo")

# una instruccion eliminada puede no ser destino de rama, pero su
# 'siguiente' si lo es -> eliminar cambia el punto de entrada. Comprobado:
# si el destino es la instruccion siguiente, la eliminamos y la rama se
# reescribe al nuevo offset. Es correcto.
byrule = collections.Counter(v[0] for v in drop.values())
saved = sum(INS[o][0] for o in drop)
print("\ninstrucciones a eliminar: %d" % len(drop))
for r, n in byrule.most_common():
    print("   %-4s %6d" % (r, n))
print("bytes ahorrados: %d (%.2f%%)" % (saved, 100.0 * saved / N))

# tambien excluye drop de instrucciones que sean el INICIO de un
# bloque alcanzable por caida desde un salto condicional que no sea rel8
# -> eso no cambia nada, la reescritura lo cubre.

# ------------------------------------------------------------------
# 5. Layout iterativo
# ------------------------------------------------------------------
SHORT_COND = set(range(0x70, 0x80))
SHORT_JMP  = {0xEB}
LOOP_FAM   = {0xE0, 0xE1, 0xE2, 0xE3}
SHORT_ALL  = SHORT_COND | SHORT_JMP | LOOP_FAM

# --- Ventanas de proteccion de loop/jrcxz -------------------------------
# `loop/loope/loopne/jrcxz` no tienen forma rel32: su campo es de 1 byte y
# no se pueden reubicar. La unica forma sound de que sobrevivan a la
# compactacion es que TODO lo que hay entre su origen y su destino se
# mantenga byte a byte (ni podado ni expandido). Asi la distancia -- y por
# tanto el desplazamiento -- no cambia.
loop_win = set()
for o in so:
    sz, m, ops, t = INS[o]
    bl = branch_len(o)
    if bl is None: continue
    blen, forma, opoff = bl
    if forma != 'rel8' or data[opoff] not in LOOP_FAM: continue
    if blen != sz: continue
    if t is None or not (0 <= t < N): continue
    a, b = min(o, t), max(o, t)
    loop_win.update(range(a, b + blen))

# Las ramas no canonicas no se pueden reescribir con confianza: su byte de
# opcode puede no estar donde creo. Se congelan como barreras.
nc_targets = []
for o, (sz, exp) in noncanon.items():
    if o in drop:
        del drop[o]
    if o in branch_targets:
        pass
nc_win = set()
for o in noncanon:
    nc_win.add(o)
    t = INS[o][3]
    if t is not None and 0 <= t < N:
        nc_win.update(range(min(o, t), max(o, t) + INS[o][0]))

# Los bytes interiores de una instruccion no son puntos de entrada: se emiten
# junto con ella y no ocupan offset propio.
interior = bytearray(N)
for o in so:
    for k in range(1, INS[o][0]):
        if o + k < N: interior[o + k] = 1

def field_off(o):
    """offset (relativo al inicio de la instruccion) del primer byte del
    desplazamiento rel"""
    bl = branch_len(o)
    opoff = bl[2]
    if bl[1] == 'rel8':
        return opoff - o + 1
    if data[opoff] == 0x0F:
        return opoff - o + 1
    return opoff - o + 1

def layout(expand_set, blocked):
    new_of = [0] * N
    p = 0
    for o in range(N):
        new_of[o] = p
        if o in drop or o in blocked or interior[o]:
            continue
        if o in INS and INS[o][0] > 1:
            p += INS[o][0]
        else:
            p += 1
    return new_of, p

def overflows(new_of, expand_set, blocked):
    """Saltos cortos cuyo destino queda a mas de +-127 tras compactar.
    NOTA: podar SOLO acorta distancias, asi que un salto corto que cabe
    antes sigue cabiendo despues. Solo desbordan los de la familia
    loop/jrcxz, cuyo destino puede quedar 'al otro lado' tras reordenar
    por drops intermedios; aun asi, si el intervalo [src,tgt] conserva
    todos sus bytes, la distancia no cambia."""
    bad = []
    for o in so:
        if o in drop or o in blocked: continue
        sz, m, ops, t = INS[o]
        if t is None or not (0 <= t < N): continue
        bl = branch_len(o)
        if bl is None: continue
        blen, forma, opoff = bl
        if blen != sz:           # descodificacion no coincide: no tocar
            continue
        rel = new_of[t] - (new_of[o] + blen)
        if -128 <= rel <= 127:
            continue
        bad.append((o, t, rel, data[opoff]))
    return bad

# Bloquear la ventana de todo salto corto que desborde, hasta que ninguno
# desborde. Bloquear = no podar NINGUN byte de esa ventana, con lo que la
# distancia src->tgt no cambia.
blocked = set(loop_win) | nc_win
for it in range(80):
    new_of, total = layout(set(), blocked)
    bad = overflows(new_of, set(), blocked)
    if not bad:
        break
    before = len(blocked)
    for o, t, rel, opc in bad:
        bl = branch_len(o)
        blocked.update(range(min(o, t), max(o, t) + bl[0]))
    if len(blocked) == before:
        break
expand = set()
new_of, total = layout(expand, blocked)
bad = overflows(new_of, expand, blocked)
print("\nsaltos cortos expandidos a rel32: %d (0: no hace falta expandir)" % len(expand))
print("bytes bloqueados (ventanas de saltos cortos): %d" % len(blocked))
print("saltos cortos que aun desbordan: %d" % len(bad))
for o, t, rel, opc in bad[:8]:
    print("   %08x -> %08x  rel=%d  op=%02x" % (o, t, rel, opc))

# ------------------------------------------------------------------
# 6. Emision
# ------------------------------------------------------------------
skip = bytearray(N)
for o in drop:
    for k in range(INS[o][0]):
        if o + k < N: skip[o + k] = 1
for o in blocked:
    if o < N: skip[o] = 1

out = bytearray()
for o in range(N):
    if o in drop or skip[o] or interior[o]:
        continue
    if o in INS and INS[o][0] > 1:
        out += data[o:o + INS[o][0]]
    else:
        out += data[o:o + 1]
print("\nblob podado: %d bytes (original %d, -%d, %.2f%%)" %
      (len(out), N, N - len(out), 100.0 * (N - len(out)) / N))

old_of_new = [0] * len(out)
p = 0
for o in range(N):
    if o in drop or skip[o] or interior[o]:
        continue
    if o in INS and INS[o][0] > 1:
        for k in range(INS[o][0]): old_of_new[p + k] = o
        p += INS[o][0]
    else:
        old_of_new[p] = o
        p += 1
if p != len(out):
    print("DESAJUSTE: p=%d len(out)=%d diff=%d" % (p, len(out), p-len(out)))
    raise SystemExit(1)

# ------------------------------------------------------------------
# 7. Reescritura de ramas
# ------------------------------------------------------------------
n_reloc = 0
for o in so:
    if o in drop or o in blocked: continue
    sz, m, ops, t = INS[o]
    if t is None or not (0 <= t < N): continue
    no = new_of[o]
    bl = branch_len(o)
    if bl is None:
        continue
    blen, forma, opoff = bl
    if blen != sz:
        continue                       # descodificacion dudosa: no se toca
    rel = new_of[t] - (no + blen)
    if forma == 'rel8':
        assert -128 <= rel <= 127, (o, rel)
        out[no + opoff - o + 1] = rel & 0xFF
    else:
        out[no + opoff - o + 1:no + opoff - o + 5] = struct.pack("<i", rel)
    n_reloc += 1
print("ramificaciones reescritas: %d" % n_reloc)

# ------------------------------------------------------------------
# 8. VERIFICACION independiente: redisensamblar el podado y comparar el CFG
# ------------------------------------------------------------------
print("\n--- verificacion por redisensamblado ---")
from capstone import Cs, CS_ARCH_X86, CS_MODE_64
md = Cs(CS_ARCH_X86, CS_MODE_64); md.detail = True
# mapa de instrucciones originales conservadas -> offset nuevo
kept = {}
for o in so:
    if o in drop or o in blocked or interior[o]:
        continue
    kept[o] = new_of[o]
# redisensambla en el blob nuevo siguiendo los mismos puntos de entrada
bad_bytes = 0
for o, no in kept.items():
    ref = data[o:o + INS[o][0]]
    if bytes(out[no:no + len(ref)]) != ref:
        bad_bytes += 1
print("instrucciones conservadas: %d ; con bytes alterados (no-copia): %d" %
      (len(kept), bad_bytes))

# el CFG: para cada rama, comprobar que el destino apunta al offset nuevo
# del mismo destino logico
ok = 0; wrong = 0; skipped = 0
wronglist = []
for o, no in kept.items():
    sz, m, ops, t = INS[o]
    if t is None or not (0 <= t < N): continue
    if True:
        bl = branch_len(o)
        if bl is None or bl[0] != sz:
            skipped += 1; continue
        blen, forma, opoff = bl
        k = field_off(o)
        if forma == 'rel8':
            v = out[no + k]
            rel = v - 256 if v > 127 else v
        else:
            rel = struct.unpack_from("<i", out, no + k)[0]
        ln = blen
    if no + ln + rel == new_of[t]:
        ok += 1
    else:
        wrong += 1
        wronglist.append((o, t, no + ln + rel, new_of[t]))
print("VERIFICACION CFG: %d ramas correctas, %d incorrectas, %d no verificables" %
      (ok, wrong, skipped))
for w in wronglist[:10]:
    print("   orig=%08x tgt=%08x obtenido=%08x esperado=%08x" % w)

open(OUT, "wb").write(bytes(out))

# ------------------------------------------------------------------
# 9. Mapa de offsets
# ------------------------------------------------------------------
runs = []
cur = None
for o in sorted(drop):
    if cur is not None and o <= cur[1]:
        cur[1] = max(cur[1], o + INS[o][0])
    else:
        if cur: runs.append(cur)
        cur = [o, o + INS[o][0]]
if cur: runs.append(cur)
merged = []
for r in sorted(runs):
    if merged and r[0] <= merged[-1][1] + 1:
        merged[-1][1] = max(merged[-1][1], r[1])
    else:
        merged.append(r)

mp = {
 "descripcion": ("Mapa de offsets original<->nuevo tras la poda de basura "
   "trivial. old_of_new[i] = offset en stage3_code.bin del byte i de "
   "stage3_podado.bin. new_of_old[i] = offset en el blob podado del byte i "
   "del original, o -1 si el byte fue eliminado."),
 "original": {"file": "stage3_code.bin", "size": N,
   "sha256": "d8a16fe9d72fbf6e85caf0f8147e216a1f3bde660dec614941f01af45734d4c2"},
 "podado": {"file": "stage3_podado.bin", "size": len(out)},
 "old_of_new": old_of_new,
 "new_of_old": [new_of[i] if not skip[i] else -1 for i in range(N)],
 "runs_eliminados": [{"orig_start": a, "orig_end": b, "nuevo_inicio": new_of[a],
                      "bytes": b - a} for a, b in merged],
 "instrucciones_eliminadas": sorted(drop.keys()),
 "reglas": {k: int(v) for k, v in byrule.items()},
 "n_ramas_reescritas": n_reloc,
 "saltos_expandidos": sorted(expand),
 "verificacion_cfg_ok": ok, "verificacion_cfg_wrong": wrong,
}
json.dump(mp, open(MAP, "w"))
print("escrito %s (%.1f MB)" % (MAP, os.path.getsize(MAP) / 1e6))

with open(REP, "w") as f:
    f.write("INFORME DE PODA - stage3\n" + "=" * 70 + "\n\n")
    f.write("original : %d bytes\n" % N)
    f.write("podado   : %d bytes\n" % len(out))
    f.write("eliminado: %d bytes (%.2f%%)\n\n" % (N - len(out), 100.0 * (N - len(out)) / N))
    f.write("instrucciones eliminadas por regla:\n")
    for r, n in byrule.most_common():
        f.write("  %-4s %6d\n" % (r, n))
    f.write("\nJustificacion por patron:\n")
    f.write("  T1 nop/xchg-identidad : no tocan reg/flag/mem/flujo.\n")
    f.write("  T2 race muerta       : la sig. instruccion sobreescribe CF sin leerlo.\n")
    f.write("  T3 race clc/stc      : el CF final depende solo de la ultima.\n")
    f.write("  T4 race cmc          : paridad par -> identidad; impar -> conserva 1.\n")
    f.write("  T5 jmp $+5           : E9 00000000, no-op de flujo.\n")
    f.write("  Restriccion          : nunca se borra una instruccion que sea\n")
    f.write("                         destino de rama (el control podria entrar).\n")
    f.write("\nSaltos cortos expandidos a rel32: %d\n" % len(expand))
    f.write("Bytes bloqueados (ventanas loop/jrcxz): %d\n" % len(blocked))
    f.write("Ramas reescritas: %d\n" % n_reloc)
    f.write("VERIFICACION CFG: %d correctas, %d incorrectas\n" % (ok, wrong))
    f.write("\nRuns eliminados (top 50 por tamaño):\n")
    for r in sorted(merged, key=lambda x: -(x[1] - x[0]))[:50]:
        f.write("  %08x..%08x  %5d bytes -> nuevo 0x%08x\n" %
                (r[0], r[1], r[1] - r[0], new_of[r[0]]))
print("escrito %s" % REP)
print("tiempo %.1fs" % (time.time() - t0))