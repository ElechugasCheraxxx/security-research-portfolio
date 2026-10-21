#!/usr/bin/env python3
"""recortar_loader.py — genera un PE reducedo con solo las secciones reales,
para que el auto-análisis de Ghidra/REA no se ahogue con ~16 MB de texto cifrado.

Se ponen a cero SizeOfRawData y VirtualSize de las secciones cifradas, se
recalcula SizeOfImage y se limpian los data directories que apuntan a ellas.
"""
import struct, sys

src = sys.argv[1] if len(sys.argv) > 1 else 'unpacked_loader.exe'
dst = sys.argv[2] if len(sys.argv) > 2 else 'loader_solo_text.exe'
f = bytearray(open(src, 'rb').read())

e = struct.unpack_from('<I', f, 0x3c)[0]
nsec = struct.unpack_from('<H', f, e + 6)[0]
optsz = struct.unpack_from('<H', f, e + 20)[0]
opt = e + 24
so = opt + optsz
magic = struct.unpack_from('<H', f, opt)[0]
dd = opt + (112 if magic == 0x20b else 96)

KEEP = {'.text', '.rdata', '.data', '.3rs'}
print('secciones:')
dropped = []
for i in range(nsec):
    b = so + i * 40
    name = f[b:b + 8].rstrip(b'\x00').decode('latin1')
    vsz, va, rsz, ra = struct.unpack_from('<IIII', f, b + 8)
    if name in KEEP:
        print(f'  {name:<10} RVA 0x{va:08x}  raw {rsz:>9}   (se conserva)')
        continue
    dropped.append((name, va, vsz))
    print(f'  {name:<10} RVA 0x{va:08x}  raw {rsz:>9}   -> SE PONE A CERO')
    struct.pack_into('<I', f, b + 8, 0)     # VirtualSize
    struct.pack_into('<I', f, b + 16, 0)    # SizeOfRawData

# SizeOfImage = último RVA conservado + su VirtualSize, alineado a SectionAlignment
sa = struct.unpack_from('<I', f, opt + 32)[0]
fa = struct.unpack_from('<I', f, opt + 36)[0]
last = 0
for i in range(nsec):
    b = so + i * 40
    name = f[b:b + 8].rstrip(b'\x00').decode('latin1')
    if name not in KEEP:
        continue
    vsz, va, rsz, ra = struct.unpack_from('<IIII', f, b + 8)
    last = max(last, va + max(vsz, rsz))
size_of_image = (last + sa - 1) & ~(sa - 1)
struct.pack_into('<I', f, opt + 56, size_of_image)
print(f'\nSizeOfImage: 0x{size_of_image:x}')

# limpiar data directories que apunten a secciones eliminadas
dirs = ['EXPORT','IMPORT','RESOURCE','EXCEPTION','SECURITY','BASERELOC',
        'DEBUG','ARCHITECTURE','GLOBALPTR','TLS','LOAD_CONFIG','BOUND_IMPORT',
        'IAT','DELAY_IMPORT','CLR']
for n, va, vsz in dropped:
    for j, dn in enumerate(dirs):
        rva, sz = struct.unpack_from('<II', f, dd + j * 8)
        if rva and rva >= va and rva < va + max(vsz, 1):
            print(f'  data directory {dn} (0x{rva:x}) apunta a {n}: anulado')
            struct.pack_into('<II', f, dd + j * 8, 0, 0)

# el punto de entrada debe caer en .text
ep = struct.unpack_from('<I', f, opt + 16)[0]
print(f'EntryPoint RVA 0x{ep:x} -> VA 0x{0x140000000+ep:x}')

open(dst, 'wb').write(f)
print(f'\nescrito {dst}: {len(f)} bytes')
