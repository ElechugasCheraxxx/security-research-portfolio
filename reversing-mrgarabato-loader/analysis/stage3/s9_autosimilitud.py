#!/usr/bin/env python3
"""
s9_autosimilitud.py -- ¿Es el blob N COPIAS de un mismo bloque?
Tests:
  1. autocorrelacion byte a byte a varios lags
  2. busqueda del periodo P tal que data[i] == data[i+P] para la mayor fraccion
  3. densidad de 'idiomas reales' en ventanas de 4 KB -> donde esta el codigo
  4. conteo de los 9 hubs:Instructiones 'lea reg,[rsp+0x140]'
"""
import os, collections, struct
from capstone import Cs, CS_ARCH_X86, CS_MODE_64

HERE = os.path.dirname(os.path.abspath(__file__))
data = open(os.path.join(HERE, "stage3_code.bin"), "rb").read()
N = len(data)
END = 0x154F13

# ---------- 1. autocorrelacion ----------
print("=== autocorrelacion de bytes (match data[i]==data[i+lag]) ===")
for lag in [4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192,
            0x10000, 0x20000, 0x30000, 0x40000, 0x80000, 0xA0000]:
    m = sum(1 for i in range(0, END - lag, 7) if data[i] == data[i + lag])
    t = len(range(0, END - lag, 7))
    print("   lag %8d (0x%06X): %.4f   (azar=%.4f)  %s" %
          (lag, lag, m / t, 1 / 256.0, "<<<" if m / t > 0.02 else ""))

# ---------- 2. periodo optimo ----------
print("\n=== busqueda del periodo P (0x400..0x200000) ===")
best = []
for P in range(0x400, 0x200000, 0x10):
    m = sum(1 for i in range(0, END - P, 97) if data[i] == data[i + P])
    t = len(range(0, END - P, 97))
    if t:
        best.append((m / t, P))
best.sort(reverse=True)
for r, P in best[:12]:
    print("   P=0x%06X (%d): match %.4f" % (P, P, r))

# ---------- 3. densidad de idiomas reales ----------
print("\n=== mapa de densidad de 'idioma real' en ventanas de 4 KB ===")
W = 0x1000
PATS = [bytes.fromhex("4881ec"), bytes.fromhex("81eb01000000"),
        bytes.fromhex("4881fc"), bytes.fromhex("4881c4"), bytes.fromhex("488d05"),
        bytes.fromhex("4881e4")]  # and rsp,imm32
dens = []
for i in range(0, END - W, W):
    c = 0
    for p in PATS:
        j = data.find(p, i, i + W)
        while j != -1:
            c += 1
            j = data.find(p, j + 1, i + W)
    dens.append((i, c))
nz = [d for d in dens if d[1] > 0]
print("   ventanas con >=1 idioma real: %d / %d" % (len(nz), len(dens)))
print("   total hits: %d" % sum(c for _, c in dens))
for i, c in dens:
    if c:
        print("   %08x  %d %s" % (i, c, "#" * min(50, c)))

# ---------- 4. los hubs ----------
print("\n=== conteo de 'lea reg64,[rsp+0x140]' (7 bytes, 48 8d XX 24 40 01 00 00) ===")
cnt = collections.Counter()
locs = []
i = 0
while True:
    i = data.find(bytes.fromhex("488d"), i, END)
    if i == -1:
        break
    if i + 7 <= N and data[i + 3] == 0x24 and data[i + 4:i + 7] == bytes.fromhex("400100"):
        cnt[data[i + 2]] += 1
        locs.append(i)
    i += 1
print("   total: %d" % len(locs))
print("   por byte ModRM reg-field:", {hex(k): v for k, v in cnt.most_common()})
print("   primeros: ", " ".join(hex(x) for x in locs[:20]))

# ---------- 5. que hay en los 9 hubs en detalle ----------
print("\n=== desensamblado de los 9 hubs (30 instr desde el destino) ===")
hubs = [0xcbb18, 0x90bc5, 0x117340, 0x9985, 0x62887, 0xcce50, 0x124358, 0xa67df, 0x81e8e]
md = Cs(CS_ARCH_X86, CS_MODE_64); md.detail = False
for h in hubs:
    print("  --- hub 0x%08x ---" % h)
    n = 0
    for ins in md.disasm(data[h:h + 60], h):
        print("    %08x  %-22s %s" % (ins.address, ins.bytes.hex(), ins.op_str))
        n += 1
        if n >= 12: break

# ---------- 6. quienes saltan a un hub, y que hay justo antes del jmp ----------
print("\n=== contexto de 24 bytes ANTES de un jmp que va a un hub ===")
md2 = Cs(CS_ARCH_X86, CS_MODE_64); md2.detail = False
# barrido lineal para边界
lin = []
p = 0
while p < END:
    ins = next(md2.disasm(data[p:p+15], p), None)
    if ins is None:
        p += 1; continue
    lin.append((p, ins.size, ins.mnemonic))
    p += ins.size
shown = 0
for o, sz, m in lin:
    if m != "jmp" or sz != 5: continue
    t = o + 5 + struct.unpack_from("<i", data, o + 1)[0]
    if t not in hubs: continue
    # retroceder 8 instrucciones
    ctx = [x for x in lin if o - 40 <= x[0] <= o + 4]
    print("  --- src %08x -> hub %08x ---" % (o, t))
    for co, cs, cm in ctx:
        ins = next(md2.disasm(data[co:co+15], co), None)
        print("     %08x  %-20s %-8s %s" % (co, ins.bytes.hex(), cm, ins.op_str))
    shown += 1
    if shown >= 6: break