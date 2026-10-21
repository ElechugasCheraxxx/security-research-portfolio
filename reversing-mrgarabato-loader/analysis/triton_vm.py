#!/usr/bin/env python3
"""Perfila el dispatcher VM con Triton leyendo RIP en cada paso.
Confirma la hipotesis: si .3q- es un interprete de bytecode, debe existir
un bucle caliente que lea un puntero a bytecode y salte de forma repetitiva."""
import sys, collections
from triton import TritonContext, ARCH, MODE

path, EP = sys.argv[1], int(sys.argv[2], 16)
img = open(path, "rb").read()
BASE = 0x140000000

ctx = TritonContext(ARCH.X86_64)
ctx.setMode(MODE.ALIGNED_MEMORY, True)
ctx.setConcreteMemoryAreaValue("memory", BASE, bytes(img))
STACK_TOP = 0x50000000
ctx.setConcreteMemoryAreaValue("memory", STACK_TOP - 0x10000, b"\x00" * 0x10000)
ctx.setRegisterValue(ctx.registers.rsp, STACK_TOP - 0x400)
ctx.setConcreteMemoryAreaValue("memory", 0x60000000, b"\x00" * 0x200000)

def rd(a, n):
    try:
        return bytes(ctx.getConcreteMemoryValue(a + i) for i in range(n))
    except Exception:
        return None

counts = collections.Counter()
N = 200000
done = None
print(f"[*] emulando desde 0x{EP:x} ({N} pasos)...", flush=True)
try:
    for _ in range(N):
        ctx.processing()
        rip = ctx.getConcreteRegisterValue(ctx.registers.rip)
        counts[rip] += 1
except Exception as e:
    done = f"{type(e).__name__}: {e}"

total = sum(counts.values())
print(f"[*] pasos: {total}   direcciones distintas: {len(counts)}")
if done:
    print(f"[*] detenido: {done}")
    print(f"    RIP final = 0x{ctx.getConcreteRegisterValue(ctx.registers.rip):x}")

print("\n[*] TOP 25 direcciones mas ejecutadas:")
for a, c in counts.most_common(25):
    b = rd(a, 8)
    tag = "  <== EP" if a == EP else ""
    inside = "3q-VM" if BASE + 0x81c000 <= a < BASE + 0xf8a8a4 else (
             "7f-code" if BASE + 0x23000 <= a < BASE + 0x80b000 else "otros")
    print(f"   0x{a:012x} [{inside:7}] x{c:<7} {(b or b'').hex()}{tag}")

# interprete tipico: un bloque pequeno de direcciones muy calientes
top = counts.most_common(40)
hot = [a for a, c in top if c > total * 0.01]
print(f"\n[*] {len(hot)} direcciones con >1% del tiempo de ejecucion "
      f"-> nucleo del dispatcher")
for a in hot:
    print(f"    0x{a:012x}  x{counts[a]}")