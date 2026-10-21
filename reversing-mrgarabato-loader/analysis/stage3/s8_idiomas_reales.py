#!/usr/bin/env python3
"""
s8_idiomas_reales.py -- Busca idiomas REALES de compilador MSVC/GCC, que no
pueden aparecer por azar en relleno. Sirve para localizar el codigo autentico
dentro del blob.
"""
import os, collections, re

HERE = os.path.dirname(os.path.abspath(__file__))
data = open(os.path.join(HERE, "stage3_code.bin"), "rb").read()
N = len(data)
END = 0x154F13

def cnt(p, start=0, end=END):
    n = 0; i = data.find(p, start, end)
    while i != -1:
        n += 1; i = data.find(p, i + 1, end)
    return n

def cnt_ratio(p, nbytes=3):
    c = cnt(p)
    e = END / float(256 ** nbytes)
    return c, e, (c / e if e else 0)

IDIOMAS = [
 # (nombre, bytes, nº bytes usados en el ratio)
 ("prologo MSVC  sub rsp,imm32",      bytes.fromhex("4881ec"), 3),
 ("prologo  mov rbp,rsp",            bytes.fromhex("488bec"), 3),
 ("epilogo  add rsp,imm32",          bytes.fromhex("4881c4"), 3),
 ("guarda callee-saved [rsp+x],rbx", bytes.fromhex("48895c24"), 3),
 ("lea r64,[rsp+d32] (args MSVC)",   bytes.fromhex("488d8424"), 3),
 ("lea r64,[rbp+d32]",               bytes.fromhex("488d85"), 3),
 ("lea r64,[rip+d32]",               bytes.fromhex("488d05"), 3),
 ("loop dec+jnz  sub ebx,1",         bytes.fromhex("81eb01000000"), 4),
 ("loop inc+jnz",                    bytes.fromhex("83c301"), 2),
 ("add rsp,0x8",                     bytes.fromhex("4883c408"), 3),
 ("ret imm16",                       bytes.fromhex("c2"), 1),
 ("mov rcx, imm32 grande",           bytes.fromhex("48b9"), 2),
 ("mov [rsp+8], rbx  (shadow)",      bytes.fromhex("48895c2408"), 4),
 ("cmp rsp, imm32 (chkbk)",          bytes.fromhex("4881fc"), 3),
 ("xorps xmm (SSE)",                  bytes.fromhex("0f57"), 2),
 ("movaps/movups xmm",               bytes.fromhex("0f28"), 2),
 ("pxor xmm",                        bytes.fromhex("663f"), 2),
 ("call [rip+d32] (IAT)",            bytes.fromhex("ff15"), 2),
 ("jmp [rip+d32]",                   bytes.fromhex("ff25"), 2),
 ("int 3 (int3)",                     bytes.fromhex("cc"), 1),
 ("movabs r64,imm64",                 bytes.fromhex("48b8"), 2),
 ("vmovdqu (AVX)",                    bytes.fromhex("c5fe"), 2),
 ("vpxor (AVX)",                      bytes.fromhex("c5f9ef"), 3),
 ("prefetch",                        bytes.fromhex("0f180d"), 3),
 ("bswap r64",                        bytes.fromhex("480fc8"), 3),
]

print("%-32s %8s %12s %10s" % ("idioma", "conteo", "esperado_azar", "ratio"))
res = []
for nm, p, nb in IDIOMAS:
    c, e, r = cnt_ratio(p, nb)
    res.append((r, nm, c, e))
res.sort(reverse=True)
for r, nm, c, e in res:
    flag = "  <<< REAL" if r > 20 else ("  (relleno?)" if r < 3 else "")
    print("%-32s %8d %12.3f %10.1f%s" % (nm, c, e, r, flag))

# ---- donde se concentran los 'sub rsp,imm32' ----
print("\n=== localizacion de 'sub rsp,imm32' (123 hits) ===")
subs = []
i = data.find(bytes.fromhex("4881ec"))
while i != -1:
    if i < END:
        sz = int.from_bytes(data[i+3:i+7], "little")
        subs.append((i, sz))
    i = data.find(bytes.fromhex("4881ec"), i + 1)
print("  total: %d" % len(subs))
c = collections.Counter(s for _, s in subs)
print("  tamaños de pila mas comunes:", c.most_common(20))
print("  tamaño maximo: %d  minimo: %d" % (max(s for _, s in subs), min(s for _, s in subs)))
print("  direccion (primeros 30):", " ".join(hex(a) for a, _ in subs[:30]))
print("  ultimos 10:", " ".join(hex(a) for a, _ in subs[-10:]))

# ---- 'mov [rsp+8], rbx' : patron de sombra de argumentos ----
print("\n=== 'mov [rsp+8..0x30], reg' (copia de args a pila, MSVC) ===")
for pat, nm in [(b"\x48\x89\x44\x24\x08", "mov [rsp+8],rax"),
                (b"\x48\x89\x4c\x24\x08", "mov [rsp+8],rcx"),
                (b"\x48\x89\x54\x24\x08", "mov [rsp+8],rdx"),
                (b"\x48\x89\x5c\x24\x18", "mov [rsp+0x18],rbx"),
                (b"\x48\x89\x6c\x24\x20", "mov [rsp+0x20],rbp"),
                (b"\x48\x89\x7c\x24\x28", "mov [rsp+0x28],rdi"),
                (b"\x4c\x89\x44\x24\x30", "mov [rsp+0x30],r8"),
                (b"\x4c\x89\x4c\x24\x38", "mov [rsp+0x38],r9"),
                (b"\x48\x8b\x44\x24\x08", "mov rax,[rsp+8]"),
                (b"\x48\x8b\x4c\x24\x08", "mov rcx,[rsp+8]"),
                (b"\x48\x8b\x54\x24\x10", "mov rdx,[rsp+0x10]"),
                (b"\x48\x8d\x4c\x24\x08", "lea rcx,[rsp+8]"),
                ]:
    print("   %-26s %6d" % (nm, cnt(pat)))

# ---- repeticion de subcadenas: buscar PLANTILLAS de basura ----
print("\n=== AUTOSIMILITUD: plantillas de 16 bytes repetidas ===")
k = 16
from collections import Counter
ch = Counter()
sample = data[:END]
for i in range(0, END - k, 4):     # alineado a 4 para no inflar
    ch[sample[i:i + k]] += 1
rep = [(c, s) for s, c in ch.items() if c > 3]
rep.sort(reverse=True)
print("  plantillas de 16B (alineadas a 4) con >3 copias: %d" % len(rep))
tot = sum(c for c, s in rep)
print("  bytes cubiertos por esas plantillas: %d" % (tot * k))
for c, s in rep[:20]:
    print("   x%-5d %s" % (c, s.hex()))

# ---- entropia de orden: N-grama de opcode mas comun ----
print("\n=== distribucion de longitudes de instruccion (barrido lineal) ===")
from capstone import Cs, CS_ARCH_X86, CS_MODE_64
md = Cs(CS_ARCH_X86, CS_MODE_64); md.detail = False
lc = Counter()
p = 0
while p < N:
    ins = next(md.disasm(data[p:p+15], p), None)
    if ins is None:
        p += 1; continue
    lc[ins.size] += 1
    p += ins.size
tot = sum(lc.values())
for L, c in sorted(lc.items()):
    print("   %d bytes : %7d  %5.2f%%" % (L, c, 100.0*c/tot))