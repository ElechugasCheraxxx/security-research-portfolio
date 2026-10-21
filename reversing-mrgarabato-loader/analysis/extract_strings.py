#!/usr/bin/env python3
"""Full plaintext string extraction (ASCII + UTF-16LE) per region of mem_bypass.bin."""
import re, sys, json
from collections import Counter

d = open('mem_bypass.bin', 'rb').read()
BASE = 0x140000000
REGIONS = [
    ('.text', 0x1000, 0x18000),
    ('.rdata', 0x18000, 0x20000),
    ('.data', 0x20000, 0x22000),
    ('.pdata', 0x22000, 0x23000),
    ('.7f (CRT/MSVC)', 0x23000, 0x81b000),
    ('.zzc (IAT)', 0x81b000, 0x81c000),
    ('.3q- bytecode', 0x81c000, 0xE3C000),
    ('.3q- VM interp', 0xE3C000, 0xF8A8A4),
    ('.3q- tail', 0xF8A8A4, 0xF8B000),
    ('.rsrc', 0xF8B000, 0xF94000),
]

ASCII_RE = re.compile(rb'[\x20-\x7e]{5,}')
WIDE_RE = re.compile(rb'(?:[\x20-\x7e]\x00){5,}')

out = {}
allhits = []
for name, s, e in REGIONS:
    blob = d[s:e]
    hits = []
    for m in ASCII_RE.finditer(blob):
        hits.append((s + m.start(), 'A', m.group().decode('latin1')))
    for m in WIDE_RE.finditer(blob):
        try:
            hits.append((s + m.start(), 'W', m.group().decode('utf-16le')))
        except Exception:
            pass
    hits.sort()
    out[name] = hits
    allhits += [(a, k, t, name) for a, k, t in hits]
    print("%-18s %6d strings" % (name, len(hits)))

json.dump([{'off': a, 'rva': hex(a), 'va': hex(BASE + a), 'kind': k, 'text': t, 'region': n}
           for a, k, t, n in allhits], open('deep_out/strings_all.json', 'w'), indent=1)

with open('deep_out/strings_all.txt', 'w') as f:
    for a, k, t, n in sorted(allhits):
        f.write("%012x %s %-16s %s\n" % (a, k, n, t))

# interesting filter
KEY = ['dll', '.exe', 'http', 'reg', 'hkey', 'software', 'class', 'panel',
       'garabato', 'bypass', 'player', 'emulator', 'mumu', 'nox', 'bluestack',
       'freefire', 'unity', 'libil2cpp', 'global-metadata', 'frida', 'xign',
       'process', 'thread', 'mutex', 'virtual', 'token', 'inject', 'password',
       'key', 'license', 'user', 'admin', 'cheat', 'aimbot', 'esp', 'wall',
       'mscoree', 'dotnet', 'runtime', 'download']
print("\n=== HIGH-VALUE STRINGS (all regions) ===")
seen = set()
for a, k, t, n in sorted(allhits):
    tl = t.lower()
    if any(x in tl for x in KEY) and t not in seen:
        seen.add(t)
        print("%012x %s %-16s %s" % (a, k, n, t))