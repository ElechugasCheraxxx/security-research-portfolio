#!/usr/bin/env python3
"""
s4_grafo_saltos.py -- Construye el grafo de los saltos lineales del blob.

Preguntas:
  1. Hay un destino "caliente" (dispatcher de aplanado)?
  2. Los objetivos caen en fronteras de instruccion?
  3. Los objetivos fuera de rango sugieren que el blob NO empieza en el offset 0
     de su direccion virtual -> buscar el desplazamiento base que hace que
     la mayoria de los E9 caigan dentro.
"""
import os, struct, collections, bisect
from capstone import Cs, CS_ARCH_X86, CS_MODE_64

HERE = os.path.dirname(os.path.abspath(__file__))
data = open(os.path.join(HERE, "stage3_code.bin"), "rb").read()
N = len(data)
md = Cs(CS_ARCH_X86, CS_MODE_64)
md.detail = False

# ---- 1. barrido lineal alineado en 0 -> mapa offset->(len,mnem) ----
print("barrido lineal...")
ins_at = {}     # off -> (size, mnem, opstr)
order = []
pos = 0
while pos < N:
    ins = next(md.disasm(data[pos:pos + 15], pos), None)
    if ins is None:
        pos += 1
        continue
    ins_at[pos] = (ins.size, ins.mnemonic, ins.op_str)
    order.append(pos)
    pos += ins.size
print("  instrucciones: %d" % len(order))

starts = sorted(ins_at)
def is_start(o):
    i = bisect.bisect_left(starts, o)
    return i < len(starts) and starts[i] == o

# ---- 2. clasificacion de jmp (solo los que SON instrucciones) ----
jmps = [(o, struct.unpack_from("<i", data, o + 1)[0], o + 5 + struct.unpack_from("<i", data, o + 1)[0])
        for o in starts if ins_at[o][1] == "jmp"]
print("jmp en frontera de instruccion: %d" % len(jmps))

cat = collections.Counter()
tgt_hist = collections.Counter()
inrange = []
for o, rel, t in jmps:
    tgt_hist[t] += 1
    if 0 <= t < N:
        cat["dentro"] += 1
        inrange.append((o, t))
    else:
        cat["fuera"] += 1
print("  destinos dentro del blob: %d   fuera: %d" % (cat["dentro"], cat["fuera"]))

print("\n=== 30 destinos mas frecuentes (todos los jmp) ===")
for t, c in tgt_hist.most_common(30):
    st = "F" if is_start(t) else "-"
    print("   tgt %08x  desde %d jmp   en_frontera=%s  bytes=%s" %
          (t, c, st, data[t:t + 8].hex()))

print("\n=== 30 destinos mas frecuentes (solo los que caen DENTRO del blob) ===")
ih = collections.Counter()
for o, t in inrange:
    ih[t] += 1
for t, c in ih.most_common(30):
    st = "F" if is_start(t) else "-"
    print("   tgt %08x  alcanzado %d veces   en_frontera=%s  bytes=%s" %
          (t, c, st, data[t:t + 8].hex()))

# ---- 3. los objetivos que caen dentro, caen en frontera de instruccion? ----
ok = sum(1 for o, t in inrange if is_start(t))
print("\nobjetivos dentro del blob que caen en frontera de instruccion: %d / %d (%.1f%%)" %
      (ok, len(inrange), 100.0 * ok / max(len(inrange), 1)))

# ---- 4. buscar el desplazamiento base: desplazar el rango del blob ----
print("\n=== hipotesis de base: si el codigo empieza en el offset B del blob,")
print("    un E9 en offset o tiene destino real = B + (o-B) + 5 + rel = o + 5 + rel")
print("    -> los destinos relativos son correctos solo si B=0.")
print("    Probamos: cuantos E9 caen dentro del blob para cada desplazamiento del rango [off, off+1.4M)")
for B in [0, 0x1000, 0x2000, 0x4000, 0x8000, 0x10000, 0x20000, 0x40000, 0x80000, 0x100000]:
    hi = min(N, B + 0x160000)
    c = 0
    for o, rel, t in jmps:
        if B <= o < hi and 0 <= t < N:
            c += 1
    print("   base=0x%06X  jmp cuyo destino cae en el blob: %d" % (B, c))

# ---- 5. estructura: longitudes de los bloques entre jmp ----
print("\n=== longitudes de las 'trazas' entre jmp consecutivos (lineal) ===")
lens = []
for i in range(len(order) - 1):
    a, b = order[i], order[i + 1]
    if ins_at[a][1] == "jmp":
        lens.append(b - a)
c = collections.Counter(lens)
for L, n in sorted(c.items())[:30]:
    print("   %3d bytes : %6d" % (L, n))
print("   ... total trazas:", len(lens))