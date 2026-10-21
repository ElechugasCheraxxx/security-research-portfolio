#!/usr/bin/env python3
"""Vuelca la imagen del sample (0x140000000+) del proceso en ejecucion.

A diferencia de dump_mem.py (que cogia el primer proceso con algo mapeado en
ese rango, a menudo services.exe/explorer.exe), este busca specifically el
proceso cuyo /proc/PID/exe o cmdline corresponde al sample.
"""
import os, sys, time, glob, hashlib, subprocess

SAMPLE = "MrGarabato-ByPassEmulator.exe"
IBASE = 0x140000000
ISPAN = 0x10000000


def sample_pids():
    out = []
    for p in glob.glob("/proc/[0-9]*"):
        pid = int(p.rsplit("/", 1)[1])
        try:
            exe = os.readlink(p + "/exe")
        except Exception:
            exe = ""
        if SAMPLE in exe:
            out.append((pid, exe))
            continue
        try:
            cl = open(p + "/cmdline", "rb").read().decode("utf8", "replace")
        except Exception:
            continue
        if SAMPLE in cl and "wineserver" not in cl:
            out.append((pid, cl.replace("\0", " ").strip()))
    return out


def regions(pid):
    regs, maps = [], []
    with open(f"/proc/{pid}/maps") as f:
        for line in f:
            perms = line.split()[1]
            lo, hi = (int(x, 16) for x in line.split()[0].split("-"))
            if hi > IBASE and lo < IBASE + ISPAN:
                regs.append((max(lo, IBASE), min(hi, IBASE + ISPAN), perms))
                maps.append(line.rstrip())
    return regs, maps


def read(pid, regs):
    base = min(r[0] for r in regs); top = max(r[1] for r in regs)
    buf = bytearray(top - base)
    with open(f"/proc/{pid}/mem", "rb", buffering=0) as m:
        for lo, hi, _ in regs:
            pos = lo
            while pos < hi:
                end = min(pos + 0x40000, hi)
                try:
                    m.seek(pos); d = m.read(end - pos)
                except Exception:
                    break
                if not d: break
                buf[pos - base:pos - base + len(d)] = d
                pos = end
    return bytes(buf), base


if __name__ == "__main__":
    out = sys.argv[1] if len(sys.argv) > 1 else "mem_hook.bin"
    secs = float(sys.argv[2]) if len(sys.argv) > 2 else 25.0
    t0 = time.time()
    best, best_key, logs = b"", None, []
    while time.time() - t0 < secs:
        ps = sample_pids()
        if not ps:
            time.sleep(0.02); continue
        for pid, who in ps:
            try:
                regs, maps = regions(pid)
            except Exception:
                continue
            if not regs: continue
            data, base = read(pid, regs)
            # clave: nº de regiones + bytes no nulos
            key = (len(regs), len(data) - data.count(0))
            logs.append(f"t={time.time()-t0:5.2f} pid={pid} regs={len(regs)} "
                        f"span=0x{len(data):x} nz={key[1]} base=0x{base:x}")
            if best_key is None or key > best_key:
                best, best_key = data, key
                open(f"{out}.maps", "w").write("\n".join(maps) + "\n")
        time.sleep(0.03)
    print("\n".join(logs[-10:]))
    if not best:
        print("[!] proceso del sample no encontrado"); sys.exit(1)
    open(out, "wb").write(best)
    print(f"[+] {len(best)} bytes  clave={best_key} -> {out}")
    print(f"[+] sha256={hashlib.sha256(best).hexdigest()}")