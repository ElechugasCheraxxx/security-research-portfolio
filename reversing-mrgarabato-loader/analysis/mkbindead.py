#!/usr/bin/env python3
"""Build reduced PEs for bindead analysis from unpacked_bypass.exe."""
import struct, sys, os, pefile

SRC = 'unpacked_bypass.exe'
SECALIGN = 0x1000


def build(out, keep, entry=None, extra_dir=None):
    """keep: dict secname -> max_raw_bytes_or_None"""
    pe = pefile.PE(SRC)
    data = open(SRC, 'rb').read()
    new_sections = []
    for sec in pe.sections:
        nm = sec.Name.rstrip(b'\x00').decode('latin1')
        if nm not in keep:
            continue
        raw = sec.get_data()
        maxr = keep[nm]
        if maxr is not None:
            raw = raw[:maxr]
        new_sections.append((nm, raw, sec.Characteristics))
    hdr = bytearray(data[:0x1000])
    shoff = pe.sections[0].get_file_offset()
    nsec = len(new_sections)
    out_off = 0x1000
    shdrs = bytearray()
    va = 0x1000
    for nm, raw, chars in new_sections:
        raw = raw + b'\x00' * ((-len(raw)) % SECALIGN)
        vs = len(raw)
        sh = bytearray(40)
        sh[0:len(nm)] = nm.encode('latin1')
        struct.pack_into('<IIII', sh, 8, vs, va, len(raw), out_off)
        struct.pack_into('<I', sh, 36, chars)
        shdrs += sh
        va += (vs + 0xFFF) & ~0xFFF
        out_off += len(raw)
        out_off = (out_off + 0xFFF) & ~0xFFF
    hdr[shoff:shoff + 40 * nsec] = shdrs
    struct.pack_into('<H', hdr, pe.FILE_HEADER.get_file_offset() + 2, nsec)
    struct.pack_into('<I', hdr, pe.OPTIONAL_HEADER.get_file_offset() + 56, va)
    e = entry if entry is not None else pe.OPTIONAL_HEADER.AddressOfEntryPoint
    struct.pack_into('<I', hdr, pe.OPTIONAL_HEADER.get_file_offset() + 16, e)
    ddoff = pe.OPTIONAL_HEADER.get_file_offset() + 112
    for i in range(16):
        struct.pack_into('<II', hdr, ddoff + i * 8, 0, 0)
    if extra_dir:
        for i, (v_, s_) in extra_dir.items():
            struct.pack_into('<II', hdr, ddoff + i * 8, v_, s_)
    parts = [bytes(hdr)]
    o = 0x1000
    for _, r, _ in new_sections:
        parts.append(b'\x00' * (o - (len(hdr) + sum(len(x) for x in parts[1:]))))
        parts.append(r)
        o += len(r)
        o = (o + 0xFFF) & ~0xFFF
    blob = b''.join(parts)
    open(out, 'wb').write(blob)
    print("%s: %d bytes, %d sections, image=0x%x, entry=0x%x" % (out, len(blob), nsec, va, e))
    for nm, _, _ in new_sections:
        print("   ", nm)


os.makedirs('bindead_out', exist_ok=True)
build('bindead_out/be_app.exe', {'.text': None, '.rdata': None, '.data': None, '.pdata': None})
build('bindead_out/be_crt.exe', {'.7 f': 0x200000})


# D) VM interpreter only: slice .3q- tail (RVA 0xE3C000 .. 0xF8A8A4) rebased to 0x1000
def build_vm(out, start_rva, length, entry_rva):
    pe = pefile.PE(SRC)
    data = open(SRC, 'rb').read()
    off = start_rva  # raw == rva in this file
    raw = data[off:off + length]
    raw = raw + b'\x00' * ((-len(raw)) % SECALIGN)
    hdr = bytearray(data[:0x1000])
    shoff = pe.sections[0].get_file_offset()
    nm = '.vmix'
    sh = bytearray(40)
    sh[0:len(nm)] = nm.encode('latin1')
    struct.pack_into('<IIII', sh, 8, len(raw), 0x1000, len(raw), 0x1000)
    struct.pack_into('<I', sh, 36, 0x60000020)
    hdr[shoff:shoff + 40] = sh
    struct.pack_into('<H', hdr, pe.FILE_HEADER.get_file_offset() + 2, 1)
    struct.pack_into('<I', hdr, pe.OPTIONAL_HEADER.get_file_offset() + 56,
                     0x1000 + ((len(raw) + 0xFFF) & ~0xFFF))
    struct.pack_into('<I', hdr, pe.OPTIONAL_HEADER.get_file_offset() + 16,
                     entry_rva - start_rva + 0x1000)
    ddoff = pe.OPTIONAL_HEADER.get_file_offset() + 112
    for i in range(16):
        struct.pack_into('<II', hdr, ddoff + i * 8, 0, 0)
    blob = bytes(hdr) + raw
    open(out, 'wb').write(blob)
    print("%s: %d bytes, vm rva 0x%x-0x%x -> new 0x1000, entry new rva 0x%x (orig 0x%x)" % (
        out, len(blob), start_rva, start_rva + length,
        entry_rva - start_rva + 0x1000, entry_rva))


build_vm('bindead_out/be_vm.exe', 0xE3C000, 0xF8A8A4 - 0xE3C000, 0xE49F04)
build_vm('bindead_out/be_vm2.exe', 0xE3C000, 0xF8A8A4 - 0xE3C000, 0xEBFD82)