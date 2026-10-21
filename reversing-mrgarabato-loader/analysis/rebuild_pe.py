#!/usr/bin/env python3
"""Reconstruye un PE navegable a partir del volcado de memoria.
El dump es la imagen en memoria (base 0x140000000). Para que las herramientas
estructuradas (r2, Ghidra, angr) lo lean bien hay que REALINEAR la tabla de
secciones al layout en memoria Y escribir de verdad esa cabecera."""
import sys, hashlib, pefile

src, dst = sys.argv[1], sys.argv[2]
img = open(src, "rb").read()
assert img[:2] == b"MZ", "la imagen no empieza por MZ"

pe = pefile.PE(data=img, fast_load=True)
need = pe.OPTIONAL_HEADER.SizeOfImage
if len(img) < need:
    img = img + b"\x00" * (need - len(img))

for s in pe.sections:
    s.PointerToRawData = s.VirtualAddress
    s.SizeOfRawData = (s.Misc_VirtualSize + 0x1FF) & ~0x1FF

# reescribir las cabeceras dentro del propio buffer de la imagen
pe.__data__ = img[:need]
hdr = pe.write()                      # construye el fichero con los raw pointers nuevos
buf = bytearray(need)
buf[:need] = img[:need]
buf[:len(hdr)] = hdr                  # sobreescribir solo la zona de cabeceras

with open(dst, "wb") as f:
    f.write(bytes(buf))

print(f"-> {dst}: {need} bytes  sha256={hashlib.sha256(bytes(buf)).hexdigest()}")
# verificacion con una herramienta independiente
v = pefile.PE(dst, fast_load=True)
for s in v.sections:
    nm = s.Name.rstrip(b"\x00").decode("latin1")
    assert s.PointerToRawData == s.VirtualAddress, f"{nm}: rawptr no alineado"
    print(f"   {nm:<8} VA=0x{s.VirtualAddress:08x} VSZ=0x{s.Misc_VirtualSize:08x} "
          f"RAW=0x{s.PointerToRawData:08x} RSZ=0x{s.SizeOfRawData:08x}  OK")
print(f"   ImageBase=0x{v.OPTIONAL_HEADER.ImageBase:x} EP=0x{v.OPTIONAL_HEADER.AddressOfEntryPoint:x}")