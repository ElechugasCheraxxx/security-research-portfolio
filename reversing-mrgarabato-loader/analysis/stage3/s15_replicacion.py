#!/usr/bin/env python3
"""
s15_replicacion.py -- ¿El ofuscador REPLICA bloques de codigo?
Busca:
  (a) constantes imediato repetidas (0x4acb722d, etc.) -> bloques clonados
  (b) secuencias de 12-24 bytes repetidas (no alineadas a 4)
  (c) cuanta del 'cuerpo' tipico: mov eax,K ; rol eax,cl ; add al,r8b ; xor al,[r9+rdx]
"""
import os, struct, collections, pickle

HERE = os.path.dirname(os.path.abspath(__file__))
data = open(os.path.join(HERE, "stage3_code.bin"), "rb").read()
N = len(data); END = 0x154F13

# ---------- (a) inmediatos de 32 bits repetidos ----------
print("=== inmediatos dword mas repetidos (ventana deslizante: cada offset 0) ===")
# buscar patron 'mov eax,imm32' = B8 xx xx xx xx y otros 'mov r32,imm32'
imm = collections.Counter()
for op in (0xB8, 0xB9, 0xBA, 0xBB, 0xBC, 0xBD, 0xBE, 0xBF):
    i = 0
    needle = bytes([op])
    while True:
        i = data.find(needle, i, END)
        if i == -1: break
        if i + 5 <= N:
            v = struct.unpack_from("<I", data, i + 1)[0]
            imm[(op - 0xB8, v)] += 1
        i += 1
top = collections.Counter()
for (r, v), n in imm.items():
    if n > 3:
        top[(r, v)] = n
print("  (reg,imm32) con >3 ocurrencias: %d valores distintos" % len(top))
for (r, v), n in top.most_common(30):
    print("    r%-2d  0x%08X  x%d" % (r, v, n))

print("\n=== 'mov r64,imm64' (REX.B8, 48 B8+r) mas repetidos ===")
imm64 = collections.Counter()
i = 0
while True:
    i = data.find(b"\x48\xb8", i, END)
    if i == -1: break
    if i + 10 <= N:
        v = struct.unpack_from("<Q", data, i + 2)[0]
        imm64[v] += 1
    i += 1
for v, n in imm64.most_common(25):
    if n > 1:
        print("    0x%016X  x%d" % (v, n))
print("  distintos movabs: %d ; con x>1: %d" % (len(imm64), sum(1 for v in imm64.values() if v > 1)))

# ---------- (b) secuencias repetidas ----------
print("\n=== secuencias de 16 bytes repetidas (offset ANY, con overlape) ===")
k = 16
idx = collections.defaultdict(list)
for i in range(0, END - k):
    idx[data[i:i + k]].append(i)
rep = {s: v for s, v in idx.items() if len(v) > 1}
print("  secuencias de 16B con >1 copia: %d ; copias totales: %d" %
      (len(rep), sum(len(v) for v in rep.values())))
print("  copies>=3: %d ; copies>=10: %d" %
      (sum(1 for v in rep.values() if len(v) >= 3),
       sum(1 for v in rep.values() if len(v) >= 10)))
top = sorted(rep.items(), key=lambda x: -len(x[1]))
for s, v in top[:15]:
    print("    x%-5d %s" % (len(v), s.hex()))
    if len(v) <= 12:
        print("            en: %s" % " ".join(hex(x) for x in v))

print("\n=== secuencias de 24 bytes repetidas ===")
k = 24
idx = collections.defaultdict(list)
for i in range(0, END - k):
    idx[data[i:i + k]].append(i)
rep = {s: v for s, v in idx.items() if len(v) > 1}
print("  secuencias de 24B con >1 copia: %d ; copias: %d" % (len(rep), sum(len(v) for v in rep.values())))
print("  copies>=3: %d" % sum(1 for v in rep.values() if len(v) >= 3))
for s, v in sorted(rep.items(), key=lambda x: -len(x[1]))[:10]:
    print("    x%-4d %s" % (len(v), s.hex()))
    print("           en: %s" % " ".join(hex(x) for x in v[:12]))

# ---------- (c) el cuerpo tipico ----------
print("\n=== cuerpo 'b82d72cb4a d3c0 4102c0 41320411' ===")
P = bytes.fromhex("b82d72cb4a")
i = 0
hits = []
while True:
    i = data.find(P, i, END)
    if i == -1: break
    hits.append(i); i += 1
print("  'mov eax,0x4acb722d': %d ocurrencias" % len(hits))
print("  offsets:", " ".join(hex(x) for x in hits[:30]))
P2 = bytes.fromhex("4a8d540420")
j = 0; h2 = []
while True:
    j = data.find(P2, j, END)
    if j == -1: break
    h2.append(j); j += 1
print("  'lea rdx,[rsp+r8+0x20]' (4a8d540420): %d ocurrencias" % len(h2))
P3 = bytes.fromhex("41320411")
k3 = 0; h3 = []
while True:
    k3 = data.find(P3, k3, END)
    if k3 == -1: break
    h3.append(k3); k3 += 1
print("  'xor al,[r9+rdx]' (41320411): %d ocurrencias" % len(h3))
print("  offsets:", " ".join(hex(x) for x in h3[:30]))

# ¿co-ocurren? distancia entre 'lea rdx,[rsp+r8+0x20]' y 'xor al,[r9+rdx]'
d = [y - x for x in h2 for y in h3 if 0 < y - x < 64]
print("  distancia [lea rdx..] -> [xor al,[r9+rdx]]: %d pares, mas comun %s" %
      (len(d), collections.Counter(d).most_common(6)))