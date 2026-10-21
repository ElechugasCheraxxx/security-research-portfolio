#!/usr/bin/env python3
"""
s11_cache_analisis.py -- Una sola pasada que:
  (1) cachea el desensamblado lineal en disco,
  (2) calcula el grafo,
  (3) investiga los 9 'hubs' con ~410 entradas cada uno,
  (4) busca el patron de las FUENTES que saltan a un hub (replicacion).
"""
import os, sys, struct, pickle, collections, bisect, statistics, time, json
from capstone import Cs, CS_ARCH_X86, CS_MODE_64
from capstone.x86_const import X86_OP_IMM

HERE = os.path.dirname(os.path.abspath(__file__))
data = open(os.path.join(HERE, "stage3_code.bin"), "rb").read()
N = len(data)
END = 0x154F13
VA_BLOB = 0x140E36000

CACHE = os.path.join(HERE, "cache_lin.pkl")
t0 = time.time()

md = Cs(CS_ARCH_X86, CS_MODE_64); md.detail = True
md.skipdata = True

if os.path.exists(CACHE):
    lin = pickle.load(open(CACHE, "rb"))
    print("cache cargado: %d entradas (%.1fs)" % (len(lin), time.time() - t0))
else:
    lin = {}
    for ins in md.disasm(data, 0):
        tgt = None
        if ins.id != 0:
            ops = ins.operands
            if (ins.mnemonic == "jmp" or ins.mnemonic == "call" or
                ins.mnemonic[0] == "j" or ins.mnemonic.startswith("loop")):
                if ops and ops[0].type == X86_OP_IMM:
                    tgt = ops[0].imm
        lin[ins.address] = (ins.size, ins.mnemonic,
                            "" if ins.id == 0 else ins.op_str, tgt)
    pickle.dump(lin, open(CACHE, "wb"), protocol=4)
    print("cache construido: %d entradas (%.1fs)" % (len(lin), time.time() - t0))

sorted_off = sorted(lin)
def is_start(o):
    i = bisect.bisect_left(sorted_off, o)
    return i < len(sorted_off) and sorted_off[i] == o

# ---------------- FUENTES de los hubs ----------------
HUBS = [0xcce50, 0x62887, 0x695f1, 0x81e8e, 0x117340, 0xcbb18,
        0x124358, 0x90bc5, 0x09985, 0xa67df]

src_of = collections.defaultdict(list)
for o, (sz, m, ops, t) in lin.items():
    if t in HUBS:
        src_of[t].append(o)
for h in HUBS:
    print("hub %08x <- %d fuentes" % (h, len(src_of[h])))

print("\n=== las 12 primeras fuentes del hub 0x09985, con 10 instr de contexto ===")
md2 = Cs(CS_ARCH_X86, CS_MODE_64); md2.detail = False
for s in sorted(src_of[0x09985])[:12]:
    print("  --- src %08x ---" % s)
    for ins in md2.disasm(data[s - 30:s + 6], s - 30):
        mk = " <<<" if ins.address == s else ""
        print("     %08x %-20s %-8s %s%s" % (ins.address, ins.bytes.hex(),
                                              ins.mnemonic, ins.op_str, mk))

# ¿las fuentes son clones unas de otras?
print("\n===.bytes 8 ANTES del jmp, por hub (primeras 20 fuentes) ===")
for h in HUBS[:4]:
    pre = [data[s - 8:s].hex() for s in sorted(src_of[h])[:20]]
    print("  hub %08x:" % h)
    c = collections.Counter(pre)
    for k, n in c.most_common(6):
        print("     %s  x%d" % (k, n))

# ---------------- estructura global de los jmp ----------------
print("\n=== ¿de donde salen los jmp? (instruccion que precede al E9) ===")
prev_of = {}
so = sorted_off
for i in range(1, len(so)):
    prev_of[so[i]] = so[i - 1]
c = collections.Counter()
for o in so:
    if lin[o][1] == "jmp" and lin[o][0] == 5:
        p = prev_of.get(o)
        c[lin[p][1] if p is not None else "?"] += 1
for m, n in c.most_common(25):
    print("   %-10s %7d" % (m, n))

print("\n=== ¿que instruccion SIGUE al jmp? (solo E9) ===")
nxt = {}
for i in range(len(so) - 1):
    nxt[so[i]] = so[i + 1]
c = collections.Counter()
for o in so:
    if lin[o][1] == "jmp" and lin[o][0] == 5:
        nx = nxt.get(o)
        c[lin[nx][1] if nx is not None else "?"] += 1
for m, n in c.most_common(25):
    print("   %-10s %7d" % (m, n))

# ---------------- distancia entre jmp consecutivos ----------------
print("\n=== gap entre jmp consecutivos en el barrido lineal ===")
gaps = []
for i in range(1, len(so)):
    if lin[so[i - 1]][1] == "jmp" and lin[so[i]][1] == "jmp":
        gaps.append(so[i] - so[i - 1])
print("   pares jmp-jmp: %d" % len(gaps))
cg = collections.Counter(gaps)
for g, n in sorted(cg.items())[:15]:
    print("   gap %3d : %7d (%.1f%%)" % (g, n, 100.0 * n / max(len(gaps), 1)))

# ---------------- ¿hay 'call' reales? ----------------
print("\n=== llamadas ===")
calls = [(o, lin[o][2], lin[o][3]) for o in so if lin[o][1] == "call"]
print("   call totales (barrido lineal): %d" % len(calls))
direct = [c for c in calls if c[2] is not None]
print("   call a destino inmediato (rel32): %d" % len(direct))
ind = [c for c in calls if c[2] is None]
print("   call indirectas (registro/memoria): %d" % len(ind))
for o, ops, t in ind[:20]:
    ins = next(md2.disasm(data[o:o+15], o), None)
    print("     %08x  %-20s %s" % (o, ins.bytes.hex(), ops))
print("   ... destinos directos, 20 primeros:")
for o, ops, t in direct[:20]:
    print("     %08x -> %08x  %s" % (o, t, "dentro" if 0 <= t < N else "FUERA"))

# ---------------- rets ----------------
print("\n=== ret / retf ===")
c = collections.Counter()
for o in so:
    m = lin[o][1]
    if m.startswith("ret") or m in ("iret","iretd","iretq"):
        c[m] += 1
print("  ", dict(c))

# ---------------- tamaño de funcion: sub rsp,imm32 -> ret ----------------
print("\n=== estimacion de funciones: 'sub rsp,imm32' ... 'ret' ===")
subs = [o for o in so if data[o:o+3] == bytes.fromhex("4881ec")]
print("   'sub rsp,imm32' alineados en frontera de instruccion: %d / %d" %
      (sum(1 for o in subs if is_start(o)), len(subs)))
rets = [o for o in so if lin[o][1] == "ret"]
print("   ret alineados: %d" % len(rets))
# emparejar cada sub con el primer ret alcanzable por avance lineal
import bisect as _b
pairs = []
for s in sorted(subs):
    if not is_start(s): continue
    i = _b.bisect_left(so, s)
    for j in range(i, min(i + 400, len(so))):
        if lin[so[j]][1] in ("ret", "retf", "jmp"):
            if lin[so[j]][1] == "ret":
                pairs.append((s, so[j], so[j] - s, j - i))
            break
szs = [p[2] for p in pairs]
print("   pares sub->ret (lineal): %d" % len(pairs))
if szs:
    print("   tamaño medio de 'funcion': %.0f bytes  mediana %d  max %d" %
          (statistics.mean(szs), statistics.median(szs), max(szs)))
    print("   dist de tamaños:", collections.Counter(
        (s // 64) * 64 for s in szs).most_common(12))

json.dump({"lin_instr": len(lin), "jmps": sum(1 for o in so if lin[o][1] == "jmp"),
           "calls": len(calls), "calls_direct": len(direct),
           "rets": len(rets), "subs": len(subs)},
          open(os.path.join(HERE, "s11_stats.json"), "w"), indent=2)
print("\nhecho en %.1fs" % (time.time() - t0))