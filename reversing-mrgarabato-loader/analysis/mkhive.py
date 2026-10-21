#!/usr/bin/env python3
"""Genera hives de registro Windows minimos pero validos (formato REGF).

Qiling exige <rootfs>/Windows/registry/{SOFTWARE,SYSTEM,NTUSER.DAT} y los carga
con python-registry, que espera una REGF real. En vez de huntar hives por el
sistema, se construyen aqui: un solo hbin de 4096 B con la clave raiz.
"""
import struct, os, time

HBIN_SIZE = 0x1000


def _cell(size, payload=b"", is_alloc=True):
    """Construye una celda REGF. Las celdas asignadas llevan tamano negativo."""
    n = len(payload)
    total = 4 + n
    total = (total + 3) & ~3          # alinear a 4
    raw = struct.pack("<i", -total if is_alloc else total) + payload
    return raw + b"\x00" * (total - len(raw))


def make_hive(root_name="ROOT"):
    # --- datos variables: nombre de la clave raiz en UTF-16LE ---
    nm = root_name.encode("utf-16-le") + b"\x00\x00"
    NK_HDR = 0x4C                       # inicio del nombre en el registro nk
    nk = bytearray(NK_HDR + len(nm))
    nk[0:2] = b"nk"                              # firma
    struct.pack_into("<H", nk, 0x02, 0x002C)      # flags: root + KnownHives...
    struct.pack_into("<Q", nk, 0x04, 0)          # timestamp
    struct.pack_into("<I", nk, 0x0C, 0)          # access bits
    struct.pack_into("<I", nk, 0x10, 0xFFFFFFFF) # parent key: -1
    struct.pack_into("<I", nk, 0x14, 0)          # subkeys estables
    struct.pack_into("<I", nk, 0x18, 0)          # subkeys volatiles
    struct.pack_into("<I", nk, 0x1C, 0xFFFFFFFF) # subkey list: -1
    struct.pack_into("<I", nk, 0x20, 0xFFFFFFFF) # volatile subkey list: -1
    struct.pack_into("<I", nk, 0x24, 0)          # numero de valores
    struct.pack_into("<I", nk, 0x28, 0xFFFFFFFF) # lista de valores: -1
    struct.pack_into("<I", nk, 0x2C, 0xFFFFFFFF) # sk record: -1
    struct.pack_into("<I", nk, 0x30, 0)          # class name offset
    struct.pack_into("<H", nk, 0x44, len(root_name))  # key name length
    struct.pack_into("<H", nk, 0x48, len(nm))    # name length (con NUL)
    struct.pack_into("<H", nk, 0x4A, 0)          # class name length
    nk[NK_HDR:NK_HDR + len(nm)] = nm

    nk_cell = bytes(_cell(len(nk), bytes(nk)))
    nk_cell_off = 0x24              # dentro del hbin (tras su cabecera de 0x20)

    # --- base block ---
    base = bytearray(0x1000)
    base[0:4] = b"regf"
    struct.pack_into("<I", base, 4, 1)    # primary seq
    struct.pack_into("<I", base, 8, 1)    # secondary seq
    ft = int((time.time() + 11644473600) * 10_000_000)   # FILETIME (epoch 1601)
    struct.pack_into("<Q", base, 12, ft)  # modification time
    struct.pack_into("<I", base, 20, 1)   # major version
    struct.pack_into("<I", base, 24, 3)   # minor version
    struct.pack_into("<I", base, 28, 0)   # file type: primary
    struct.pack_into("<I", base, 32, 1)   # file format
    # Offsets que lee python-registry: root cell en 0x24, hbins size en 0x28
    struct.pack_into("<I", base, 0x24, nk_cell_off)
    struct.pack_into("<I", base, 0x28, HBIN_SIZE)
    struct.pack_into("<I", base, 0x2C, 1)  # clustering factor

    # --- hbin ---
    hbin = bytearray(HBIN_SIZE)
    hbin[0:4] = b"hbin"
    struct.pack_into("<I", hbin, 4, 0)          # offset of first bin
    struct.pack_into("<I", hbin, 8, 1)          # number of bins
    struct.pack_into("<I", hbin, 12, HBIN_SIZE) # size of this bin

    # escribir la celda nk en su offset
    hbin[nk_cell_off:nk_cell_off + len(nk_cell)] = nk_cell

    out = bytes(base) + bytes(hbin)
    return out


def main(rootdir):
    reg = os.path.join(rootdir, "Windows", "registry")
    os.makedirs(reg, exist_ok=True)
    HIVES = ("SECURITY", "SAM", "SOFTWARE", "SYSTEM", "HARDWARE", "NTUSER.DAT",
             "DEFAULT", "COMPONENTS")
    for name in HIVES:
        p = os.path.join(reg, name)
        data = make_hive("ROOT")
        with open(p, "wb") as f:
            f.write(data)
        print("  %-14s %d B" % (name, len(data)))


if __name__ == "__main__":
    import sys
    main(sys.argv[1] if len(sys.argv) > 1 else "/tmp/opencode/qlrootfs/x86_64")