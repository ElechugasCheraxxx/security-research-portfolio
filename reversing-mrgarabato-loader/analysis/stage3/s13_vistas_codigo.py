#!/usr/bin/env python3
"""
s13_vistas_codigo.py -- Vistas largas de codigo alrededor de puntos de anclaje
reales (prologos MSVC, hubs, y 'sub ebx,1; jne'), siguiendo el flujo.
Sirve para decidir si la 'basura' es intercalada de forma podable o si el
codigo esta realmente corrupto/desalineado.
"""
import os, struct, pickle, collections
from capstone import Cs, CS_ARCH_X86, CS_MODE_64

HERE = os.path.dirname(os.path.abspath(__file__))
data = open(os.path.join(HERE, "stage3_code.bin"), "rb").read()
N = len(data)
lin = pickle.load(open(os.path.join(HERE, "cache_lin.pkl"), "rb"))
md = Cs(CS_ARCH_X86, CS_MODE_64); md.detail = False

def dump(start, n, label):
    print("\n" + "=" * 78)
    print("### %s @ 0x%08x" % (label, start))
    print("=" * 78)
    p = start
    for i in range(n):
        e = lin.get(p)
        if e is None:
            # desalineado: desensamblamos aqui
            ins = next(md.disasm(data[p:p+15], p), None)
            if ins is None:
                print("  %08x  << bytes %s (no desensambla) >>" % (p, data[p:p+6].hex()))
                p += 1
                continue
            print("  %08x* %-20s %-8s %s" % (p, ins.bytes.hex(), ins.mnemonic, ins.op_str))
            p += ins.size
            continue
        sz, m, ops, t = e
        extra = ""
        if t is not None:
            extra = "   ; -> 0x%08x" % t
        print("  %08x  %-20s %-8s %s%s" % (p, data[p:p + sz].hex(), m, ops, extra))
        p += sz

# 1. prologos 'sub rsp, imm32' con sizes raros (0x138, 0x158) y normales
subs = [(o, struct.unpack_from("<I", data, o + 3)[0]) for o in sorted(lin)
        if data[o:o + 3] == bytes.fromhex("4881ec")]
subs_lit = [(o, s) for o, s in subs if o in lin]
print("prologos 'sub rsp,imm32' en frontera: %d" % len(subs_lit))
big = [x for x in subs_lit if x[1] >= 128]
print("  de ellos con frame >=128: %d -> %s" % (len(big), " ".join(hex(o) for o, _ in big[:12])))
for o, s in big[:3]:
    dump(o, 26, "prologo MSVC frame=0x%x" % s)

# 2. 'sub ebx,1' seguido de jne : bucle real
print("\n\n### busqueda de 'sub ebx,1' en frontera de instruccion")
loc = [(o, lin[o + 6][1] if o + 6 in lin else "?") for o in sorted(lin)
       if data[o:o + 6] == bytes.fromhex("81eb01000000")]
print("   %d sitios; siguiente instruccion: %s" %
      (len(loc), collections.Counter(m for _, m in loc).most_common(8)))
for o, nx in loc[:3]:
    dump(max(0, o - 24), 20, "contexto de sub ebx,1")

# 3. los hubs
for h in (0x9985, 0xcce50, 0x695f1):
    dump(h, 20, "HUB")

# 4. zona de un 'sub rsp,0x20' (110 de ellos: suspicious = stub?)
print("\n\n### 'sub rsp,0x20' (110 ocurrencias)")
s20 = [(o, lin[o + 7][1]) for o in sorted(lin)
       if data[o:o + 7] == bytes.fromhex("4881ec20000000")]
print("   en frontera: %d ; siguiente: %s" % (len(s20), collections.Counter(m for _, m in s20).most_common(6)))
for o, nx in s20[:3]:
    dump(o, 12, "sub rsp,0x20")

# 5. el final del blob
dump(0x154E00, 60, "cola del blob")
dump(0x151560, 40, "cola 2")