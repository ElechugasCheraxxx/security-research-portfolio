#!/usr/bin/env python3
"""c_03_layout.py -- Mapa del volcado: donde esta el PE, que regions hay."""
import struct, collections

DUMP = "/root/mrgarabato_analysis/run/stage3/wine__w7.bin"
d = open(DUMP, "rb").read()
N = len(d)
print("dump:", hex(N), d[:64].hex())

# buscar cabeceras PE/IMAGE y firmas de regiones de wine
for pat, nm in ((b"MZ", "MZ"), (b"PE\0\0", "PE\\0\\0"), (b"\0\0\0\0MZ", "..MZ"),
                (b"wine_", "wine_"), (b"WINE", "WINE")):
    hits = []
    st = 0
    while True:
        i = d.find(pat, st)
        if i < 0 or len(hits) >= 25: break
        hits.append(i); st = i+1
    print(f"{nm:10s}: {len(hits)} hits -> " + ", ".join("0x%X"%h for h in hits[:25]))

# el volcado son 0x76E000 bytes = 7.79MB. Base?
print("\nprimeros 0x100 bytes:")
for i in range(0, 0x100, 16):
    row = d[i:i+16]
    print(f"  {i:06x}: " + " ".join("%02x"%c for c in row).ljust(48) +
          " " + "".join(chr(c) if 32<=c<127 else "." for c in row))

# donde cae .rdata segun el enunciado
print("\n.vista de 0x021600-0x021780 (inicio de .rdata segun enunciado):")
for i in range(0x21600, 0x21780, 16):
    row = d[i:i+16]
    print(f"  {i:06x}: " + " ".join("%02x"%c for c in row).ljust(48) +
          " " + "".join(chr(c) if 32<=c<127 else "." for c in row))

# el PE header deberia estar por debajo de 0x21700 si el dump empieza en la base.
# Busca el patron DOS header estandar: 4D5A ... "This program cannot be run in DOS mode"
for sig, nm in ((b"This program cannot be run in DOS mode", "dosstub"),
                (b".text", ".text"), (b".rdata", ".rdata"), (b".data", ".data")):
    hits=[]; st=0
    while len(hits)<10:
        i=d.find(sig, st)
        if i<0: break
        hits.append(i); st=i+1
    print(f"{nm:12s}: " + ", ".join("0x%X"%h for h in hits))

# ??? el dump empieza en 0 con c0498bf8 -- eso parece codigo x86 (little endian f8 8b 49 c0
# => en little endian los 4 bytes son f8 8b 49 c0 -> "clc; mov ecx,[ecx-40h]")
# Busca 'MZ' mas alla de 0x20000
print("\nprimeras 5 coincidencias de b'MZ' en el dump:")
st=0; c=0
while c<5:
    i=d.find(b"MZ", st)
    if i<0: break
    print("   0x%X : %s" % (i, d[i:i+24].hex()))
    st=i+1; c+=1
