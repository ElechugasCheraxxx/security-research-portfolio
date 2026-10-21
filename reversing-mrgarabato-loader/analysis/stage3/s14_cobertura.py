#!/usr/bin/env python3
"""
s14_cobertura.py -- Analiza la COBERTURA del descenso recursivo y que hay en la
parte NO alcanzable. Ademas traza hacia atras desde los prologos MSVC reales.
"""
import os, sys, struct, pickle, collections, bisect, statistics, time
from capstone import Cs, CS_ARCH_X86, CS_MODE_64
from capstone.x86_const import X86_OP_IMM

HERE = os.path.dirname(os.path.abspath(__file__))
data = open(os.path.join(HERE, "stage3_code.bin"), "rb").read()
N = len(data); END = 0x154F13
lin = pickle.load(open(os.path.join(HERE, "cache_lin.pkl"), "rb"))
so = sorted(lin)
soset = set(so)

md = Cs(CS_ARCH_X86, CS_MODE_64); md.detail = True
c2 = {}
def dis(o):
    v = c2.get(o)
    if v is not None: return v
    r = None
    if 0 <= o < N:
        r = next(md.disasm(data[o:o + 15], o), None)
    if r is None:
        t = (1, ".bad", "", None)
    else:
        t = None
        if (r.mnemonic == "jmp" or r.mnemonic == "call" or r.mnemonic[0] == "j"
                or r.mnemonic.startswith("loop")) and r.operands and r.operands[0].type == X86_OP_IMM:
            t = r.operands[0].imm
        t = (r.size, r.mnemonic, r.op_str, t) if False else (r.size, r.mnemonic, r.op_str, t)
    c2[o] = t
    return t

COND = {"je","jne","jz","jnz","jb","jbe","ja","jae","jl","jle","jg","jge","js","jns",
        "jo","jno","jp","jnp","jc","jnc","jcxz","jrcxz","jecxz","loop","loope","loopne"}
UN = {"jmp"}
RET = {"ret","retf","iret","iretd","iretq"}
TERM = RET | {"hlt","ud2"}

# ---------- semillas: TODO destino de E9 + TODO sub rsp + hubs ----------
seeds = set()
for o in range(END):
    if data[o] == 0xE9:
        t = o + 5 + struct.unpack_from("<i", data, o + 1)[0]
        if 0 <= t < N: seeds.add(t)
i = data.find(b"\x48\x81\xec")
while i != -1 and i < END:
    seeds.add(i); i = data.find(b"\x48\x81\xec", i + 1)
print("semillas: %d" % len(seeds))

# ---------- descenso recursivo completo ----------
INS = {}
work = list(seeds)
outside = collections.Counter()
while work:
    o = work.pop()
    if o in INS: continue
    if not (0 <= o < N):
        outside[o] += 1; continue
    k = 0
    while True:
        if o in INS: break
        sz, m, ops, t = dis(o)
        INS[o] = (sz, m, t)
        k += 1
        if m in COND:
            if t is not None: work.append(t)
            work.append(o + sz); break
        if m in UN:
            if t is not None: work.append(t)
            break
        if m in TERM: break
        if m == "call" and t is not None: work.append(t)
        o += sz
        if k > 2000: break

reach_bytes = sum(v[0] for v in INS.values())
print("alcanzable: %d instr, %d bytes (%.2f%% del blob)" %
      (len(INS), reach_bytes, 100.0 * reach_bytes / END))
print("saltos a fuera del blob: %d" % sum(outside.values()))

# ---------- ¿que hay en lo NO alcanzable? ----------
unreach = [o for o in so if o not in INS]
print("\ninstrucciones del barrido lineal NO alcanzables: %d (%.1f%%)" %
      (len(unreach), 100.0 * len(unreach) / len(so)))
mb = collections.Counter(lin[o][1] for o in unreach)
mr = collections.Counter(INS[o][1] for o in INS)
print("\n%-10s %10s %10s %8s" % ("mnem", "alcanz %", "NO alc %", "ratio"))
rows = []
for m in set(mb) | set(mr):
    a = 100.0 * mr.get(m, 0) / max(len(INS), 1)
    b = 100.0 * mb.get(m, 0) / max(len(unreach), 1)
    rows.append((b / a if a else 999, m, a, b))
rows.sort(reverse=True)
for r, m, a, b in rows[:22]:
    print("%-10s %9.2f%% %9.2f%% %8.2f" % (m, a, b, r))

# ¿los 'sub rsp' están alcanzables?
subs = [o for o in so if data[o:o+3] == bytes.fromhex("4881ec")]
print("\n'sub rsp,imm32': %d totales, %d alcanzables (%.1f%%)" %
      (len(subs), sum(1 for o in subs if o in INS),
       100.0 * sum(1 for o in subs if o in INS) / len(subs)))
rets = [o for o in so if lin[o][1] in RET]
print("ret: %d totales, %d alcanzables" % (len(rets), sum(1 for o in rets if o in INS)))

# ---------- traza hacia ATRAS desde cada prologo MSVC ----------
print("\n\n=== traza hacia atras desde los 13 prologos con frame>=0x80 ===")
big = [(o, struct.unpack_from("<I", data, o + 3)[0]) for o in subs
       if struct.unpack_from("<I", data, o + 3)[0] >= 128]
preds = collections.defaultdict(set)
for o, (sz, m, t) in INS.items():
    if t is not None and t in INS:
        preds[t].add(o)

def trace_back(start, depth=3, maxn=25):
    cur = {start}
    for d in range(depth):
        nxt = set()
        for x in cur:
            nxt |= preds.get(x, set())
        if not nxt: break
        print("   gen %d: %d predecesores -> %s" %
              (d + 1, len(nxt), " ".join(hex(y) for y in sorted(nxt)[:maxn])))
        cur = nxt
    return cur

for o, fr in big[:6]:
    print("\n  prologo 0x%08x frame=0x%x" % (o, fr))
    trace_back(o)

# ---------- los hubs: ¿son alcanzables sus fuentes? ----------
print("\n\n=== los 10 hubs: alcanzabilidad de sus 418 fuentes ===")
HUBS = [0xcce50,0x62887,0x695f1,0x81e8e,0x117340,0xcbb18,0x124358,0x90bc5,0x9985,0xa67df]
for h in HUBS:
    srcs = [o for o in so if lin[o][3] == h]
    ra = sum(1 for o in srcs if o in INS)
    # el hub mismo alcanzable?
    print("   hub %08x  alcanzable=%s  fuentes=%d alcanzables=%d" %
          (h, h in INS, len(srcs), ra))

import pickle as pk
pk.dump({"INS": dict(INS)},
        open(os.path.join(HERE, "cache_ins.pkl"), "wb"), protocol=4)
print("\nescrito cache_ins.pkl")