#!/usr/bin/env python3
"""Localiza las funciones que referencian las cadenasclave del payload
(C2, emuladores, deteccion de VM) escaneando LEA/MOV rip-relativos."""
import sys
from capstone import *
from capstone.x86 import X86_OP_MEM, X86_REG_RIP

img = open(sys.argv[1], "rb").read()
BASE = 0x140000000
md = Cs(CS_ARCH_X86, CS_MODE_64); md.detail = True

INTEREST = {
    0x19f70: "C2 https://mrgarabato.com/",
    0x19ef8: "mutex UpdatedFreeFire_ByPass",
    0x1a208: "HD-Player.exe (BlueStacks)",
    0x1a218: "MEmu.exe",
    0x1a1f0: "[+] Checking Update",
    0x1a280: "[+] Injection Process",
    0x1a298: "[+] Success",
    0x1f50:  "expired",
    0x1fa0:  "Outdated version",
    0x19f28: "YX9Y0KWPU6 (token compartido)",
    0x19f38: "XG-IXn*bf!DAVvVQt? (ofuscado)",
}

# solo regiones con codigo limpio
REGIONS = [(0x1000, 0x18000), (0x23000, 0x57000), (0x59000, 0x80b000)]

hits = {}
for lo, hi in REGIONS:
    for i in md.disasm(img[lo:hi], BASE + lo):
        for op in i.operands:
            if op.type == X86_OP_MEM and op.mem.base == X86_REG_RIP:
                tgt = i.address + i.size + op.mem.disp
                off = tgt - BASE
                if off in INTEREST:
                    hits.setdefault(i.address, set()).add(INTEREST[off])

print(f"[+] {len(hits)} instrucciones referencian las cadenas clave:\n")
for addr in sorted(hits):
    print(f"  0x{addr:012x}  ->  {', '.join(sorted(hits[addr]))}")

# agrupar en funciones por proximidad (heuristica: mismo bloque de 0x1000)
print("\n[+] funciones candidatas (agrupadas):")
groups = {}
for a in sorted(hits):
    groups.setdefault(a & ~0xFFF, []).append(a)
for g in sorted(groups):
    print(f"\n  --- funcion ~0x{g:012x} ---")
    for a in groups[g]:
        print(f"      0x{a:012x}  {', '.join(sorted(hits[a]))}")