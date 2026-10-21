#!/usr/bin/env python3
"""
s7_descenso_recursivo.py  (v2, correcto)
Descenso recursivo EXHAUSTIVO con las dos ramas de todo salto condicional.
Mide cobertura real del blob, construye CFG, y clasifica bloques.

Diferencias con la v1 (que estaba mal):
  - se exploran AMBAS ramas de cada salto condicional
  - el guardia de longitud de traza es por bloque, no global
  - aristas/entrada/salida bien calculadas
"""
import os, struct, collections, bisect, json, statistics, sys
from capstone import Cs, CS_ARCH_X86, CS_MODE_64

HERE = os.path.dirname(os.path.abspath(__file__))
data = open(os.path.join(HERE, "stage3_code.bin"), "rb").read()
N = len(data)
END = 0x154F13
RVA_BLOB = 0xE36000
VA_BLOB  = 0x140E36000

md = Cs(CS_ARCH_X86, CS_MODE_64)
md.detail = False

# ---------- cache de desensamblado ----------
_cache = {}
def dis(o):
    v = _cache.get(o)
    if v is not None:
        return v
    r = None
    if 0 <= o < N:
        r = next(md.disasm(data[o:o + 15], o), None)
    # guardamos (size, mnem, target_rel_str)
    if r is None:
        t = (1, ".bad", None)
    else:
        t = (r.size, r.mnemonic, r.op_str)
    _cache[o] = t
    return t

COND = {"je","jne","jz","jnz","jb","jbe","ja","jae","jl","jle","jg","jge","js","jns",
        "jo","jno","jp","jnp","jc","jnc","jcxz","jrcxz","jecxz","loop","loope","loopne"}
UNCOND = {"jmp"}
RET = {"ret","retf","retfq","iret","iretd","iretq"}
TERM = RET | {"hlt","ud2"}

def target_of(o):
    """Devuelve destino de un salto directo o None."""
    sz, m, ops = dis(o)
    if ops and ops.startswith("0x"):
        try:
            return int(ops, 16)
        except ValueError:
            return None
    return None

# ---------- 1. semillas ----------
seeds = set()
mdf = Cs(CS_ARCH_X86, CS_MODE_64); mdf.detail = False
lin = []
p = 0
while p < N:
    ins = next(mdf.disasm(data[p:p + 15], p), None)
    if ins is None:
        p += 1
        continue
    lin.append((p, ins.size, ins.mnemonic))
    p += ins.size
for o, sz, m in lin:
    if m == "jmp":
        t = target_of(o)
        if t is not None:
            seeds.add(t)
i = data.find(b"\x48\x81\xec")
while i != -1:
    seeds.add(i); i = data.find(b"\x48\x81\xec", i + 1)
seeds = {s for s in seeds if 0 <= s < N}
print("instrucciones del barrido lineal: %d ; semillas: %d" % (len(lin), len(seeds)))

# ---------- 2. descenso recursivo con ambas ramas ----------
INS = {}            # off -> (size, mnem, tgt)
work = list(seeds)
outside = collections.Counter()
while work:
    o = work.pop()
    if o in INS:
        continue
    if not (0 <= o < N):
        outside[o] += 1
        continue
    n_in_trace = 0
    while True:
        if o in INS:
            break
        sz, m, ops = dis(o)
        tgt = target_of(o) if (m in COND or m in UNCOND) else None
        INS[o] = (sz, m, tgt)
        n_in_trace += 1
        if m in COND:
            if tgt is not None:
                work.append(tgt)
            work.append(o + sz)
            break
        if m in UNCOND:
            if tgt is not None:
                work.append(tgt)
            break
        if m in TERM:
            break
        if m == "call":
            t = target_of(o) if ops.startswith("0x") else None
            if t is not None and 0 <= t < N:
                work.append(t)
        o += sz
        if n_in_trace > 2000:
            break

cov = sum(v[0] for v in INS.values())
print("instrucciones alcanzables: %d / %d" % (len(INS), len(lin)))
print("bytes alcanzables:         %d / %d (%.2f%%)" % (cov, N, 100.0 * cov / N))
mn = collections.Counter(v[1] for v in INS.values())
print("mnemonicos alcanzables: ret=%d  call=%d  jmp=%d  cond=%d" %
      (mn["ret"], mn["call"], mn["jmp"],
       sum(mn[c] for c in COND)))

print("\n=== destinos FUERA del blob ===")
neg = [(t - VA_BLOB, c) for t, c in outside.items() if t < VA_BLOB]
pos = [(t - VA_BLOB, c) for t, c in outside.items() if t >= VA_BLOB]
print("  por debajo (zona cifrada de .w7/): %d saltos, %d destinos distintos"
      % (sum(c for _, c in neg), len(neg)))
if neg:
    cn = collections.Counter()
    for t, c in neg: cn[t] += c
    for t, c in cn.most_common(12):
        print("    rel %+10d  RVA 0x%08X  VA 0x%016X  n=%d" % (t, t + RVA_BLOB, VA_BLOB + t, c))
print("  por encima: %d saltos, %d destinos" % (sum(c for _, c in pos), len(pos)))

# ---------- 3. bloques basicos ----------
leaders = set()
for o, (sz, m, t) in INS.items():
    if m in COND:
        if t is not None and t in INS: leaders.add(t)
        if o + sz in INS: leaders.add(o + sz)
    elif m in UNCOND:
        if t is not None and t in INS: leaders.add(t)
        if o + sz in INS: leaders.add(o + sz)
    elif m in TERM or m == "call":
        if o + sz in INS: leaders.add(o + sz)
allst = sorted(INS)
leaders = {l for l in leaders if l in INS}

blks = []
cur = None
for o in allst:
    sz, m, t = INS[o]
    if cur is None or o in leaders:
        if cur: blks.append(cur)
        cur = [o, o + sz, [o]]
    else:
        cur[1] = o + sz
        cur[2].append(o)
    if m in COND or m in UNCOND or m in TERM:
        blks.append(cur); cur = None
if cur: blks.append(cur)

bidx = {s: i for i, (s, e, n) in enumerate(blks)}
edges = collections.Counter()
for i, (s, e, n) in enumerate(blks):
    last = n[-1]
    sz, m, t = INS[last]
    if m in COND:
        if t in bidx: edges[(i, bidx[t])] += 1
        nx = last + sz
        if nx in bidx: edges[(i, bidx[nx])] += 1
    elif m in UNCOND:
        if t in bidx: edges[(i, bidx[t])] += 1
indeg = collections.Counter(); outdeg = collections.Counter()
for (a, b), c in edges.items():
    outdeg[a] += 1; indeg[b] += 1
nor = sum(1 for i, (s, e, n) in enumerate(blks) if INS[n[-1]][1] in RET)

print("\n=== BLOQUES BASICOS ===")
print("  bloques:            %d" % len(blks))
print("  aristas:            %d  (media %.2f salidas/bloque)" % (sum(edges.values()),
                                                               sum(edges.values()) / len(blks)))
print("  bloques que terminan en ret: %d" % nor)
print("  bloques sin entrada: %d (%.1f%%)" % (sum(1 for i in range(len(blks)) if indeg[i] == 0),
                                               100.0 * sum(1 for i in range(len(blks)) if indeg[i]==0)/len(blks)))
sizes = [e - s for s, e, n in blks]
ni = [len(n) for s, e, n in blks]
print("  tamaño: media %.1f B / mediana %d / max %d ; instr media %.1f / mediana %d" %
      (statistics.mean(sizes), statistics.median(sizes), max(sizes),
       statistics.mean(ni), statistics.median(ni)))

# classify blocks
FS = mn  #Counter
junkish = {"clc","stc","cmc","nop","xchg","lahf","sahf","pushfq","popfq",
           "cbw","cwd","cdq","cqo","cwde","cdqe","stosb","lodsb","scasb",
           "in","out","ins","outs","hlt","cmpsb","movsb","movsq"}
def purity(n):
    """fraccion de instrucciones del bloque que son basura trivial"""
    if not n: return 0.0
    j = sum(1 for o in n if INS[o][1] in junkish)
    return j / float(len(n))
bins = collections.Counter()
for s, e, n in blks:
    bins[round(purity(n), 1)] += 1
print("\n=== bloques por fraccion de 'basura trivial' (clc/stc/cmc/nop/xchg/...) ===")
for k in sorted(bins):
    print("   %.1f : %6d bloques" % (k, bins[k]))

# ---------- 4. hubs / aplanado ----------
hub = sorted([i for i in range(len(blks)) if indeg[i] > 5], key=lambda i: -indeg[i])
print("\n=== NODOS DE APLANADO (indeg>5): %d ===" % len(hub))
for i in hub[:20]:
    s, e, n = blks[i]
    print("   blk %08x..%08x  indeg=%4d  outdeg=%2d  instrs=%3d  fin=%s" %
          (s, e, indeg[i], outdeg[i], len(n), INS[n[-1]][1]))

json.dump({"instructions_alcanzables": len(INS), "bytes_alcanzables": cov,
           "bloques": len(blks), "aristas": sum(edges.values()),
           "nodos_aplanado_indeg5": len(hub), "bloques_ret": nor},
          open(os.path.join(HERE, "s7_cfg.json"), "w"), indent=2)

# dump de bloques para reutilizar
with open(os.path.join(HERE, "s7_bloques.txt"), "w") as f:
    for i, (s, e, n) in enumerate(blks):
        f.write("%08x %08x %d\n" % (s, e, len(n)))
print("\nescrito s7_cfg.json y s7_bloques.txt")