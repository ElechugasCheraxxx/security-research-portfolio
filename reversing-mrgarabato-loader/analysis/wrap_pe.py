#!/usr/bin/env python3
"""wrap_pe.py — envuelve codigo x86-64 crudo en un PE minimo analizable.

Uso: wrap_pe.py <entrada.bin> <salida.exe> [rva_base_hex]

El .text contiene el codigo tal cual y el EntryPoint apunta al inicio, de modo
que las direcciones de Ghidra coinciden con el layout original del binario
protegido (el .text arranca en el RVA indicado).
"""
import struct
import sys

src = sys.argv[1]
dst = sys.argv[2]
rva = int(sys.argv[3], 16) if len(sys.argv) > 3 else 0x1000
code = open(src, 'rb').read()

IB = 0x140000000
SA = 0x1000
FA = 0x200
vsz = (len(code) + SA - 1) & ~(SA - 1)
rsz = (len(code) + FA - 1) & ~(FA - 1)

# ---- DOS header: 64 bytes de campos + relleno hasta 0x80 ----
hdr = bytearray(0x80)
hdr[0:2] = b'MZ'
struct.pack_into('<H', hdr, 2, 0x90)        # e_cblp
struct.pack_into('<H', hdr, 4, 3)           # e_cp
struct.pack_into('<H', hdr, 8, 4)           # e_cparhdr
struct.pack_into('<H', hdr, 0x18, 0x40)     # e_lfarlc
struct.pack_into('<I', hdr, 0x3C, 0x80)     # e_lfanew

# ---- PE signature + COFF header ----
pe = bytearray(b'PE\x00\x00')
pe += struct.pack('<HHIIIHH', 0x8664, 1, 0, 0, 0, 0xF0, 0x22)

# ---- Optional header (PE32+) ----
opt = bytearray()
opt += struct.pack('<HBB', 0x20B, 14, 39)          # Magic, linker
opt += struct.pack('<I', len(code))                 # SizeOfCode
opt += struct.pack('<I', 0)                         # SizeOfInitializedData
opt += struct.pack('<I', 0)                         # SizeOfUninitializedData
opt += struct.pack('<I', rva)                       # AddressOfEntryPoint
opt += struct.pack('<I', rva)                       # BaseOfCode
opt += struct.pack('<Q', IB)                        # ImageBase
opt += struct.pack('<II', SA, FA)                   # section/file alignment
opt += struct.pack('<HHHHHH', 6, 0, 0, 0, 6, 0)     # OS/Image/Subsystem versions
opt += struct.pack('<I', 0)                         # Win32VersionValue
opt += struct.pack('<I', vsz + SA)                  # SizeOfImage
opt += struct.pack('<I', 0x200)                     # SizeOfHeaders
opt += struct.pack('<I', 0)                         # CheckSum
opt += struct.pack('<H', 3)                         # Subsystem = console
opt += struct.pack('<H', 0x8120)                    # DllCharacteristics
opt += struct.pack('<Q', 0x100000)                  # SizeOfStackReserve
opt += struct.pack('<Q', 0x1000)                    # SizeOfStackCommit
opt += struct.pack('<Q', 0x100000)                  # SizeOfHeapReserve
opt += struct.pack('<Q', 0x1000)                    # SizeOfHeapCommit
opt += struct.pack('<I', 0)                         # LoaderFlags
opt += struct.pack('<I', 16)                        # NumberOfRvaAndSizes
opt += b'\x00' * (16 * 8)                           # data directories
assert len(opt) == 112 + 16 * 8, len(opt)   # campos estandar + data directories

# ---- Section header ----
sec = bytearray()
sec += b'.text\x00\x00\x00'
sec += struct.pack('<IIII', vsz, rva, rsz, 0x200)   # VSZ, RVA, RSZ, rawptr
sec += struct.pack('<IIHHI', 0, 0, 0, 0, 0x60000020)  # CODE|EXECUTE|READ

out = bytearray()
out += hdr + pe + opt + sec
out += b'\x00' * (0x200 - len(out))
out += code
out += b'\x00' * (rsz - len(code))

open(dst, 'wb').write(out)
print(f"{dst}: {len(out)} B")
print(f"  .text  RVA 0x{rva:x}   codigo {len(code)} B")
print(f"  EP     VA 0x{IB + rva:x}  == primer byte del codigo extraido")