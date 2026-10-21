#!/usr/bin/env python3
"""
s10_calibracion.py -- CALIBRACION CONTRA CODIGO REAL CONOCIDO.
Compara la estadística del blob stage3 con loader_solo_text.exe (133 KB de .text
ya recuperado y confirmado como código real del malware). Si stage3 no se parece
a .text, no es "código ofuscado" sino otra cosa.
"""
import os, collections, struct, sys
from capstone import Cs, CS_ARCH_X86, CS_MODE_64

HERE = os.path.dirname(os.path.abspath(__file__))
RUN  = os.path.dirname(HERE)

def stats(path, label, limit=None, base=0):
    d = open(path, "rb").read()
    if limit:
        d = d[:limit]
    md = Cs(CS_ARCH_X86, CS_MODE_64); md.detail = False
    mn = collections.Counter()
    lc = collections.Counter()
    pre = collections.Counter()
    p = 0
    N = len(d)
    bad = 0
    while p < N:
        ins = next(md.disasm(d[p:p + 15], p), None)
        if ins is None:
            p += 1; bad += 1; continue
        mn[ins.mnemonic] += 1
        lc[ins.size] += 1
        b = d[p]
        if b == 0x66: pre["66 opsize"] += 1
        if b == 0xF2: pre["F2 repne"] += 1
        if b == 0xF3: pre["F3 rep"] += 1
        if b == 0x48 or b == 0x49 or (0x40 <= b <= 0x4F): pre["REX"] += 1
        p += ins.size
    tot = sum(mn.values())
    # histogram bytes
    hb = collections.Counter(d)
    exp = N / 256.0
    chi = sum((hb.get(i, 0) - exp) ** 2 / exp for i in range(256)) / 255
    return dict(label=label, n=len(d), instr=tot, mn=mn, lc=lc, pre=pre,
                chi=chi, bad=bad, data=d)

A = stats(os.path.join(HERE, "stage3_code.bin"), "stage3 (1.33 MB)", limit=0x154F13)
REF = os.path.join(RUN, "loader_solo_text.exe")
if os.path.exists(REF):
    B = stats(REF, "loader_solo_text.exe (referencia)")
else:
    B = None

if B is None:
    print("no encuentro loader_solo_text.exe; uso stage2_code.bin")
    B = stats(os.path.join(RUN, "stage2_code.bin"), "stage2_code.bin", limit=0x154F13)

def show(S):
    tot = S["instr"]
    print("\n########## %s ##########" % S["label"])
    print("bytes=%d  instrucciones=%d  instruccion/100B=%.2f  desync=%d  chi2/255=%.1f"
          % (S["n"], tot, 100.0 * tot / S["n"], S["bad"], S["chi"]))
    print("  longitudes de instruccion:")
    for L in range(1, 13):
        c = S["lc"][L]
        if c:
            print("    %2dB : %7d  %5.2f%%  %s" % (L, c, 100.0 * c / tot, "#" * int(50.0 * c / tot)))
    print("  prefijos:")
    for k, c in S["pre"].most_common():
        print("    %-12s %7d  %5.2f%%" % (k, c, 100.0 * c / tot))
    print("  top-25 mnemonicos:")
    for m, c in S["mn"].most_common(25):
        print("    %-10s %7d  %5.2f%%" % (m, c, 100.0 * c / tot))

show(A)
show(B)

print("\n########## COMPARATIVA ##########")
print("%-14s %12s %12s %8s" % ("mnemonico", "stage3 %", "refer %", "ratio"))
allm = set(A["mn"]) | set(B["mn"])
rows = []
for m in allm:
    a = 100.0 * A["mn"].get(m, 0) / A["instr"]
    b = 100.0 * B["mn"].get(m, 0) / B["instr"]
    rows.append((a / b if b else 999, m, a, b))
rows.sort(reverse=True)
for r, m, a, b in rows[:20]:
    print("%-14s %11.3f%% %11.3f%% %8.2f" % (m, a, b, r))
print("  ...")
for r, m, a, b in rows[-20:]:
    print("%-14s %11.3f%% %11.3f%% %8.2f" % (m, a, b, r))

print("\n########## longitudes ##########")
print("%-6s %12s %12s" % ("len", "stage3 %", "ref %"))
for L in range(1, 13):
    a = 100.0 * A["lc"][L] / A["instr"]
    b = 100.0 * B["lc"][L] / B["instr"]
    if a or b:
        print("%-6d %11.2f%% %11.2f%%" % (L, a, b))