#!/usr/bin/env python3
"""
s5_mapa_regiones.py -- Mapa estructural del blob: donde hay regiones densas de
E9, donde hay 'codigo' y donde hay relleno/bytes sueltos. Ademas intenta
encontrar la ALINEACION real del flujo (offset de inicio) probando cada
offset 0..15 y midiendo cuantos jmp caen en destinos validos.
"""
import os, struct, collections, bisect
from capstone import Cs, CS_ARCH_X86, CS_MODE_64

HERE = os.path.dirname(os.path.abspath(__file__))
data = open(os.path.join(HERE, "stage3_code.bin"), "rb").read()
N = len(data)

# ---- barrido lineal (offset 0) ----
md = Cs(CS_ARCH_X86, CS_MODE_64)
md.detail = False
ins_at = {}
order = []
pos = 0
while pos < N:
    ins = next(md.disasm(data[pos:pos + 15], pos), None)
    if ins is None:
        pos += 1
        continue
    ins_at[pos] = (ins.size, ins.mnemonic)
    order.append(pos)
    pos += ins.size
starts = sorted(ins_at)
def is_start(o):
    i = bisect.bisect_left(starts, o)
    return i < len(starts) and starts[i] == o

# ---- 1. regiones densas de E9 ----
jmps = [o for o in starts if ins_at[o][1] == "jmp"]
print("=== regiones de E9 consecutivas separadas por exactamente 5 bytes ===")
regions = []
cur = [jmps[0]]
for a, b in zip(jmps, jmps[1:]):
    if b - a == 5:
        cur.append(b)
    else:
        regions.append(cur)
        cur = [b]
regions.append(cur)
regions.sort(key=len, reverse=True)
print("  regiones totales: %d" % len(regions))
print("  %-12s %-12s %8s" % ("ini", "fin", "largo"))
for r in regions[:25]:
    print("  %08x   %08x   %8d  (%d saltos)" % (r[0], r[-1] + 5, r[-1] + 5 - r[0], len(r)))
tot_dense = sum(len(r) for r in regions if len(r) > 4)
print("  saltos en regiones >4: %d  (bytes cubiertos: %d)" %
      (tot_dense, sum(len(r) * 5 for r in regions if len(r) > 4)))

# ---- 2. mapa de calor: densidad de E9 por ventana de 64 KB ----
print("\n=== densidad de E9 por ventana de 0x10000 (byte inicial, n_jmp) ===")
W = 0x10000
w = [0] * ((N + W - 1) // W)
for o in jmps:
    w[o // W] += 1
for i, c in enumerate(w):
    bar = "#" * min(60, c)
    print("  %08x  %6d  %s" % (i * W, c, bar))

# ---- 3. alineacion: para cada offset inicial A en 0..15, medir ----
print("\n=== calidad del barrido lineal por alineacion inicial (0..15) ===")
print("   (metrica: nº de E9 cuyo destino cae dentro del blob)")
mdA = Cs(CS_ARCH_X86, CS_MODE_64)
mdA.detail = False
for A in range(16):
    n = 0
    jj = 0
    inside = 0
    p = A
    while p < N:
        ins = next(mdA.disasm(data[p:p + 15], p), None)
        if ins is None:
            p += 1
            continue
        n += 1
        if ins.mnemonic == "jmp":
            jj += 1
            t = p + 5 + struct.unpack_from("<i", data, p + 1)[0]
            if 0 <= t < N:
                inside += 1
        p += ins.size
    print("   A=%2d  instr=%7d  jmp=%6d  destino_dentro=%6d" % (A, n, jj, inside))

# ---- 4. los 9 destinos calientes: desensamblar la zona ----
print("\n=== zona de los destinos calientes ===")
hot = collections.Counter()
for o in starts:
    if ins_at[o][1] == "jmp":
        t = o + 5 + struct.unpack_from("<i", data, o + 1)[0]
        hot[t] += 1
top = [t for t, c in hot.most_common(9)]
print("  los 9 mas alcanzados:", " ".join(hex(t) for t in top))
md2 = Cs(CS_ARCH_X86, CS_MODE_64)
md2.detail = False
for t in top[:3]:
    print("\n  --- contexto de 0x%08x ---" % t)
    for ins in md2.disasm(data[max(0, t - 32):t + 64], max(0, t - 32)):
        mark = "  <<< DESTINO" if ins.address == t else ""
        print("    %08x  %-22s %s%s" % (ins.address, ins.bytes.hex(), ins.op_str, mark))
    # y quien salta aqui
    srcs = [o for o in starts
            if ins_at[o][1] == "jmp" and o + 5 + struct.unpack_from("<i", data, o + 1)[0] == t]
    print("    fuentes: %d, ej: %s" % (len(srcs), " ".join(hex(s) for s in srcs[:10])))
    for s in srcs[:3]:
        print("      src %08x  bytes anteriores: %s" % (s, data[max(0, s - 20):s].hex()))