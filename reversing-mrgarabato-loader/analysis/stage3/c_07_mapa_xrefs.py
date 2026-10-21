#!/usr/bin/env python3
"""c_07_mapa_xrefs.py -- Verifica dump<->imagen y busca referencias al blob en .text/.rdata."""
import struct, re
from capstone import Cs, CS_ARCH_X86, CS_MODE_64

RUN = "/root/mrgarabato_analysis/run/"
DUMP = RUN+"stage3/wine__w7.bin"
IMG  = RUN+"loader_solo_text.exe"
d = open(DUMP, "rb").read()
im = open(IMG, "rb").read()

print("dump=%d img=%d" % (len(d), len(im)))
b1 = d[0x227A0:0x22A00]; b2 = d[0x22A50:0x22BE0]

# 1) el blob aparece literal en la imagen?
for nm, b, off in (("BLOB1", b1, 0x227A0), ("BLOB2", b2, 0x22A50)):
    hits = []; st = 0
    while len(hits) < 6:
        i = im.find(b, st)
        if i < 0: break
        hits.append(i); st = i+1
    print(f"{nm}: en loader_solo_text.exe en offsets {[hex(h) for h in hits]}")
    if off in [h for h in hits]: print("   -> coincide con el offset del dump (dump_off == file_off)")

# 2) .text del dump vs .text de la imagen
print("\ncomparacion dump[0:0x20A00] (supuesto .text) vs img[0x1000:0x21A00]")
a = d[0:0x2086C]; b = im[0x1000:0x1000+0x2086C]
same = sum(1 for x,y in zip(a,b) if x==y)
print(f"  bytes iguales: {same}/{len(a)} ({same/len(a)*100:.2f}%)")

# 3) el dump empieza en RVA 0x1000? compara los primeros bytes
print("  dump[0:16] =", d[:16].hex())
print("  img [0x1000:0x1010] =", im[0x1000:0x1010].hex())

# 4) buscar referencias RIP-relativas a RVA 0x237A0 / 0x23A50 dentro de la imagen
print("\n--- barrido de referencias RIP-relativas en TODO el fichero imagen ---")
targets = {0x237A0: "BLOB1(RVA)", 0x23A50: "BLOB2(RVA)",
           0x227A0: "BLOB1(fileoff)", 0x22A50: "BLOB2(fileoff)"}
found = []
md = Cs(CS_ARCH_X86, CS_MODE_64); md.detail = False
for i in range(0x1000, 0x21000):
    pass
# mas rapido: slide sobre el .text
code = im[0x1000:0x2086C]
base = 0x1000
for ins in md.disasm(code, base):
    m = re.search(r"\[rip \+ (0x[0-9a-f]+)\]|\[rip - (0x[0-9a-f]+)\]", ins.op_str)
    if not m: continue
    off = int(m.group(1) or m.group(2), 16)
    if ins.op_str.startswith("[rip -"): off = -off
    tgt = ins.address + ins.size + off
    if tgt in targets:
        found.append((ins.address, ins.mnemonic, ins.op_str, targets[tgt]))
print(f"  coincidencias en .text: {len(found)}")
for f in found[:40]: print("   0x%06X  %-8s %-40s -> %s" % f)

# 5)同样的 barrido con el dump (por si el volcado tiene el .text en otra parte)
print("\n--- barrido sobre el volcado completo (solo .text plausible 0..0x21000) ---")
cnt=0
for ins in md.disasm(d[0x1000:0x21000], 0x825000+0x1000):
    m = re.search(r"\[rip \+ (0x[0-9a-f]+)\]|\[rip - (0x[0-9a-f]+)\]", ins.op_str)
    if not m: continue
    off = int(m.group(1) or m.group(2), 16)
    if ins.op_str.startswith("[rip -"): off = -off
    tgt = ins.address + ins.size + off
    if tgt in (0x825000+0x227A0, 0x825000+0x22A50):
        cnt+=1; print("   0x%X %s %s" % (ins.address, ins.mnemonic, ins.op_str))
print("  coincidencias:", cnt)

# 6) ¿existe algun patron de 32 bits 0x227A0 / 0x22A50little-endian en la imagen?
print("\n--- valores 0x227A0/0x22A50/0x237A0/0x23A50 como dword en la imagen ---")
for v in (0x227A0, 0x22A50, 0x237A0, 0x23A50):
    pat = struct.pack("<I", v)
    hits=[]; st=0
    while len(hits)<10:
        i = im.find(pat, st)
        if i<0: break
        hits.append(i); st=i+1
    print(f"  0x{v:X}: {[hex(h) for h in hits]}")
