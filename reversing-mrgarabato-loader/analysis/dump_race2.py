#!/usr/bin/env python3
"""
dump_race2.py -- Congelar el proceso cuando el desempaquetado este COMPLETO.

Version 2 de la carrera contra el anti-VM:
  * el PID se busca una sola vez y se cachea (el glob sobre /proc era lo que
    hacia que la deteccion tardase 63 s)
  * se sondean las regiones que el packer rellena en orden:
      .text  (VA 0x001000)  codigo
      .rdata (VA 0x06B000)  cadenas/constantes
      .data  (VA 0x08B000)  3,2 MB de datos  <-- puede contener payloads
      .b:%   (VA 0x39D000)  4 MB, destino de la descompresion
  * se congela cuando .data y .b:% tienen ambos contenido significativo, o
    cuando el total deja de crecer (el packer ya termino)
  * margen de gracia antes de congelar para que termine cualquier copia en curso

Uso: dump_race2.py <exe> <salida.bin>
"""
import os, sys, time, glob, signal, hashlib, subprocess

BASE = 0x140000000
REGIONS = [
    ("text",  0x001000, 0x0006A000),
    ("rdata", 0x06B000, 0x00020000),
    ("data",  0x08B000, 0x0030D000),
    ("bdest", 0x39D000, 0x003D2000),
]
IMG_SPAN = 0xE56000            # SizeOfImage real
FAKE = "/tmp/opencode/fakedmi"
MOUNTS = ("for f in %s/*; do b=$(basename $f); "
          "[ -e /sys/class/dmi/id/$b ] && mount --bind $f /sys/class/dmi/id/$b 2>/dev/null; "
          "done; true" % FAKE)


def find_pid(want):
    best = None
    for p in glob.glob("/proc/[0-9]*"):
        try:
            with open(p + "/maps") as f:
                if not any(int(l.split("-")[0], 16) == BASE for l in f):
                    continue
            with open(p + "/cmdline", "rb") as c:
                cmd = c.read().replace(b"\x00", b" ").decode("latin1").lower()
            if want in cmd:
                pid = int(p.split("/")[-1])
                if best is None or pid > best:
                    best = pid
        except Exception:
            continue
    return best


def nz(pid, va, span):
    """bytes no nulos en [va, va+span)."""
    n = 0
    try:
        with open("/proc/%d/mem" % pid, "rb", buffering=0) as m:
            for a in range(va, va + span, 0x10000):
                try:
                    m.seek(a)
                    d = m.read(min(0x10000, va + span - a))
                    if d:
                        n += len(d) - d.count(b"\x00")
                except Exception:
                    continue
    except Exception:
        return -1
    return n


def read_span(pid, lo, hi):
    buf = bytearray(hi - lo)
    try:
        with open("/proc/%d/mem" % pid, "rb", buffering=0) as m:
            for a in range(lo, hi, 0x20000):
                try:
                    m.seek(a)
                    d = m.read(min(0x20000, hi - a))
                    if d:
                        buf[a - lo:a - lo + len(d)] = d
                except Exception:
                    continue
    except Exception:
        pass
    return bytes(buf)


def freeze(pid):
    try:
        os.kill(pid, signal.SIGSTOP)
    except Exception:
        pass
    try:
        for t in glob.glob("/proc/%d/task/[0-9]*" % pid):
            try:
                os.kill(int(t.split("/")[-1]), signal.SIGSTOP)
            except Exception:
                pass
    except Exception:
        pass


def main():
    target, out = sys.argv[1], sys.argv[2]
    want = os.path.basename(target).lower()
    env = dict(os.environ, DISPLAY="", WINEDEBUG="-all")
    subprocess.Popen(["unshare", "-m", "bash", "-c",
                      MOUNTS + '; exec wine "$@"', "_", target],
                     env=env, stdout=subprocess.DEVNULL,
                     stderr=open("dump_race2.relay", "wb"))

    t0 = time.time()
    pid = None
    prev_total, stable = -1, 0
    while time.time() - t0 < 120:
        if pid is None:
            pid = find_pid(want)
            if pid:
                print("[+] PID %d (t=%.1fs)" % (pid, time.time() - t0), flush=True)
            continue
        stats = {k: nz(pid, va, sp) for k, va, sp in REGIONS}
        if any(v < 0 for v in stats.values()):
            pid = None
            continue
        total = sum(v for v in stats.values() if v > 0)
        print("    t=%5.1f  text=%-7d rdata=%-7d data=%-8d bdest=%-8d total=%d"
              % (time.time() - t0, stats["text"], stats["rdata"],
                 stats["data"], stats["bdest"], total), flush=True)
        ready = stats["text"] > 10000 and stats["data"] > 200000 and stats["bdest"] > 200000
        if total == prev_total and total > 500000:
            stable += 1
        else:
            stable = 0
        prev_total = total
        if ready or stable >= 3:
            print("[+] desempaquetado completo (ready=%s stable=%d) -> congelando"
                  % (ready, stable), flush=True)
            time.sleep(1.5)            # margen para copias en curso
            freeze(pid)
            time.sleep(0.4)
            img = read_span(pid, BASE, BASE + IMG_SPAN)
            open(out, "wb").write(img)
            print("[+] volcado %d B -> %s  sha256=%s"
                  % (len(img), out, hashlib.sha256(img).hexdigest()[:24]), flush=True)
            try:
                os.kill(pid, signal.SIGKILL)
            except Exception:
                pass
            return 0
    print("[!] agotado", flush=True)
    return 1


if __name__ == "__main__":
    sys.exit(main())
