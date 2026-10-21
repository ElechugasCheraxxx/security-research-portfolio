#!/usr/bin/env python3
"""Descifra cadenas ofuscadas del LoaderAdvanced con
   plain[i] = cipher[i] ^ ((0x53 + idx + i) & 0xFF)
   probando los 256 idx (vectorizado con numpy)."""
import sys, string, numpy as np

KEY0 = 0x53
PRINT = set(range(0x20, 0x7f)) | {0x09, 0x0a, 0x0d, 0x00, 0xe1, 0xf3, 0xed, 0xa1, 0xbf, 0xa9}
KWS = ("SOFTWARE","SYSTEM","HARDWARE","Microsoft","Windows","CurrentVersion",
       "Classes","Control","Description","ACPI","Enum","Bios","Version",
       "virtual","vbox","qemu","sandbox","wine","kvm","xen","kernel32","ntdll",
       "user32","advapi","setupapi","x64dbg","wireshark","procmon","ProcessHacker",
       ".exe",".dll",".sys","Driver","\\\\.","SystemDrive","Divert","Emulator",
       "FreeFire","MrGarabato","HKEY","Registry","ProgramFiles","WinDivert",
       "open","create","delete","start","stop","php","http","sc ")

path = sys.argv[1]
LO = int(sys.argv[2], 16); HI = int(sys.argv[3], 16)
MINLEN = int(sys.argv[4]) if len(sys.argv) > 4 else 5
THRESH = int(sys.argv[5]) if len(sys.argv) > 5 else 40
MAXRUN = 96

img = open(path, "rb").read()
buf = np.frombuffer(img[LO:HI], dtype=np.uint8)
N = len(buf)
pos = np.arange(N, dtype=np.int64)
mask = np.zeros(N, dtype=bool)
for c in PRINT:
    mask |= (buf == c)
# precomputa runs maximos una vez sobre mask
runs = []
d = np.diff(mask.astype(np.int8))
starts = list(np.where(d == 1)[0] + 1)
ends = list(np.where(d == -1)[0] + 1)
if mask[0]:
    starts.insert(0, 0)
if mask[-1]:
    ends.append(N)
for s, e in zip(starts, ends):
    if e - s >= MINLEN:
        runs.append((s, e))
print("[+] %d runs imprimibles >= %d" % (len(runs), MINLEN), flush=True)

cand = {}
for idx in range(256):
    key = ((KEY0 + idx + pos) & 0xFF).astype(np.uint8)
    dec = np.bitwise_xor(buf, key)
    for s, e in runs:
        seg = dec[s:min(e, s + MAXRUN)]
        sc = bytes(seg)
        q = 0
        for k in KWS:
            if k.encode() in sc.lower():
                q += 60 + 2 * len(k)
        # penaliza terminacion suelta
        if e - s > MAXRUN:
            q -= 30
        key2 = (idx + s) & 0xFF
        best = cand.get(s)
        if best is None or q > best[0]:
            cand[s] = (q, key2, sc)

rows = [(LO + s, v[1], v[0], v[2]) for s, v in cand.items() if v[0] >= THRESH]
rows.sort(key=lambda t: (-t[2], t[0]))
kept, last = [], -1
for off, idx, q, seg in rows:
    if off + len(seg) <= last:
        continue
    kept.append((off, idx, q, seg))
    last = off + len(seg)

print("[+] %d cadenas recuperadas\n" % len(kept))
print("  %-10s %-6s %-6s %s" % ("RVA", "idx", "score", "cadena"))
for off, idx, q, seg in kept:
    print("  0x%06x   0x%02x   %5d  %s" % (off, idx, q, seg.decode("latin1")))
with open("strings_loader.txt", "w") as f:
    for off, idx, q, seg in kept:
        f.write("0x%06x\tidx=0x%02x\tq=%d\t%s\n" % (off, idx, q, seg.decode("latin1")))
print("\n[+] -> strings_loader.txt")
