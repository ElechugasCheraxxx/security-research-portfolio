#!/usr/bin/env python3
"""Descenso recursivo sobre el interprete VM (RVA 0xE3C000-0xF8A8A4).
El desensamblado lineal muere en el primer byte invalido porque el codigo esta
desincronizado a proposito. Aqui se siembra en puntos conocidos y se siguen
todos los saltos, construyendo el grafo real y la tabla de handlers."""
import sys, collections, struct, json
from capstone import *
from capstone.x86 import *

img = open("mem_bypass.bin", "rb").read()
BASE = 0x140000000
LO, HI = 0xE3C000, 0xF8A8A4

md = Cs(CS_ARCH_X86, CS_MODE_64)
md.detail = True


def decode(addr, count=1):
    off = addr - BASE
    if off < 0 or off >= len(img):
        return []
    try:
        return list(md.disasm(img[off:off + 15], addr, count=count))
    except Exception:
        return []


def direct_target(ins):
    """Devuelve el destino si el salto es relativo directo."""
    if ins.id not in (X86_INS_JMP, X86_INS_CALL):
        return None
    try:
        t = int(ins.op_str, 16)
        return t
    except ValueError:
        return None


def in_range(a):
    return BASE + LO <= a < BASE + HI


# semillas: inicio de la zona + destinos de salto ya observados
SEEDS = [BASE + 0xE3C000,
         BASE + 0xE5FFB4, BASE + 0xEBFD82, BASE + 0xF47DD4,
         BASE + 0xF16965, BASE + 0xF50F1A, BASE + 0xE87B20,
         BASE + 0xF76240, BASE + 0xF21D77]
# anclas: direcciones de .3q- que la traza demuestra ejecutadas
try:
    for line in open("anchors_3q.txt"):
        SEEDS.append(int(line.split()[0]))
except FileNotFoundError:
    pass

visited = {}        # addr -> (size, bytes, mnemonic, opstr)
edges = collections.Counter()     # (origen,destino) para saltos directos
targets = collections.Counter()   # destinos alcanzados
worklist = list(SEEDS)
MAX = 3000000

while worklist and len(visited) < MAX:
    a = worklist.pop()
    if a in visited or not in_range(a):
        continue
    ins = decode(a, 1)
    if not ins:
        continue
    i = ins[0]
    visited[a] = (i.size, i.bytes.hex(), i.mnemonic, i.op_str)

    # continuar linealmente (salvo en saltos/retornos)
    nxt = a + i.size
    if i.id in (X86_INS_RET, X86_INS_HLT, X86_INS_INT3, X86_INS_UD2):
        continue
    if i.id == X86_INS_JMP:
        t = direct_target(i)
        if t and in_range(t):
            edges[(a, t)] += 1
            targets[t] += 1
            worklist.append(t)
            continue          # un jmp no tiene flujo lineal posterior
    if i.id == X86_INS_CALL:
        t = direct_target(i)
        if t and in_range(t):
            edges[(a, t)] += 1
            targets[t] += 1
            worklist.append(t)
    # ramas condicionales: ambas se siguen
    if i.mnemonic.startswith("j") and i.id != X86_INS_JMP:
        t = direct_target(i)
        if t and in_range(t):
            edges[(a, t)] += 1
            targets[t] += 1
            worklist.append(t)
    # flujo lineal
    worklist.append(nxt)

print("[+] direcciones decodificadas: %d" % len(visited))
print("    saltos/call directos dentro del interprete: %d" % len(edges))

print("\n[*] TOP 30 destinos mas referenciados (posibles handlers de la VM):")
for t, n in targets.most_common(30):
    print("   0x%x  referenciado %d veces" % (t, n))

# cluster de handlers: destinos que nunca vuelven al flujo principal
print("\n[*] handlers (destinos alcanzados solo por salto directo):")
hh = [t for t, n in targets.most_common(80) if n >= 1]
print("   %d candidatos" % len(hh))

with open("vm_dispatch_graph.json", "w") as f:
    json.dump({"visited": {hex(k): v for k, v in visited.items()},
               "edges": [[hex(a), hex(b), n] for (a, b), n in edges.items()]}, f)
print("\n[+] grafo -> vm_dispatch_graph.json")

# volcar los handlers mas referenciados para inspeccion
print("\n" + "=" * 70)
print("DESENSAMBLADO DE LOS 10 HANDLERS MAS REFERENCIADOS")
print("=" * 70)
for t, n in targets.most_common(10):
    print("--- handler 0x%x (ref %d) ---" % (t, n))
    a = t
    for _ in range(14):
        off = a - BASE
        if off < 0 or off >= len(img):
            break
        try:
            ii = list(md.disasm(img[off:off + 15], a, count=1))
        except Exception:
            break
        if not ii:
            print("    0x%x  <no decodificable>" % a)
            break
        x = ii[0]
        print("    0x%x  %-24s %-8s %s" % (x.address, x.bytes.hex(), x.mnemonic, x.op_str))
        if x.id in (X86_INS_JMP, X86_INS_RET):
            break
        a = x.address + x.size
    print()