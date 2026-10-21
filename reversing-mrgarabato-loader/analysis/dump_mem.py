#!/usr/bin/env python3
"""Vuelca rapido la imagen PE de memoria. Sin sleep, buffer ajustado al
tamano realmente mapeado, y captura /proc/PID/maps en cada iteracion."""
import os, sys, time, subprocess, glob, hashlib

winpath = sys.argv[1]
out     = sys.argv[2]
IBASE   = 0x140000000
TARGET_WINPATH = sys.argv[1] if len(sys.argv) > 1 else "sample.exe"
FAKE    = "/tmp/opencode/fakedmi"
MOUNTS  = "for f in %s/*; do b=$(basename $f); [ -e /sys/class/dmi/id/$b ] && mount --bind $f /sys/class/dmi/id/$b 2>/dev/null; done; true" % FAKE

subprocess.Popen(["unshare","-m","bash","-c",MOUNTS+'; exec wine "$@"',"_",winpath],
                 env=dict(os.environ, WINEDEBUG="-all", DISPLAY=""),
                 stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)

def all_pids():
    return [int(p.split("/")[-1]) for p in glob.glob("/proc/[0-9]*")]

def image_regions(pid):
    regs, maps = [], []
    try:
        with open(f"/proc/{pid}/maps") as f:
            for line in f:
                lo, hi = (int(x,16) for x in line.split()[0].split("-"))
                if hi > IBASE and lo < IBASE + 0x10000000:
                    regs.append((max(lo,IBASE), min(hi,IBASE+0x10000000)))
                    maps.append(line.rstrip())
    except Exception:
        pass
    return regs, maps

def scan_for_image():
    """Selecciona el proceso DEL SAMPLE por nombre de ejecutable.

    Wine mapea sus DLL en 0x140000000 en CADA proceso (services.exe,
    explorer.exe, winedbg...), asi que buscar solo por esa direccion devuelve
    el proceso de Wine con PID mas bajo, no el sample. Hay que filtrar."""
    import os
    want = os.path.basename(TARGET_WINPATH).lower()
    fallback = None
    for pid in all_pids():
        regs, maps = image_regions(pid)
        if not regs:
            continue
        try:
            with open("/proc/%d/cmdline" % pid, "rb") as c:
                cmd = c.read().replace(b"\x00", b" ").decode("latin1").lower()
        except Exception:
            continue
        if want in cmd:
            return pid, regs, maps
        if fallback is None:
            fallback = (pid, regs, maps)
    return fallback if fallback else (None, None, None)

def read(pid, regs):
    if not regs: return b""
    base = min(r[0] for r in regs); top = max(r[1] for r in regs)
    buf = bytearray(top - base)
    try:
        with open(f"/proc/{pid}/mem","rb",buffering=0) as m:
            for lo, hi in regs:
                pos = lo
                while pos < hi:
                    end = min(pos + 0x20000, hi)
                    try:
                        m.seek(pos); d = m.read(end-pos)
                        if not d: break
                        buf[pos-base:pos-base+len(d)] = d
                    except Exception: break
                    pos = end
    except Exception:
        pass
    return bytes(buf), base

best, best_key, logs, miss = b"", None, [], 0
t0 = time.time()
while time.time() - t0 < 40:
    pid, regs, maps = scan_for_image()
    if pid:
        miss = 0
        data, base = read(pid, regs)
        nz = len(data) - data.count(0)
        key = (len(regs), nz)
        logs.append(f"t={time.time()-t0:5.2f}s regs={len(regs)} span=0x{len(data):x} no-nulo={nz}")
        if best_key is None or key > best_key:
            best, best_key = data, key
    else:
        miss += 1
        # tolerar el arranque; cortar solo tras many misses seguidos
        if miss > 400 and best_key is not None:
            break
        if miss > 400 and time.time() - t0 > 25:
            break

print("\n".join(logs[-12:]))
if not best:
    print("[!] sin captura"); sys.exit(1)
open(out,"wb").write(best)
print(f"[+] capturado {len(best)} bytes, clave={best_key} -> {out}")
print(f"[+] sha256={hashlib.sha256(best).hexdigest()}")