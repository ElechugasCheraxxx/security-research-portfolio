#!/usr/bin/env python3
"""
s12_hubs_plantillas.py -- Investigacion del patron 'lea reg,[rsp+0x140]' y la
distribucion de destinos de los E9. Usa el cache (rapido).
"""
import os, sys, struct, pickle, collections, bisect, statistics

HERE = os.path.dirname(os.path.abspath(__file__))
data = open(os.path.join(HERE, "stage3_code.bin"), "rb").read()
N = len(data)
END = 0x154F13
lin = pickle.load(open(os.path.join(HERE, "cache_lin.pkl"), "rb"))
so = sorted(lin)

# ---------- 1. la plantilla de 7 bytes de los hubs ----------
PAT = bytes.fromhex("488d")          # 48 8d XX 24 40 01 00 00
print("=== conteo de '48 8D XX 24 40 01 00 00'  (lea r64,[rsp+0x140]) ===")
locs = []
i = 0
while True:
    i = data.find(b"\x48\x8d", i, END)
    if i == -1:
        break
    if i + 7 <= N and data[i + 3] == 0x24 and data[i + 4:i + 7] == bytes.fromhex("400100"):
        locs.append(i)
    i += 1
print("   total: %d" % len(locs))
print("   esperado si fuera azar: %.3f" % (END / 2.0 / (256.0 ** 5)))
creg = collections.Counter(data[l + 2] for l in locs)
print("   por registro destino:", {hex(k): v for k, v in creg.most_common()})
print("   primeros 20 offsets:", " ".join(hex(x) for x in locs[:20]))
print("   ultimo:", hex(locs[-1]))
# alineados a frontera de instruccion?
soset = set(so)
print("   de ellos en frontera de instruccion (barrido lineal): %d (%.1f%%)" %
      (sum(1 for l in locs if l in soset), 100.0 * sum(1 for l in soset and locs) / len(locs)))

# tambien el patron mas general: 48 8D XX 24 YY YY YY YY con disp pequeno
print("\n=== '48 8D XX 24 d32'  (lea r64,[rsp+d32]) con d en 0..0x400 ===")
cnt_d = collections.Counter()
i = 0
while True:
    i = data.find(b"\x48\x8d", i, END)
    if i == -1:
        break
    if i + 7 <= N and data[i + 3] == 0x24:
        d = struct.unpack_from("<I", data, i + 4)[0]
        if d < 0x400:
            cnt_d[d] += 1
    i += 1
print("   total con disp<0x400: %d" % sum(cnt_d.values()))
print("   disp mas comunes:", [(hex(k), v) for k, v in cnt_d.most_common(20)])

# ---------- 2. distribucion de destinos de E9 ----------
print("\n=== distribucion de destinos de los E9 (los 37.455 bytes E9) ===")
tgt = collections.Counter()
tgtin = collections.Counter()
for o in range(END):
    if data[o] == 0xE9:
        t = o + 5 + struct.unpack_from("<i", data, o + 1)[0]
        tgt[t] += 1
        if 0 <= t < END:
            tgtin[t] += 1
print("   E9 totales: %d ; destinos distintos: %d ; dentro del blob: %d (%d distintos)" %
      (sum(tgt.values()), len(tgt), sum(tgtin.values()), len(tgtin)))
c = collections.Counter(tgtin.values())
print("   histograma de in-degree (dentro del blob):")
for k in sorted(c)[:20]:
    print("     indeg=%-6d %6d destinos" % (k, c[k]))
print("     ...")
print("   reparto del total de aristas E9->dentro por clase de indeg:")
tot = sum(tgtin.values())
acc = 0
for k in sorted(c):
    acc += k * c[k]
    if k <= 12:
        print("     indeg<=%-4d -> %8d aristas (%.1f%%)" % (k, acc, 100.0 * acc / tot))

# los hubs = destinos con indice 0x140 en la instruccion
print("\n=== ¿los hubs coinciden con 'lea r,[rsp+0x140]'? ===")
locsset = set(locs)
hits = [t for t, n in tgtin.items() if n >= 50]
print("   destinos con indeg>=50: %d" % len(hits))
print("   de esos, en el patron lea [rsp+0x140]: %d" % sum(1 for t in hits if t in locsset))
for t in sorted(hits, key=lambda x: -tgtin[x])[:15]:
    print("     %08x  indeg=%4d  bytes=%s" % (t, tgtin[t], data[t:t + 10].hex()))

# ---------- 3. cadenas de E9 consecutivos ----------
print("\n=== cadenas de E9 consecutivos (>=3) ===")
chains = []
cur = None
for i in range(len(so) - 1):
    a, b = so[i], so[i + 1]
    if lin[a][1] == "jmp" and lin[a][0] == 5 and b - a == 5 and lin[b][1] == "jmp":
        if cur is None:
            cur = [a, b]
        else:
            cur[1] = b
    else:
        if cur and (cur[1] - cur[0]) // 5 >= 3:
            chains.append(tuple(cur))
        cur = None
if cur and (cur[1] - cur[0]) // 5 >= 3:
    chains.append(tuple(cur))
print("   cadenas de >=3 E9 pegados: %d" % len(chains))
lc = collections.Counter((b - a) // 5 + 1 for a, b in chains)
print("   longitudes:", sorted(lc.items())[:15])
print("   primeras 10:")
for a, b in chains[:10]:
    print("     %08x..%08x (%d saltos) -> %s" %
          (a, b, (b - a) // 5 + 1,
           " ".join(hex(a + 5 + struct.unpack_from("<i", data, a + 5 * k + 1)[0])
                     for k in range((b - a) // 5 + 1))))

# ---------- 4. cuanta basura trivial hay exactamente ----------
print("\n=== BASURA TRIVIAL: conteo exacto en fronteras de instruccion ===")
TRIV = ["clc", "stc", "cmc", "nop", "xchg", "lahf", "sahf", "cbw", "cwd", "cdq",
        "cqo", "cwde", "cdqe", "hlt", "pushfq", "popfq", "sal", "stosb", "stosw",
        "stosd", "stosq", "lodsb", "lodsq", "movsb", "movsq", "scasb", "cmpsb",
        "insb", "outsb", "xlatb", "wait", "emms"]
c = collections.Counter()
for o in so:
    m = lin[o][1]
    if m in TRIV:
        c[m] += 1
tot = sum(c.values())
print("   total basura trivial en frontera: %d / %d instr = %.2f%%  (%d bytes)" %
      (tot, len(so), 100.0 * tot / len(so), sum(lin[o][0] for o in so if lin[o][1] in TRIV)))
for m, n in c.most_common():
    print("     %-8s %7d" % (m, n))