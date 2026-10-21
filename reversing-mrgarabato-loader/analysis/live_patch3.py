#!/usr/bin/env python3
"""
live_patch3.py -- Neutraliza el epilogo anti-VM por BUSQUEDA DE PATRON, para
que sirva con cualquier build del empaquetador (los RVAs de live_patch2.py eran
fijos de un solo build).

El protector invoca toda API desde la VM siempre con la misma secuencia:

    48 8B 04 24          mov  rax,[rsp]
    48 83 EC 20          sub  rsp,0x20
    FF D0                call rax            <-- la API
    48 8B 64 24 25       mov  rsp,[rsp+0x25]

El `mov rsp,[rsp+0x25]` posterior restaura la pila desde el frame de la VM,
por lo que anular el `call rax` (FF D0 -> 90 90) NO desequilibra la pila: la VM
se autocura en la instruccion siguiente.

Sobre ese frame se invocan MessageBoxW('Sorry... Virtual Machine'),
ExitProcess(0xDEADC0DE) y las sondas anti-VM. Anulando todas las llamadas,
ninguna se ejecuta.

Se parchea en memoria porque .text tiene SizeOfRawData=0: el packer lo
descomprime en runtime y sobrescribiria cualquier parche en disco.

Uso:  live_patch3.py <exe> <salida.bin>
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

# mov rax,[rsp] ; sub rsp,0x20 ; call rax ; mov rsp,[rsp+0x25]
EPILOG = bytes.fromhex("488b0424" "4883ec20" "ffd0" "488b642425")
CALL_OFF = 9          # desplazamiento del FF D0 dentro del patron
NOP2 = b"\x90\x90"

# .text vive en RVA 0x1000 con tamano ~0x21000 en estos builds
TEXT_LO, TEXT_HI = 0x1000, 0x40000
IMG_SPAN = 0x1000000


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


def read_text(mem):
    mem.seek(BASE + TEXT_LO)
    return mem.read(TEXT_HI - TEXT_LO)


def patch_calls(blob, already):
    """Devuelve (nuevos, n) con los offsets de los call rax del epilogo."""
    found = []
    i = 0
    while True:
        i = blob.find(EPILOG, i)
        if i < 0:
            break
        if i not in already:
            found.append(i)
        i += 1
    return found


def main():
    target = sys.argv[1]
    out = sys.argv[2]

    env = dict(os.environ, DISPLAY="")
    env["WINEDEBUG"] = "-all"
    subprocess.Popen(
        ["unshare", "-m", "bash", "-c", MOUNTS + '; exec wine "$@"', "_", target],
        env=env, stdout=subprocess.DEVNULL,
        stderr=open("live_patch3.relay", "wb"))

    pid = None
    t0 = time.time()
    patched = set()
    dumped = False

    while time.time() - t0 < 90:
        if pid is None:
            pid = find_pid(target)
            if pid:
                print("[+] PID %d" % pid, flush=True)
            continue
        try:
            with open("/proc/%d/mem" % pid, "rb+", buffering=0) as mem:
                blob = read_text(mem)
                if blob.count(b"\x00") == len(blob):
                    continue
                hits = patch_calls(blob, patched)
                if hits:
                    for h in hits:
                        mem.seek(BASE + TEXT_LO + h + CALL_OFF)
                        cur = mem.read(2)
                        if cur != NOP2:
                            mem.seek(BASE + TEXT_LO + h + CALL_OFF)
                            mem.write(NOP2)
                        patched.add(h)
                    print("[+] parcheados %d call rax del epilogo (total %d)"
                          % (len(hits), len(patched)), flush=True)

                if patched and not dumped:
                    time.sleep(0.5)
                    buf = bytearray(IMG_SPAN)
                    with open("/proc/%d/mem" % pid, "rb", buffering=0) as r:
                        for off in range(0, IMG_SPAN, 0x20000):
                            try:
                                r.seek(BASE + off)
                                d = r.read(0x20000)
                                buf[off:off + len(d)] = d
                            except Exception:
                                continue
                    open(out, "wb").write(bytes(buf))
                    nz = IMG_SPAN - bytes(buf).count(b"\x00")
                    print("[+] imagen volcada -> %s  (%d B no nulos)"
                          % (out, nz), flush=True)
                    dumped = True
        except (ProcessLookupError, PermissionError) as e:
            # El proceso muere en milisegundos tras desempaquetar: no es un
            # error, es la ventana. Se sigue buscando al siguiente.
            pid = None
            continue
        except OSError as e:
            print("[!] OSError: %s" % e, flush=True)
            break

    print("\n[*] call rax anulados: %d" % len(patched))
    return 0 if patched else 1


if __name__ == "__main__":
    sys.exit(main())
