#!/usr/bin/env python3
"""
w_08_funcs.py -- Reconstruye funciones y grafo de control SOBRE LAS ZONAS EN
CLARO de wine__w7.bin.

Hallazgo previo que se explota: BASE VA = 0. Un `lea rax,[rip+X]` en el
offset `a` produce el offset de destino `a + size + disp` DENTRO del propio
blob: el volcado conserva el direccionamiento relativo de seccion.

Zonas en claro (medidas con w_06):
   FRENTE  0x000000..0x06A000   codigo + .rdata del loader (cadenas aqui)
   COLA    0x06B5000..0x0770000  codigo/datos tardios

Todo en O(n log n): indice off->i como array, sin bucles cuadraticos.
"""
import os, sys, collections, json, struct, bisect, time
import numpy as np
from capstone import Cs, CS_ARCH_X86, CS_MODE_64

HERE = os.path.dirname(os.path.abspath(__file__))
raw = open(os.path.join(HERE, "wine__w7.bin"), "rb").read()
N = len(raw)

z = np.load(os.path.join(HERE, "w_cache.npz"))
COFF = z["off"]; CSIZ = z["size"]; CMID = z["mid"]; CTGT = z["tgt"]
mnems = [str(x) for x in z["mnems"]]
MID = {m: i for i, m in enumerate(mnems)}
n = len(COFF)
print("cache: %d instrucciones, %d mnemonicos" % (n, len(mnems)))

CODE_REGIONS = [(0x000000, 0x06A000), (0x6B5000, N)]
# mascara booleana por offset: belong_to_code(off)
incode = np.zeros(N + 16, np.bool_)
for a, b in CODE_REGIONS:
    incode[a:min(b, N)] = True

# indice off -> i, construido como array (N+16 entradas)
IDX = np.full(N + 16, -1, np.int32)
IDX[COFF] = np.arange(n, dtype=np.int32)

COND = set(i for i, m in enumerate(mnems)
           if m.startswith("j") or m.startswith("loop"))
COND.discard(MID["jmp"])
UNCOND = {MID["jmp"]}
RET = {MID[m] for m in ("ret", "retf", "retfq") if m in MID}
TERM = set(RET)
CALL = MID["call"]
isbranch = np.zeros(n, np.bool_)
for i in (COND | UNCOND): isbranch[i] = True

t0 = time.time()
# ---------------- semillas ----------------
seeds = set()
tg = CTGT
ok = (tg >= 0) & incode[np.clip(tg, 0, N)]
seeds.update(tg[ok].tolist())
for pat in (b"\x48\x81\xec", b"\x48\x8d\xac\x24", b"\x40\x53", b"\x55\x48\x8b\xec",
            b"\x48\x89\x5c\x24", b"\x48\x83\xec", b"\x48\x8b\xc4",
            b"\x4c\x8b\xdc", b"\x48\x89\x4c\x24", b"\x53\x48"):
    i = raw.find(pat)
    while i != -1 and i < N:
        if incode[i]: seeds.add(i)
        i = raw.find(pat, i + 1)
# el offset siguiente a cada ret es entrada
ridx = np.nonzero(np.isin(CMID, list(RET)))[0]
nx = COFF[ridx] + CSIZ[ridx]
seeds.update(nx[nx < N][incode[nx[nx < N]]].tolist())
seeds = np.array(sorted(seeds), np.int64)
print("semillas: %d  (%.1fs)" % (len(seeds), time.time() - t0))

# ---------------- descenso recursivo ----------------
# pila de TRACAS (secuencias lineales). Cada traza se guarda como lista.
reach = np.zeros(N + 16, np.bool_)
work = seeds.tolist()
traj = []
MAXI = 4000
while work or traj:
    if work:
        o = work.pop()
    else:
        o = traj.pop()
        if o is None:
            continue
    k = 0
    while True:
        if o < 0 or o >= N or not incode[o] or reach[o]:
            break
        i = IDX[o]
        if i < 0:
            reach[o] = True          # frontera no desensamblada
            break
        reach[o] = True
        m = CMID[i]
        sz = CSIZ[i]
        if isbranch[i]:
            t = tg[i]
            if t >= 0 and incode[min(t, N)]:
                work.append(int(t))
            if m in COND:
                work.append(int(o + sz))
            else:
                traj.append(int(o + sz))   # el jmp cae, su sucesor no
            break
        if m in TERM:
            break
        if m == CALL:
            t = tg[i]
            if t >= 0 and incode[min(t, N)]:
                work.append(int(t))
        o += int(sz)
        k += 1
        if k > MAXI:
            break
ins_idx = np.nonzero(reach[:N] & (IDX[:N] >= 0))[0]
print("instrucciones alcanzables: %d   (%.1fs)" % (len(ins_idx), time.time() - t0))
cov = int(CSIZ[ins_idx].astype(np.int64).sum())
tot_code = sum(b - a for a, b in CODE_REGIONS)
print("bytes alcanzables: %d / %d de las zonas en claro (%.2f%%) / %d totales (%.2f%%)"
      % (cov, tot_code, 100.0 * cov / tot_code, N, 100.0 * cov / N))
mc = collections.Counter(mnems[CMID[ins_idx]].tolist())
print("ret=%d call=%d jmp=%d cond=%d  |  top: %s" %
      (sum(mc[m] for m in mnems if m in ("ret", "retf", "retfq")), mc["call"],
       mc["jmp"], sum(v for k, v in mc.items()
                      if k.startswith("j") or k.startswith("loop")),
       mc.most_common(12)))

# ---------------- bloques basicos ----------------
b_idx = np.nonzero(isbranch[ins_idx] | np.isin(CMID[ins_idx], list(TERM | {CALL})))[0]
lead_off = set()
for k in b_idx.tolist():
    i = ins_idx[k]
    o = int(COFF[i]); m = CMID[i]; sz = int(CSIZ[i]); t = tg[i]
    if t >= 0 and reach[min(t, N)] and incode[min(t, N)]:
        lead_off.add(int(t))
    if m in COND and incode[min(o + sz, N)]:
        lead_off.add(o + sz)
    if m in COND and incode[min(o + sz, N)]:
        pass
lead = np.zeros(N + 16, np.bool_)
lead[np.array(sorted(lead_off), np.int64)] = True

# construccion de bloques en una pasada
offs = COFF[ins_idx]
newblk = np.zeros(len(offs), np.bool_)
newblk[1:] = lead[offs[1:]]
newblk[0] = True
blkstart = np.nonzero(newblk)[0]
blk_of_ins = np.zeros(len(offs), np.int64)
blk_of_ins[blkstart] = np.arange(len(blkstart))
blk_of_ins = np.maximum.accumulate(blk_of_ins)
nblk = len(blkstart)
bstart = offs[blkstart]
bend = np.empty(nblk, np.int64)
bend[:-1] = offs[blkstart[1:]]
bend[-1] = offs[-1] + CSIZ[ins_idx[-1]]
blast_mid = CMID[ins_idx][blkstart]
blast_tgt = tg[ins_idx][blkstart]
print("\nBLOQUES: %d" % nblk)
nret = int(np.isin(blast_mid, list(TERM)).sum())
print("bloques que terminan en ret: %d" % nret)

# aristas
src = []; dst = []
cond = np.isin(blast_mid, list(COND))
unc = blast_mid == MID["jmp"]
bi_tgt = np.full(N + 16, -1, np.int64)
bi_tgt[bstart] = np.arange(nblk)
for k in np.nonzero(cond | unc)[0]:
    t = blast_tgt[k]
    if t >= 0 and bi_tgt[min(t, N)] >= 0:
        src.append(k); dst.append(bi_tgt[min(t, N)])
    if cond[k]:
        nx = bstart[k] + 0   # el sucesor lineal es el inicio del bloque k+1
        if k + 1 < nblk:
            src.append(k); dst.append(k + 1)
src = np.array(src, np.int64); dst = np.array(dst, np.int64)
# deduplicar
pairs = src * np.int64(nblk + 1) + dst
pairs = np.unique(pairs)
src = pairs // (nblk + 1); dst = pairs % (nblk + 1)
print("aristas: %d  (media %.2f salidas/bloque)" % (len(src), len(src) / nblk))
indeg = np.bincount(dst, minlength=nblk)
outdeg = np.bincount(src, minlength=nblk)
print("bloques sin entrada: %d (%.1f%%)" % ((indeg == 0).sum(), 100.0 * (indeg == 0).mean()))

# componentes conexas
import networkx as nx
G = nx.DiGraph(); G.add_nodes_from(range(nblk)); G.add_edges_from(zip(src.tolist(), dst.tolist()))
comps = list(nx.weakly_connected_components(G))
cs = sorted((len(c) for c in comps), reverse=True)
print("componentes conexas (debil): %d ; mayores: %s" % (len(comps), cs[:12]))

# nodos de aplanado
hub = np.nonzero(indeg > 5)[0]
print("nodos de aplanado (indeg>5): %d" % len(hub))
oh = np.argsort(-indeg[hub])[:20]
for i in oh.tolist():
    print("   %08x..%08x indeg=%4d outdeg=%2d fin=%s" %
          (bstart[i], bend[i], indeg[i], outdeg[i], mnems[blast_mid[i]]))

# ---------------- funciones ----------------
entry = set(np.nonzero(indeg == 0)[0].tolist())
cm = CMID[ins_idx] == CALL
called_t = tg[ins_idx][cm]
called_t = called_t[(called_t >= 0) & (bi_tgt[np.clip(called_t, 0, N)] >= 0)]
entry.update(bi_tgt[called_t].tolist())
# retorno de llamada: el bloque siguiente a un call tambien es entrada
call_idx = ins_idx[cm]
nxt = COFF[call_idx] + CSIZ[call_idx]
nxt = nxt[nxt < N]
bb = bi_tgt[nxt]
entry.update(bb[bb >= 0].tolist())
entry = np.array(sorted(entry), np.int64)
print("\nfunciones candidatas: %d" % len(entry))

# rango por pertenencia: cada bloque pertenece a la funcion(entry) mas cercana
# por debajo que lo domina en el CFG. Aproximacion estandar y O(n log n):
# para cada bloque, se busca el primer entry <= bstart en el mismo componente.
fstart = bstart[entry]
owner = np.searchsorted(fstart, bstart, side="right") - 1
owner[owner < 0] = -1
fg = np.where(owner >= 0)[0]
frange = collections.defaultdict(lambda: [10 ** 9, -1, 0])
for k in fg.tolist():
    f = owner[k]
    r = frange[int(f)]
    r[0] = min(r[0], int(bstart[k])); r[1] = max(r[1], int(bend[k])); r[2] += 1
szs = [r[1] - r[0] for r in frange.values()]
print("rangos: tamano medio %.0f B  mediana %d  max %d" %
      (np.mean(szs), int(np.median(szs)), max(szs)))
with open(os.path.join(HERE, "w_funciones.txt"), "w") as f:
    for e in entry.tolist():
        r = frange[int(e)]
        f.write("%08x %08x %d %d\n" % (r[0], r[1], r[2], bstart[e]))
with open(os.path.join(HERE, "w_bloques.txt"), "w") as f:
    for k in range(nblk):
        f.write("%08x %08x %d %s\n" % (bstart[k], bend[k],
                                       int((newblk & (blk_of_ins == k)).sum()),
                                       mnems[blast_mid[k]]))
json.dump({"instr_alcanzables": int(len(ins_idx)), "bytes_alcanzables": cov,
           "zonas_en_claro": CODE_REGIONS, "bytes_zonas": tot_code,
           "bloques": int(nblk), "aristas": int(len(src)),
           "bloques_ret": nret, "componentes": len(comps),
           "componentes_mayores": cs[:12], "funciones": int(len(entry)),
           "nodos_aplanado": int(len(hub)),
           "tam_medio_funcion": float(np.mean(szs)), "tam_max_funcion": int(max(szs)),
           "instrucciones_lineales_totales": int(n)},
          open(os.path.join(HERE, "w_cfg.json"), "w"), indent=2)
print("\nescrito w_funciones.txt, w_bloques.txt, w_cfg.json  (%.1fs)" % (time.time() - t0))
