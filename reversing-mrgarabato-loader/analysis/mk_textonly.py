#!/usr/bin/env python3
"""PE recortado (solo .text/.rdata/.data/.pdata) con el layout de memoria real
para que Ghidra pueda analizar rapido la zona de codigo limpia."""
import struct

pe_img = open("unpacked_loader.exe", "rb").read()
mem = open("mem_loader.bin", "rb").read()
DST = "loader_textonly.exe"

hdr = bytearray(pe_img[:0x1000])
peoff = struct.unpack_from("<I", hdr, 0x3c)[0]
nsec = struct.unpack_from("<H", hdr, peoff + 6)[0]
szopt = struct.unpack_from("<H", hdr, peoff + 20)[0]
opt = peoff + 24
sec0 = opt + szopt

KEEP = {0, 1, 2, 3}
last = 0
for i in range(nsec):
    off = sec0 + i * 40
    vsz = struct.unpack_from("<I", hdr, off + 8)[0]
    va = struct.unpack_from("<I", hdr, off + 12)[0]
    if i in KEEP:
        last = max(last, va + ((vsz + 0xFFF) & ~0xFFF))
    else:
        hdr[off + 8:off + 12] = struct.pack("<I", 0)
        hdr[off + 16:off + 20] = struct.pack("<I", 0)
        hdr[off + 20:off + 24] = struct.pack("<I", 0)
        hdr[off + 36:off + 40] = struct.pack("<I", 0xC0000040)

struct.pack_into("<I", hdr, opt + 56, last)     # SizeOfImage
struct.pack_into("<I", hdr, opt + 16, 0x1000)   # EP -> .text

# cuerpo = imagen completa hasta 'last' (offset de fichero == RVA)
body = bytearray(mem[:last])
body[0:0x1000] = hdr
# ajusta SizeOfRawData de las secciones conservadas para que quepan
for i in range(nsec):
    off = sec0 + i * 40
    va = struct.unpack_from("<I", hdr, off + 12)[0]
    vsz = struct.unpack_from("<I", hdr, off + 8)[0]
    if i in KEEP:
        struct.pack_into("<I", body, off + 16, (vsz + 0x1FF) & ~0x1FF)

open(DST, "wb").write(bytes(body))
print("[+] %s: %d bytes, SizeOfImage=0x%x" % (DST, len(body), last))