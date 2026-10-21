#!/usr/bin/env python3
"""Rompe los hashes FNV-1a-32 del binario enumerando los exports reales de las
DLL de Windows presentes en el prefix de Wine."""
import os, sys, glob, struct
import pefile

FNV_OFF = 0x811c9dc5
FNV_PRM = 0x01000193


def fnv1a32(s: bytes) -> int:
    h = FNV_OFF
    for c in s:
        h = ((c ^ h) * FNV_PRM) & 0xFFFFFFFF
    return h


sysdir = sys.argv[1] if len(sys.argv) > 1 else \
    "/root/mrgarabato_analysis/run/wineprefix/drive_c/windows/system32"
hashfile = sys.argv[2] if len(sys.argv) > 2 else "hashes.txt"

targets = {}
for line in open(hashfile):
    line = line.strip()
    if line.startswith("0x"):
        targets[int(line, 16)] = None
# ruido tipico (no son hashes de nombres)
NOISE = {0xFFFFFFFF, 0xFFFFFFFE, 0x7FFFFFFF, 0, 1}

found = {}
names = set()
dlls = 0
for path in glob.glob(os.path.join(sysdir, "*.dll")) + \
         glob.glob(os.path.join(sysdir, "*.DLL")) + \
         glob.glob(os.path.join(sysdir, "*.exe")):
    try:
        pe = pefile.PE(path, fast_load=True)
        pe.parse_data_directories(directories=[pefile.DIRECTORY_ENTRY["IMAGE_DIRECTORY_ENTRY_EXPORT"]])
        if not hasattr(pe, "DIRECTORY_ENTRY_EXPORT"):
            continue
        dlls += 1
        for sym in pe.DIRECTORY_ENTRY_EXPORT.symbols:
            if not sym.name:
                continue
            n = sym.name.decode("latin1", "replace")
            names.add(n)
            h = fnv1a32(n.encode("latin1"))
            if h in targets and h not in NOISE:
                found.setdefault(h, set()).add("%s!%s" % (os.path.basename(path), n))
    except Exception:
        continue

print(f"[+] {dlls} DLLs de Windows leidas, {len(names)} nombres de export unicos")
print(f"[+] {len(targets)} hashes objetivo\n")
print("  HASH        RESUELTO")
print("  ----------  ------------------------------------------")
for h in sorted(targets):
    if h in found:
        for v in sorted(found[h]):
            print(f"  0x{h:08x}  {v}")
    else:
        print(f"  0x{h:08x}  (sin coincidir)")

# guardar el mapa de hashes -> todo, por si hace falta mas adelante
with open("fnv_map.txt", "w") as f:
    for h in sorted(found):
        f.write("0x%08x %s\n" % (h, " | ".join(sorted(found[h]))))
print("\n[+] mapa completo -> fnv_map.txt")