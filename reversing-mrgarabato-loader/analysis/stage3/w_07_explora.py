#!/usr/bin/env python3
"""
w_07_explora.py -- Explora el contenido REAL de wine__w7.bin: donde estan las
cadenas, como las referencia el codigo, y cual es la base VA del blob.
"""
import os, re, collections, struct
import numpy as np
from capstone import Cs, CS_ARCH_X86, CS_MODE_64
from capstone.x86_const import X86_OP_MEM, X86_REG_RIP

HERE = os.path.dirname(os.path.abspath(__file__))
raw = open(os.path.join(HERE, "wine__w7.bin"), "rb").read()
N = len(raw)
md = Cs(CS_ARCH_X86, CS_MODE_64); md.detail = True

z = np.load(os.path.join(HERE, "w_cache.npz"))
off, size, mid, tgt = z["off"], z["size"], z["mid"], z["tgt"]
mnems = [str(x) for x in z["mnems"]]

# ---------------- 1. donde estan las cadenas ----------------
print("=" * 100)
print("1. CADENAS CLAVE EN wine__w7.bin")
print("=" * 100)
KEYS = [b"MRGARABATO", b"/Auth/api/neural_login.php", b"NeuralAuth", b"MiDriver",
        b"WinDivert", b"Waiting for emulator", b"Injection Process", b"PhoneHx",
        b"HD-Player.exe", b"MEmu.exe", b"hwid_affected", b"last_login",
        b"sc create", b"neural_login", b"token", b"expired", b"hwid"]
strstart = {}
for k in KEYS:
    i = 0
    while True:
        i = raw.find(k, i)
        if i < 0:
            break
        j = i
        while j > 0 and 32 <= raw[j - 1] < 127:
            j -= 1
        e = i
        while e < N and 32 <= raw[e] < 127:
            e += 1
        s = raw[j:e].decode(errors="replace")
        print("  %-26s @ %08x  (cadena desde %08x, %d B)\n        %r"
              % (k.decode(), i, j, e - j, s[:110]))
        strstart[j] = s
        i += 1
        if i > N:
            break

# ---------------- 2. inventario de cadenas del frente claro ----------------
print()
print("=" * 100)
print("2. INVENTARIO DE CADENAS (>= 6 chars) por region de 64 KB del frente")
print("=" * 100)
def strscan(lo, hi, minlen=6):
    out = []
    i = lo; cur = bytearray(); st = lo
    while i < hi:
        c = raw[i]
        if 32 <= c < 127:
            if not cur: st = i
            cur.append(c)
        else:
            if len(cur) >= minlen: out.append((st, bytes(cur).decode()))
            cur = bytearray()
        i += 1
    return out

front = strscan(0, 0x6A000, 8)
print("cadenas >= 8 en 0x000000..0x06A000: %d" % len(front))
byb = collections.defaultdict(list)
for o, s in front:
    byb[o >> 16].append((o, s))
for b in sorted(byb):
    print("  bloque %04x000 : %4d cadenas" % (b, len(byb[b])))

# ---------------- 3. referencias RIP-relativas ----------------
print()
print("=" * 100)
print("3. REFERENCIAS RIP-RELATIVAS EN EL CODIGO CLARO (0x0..0x6A000)")
print("=" * 100)
sel = np.nonzero((off >= 0) & (off < 0x6A000))[0]
print("instrucciones: %d" % len(sel))
refs = []
for i in sel:
    a = int(off[i])
    ins = next(md.disasm(raw[a:a + 15], a), None)
    if ins is None:
        continue
    for op in ins.operands:
        if op.type == X86_OP_MEM and op.mem.base == X86_REG_RIP:
            refs.append((a, ins.mnemonic, ins.op_str, a + ins.size + op.mem.disp))
print("operandos con base RIP: %d" % len(refs))
for a, m, ops, va in refs[:25]:
    print("   %08x  %-8s %-30s -> VA 0x%x" % (a, m, ops, va))

# ---------------- 4. deducir la BASE ----------------
print()
print("=" * 100)
print("4. DEDUCIR LA BASE VA")
print("=" * 100)
# Candidatos: los destinos RIP mas frecuentes son tablas/imports o strings.
# Probamos la hipotesis heredada BASE=0x140E36000 (RVA 0xE36000).
vot = collections.Counter()
# conjunto de inicios de cadena conocidos
sset = set(strstart)
allstr = {}
for o, s in front:
    allstr[o] = s
for o, s in strscan(0x6B0000, N, 8):
    allstr[o] = s
print("cadenas indexadas: %d" % len(allstr))
for a, m, ops, va in refs:
    for BASE, tag in ((0x140E36000, "RVA 0xE36000"), (0x0, "BASE=0")):
        o = va - BASE
        if o in allstr:
            vot[(tag, o)] += 1
print("coincidencias (string alcanzada con la base heredada): %d" % sum(vot.values()))
# votacion general de la base: para cada ref y cada string, la diferencia
# se agrupa; se pide la moda global.
samp = refs[:4000]
c = collections.Counter()
for a, m, ops, va in samp:
    for o in allstr:
        c[va - o] += 1
print("\nmodas de (VA_destino - offset_cadena):")
for b, n in c.most_common(8):
    print("   0x%012X   n=%d   -> RVA si BASE=0x140000000: 0x%08X" %
          (b, n, (b + 0x140000000) & 0xFFFFFFFF))
