#!/usr/bin/env python3
"""Parche en vivo del epilogo anti-VM, por dentro de la VM.

La VM (.3q-) invoca toda API con la misma secuencia:

    mov rax,[rsp+0x00] ; sub rsp,0x20 ; call rax ; mov rsp,[rsp+0x25]

El `mov rsp,[rsp+0x25]` posterior restaura la pila desde el frame de la VM,
por lo que anular el `call rax` (FF D0 -> 90 90) NO desequilibra la pila: la
VM se autocura en la siguiente instruccion.

Ademas el condicional de decision es `0f85 <rel32>` (jnz). Cambiar el primer
byte a `e9` lo convierte en `jmp` con EXACTAMENTE el mismo desplazamiento
(e9 <rel32>), asi que basta un byte para forzar la rama.

Se aplica en memoria porque .text tiene SizeOfRawData=0: el packer lo
descomprime desde .3q- en runtime y sobrescribiria cualquier parche en disco.
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

# --- funciones de chequeo en .text: devolver 0 = "no detectado" --------------
NOP_EAX_RET = bytes.fromhex("31c0c3")
TEXT_FUNCS = {
    0x12290: "enumera procesos (vmtoolsd/vmware*/VGAuthService)",
    0x120F0: "RegOpenKeyA -> HARDWARE\\ACPI\\DSD",
    0x12100: "RegOpenKeyA -> HARDWARE\\ACPI\\DSD (2)",
    0x0EE70: "registros de depuracion (GetThreadContext)",
    0x0EE80: "registros de depuracion (2)",
    0x0DD10: "hash-user adicional",
    0x0F1E0: "CreateToolhelp32Snapshot/Process32Next",
    0x10E20: "hash-user adicional (2)",
    0x11020: "GetCurrentThread/GetThreadContext",
}

# --- puntos del epilogo dentro de la VM ------------------------------------
# NOPear el `call rax` (FF D0) que invoca cada API del epilogo.
VM_CALLS = {
    0x0ECBE3F: ("FF D0", "ExitProcess(0xDEADC0DE)  <-- si no lo anulo, el proceso muere"),
    0x0E6C375: ("FF D0", "MessageBoxW('Sorry... Virtual Machine')"),
    0x08578D9: ("FF D0", "LoadLibraryA('user32.dll')"),
}

# --- condicional de decision: 0F85 -> E9  (jnz -> jmp, mismo destino) -------
FORCE_BRANCH = {
    0x0E4D451: ("0f", "e9", "condicional de decision de la VM (jnz -> jmp)"),
}


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
    out = sys.argv[2] if len(sys.argv) > 2 else "mem_patched2.bin"
    debug = sys.argv[3] if len(sys.argv) > 3 else "-all"

    env = dict(os.environ, DISPLAY="")
    env["WINEDEBUG"] = debug
    subprocess.Popen(["unshare", "-m", "bash", "-c", MOUNTS + '; exec wine "$@"', "_", target],
                     env=env, stdout=subprocess.DEVNULL,
                     stderr=open("live_patch2.relay", "wb"))

    # RVA -> (bytes esperados, bytes a escribir, descripcion)
    jobs = {}
    for rva, desc in TEXT_FUNCS.items():
        jobs[rva] = (None, NOP_EAX_RET, ".text  " + desc)
    for rva, (sig, desc) in VM_CALLS.items():
        jobs[rva] = (bytes.fromhex(sig), b"\x90\x90", "VM     " + desc)
    for rva, (old, new, desc) in FORCE_BRANCH.items():
        jobs[rva] = (bytes.fromhex(old + "85"), bytes.fromhex(new + "85"), "RAMA   " + desc)

    pid = None
    t0 = time.time()
    done = set()
    dumped = False

    while time.time() - t0 < 90:
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
            # "rb+": escribir en /proc/PID/mem exige modo lectura+escritura.
            # Con "rb" m.write lanza io.UnsupportedOperation (subclase de OSError).
            with open("/proc/%d/mem" % pid, "rb+", buffering=0) as m:
                for rva in jobs:
                    if rva in done:
                        continue
                    want_sig, payload, desc = jobs[rva]
                    m.seek(BASE + rva)
                    cur = m.read(len(payload) + 2)
                    if not cur or len(cur) < len(payload):
                        continue
                    if cur[:2] == b"\x00\x00" or cur == b"\xff" * len(cur):
                        continue                      # aun no desempaquetado
                    if want_sig and not cur.startswith(want_sig):
                        continue
                    m.seek(BASE + rva)
                    m.write(payload)
                    done.add(rva)
                    print("[+] 0x%07x  %s" % (rva, desc), flush=True)
        except (ProcessLookupError, PermissionError, OSError) as e:
            print("[!] %s: %s" % (type(e).__name__, e), flush=True)
            break

        if len(done) >= len(jobs) // 2 and not dumped:
            time.sleep(0.8)
            try:
                buf = bytearray(0x1000000)
                with open("/proc/%d/mem" % pid, "rb", buffering=0) as m:
                    for off in range(0, 0x1000000, 0x20000):
                        try:
                            m.seek(BASE + off)
                            d = m.read(0x20000)
                            buf[off:off + len(d)] = d
                        except Exception:
                            continue
                open(out, "wb").write(bytes(buf))
                print("[+] imagen volcada -> %s" % out, flush=True)
                dumped = True
            except Exception as e:
                print("[!] volcado fallo: %s" % e, flush=True)
        time.sleep(0.002)

    print("\n[*] parches aplicados: %d/%d" % (len(done), len(jobs)))
    for rva in sorted(jobs):
        print("    %s  0x%07x  %s" % ("OK " if rva in done else "-- ", rva, jobs[rva][2]))
    return 0 if done else 1


if __name__ == "__main__":
    sys.exit(main())