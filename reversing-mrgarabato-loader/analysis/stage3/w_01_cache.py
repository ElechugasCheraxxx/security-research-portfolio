#!/usr/bin/env python3
"""
w_01_cache.py -- Barrido lineal de desensamblado sobre el volcado de Wine
(wine__w7.bin, 7.790.592 B) y cache compacta en numpy.

Diferencias frente a s11_cache_analisis.py:
  * multiprocessing por trozos (8 nucleos)
  * cache en npz (numpy) en vez de pickle dict: carga en <1s y ocupa 1/4 de
    memoria. Con 7,8 MB hay ~2,6M instrucciones; un dict de pickle pasaria
    de 1 GB y tardaria ~40s en cargar.
  * el destino de cada rama directa se lee de capstone (no parseando op_str)
    y, en vez de depender de op_str, se re-deriva de los bytes crudos: en
    x86-64 el desplazamiento de un salto directo SIEMPRE es el ultimo campo.

Formato de w_cache.npz:
    off  uint32  offset de la instruccion (relativo al blob)
    size uint8   longitud en bytes
    mid  uint16  indice dentro de la lista `mnems`
    tgt  int64   destino (relativo al blob) de rama directa, o -1
"""
import os, sys, time, collections
import numpy as np
from capstone import Cs, CS_ARCH_X86, CS_MODE_64

HERE = os.path.dirname(os.path.abspath(__file__))
BLOB = os.path.join(HERE, "wine__w7.bin")
CACHE = os.path.join(HERE, "w_cache.npz")
NP = 8

G_JUMP, G_CALL = 1, 2   # capstone.x86_const
PRE = {0x66, 0x67, 0xF0, 0xF2, 0xF3, 0x2E, 0x36, 0x3E, 0x26, 0x64, 0x65}

_data = None


def getdata():
    return _data


def branch_target(a, ins):
    """Destino relativo-al-blob de un salto/llamada directa, o -1.
    Regla: en x86-64 el campo de desplazamiento de un salto directo es
    siempre el ULTIMO campo de la instruccion (rel8 -> ultimo byte,
    rel32 -> ultimos 4 bytes)."""
    sz = ins.size
    b = bytes(ins.bytes)
    if sz < 2:
        return -1
    if b[0] == 0x0F and 0x80 <= b[1] <= 0x8F:
        return a + sz + int.from_bytes(b[-4:], "little", signed=True)
    if sz >= 5 and b[-5] in (0xE8, 0xE9):
        return a + sz + int.from_bytes(b[-4:], "little", signed=True)
    # rel8 con o sin prefijos: saltar los prefijos hasta el opcode
    i = 0
    while i < sz - 1 and (b[i] in PRE or 0x40 <= b[i] <= 0x4F):
        i += 1
    op = b[i]
    if 0x70 <= op <= 0x7F or op in (0xEB, 0xE0, 0xE1, 0xE2, 0xE3):
        return a + sz + int.from_bytes(b[-1:], "little", signed=True)
    return -1


def sweep(args):
    lo, hi, path = args
    data = open(path, "rb").read()
    md = Cs(CS_ARCH_X86, CS_MODE_64); md.detail = True; md.skipdata = True
    offs, szs, mns, tgts = [], [], [], []
    for ins in md.disasm(data[lo:hi], lo):
        a = ins.address
        if a >= hi:
            break
        if a < lo:
            continue
        offs.append(a); szs.append(ins.size)
        if ins.id == 0:
            mns.append(".byte"); tgts.append(-1); continue
        mns.append(ins.mnemonic)
        if ins.group(G_JUMP) or ins.group(G_CALL):
            tgts.append(branch_target(a, ins))
        else:
            tgts.append(-1)
    return (np.array(offs, np.uint32), np.array(szs, np.uint8),
            np.array(mns), np.array(tgts, np.int64))


def derive_targets(off, size, mid, mnems, data):
    """Re-deriva los destinos de rama DIRECTA a partir de los bytes crudos,
    sin capstone: se sabe que instruccion es rama por su mnemonico, y el
    desplazamiento es siempre el ultimo campo."""
    isrel32 = set()
    iscond = set()
    isjmps = set()
    for i, m in enumerate(mnems):
        if m.startswith("loop") or m in ("jecxz", "jcxz", "jrcxz"):
            isrel32.add(i)
        elif m in ("jmp",):
            isjmps.add(i)
        elif m.startswith("j"):
            iscond.add(i)
    tgt = np.full(len(off), -1, np.int64)
    for k in range(len(off)):
        i = int(mid[k])
        if i not in iscond and i not in isjmps and i not in isrel32:
            continue
        a = int(off[k]); sz = int(size[k])
        b = data[a:a + sz]
        if len(b) < 2:
            continue
        if b[0] == 0x0F and 0x80 <= b[1] <= 0x8F:
            tgt[k] = a + sz + int.from_bytes(b[-4:], "little", signed=True); continue
        if sz >= 5 and b[-5] in (0xE8, 0xE9):
            tgt[k] = a + sz + int.from_bytes(b[-4:], "little", signed=True); continue
        j = 0
        while j < sz - 1 and (b[j] in PRE or 0x40 <= b[j] <= 0x4F):
            j += 1
        op = b[j]
        if 0x70 <= op <= 0x7F or op in (0xEB, 0xE0, 0xE1, 0xE2, 0xE3):
            tgt[k] = a + sz + int.from_bytes(b[-1:], "little", signed=True)
    return tgt


def main():
    from multiprocessing import Pool
    t0 = time.time()
    data = open(BLOB, "rb").read()
    N = len(data)
    print("blob: %s  %d bytes (%.2f MB)" % (os.path.basename(BLOB), N, N / 1e6))

    if os.path.exists(CACHE):
        z = np.load(CACHE)
        offs, szs, mids = z["off"], z["size"], z["mid"]
        mnems = [str(x) for x in z["mnems"]]
        print("cache existente: %d instrucciones; re-derivando destinos" % len(offs))
        tgt = derive_targets(offs, szs, mids, mnems, data)
        np.savez(CACHE, off=offs, size=szs, mid=mids, tgt=tgt,
                 mnems=np.array(mnems))
        stats(offs, szs, mids, tgt, mnems, N, CACHE, t0)
        return

    step = (N + NP - 1) // NP
    jobs = []
    for i in range(NP):
        lo = 0 if i == 0 else i * step
        hi = min((i + 1) * step, N)
        jobs.append((lo, hi, BLOB))
    print("desensamblando en %d trozos..." % NP)
    with Pool(NP) as p:
        res = p.map(sweep, jobs)

    byoff = {}
    for o, s, m, t in res:
        byoff.update({int(o[i]): (int(s[i]), m[i], int(t[i])) for i in range(len(o))})
    del res
    print("  lineal bruto: %d instrucciones (%.1fs)" % (len(byoff), time.time() - t0))

    keys = sorted(byoff)
    offs = np.array(keys, np.uint32)
    szs = np.fromiter((byoff[o][0] for o in keys), np.uint8, len(keys))
    mns = np.fromiter((byoff[o][1] for o in keys), np.dtype('U16'), len(keys))
    tgt = np.fromiter((byoff[o][2] for o in keys), np.int64, len(keys))
    del byoff

    mnems = sorted(set(mns.tolist()))
    midx = {m: i for i, m in enumerate(mnems)}
    mids = np.array([midx[m] for m in mns.tolist()], np.uint16)
    del mns

    np.savez(CACHE, off=offs, size=szs, mid=mids, tgt=tgt, mnems=np.array(mnems))
    stats(offs, szs, mids, tgt, mnems, N, CACHE, t0)


def stats(offs, szs, mids, tgt, mnems, N, path, t0):
    import collections
    cov = int(szs.astype(np.int64).sum())
    nb = int((tgt >= 0).sum())
    print("\ninstrucciones:        %d" % len(offs))
    print("cobertura lineal:     %d / %d bytes (%.2f%%)  -> %d bytes sin cubrir"
          % (cov, N, 100.0 * cov / N, N - cov))
    print("ramas directas:       %d  (%.2f%%)" % (nb, 100.0 * nb / len(offs)))
    print("fuera del blob:       %d"
          % int(((tgt < 0) & (tgt != -1)).sum()))
    hist = collections.Counter(mnems[i] for i in mids.tolist())
    print("\n%-12s %9s %7s" % ("MNEM", "COUNT", "PCT"))
    for m, c in hist.most_common(45):
        print("%-12s %9d %6.2f%%" % (m, c, 100.0 * c / len(offs)))
    junk = sum(hist[m] for m in ("clc", "stc", "cmc", "nop"))
    print("\nclc+stc+cmc+nop: %d = %.1f%%" % (junk, 100.0 * junk / len(offs)))
    print("escrito %s (%.1f MB) en %.1fs" % (path, os.path.getsize(path) / 1e6,
                                            time.time() - t0))


if __name__ == "__main__":
    main()
