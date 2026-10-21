#!/usr/bin/env python3
"""
dump_race.py -- Gana la carrera contra el anti-VM.

El packer descomprime el codigo original en .text (raw=0 en disco) y a
continuacion el anti-VM hace sus comprobaciones (procesos, registro,
GetThreadContext) antes de ExitProcess(0xDEADC0DE).

Esas comprobaciones cuestan tiempo. En el instante en que .text deja de estar
a cero se envia SIGSTOP: el proceso queda congelado con el codigo ya
desempaquetado y ANTES de que las sondas concluyan. Entonces se vuelca la
imagen completa sin prisa.

Uso: dump_race.py <exe> <salida.bin>
"""
import os, sys, time, glob, signal, hashlib, subprocess

BASE = 0x140000000
TEXT_VA = 0x140001000
TEXT_SPAN = 0x80000          # .text de estos builds: 130-450 KB
IMG_SPAN = 0x1200000         # 18 MB: cubre SizeOfImage con margen
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


def main():
    target, out = sys.argv[1], sys.argv[2]
    want = os.path.basename(target).lower()

    env = dict(os.environ, DISPLAY="", WINEDEBUG="-all")
    subprocess.Popen(["unshare", "-m", "bash", "-c",
                      MOUNTS + '; exec wine "$@"', "_", target],
                     env=env, stdout=subprocess.DEVNULL,
                     stderr=open("dump_race.relay", "wb"))

    print("[*] buscando .text no vacio en %s ..." % want, flush=True)
    t0 = time.time()
    stopped = False
    while time.time() - t0 < 90:
        pid = find_pid(want)
        if not pid:
            continue
        blob = read_span(pid, TEXT_VA, TEXT_VA + TEXT_SPAN)
        nz = len(blob) - blob.count(b"\x00")
        if nz > 4096:                      # ya hay codigo desempaquetado
            print("[+] PID %d: .text con %d B no nulos a t=%.3fs -> SIGSTOP"
                  % (pid, nz, time.time() - t0), flush=True)
            try:
                os.kill(pid, signal.SIGSTOP)
            except Exception:
                pass
            # congelar tambien los hilos hermanos
            try:
                for t in glob.glob("/proc/%d/task/[0-9]*" % pid):
                    try:
                        os.kill(int(t.split("/")[-1]), signal.SIGSTOP)
                    except Exception:
                        pass
            except Exception:
                pass
            stopped = True
            time.sleep(0.3)
            img = read_span(pid, BASE, BASE + IMG_SPAN)
            open(out, "wb").write(img)
            print("[+] volcado %d B -> %s  sha256=%s"
                  % (len(img), out, hashlib.sha256(img).hexdigest()[:24]), flush=True)
            try:
                os.kill(pid, signal.SIGKILL)
            except Exception:
                pass
            break
    if not stopped:
        print("[!] no se pudo congelar a tiempo", flush=True)
        return 1
    return 0


if __name__ == "__main__":
    sys.exit(main())
