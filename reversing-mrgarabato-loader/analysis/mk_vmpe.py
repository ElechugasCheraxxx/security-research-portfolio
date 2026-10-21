#!/usr/bin/env python3
"""Construye PEs minimos que contienen SOLO las secciones que interesan,
manteniendo ImageBase 0x140000000 y los RVAs originales, para que las
herramientas (RetDec, IDA, Hopper, Ghidra) trabajen sobre direcciones que
coincidan con los RVAs ya documentados.

Uso:
  mk_vmpe.py out.exe LO:HI[:NAME] [LO:HI[:NAME] ...]
"""
import struct, sys

BASE = 0x140000000
img = open("mem_bypass.bin", "rb").read()


def build(out, sections, entry_rva=None):
    """sections: lista de (rva, hi, name)"""
    FILEALIGN = 0x200
    SECALIGN = 0x1000
    nsec = len(sections)
    hdrsz = 0x200 + 40 * nsec
    off = hdrsz

    sec_hdrs = b""
    body = b""
    for (rva, hi, name) in sections:
        vsz = hi - rva
        # alinear RVA inicial a SECALIGN hacia abajo
        rva_a = (rva // SECALIGN) * SECALIGN
        pad_front = rva - rva_a
        rawsz = ((vsz + pad_front) + FILEALIGN - 1) // FILEALIGN * FILEALIGN
        # espacio de headers
        if off < rva_a:
            filler = b"\x00" * (rva_a - off)
            body += filler
            off += rva_a - off
        data = img[rva:hi]
        body += data + b"\x00" * (rawsz - pad_front - len(data))
        off += rawsz
        nm = name.encode()[:8].ljust(8, b"\x00")
        sec_hdrs += struct.pack(
            "<8sIIIIIIHHI", nm, vsz, rva_a, rawsz, off - rawsz,
            0, 0, 0, 0, 0x60000020)
    size_of_image = ((max(s[1] for s in sections) + SECALIGN - 1)
                     // SECALIGN * SECALIGN)

    if entry_rva is None:
        entry_rva = sections[0][0]

    opt = struct.pack(
        "<HBBIIIII",
        0x20B,              # Magic PE32+
        14,                 # MajorLinkerVersion
        0,                  # MinorLinkerVersion
        len(body) + hdrsz,  # SizeOfCode
        0,                  # SizeOfInitializedData
        0,                  # SizeOfUninitializedData
        entry_rva,          # AddressOfEntryPoint
        hdrsz,              # BaseOfCode
    )
    opt += struct.pack("<Q", BASE)                 # ImageBase (8 bytes en PE32+)
    opt += struct.pack("<II", SECALIGN, FILEALIGN)  # Section/FileAlignment
    opt += struct.pack("<HHHHHH", 6, 0, 0, 0, 6, 0)  # OS/Image/Subsys versions
    opt += struct.pack("<III", 0, size_of_image, hdrsz)   # Win32ver, SizeOfImage, SizeOfHeaders
    opt += struct.pack("<I", 2)                    # Subsystem = GUI
    opt += struct.pack("<I", 0x100000)             # DllCharacteristics (NX|ASLR|TSAWARE)
    opt += struct.pack("<QQQQ", 0x100000, 0x1000,   # stack reserve/commit
                       0x100000, 0x1000)           # heap  reserve/commit
    opt += struct.pack("<II", 0, 16)               # LoaderFlags, NumberOfRvaAndSizes
    opt += b"\x00" * (16 * 8)                      # data dirs (0..15)
    # la optional header debe acabar exactamente en 0x200
    opt += b"\x00" * (0x200 - 0x98 - len(opt))
    assert len(opt) == 0x200 - 0x98, len(opt)

    dos = bytearray(0x80)
    dos[0:2] = b"MZ"
    struct.pack_into("<I", dos, 0x3C, 0x80)

    nt = b"PE\x00\x00" + struct.pack("<HHIIIHH", 0x8664, nsec, 0, 0, 0, 0x168, 0x22)
    nt += opt
    assert len(nt) + 0x80 == 0x200, len(nt)
    out_data = bytes(dos) + nt + sec_hdrs
    out_data += body
    open(out, "wb").write(out_data)
    print(f"{out}: {len(out_data)} bytes, {nsec} secciones, "
          f"SizeOfImage=0x{size_of_image:x}, entry RVA 0x{entry_rva:x}")


if __name__ == "__main__":
    out = sys.argv[1]
    secs = []
    for a in sys.argv[2:]:
        parts = a.split(":")
        lo, hi = int(parts[0], 16), int(parts[1], 16)
        nm = parts[2] if len(parts) > 2 else f"s{lo:x}"[:8]
        secs.append((lo, hi, nm))
    build(out, secs)