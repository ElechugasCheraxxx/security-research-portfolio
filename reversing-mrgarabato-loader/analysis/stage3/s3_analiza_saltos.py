#!/usr/bin/env python3
"""
s3_analiza_saltos.py -- Analiza la estructura de los E9 (jmp rel32) del blob.
Clasifica cada jmp segun la distancia al objetivo:
   NOOP      jmp $+5        (salta a la siguiente instruccion -> no-op)
   SKIP      jmp $+5+k      con 0<k<umbral (salta sobre basura)
   FWD/BWD   destinos lejanos
   OUT       destino fuera del blob
"""
import os, struct, collections, sys
from capstone import Cs, CS_ARCH_X86, CS_MODE_64

HERE = os.path.dirname(os.path.abspath(__file__))
data = open(os.path.join(HERE, "stage3_code.bin"), "rb").read()
N = len(data)
END = 0x154F13   # ultimo byte no nulo

md = Cs(CS_ARCH_X86, CS_MODE_64)
md.detail = False


def find_all(hay, needle, step=1):
    out = []
    i = hay.find(needle)
    while i != -1:
        out.append(i)
        i = hay.find(needle, i + step)
    return out


print("blob: %d bytes (0x%X..0x%X)" % (N, 0, N - 1))
jmps = find_all(data, b"\xe9")
print("ocurrencias del byte E9: %d" % len(jmps))

cat = collections.Counter()
dist = collections.Counter()
oo = []
for off in jmps:
    if off + 5 > N:
        cat["truncado"] += 1
        continue
    rel = struct.unpack_from("<i", data, off + 1)[0]
    tgt = off + 5 + rel
    oo.append((off, tgt, rel))
    if rel == 0:
        cat["NOOP  jmp $+5"] += 1
    elif 0 < rel <= 64:
        cat["SKIP  +1..+64"] += 1
        dist[rel] += 1
    elif rel < 0:
        if tgt < 0:
            cat["BWD   fuera"] += 1
        elif -4096 <= rel:
            cat["BWD   corta (-4k..-1)"] += 1
            dist[rel] += 1
        else:
            cat["BWD   larga (<-4k)"] += 1
    else:
        if tgt >= END:
            cat["FWD   fuera del blob"] += 1
        elif rel > 4096:
            cat["FWD   larga (>4k)"] += 1
        else:
            cat["FWD   +65..+4096"] += 1
            dist[rel] += 1

print("\n=== clasificacion de E9 rel32 ===")
for k, v in cat.most_common():
    print("  %-26s %7d  %5.2f%%" % (k, v, 100.0 * v / len(jmps)))

print("\n=== distancias mas comunes (las 40 mas frecuentes) ===")
for d, c in dist.most_common(40):
    print("   rel=%+8d  n=%6d" % (d, c))

# donde caen los NOOP: estan en frontera de instruccion?
# re-lee el volcado lineal para saber que offsets son inicios de instruccion
ins_starts = set()
pos = 0
cnt = 0
while pos < N:
    ins = next(md.disasm(data[pos:pos + 15], pos), None)
    if ins is None:
        pos += 1
        continue
    ins_starts.add(pos)
    pos += ins.size
    cnt += 1
print("\ninicios de instruccion (barrido lineal alineado en 0): %d" % len(ins_starts))

noop = [o for o, t, r in oo if r == 0]
skip = [o for o, t, r in oo if 0 < r <= 64]
print("E9 NOOP en frontera de instruccion: %d / %d (%.1f%%)" %
      (sum(1 for o in noop if o in ins_starts), len(noop),
       100.0 * sum(1 for o in noop if o in ins_starts) / max(len(noop), 1)))
print("E9 SKIP en frontera de instruccion: %d / %d (%.1f%%)" %
      (sum(1 for o in skip if o in ins_starts), len(skip),
       100.0 * sum(1 for o in skip if o in ins_starts) / max(len(skip), 1)))

# bytes salteados por los SKIP
skipped = collections.Counter()
for o, t, r in oo:
    if 0 < r <= 64:
        skipped[r - 5] += 1
print("\n=== bytes salteados por los 'SKIP +1..+64' ===")
tot = sum(skipped.values())
for nb, c in sorted(skipped.items()):
    print("   salta %3d bytes : %6d" % (nb, c))

# contenido de los bloques saltados
print("\n=== contenido de 20 bloques saltados ===")
md2 = Cs(CS_ARCH_X86, CS_MODE_64)
shown = 0
for o, t, r in oo:
    if not (0 < r <= 16):
        continue
    body = data[o + 5:t]
    dis = []
    for ins in md2.disasm(body, o + 5):
        dis.append("%s %s" % (ins.mnemonic, ins.op_str))
    print("  %08x jmp %08x (salta %d): %s" % (o, t, r - 5, " ; ".join(dis)))
    shown += 1
    if shown >= 20:
        break

# ejecucion: cuantas instrucciones hay entre dos NOOP consecutivos
print("\n=== secuencia tipica entre NOOPs (primer NOOP y 30 bytes antes/despues) ===")
shown = 0
for o, t, r in oo:
    if r != 0:
        continue
    print("  --- NOOP en %08x ---" % o)
    for ins in md2.disasm(data[max(0, o - 40):o + 45], max(0, o - 40)):
        mark = "  <<<" if ins.address == o else ""
        print("    %08x  %-20s %s%s" % (ins.address, ins.bytes.hex(), ins.op_str, mark))
    shown += 1
    if shown >= 4:
        break