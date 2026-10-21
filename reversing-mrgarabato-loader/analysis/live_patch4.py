#!/usr/bin/env python3
"""Anula todas las llamadas nativas de deteccion que hace la VM.

La VM (.3q-) invoca TODA API asi:

    mov rax,[rsp+0x00] ; sub rsp,0x20 ; call rax ; mov rsp,[rsp+0x25]

asi que el `call rax` (FF D0) acaba siempre en ret-2. Localizando las
direcciones de retorno en la traza de relay se obtiene el sitio exacto de cada
llamada, sin necesidad de desensamblar codigo desincronizado.

Se anulan las comprobaciones que NO viven en .text (imposibles de parchear
alli) y que la VM ejecuta por su cuenta:

  NtQueryInformationProcess(ProcessDebugPort / DebugObjectHandle)
  NtQuerySystemInformation(SystemKernelDebuggerInformation / SystemModuleInformation)

Dejar la llamada sin ejecutar deja el buffer de salida sin tocar; la VM ve
ceros y da el resultado 'nada sospechoso'.

Ademas anula el epilogo (MessageBoxW / ExitProcess) para que el recorrido
posterior al 'fallo' no termine en un MessageBox ni en la muerte del proceso.
"""
import os
import re
import sys
import time
import glob
import subprocess

BASE = 0x140000000
FAKE = "/tmp/opencode/fakedmi"
MOUNTS = ("for f in %s/*; do b=$(basename $f); "
          "[ -e /sys/class/dmi/id/$b ] && mount --bind $f /sys/class/dmi/id/$b 2>/dev/null; "
          "done; true" % FAKE)

TRACE = "live_patch3_jmp.relay"

DETECT = {
    "NtQueryInformationProcess": "anti-depuracion (DebugPort / DebugObjectHandle)",
    "NtQuerySystemInformation": "anti-depuracion + enumeracion de modulos",
}

EPILOGUE = {
    0x0ECBE3F: "ExitProcess",
    0x0E6C375: "MessageBoxW",
}

TEXT_FUNCS = {
    0x12290: "procesos: vmtoolsd/vmware*/VGAuthService",
    0x120F0: "registro HARDWARE\\ACPI\\DSD",
    0x12100: "registro ACPI (2)",
    0x0EE70: "registros de depuracion",
    0x0EE80: "registros de depuracion (2)",
    0x0DD10: "hash-user adicional",
    0x0F1E0: "CreateToolhelp32Snapshot/Process32Next",
    0x10E20: "hash-user adicional (2)",
    0x11020: "GetThreadContext",
}

CALLPAT = re.compile(rb'Call\s+(\S+?)\((.*?)\)\s+ret=([0-9a-f]+)')


def sites_from_trace(trace):
    """Devuelve {rva_call: descripcion} para cada llamada de deteccion de la VM."""
    out = {}
    seen = set()
    for line in open(trace, "rb"):
        m = CALLPAT.search(line)
        if not m:
            continue
        api = m.group(1).decode("latin1").split(".")[-1]
        if api not in DETECT:
            continue
        ret = int(m.group(3), 16)
        if not (BASE <= ret < BASE + 0x1000000):
            continue                      # la hizo un modulo de Wine, no el binario
        rva = ret - BASE - 2                # el `call rax` (FF D0) acaba en ret-2
        if rva in seen:
            continue
        seen.add(rva)
        arg = m.group(2).decode("latin1")[:46]
        out[rva] = "%s(%s)" % (api, arg)
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
    out = sys.argv[2] if len(sys.argv) > 2 else "mem_p4.bin"
    debug = sys.argv[3] if len(sys.argv) > 3 else "-all"

    ref = open("mem_bypass.bin", "rb").read()
    sites = sites_from_trace(TRACE)
    print("=== sitios de deteccion nativos de la VM localizados desde la traza ===")
    jobs = {}
    for rva, desc in sites.items():
        b = ref[rva:rva + 2]
        ok = b == b"\xff\xd0"
        print("  0x%07x  %-12s %-46s %s" % (rva, b.hex(), desc, "call rax OK" if ok else "*** NO es call rax ***"))
        if ok:
            jobs[rva] = (b"\xff\xd0", b"\x90\x90", "VM  deteccion nativa: " + desc)
    for rva, d in EPILOGUE.items():
        jobs[rva] = (b"\xff\xd0", b"\x90\x90", "VM  epilogo: " + d)
    for rva, d in TEXT_FUNCS.items():
        jobs[rva] = (None, bytes.fromhex("31c0c3"), ".text " + d)
    print("\nparches a aplicar: %d\n" % len(jobs))

    env = dict(os.environ, DISPLAY="")
    env["WINEDEBUG"] = debug
    subprocess.Popen(["unshare", "-m", "bash", "-c", MOUNTS + '; exec wine "$@"', "_", target],
                     env=env, stdout=subprocess.DEVNULL, stderr=open("live_patch4.relay", "wb"))

    pid, t0, done, dumped = None, time.time(), set(), False
    while time.time() - t0 < 75:
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
                for rva in jobs:
                    if rva in done:
                        continue
                    sig, payload, desc = jobs[rva]
                    m.seek(BASE + rva)
                    cur = m.read(len(payload) + 2)
                    if not cur or len(cur) < len(payload) or cur[:2] == b"\x00\x00":
                        continue
                    if sig and not cur.startswith(sig):
                        continue
                    m.seek(BASE + rva)
                    m.write(payload)
                    done.add(rva)
                    print("[+] 0x%07x  %s" % (rva, desc), flush=True)
        except (ProcessLookupError, PermissionError, OSError) as e:
            print("[!] %s: %s" % (type(e).__name__, e), flush=True)
            break

        if len(done) >= len(sites) and sites and not dumped:
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

    print("\n[*] parches %d/%d" % (len(done), len(jobs)))
    for rva in sorted(jobs):
        print("    %s 0x%07x  %s" % ("OK " if rva in done else "-- ", rva, jobs[rva][2]))
    return 0 if done else 1


if __name__ == "__main__":
    sys.exit(main())