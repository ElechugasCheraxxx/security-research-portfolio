#!/usr/bin/env python3
"""c_06_secciones.py -- Localiza la seccion PE que contiene 0x227A0 y 0x22A50."""
import struct, os

CAND = ["/root/mrgarabato_analysis/run/stage3/wine_unpacked.exe",
        "/root/mrgarabato_analysis/run/stage3/stage3_code.exe",
        "/root/mrgarabato_analysis/run/loader_solo_text.exe",
        "/root/mrgarabato_analysis/run/mem_loader.bin"]
for p in CAND:
    if not os.path.exists(p): continue
    d = open(p, "rb").read()
    print("="*72); print(p, len(d), "bytes")
    if d[:2] != b"MZ":
        # busca MZ
        i = d.find(b"MZ")
        print("  no empieza con MZ; primer MZ en 0x%X" % (i if i>=0 else -1))
        continue
    e = struct.unpack_from("<I", d, 0x3C)[0]
    if d[e:e+4] != b"PE\0\0":
        print("  sin firma PE en e_lfanew=0x%X" % e); continue
    coff = e+4
    mach, nsec, tds, psym, nsym, optsz, ch = struct.unpack_from("<HHIIIHH", d, coff)
    opt = coff+20
    magic = struct.unpack_from("<H", d, opt)[0]
    imgbase = struct.unpack_from("<Q", d, opt+24)[0] if magic == 0x20B else struct.unpack_from("<I", d, opt+28)[0]
    print("  machine=0x%04X nsec=%d magic=0x%X ImageBase=0x%X SizeOfImage=0x%X" %
          (mach, nsec, magic, imgbase, struct.unpack_from("<I", d, opt+56 if magic==0x20B else opt+56)[0]))
    secoff = opt+optsz
    secs=[]
    for i in range(nsec):
        o = secoff+i*40
        nm = d[o:o+8].rstrip(b"\0").decode("latin1")
        vsz, va, rsz, rp = struct.unpack_from("<IIII", d, o+8)
        chh = struct.unpack_from("<I", d, o+36)[0]
        secs.append((nm,vsz,va,rsz,rp,chh))
        print(f"    {nm:8s} VSz=0x{vsz:06X} VA=0x{va:06X} RawSz=0x{rsz:06X} RawPtr=0x{rp:06X} Ch=0x{chh:08X}")
    for tag, off in (("BLOB1", 0x227A0), ("BLOB2", 0x22A50)):
        for nm,vsz,va,rsz,rp,chh in secs:
            if va <= off < va+max(vsz,rsz):
                fo = rp + (off-va)
                ok = "OK" if fo < len(d) else "FUERA"
                print(f"    -> {tag} RVA 0x{off:X} en seccion {nm}, RawPtr 0x{fo:X} ({ok})")
