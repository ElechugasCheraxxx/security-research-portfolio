#!/usr/bin/env python3
"""Experimento decisivo: neutraliza las detecciones INLINE de VM.

CPUID y RDTSC no generan ninguna llamada a la API, asi que son invisibles en
la traza de relay y ningun parche de .text las alcanza. Ambas miden lo mismo:
si hay un hipervisor debajo (bit 31 de ECX en CPUID) y cuanto tarda el codigo
en ejecutarse (RDTSC).

En un QEMU ambos las delatan. Se sustituyen por instrucciones inocuas de la
MISMA LONGITUD, para no desplazar nada:

    0F A2  CPUID  ->  31 C0   xor eax,eax    (hoja 0: sin hipervisor)
    0F 31  RDTSC  ->  31 C0   xor eax,eax    (delta de tiempo cero)

Importante: NO se toca el epilogo (MessageBoxW / ExitProcess). Si el dialogo
'no puede ejecutarse en una maquina virtual' desaparece, es prueba de que la
deteccion era inline. Si sigue apareciendo, queda descartada.
"""
import os
import sys
import time
import glob
import subprocess

BASE = 0x140000000
FAKE = "/tmp/opencode/fakedmi"
MOUNTS = ("for f in %s/*; do b=$(basename $f); "
          "[ -e /sys/class/dmi/id/$b ] && mount --bind $f /sys/class/dmi/id/$b 2>/dev/null; "
          "done; true" % FAKE)

ZONES = ((0x1000, 0x18000, ".text"),
         (0xE3C000, 0xF8A8A4, ".3q-INTERPRETE"))

REPL = {b"\x0f\xa2": b"\x31\xc0",   # CPUID -> xor eax,eax
        b"\x0f\x31": b"\x31\xc0"}   # RDTSC -> xor eax,eax


def sites(ref="mem_bypass.bin"):
    d = open(ref, "rb").read()
    out = []
    for lo, hi, name in ZONES:
        for pat, pay in REPL.items():
            i = d.find(pat, lo, hi)
            while i >= 0:
                out.append((i, pat, pay, name))
                i = d.find(pat, i + 1, hi)
    return out


def find_pid(target):
    want = os.path.basename(target).lower()
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


def main():
    target = sys.argv[1] if len(sys.argv) > 1 else r"C:\work\MrGarabato-ByPassEmulator.exe"
    debug = "+relay"

    # imagen de referencia: la que corresponde al binario que se ejecuta
    ref = sys.argv[4] if len(sys.argv) > 4 else "mem_bypass.bin"
    which = sys.argv[5] if len(sys.argv) > 5 else "both"   # cpuid | rdtsc | both
    if which in ("cpuid", "both"):
        REPL.pop(b"\x0f\x31", None) if which == "cpuid" else None
    if which == "rdtsc":
        REPL.pop(b"\x0f\xa2", None)
    todo = sites(ref)
    print("[i] referencia: %s   modo: %s" % (ref, which))
    from collections import Counter
    print("=== sitios CPUID/RDTSC a neutralizar ===")
    for (lo, hi, nm) in ZONES:
        c = Counter(pat.hex() for rva, pat, pay, z in todo if z == nm)
        print("  %-16s %s" % (nm, dict(c)))
    print("  total: %d\n" % len(todo))

    env = dict(os.environ, DISPLAY="")
    env["WINEDEBUG"] = debug
    # Lanzar a traves del wrapper de red: DMI falso + /etc/hosts que manda
    # el panel del C2 a 127.0.0.1, para que la peticion quede capturada
    # en esta maquina en vez de salir a Internet.
    launcher = sys.argv[3] if len(sys.argv) > 3 else "./fake_dmi_net.sh"
    subprocess.Popen(["unshare", "-m", launcher, "wine", target],
                     env=env, stdout=open("sample_stdout.txt", "wb"),
                     stderr=open("live_patch5.relay", "wb"))

    pid, t0, done = None, time.time(), set()
    while time.time() - t0 < 60:
        if pid is None:
            pid = find_pid(target)
            if pid:
                print("[+] PID %d" % pid, flush=True)
            time.sleep(0.002)
            continue
        if not os.path.exists("/proc/%d" % pid):
            print("[i] proceso terminado", flush=True)
            break
        try:
            with open("/proc/%d/mem" % pid, "rb+", buffering=0) as m:
                for rva, pat, pay, nm in todo:
                    if rva in done:
                        continue
                    m.seek(BASE + rva)
                    cur = m.read(2)
                    if cur == pat:
                        m.write(pay)
                        done.add(rva)
                    elif cur not in (b"\x00\x00",):
                        done.add(rva)      # ya alterado / no es el esperado
        except (ProcessLookupError, PermissionError, OSError) as e:
            print("[!] %s: %s" % (type(e).__name__, e), flush=True)
            break
        if len(done) == len(todo):
            print("[+] los %d sitios estan neutros" % len(todo), flush=True)
            break
        time.sleep(0.002)

    print("\n[*] neutralizados %d/%d" % (len(done), len(todo)))
    return 0


if __name__ == "__main__":
    sys.exit(main())