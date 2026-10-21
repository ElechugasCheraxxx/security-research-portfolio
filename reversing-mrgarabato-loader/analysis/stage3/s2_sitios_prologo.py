#!/usr/bin/env python3
"""
s2_sitios_prologo.py -- Localiza los 'sub rsp, imm32' (48 81 EC) y otros
patrones de prologo MSVC, y desensambla una ventana a su alrededor alineando
el valla de prologo como inicio de funcion. Sirve para decidir la alineacion
correcta del barrido lineal.
"""
import os, struct, collections
from capstone import Cs, CS_ARCH_X86, CS_MODE_64

HERE = os.path.dirname(os.path.abspath(__file__))
data = open(os.path.join(HERE, "stage3_code.bin"), "rb").read()
N = len(data)
md = Cs(CS_ARCH_X86, CS_MODE_64)
md.detail = False

# --- busqueda de patrones de prologo ---
pats = {
    "sub_rsp_imm32   (48 81 EC)":  bytes.fromhex("4881ec"),
    "mov_rbp_rsp     (48 8B EC)":  bytes.fromhex("488bec"),
    "mov_[rsp+x],rbx (48 89 5C 24)": bytes.fromhex("48895c24"),
    "push_rbp        (55)"+"\x00"*0: b"\x55\x48",
    "lea_rax_rip     (48 8D 05)":  bytes.fromhex("488d05"),
    "int3            (CC)":         b"\xcc",
}

def find_all(hay, needle):
    out = []
    i = hay.find(needle)
    while i != -1:
        out.append(i)
        i = hay.find(needle, i + 1)
    return out

sites = collections.OrderedDict()
for k, p in pats.items():
    if len(p) == 3 and k.startswith("push_rbp"):
        continue
    sites[k] = find_all(data, p)

for k, v in sites.items():
    print("%-32s %6d  primeros: %s" % (k, len(v), " ".join(hex(x) for x in v[:8])))

# --- ventanas alrededor de cada prologo ---
prol = sites["sub_rsp_imm32   (48 81 EC)"]
print("\n=== ventanas de 20 instr desde cada 'sub rsp,imm32' (alineado en el prologo) ===")
with open(os.path.join(HERE, "s2_ventanas_prologo.txt"), "w") as f:
    for p in prol[:14]:
        f.write("\n######## prologo en 0x%08x ########\n" % p)
        n = 0
        for ins in md.disasm(data[p:p + 160], p):
            f.write("  %08x  %-24s %s\n" % (ins.address, ins.bytes.hex(), ins.op_str))
            n += 1
            if n >= 22:
                break

# --- alineacion:ahead test con ventana deslizante ---
# Para cada alineacion inicial 0..15,有多少 "sub rsp" caen justo en frontera de instr
print("\n=== test de alineacion global (0..15) ===")
for a in range(16):
    ok = 0
    tot = 0
    off = a
    while off < N:
        ins = next(md.disasm(data[off:off + 15], off), None)
        if ins is None:
            off += 1
            continue
        tot += 1
        if ins.mnemonic == "ret":
            ok += 1
        off += ins.size
    print("  alineacion %2d: %7d instr, %5d ret (%.2f%%)" % (a, tot, ok, 100.0 * ok / max(tot, 1)))