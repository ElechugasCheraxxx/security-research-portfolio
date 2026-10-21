#!/usr/bin/env python3
"""xorscan.py (numpy) -- recover strings encrypted with
       p[i] = c[i] ^ ((0x53 + idx + i) & 0xFF)
For every value of the running index `idx` (0..255) we decode a whole region
with numpy and then regex for printable runs.  Fast enough for the 6.2 MB
bytecode blob.
"""
import re, sys
import numpy as np

IMG = sys.argv[1] if len(sys.argv) > 1 else 'mem_bypass.bin'
d = open(IMG, 'rb').read()
BASE = 0x140000000
RX = re.compile(rb'[\x20-\x7e]{5,}')

REGIONS = [('.text', 0x1000, 0x18000),
           ('.rdata', 0x18000, 0x20000),
           ('.data', 0x20000, 0x22000),
           ('.pdata', 0x22000, 0x23000),
           ('.3q- bytecode', 0x81c000, 0xE3C000),
           ('.3q- VM interp', 0xE3C000, 0xF8A8A4)]

words = [b'windows', b'system', b'kernel', b'error', b'file', b'path', b'user',
         b'soft', b'microsoft', b'process', b'thread', b'version', b'driver',
         b'registry', b'\\\\', b'.exe', b'.dll', b'.sys', b'http', b'program',
         b'\\\\??\\\\', b'device', b'\\\\device', b'\\\\??', b'virtual', b'protect',
         b'alloc', b'write', b'read', b'open', b'close', b'create', b'delete',
         b'module', b'library', b'load', b'query', b'handle', b'key', b'value',
         b'current', b'control', b'service', b'install', b'uninstall', b'start',
         b'stop', b'net', b'socket', b'connect', b'send', b'recv', b'package',
         b'global', b'local', b'base', b'image', b'inject', b'map', b'section']

out = []
for name, s, e in REGIONS:
    buf = np.frombuffer(d, dtype=np.uint8, count=e - s, offset=s)
    n = buf.size
    ar = np.arange(n, dtype=np.uint8)
    for idx in range(256):
        key = ((np.uint8(idx) + np.uint8(0x53)) + ar).astype(np.uint8)  # (0x53+idx+i)&0xFF
        dec = np.bitwise_xor(buf, key).tobytes()
        for m in RX.finditer(dec):
            t = m.group()
            tl = t.lower()
            hits = sum(1 for w in words if w in tl)
            if hits == 0:
                continue
            letters = sum(1 for c in t if 65 <= c <= 90 or 97 <= c <= 122)
            if letters / len(t) < 0.55:
                continue
            out.append((hits, s + m.start(), name, idx, t))

out.sort(key=lambda x: (-x[0], x[1]))
with open('deep_out/xorscan_hits.txt', 'w') as f:
    for h, off, name, idx, t in out:
        f.write("%012x %-14s idx=%3d hits=%d  %s\n" % (off, name, idx, h, t.decode('latin1')))
print("recovered %d candidate strings" % len(out))
seen = set()
for h, off, name, idx, t in out:
    k = t.decode('latin1')
    if k in seen:
        continue
    seen.add(k)
    print("%012x %-14s idx=%3d  %s" % (off, name, idx, k))