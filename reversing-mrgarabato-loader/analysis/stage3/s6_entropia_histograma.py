#!/usr/bin/env python3
"""
s6_entropia_histograma.py -- Analiza la distribucion de BYTES del blob.
Preguntas decisivas:
  A. ¿Es el blob uniforme (ruido cifrado) o tiene alfabetos restringidos?
  B. ¿Cuantos bytes distintos aparecen y con que frecuencia?
  C. Chi2/255 por bloques, y top bytes.
  D. ¿Los "hot hubs" de jmp forman una estructura repetida (plantilla)?
"""
import os, collections, math, struct

HERE = os.path.dirname(os.path.abspath(__file__))
data = open(os.path.join(HERE, "stage3_code.bin"), "rb").read()
N = len(data)
END = 0x154F13

h = collections.Counter(data)
print("=== histogram global de bytes (blob %d B) ===" % N)
print("bytes distintos usados: %d / 256" % len(h))
exp = N / 256.0
chi = sum((h.get(i, 0) - exp) ** 2 / exp for i in range(256))
print("chi2/255 = %.2f   (uniforme puro daria ~1.0)" % (chi / 255))
print("\n%5s %9s %8s %6s  %s" % ("byte", "count", "esperado", "ratio", "mnem tipico"))
MN = {0x48:"REX.W", 0x00:"add/or", 0x8b:"mov", 0xff:"grp5", 0x89:"mov", 0x83:"grp1",
      0xe9:"jmp", 0x74:"je", 0x75:"jne", 0xf8:"clc", 0xf9:"stc", 0xf5:"cmc",
      0x0f:"esc2", 0x8d:"lea", 0xc3:"ret", 0xc2:"ret", 0xcc:"int3", 0x90:"nop",
      0xd3:"grp2 rcl/rol/ror", 0x0f: "esc2"}
for b, c in h.most_common(48):
    print("%02X    %9d %9.0f %6.2f  %s" % (b, c, exp, c / exp, MN.get(b, "")))
print("...")
for b in range(256):
    if h.get(b, 0) == 0:
        print("byte %02X ausente" % b)

# ---- chi2 por bloques de 32 KB ----
print("\n=== chi2/255 por bloques de 32 KB ===")
B = 0x8000
for i in range(0, END, B):
    blk = data[i:i + B]
    hb = collections.Counter(blk)
    e = len(blk) / 256.0
    c2 = sum((hb.get(j, 0) - e) ** 2 / e for j in range(256)) / 255
    print("  %08x  chi2/255=%8.2f  distintos=%3d" % (i, c2, len(hb)))

# ---- los hubs: comparar sus 32 bytes ----
print("\n=== los 9 hubs de jmp: contexto de 24 bytes en el destino ===")
hubs = [0xcbb18, 0x90bc5, 0x117340, 0x9985, 0x62887, 0xcce50, 0x124358, 0xa67df, 0x81e8e]
for t in hubs:
    print("  %08x  %s" % (t, data[t:t + 24].hex()))

print("\n=== 32 bytes que ANTECEDEN a cada hub (el 'prefijo' comun) ===")
pref = [data[t - 32:t] for t in hubs]
for t, p in zip(hubs, pref):
    print("  %08x  %s" % (t - 32, p.hex()))

# ---- comparar con bytes aleatorios: distribucion de "longitud de instruccion" ----
# proxy: los bytes E9 con destino dentro, su distribution
print("\n=== prueba de autenticidad: patrones de 3 bytes mas discriminating ===")
tests = {
    "48 81 EC (sub rsp,i32)": bytes.fromhex("4881ec"),
    "48 8B EC (mov rbp,rsp)": bytes.fromhex("488bec"),
    "0F 85 (jne rel32)":     bytes.fromhex("0f85"),
    "48 8D (lea r64)":        bytes.fromhex("488d"),
    "FF D0 (call rax)":       bytes.fromhex("ffd0"),
    "FF 15 (call [rip+d])":   bytes.fromhex("ff15"),
    "48 FF (call/jmp r64)":   bytes.fromhex("48ff"),
    "4C 89 (mov r/m64,r8+)":  bytes.fromhex("4c89"),
    "C3 (ret)":               b"\xc3",
    "CC (int3)":              b"\xcc",
    "F8 (clc)":               b"\xf8",
    "0F 1F (nop mult)":       bytes.fromhex("0f1f"),
    "90 (nop)":               b"\x90",
}
print("%-26s %8s %12s %9s" % ("patron", "conteo", "esperado(rnd)", "ratio"))
for k, p in tests.items():
    c = 0
    i = data.find(p)
    while i != -1:
        c += 1
        i = data.find(p, i + 1)
    e = N / float(len(p)) / (256.0 ** (len(p) - 1)) if len(p) > 1 else N / 256.0
    print("%-26s %8d %12.2f %9.1f" % (k, c, e, c / e if e else 0))

# ---- frecuencia de 'E9' por posicion: ¿uniforme o en racimos? ----
print("\n=== autocorrelacion de la posicion de E9 (lag 5..64) ===")
e9 = [i for i in range(END) if data[i] == 0xE9]
eset = set(e9)
for lag in [5, 10, 20, 40, 80, 160, 320, 1000, 4096]:
    c = sum(1 for x in e9 if (x + lag) in eset)
    print("   lag %5d : %6d pares (esperado %.1f)" % (lag, c, len(e9) * len(e9) / float(N)))