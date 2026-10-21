#!/usr/bin/env python3
"""Parcheo en vivo del sample bajo Wine.

El packer comprime el codigo original: en el binario en disco solo el 3,5% de
los bloques de .text aparecen literales, y .text tiene SizeOfRawData=0. Por eso
el parche NO se puede aplicar en el fichero; se aplica en memoria, en el
momento en que el packer termina de desempaquetar y antes de que se ejecuten
las comprobaciones anti-VM.

Estrategia: sondea /proc/PID/mem en la direccion de cada funcion de chequeo
esperando su prologo real; en cuanto aparece, sobreescribe con
`xor eax,eax ; ret` (31 C0 C3) para que devuelva 'no detectado'.
"""
import os, sys, time, glob, subprocess, hashlib

BASE = 0x140000000
TARGET_WINPATH = sys.argv[1] if len(sys.argv) > 1 else "sample.exe"
FAKE = "/tmp/opencode/fakedmi"
MOUNTS = ("for f in %s/*; do b=$(basename $f); "
          "[ -e /sys/class/dmi/id/$b ] && mount --bind $f /sys/class/dmi/id/$b 2>/dev/null; "
          "done; true" % FAKE)

# RVAs de las funciones anti-VM identificadas, con su prologo esperado
TARGETS = {
    # RVA  -> prologo esperado (None = parchar en cuanto tenga contenido)
    0x12290: bytes.fromhex("48895c240848897c"),   # enumera procesos: vmtoolsd/vmware*/VGAuthService
    0x120F0: bytes.fromhex("48895c240848896c"),   # RegOpenKeyA -> HARDWARE\ACPI\DSD
    0x12100: bytes.fromhex("48895c240848896c"),
    0xEE70:  bytes.fromhex("48895c240848896c"),   # GetThreadContext / registros de depuracion
    0xEE80:  bytes.fromhex("4883ec40"),           # idem
    0xDD10:  bytes.fromhex("48895c2408488974"),   # otro hash-user
    0x10E20: bytes.fromhex("48895c24"),           # FNV users
    0x10E36: bytes.fromhex("48895c24"),
    0xF1E0:  bytes.fromhex("48895c24"),           # CreateToolhelp32Snapshot/Process32Next
    0x11020: bytes.fromhex("48895c24"),           # GetCurrentThread/GetThreadContext
    0x120F0: bytes.fromhex("48895c240848896c"),
    0x9804:  bytes.fromhex("48895c24"),
}
# parche: xor eax,eax ; ret  -> devuelve 0 (falso = no detectado)
PATCH = bytes.fromhex("31c0c3")


def find_pid():
    """Selecciona el proceso DEL SAMPLE, no cualquier proceso de Wine.
    Wine mapea sus DLL en 0x140000000 en CADA proceso (services.exe,
    explorer.exe, winedbg...), asi que buscar solo por esa direccion es
    ambiguo. Hay que filtrar por el nombre del ejecutable."""
    import os
    want = os.path.basename(TARGET_WINPATH).lower()
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
                # el sample es el mas reciente si hay varios
                if best is None or pid > best:
                    best = pid
        except Exception:
            continue
    return best


def main():
    target = sys.argv[1] if len(sys.argv) > 1 else r"C:\work\MrGarabato-ByPassEmulator.exe"
    out    = sys.argv[2] if len(sys.argv) > 2 else "mem_patched.bin"

    env = dict(os.environ, DISPLAY="")
    env["WINEDEBUG"] = sys.argv[3] if len(sys.argv) > 3 else "-all"
    subprocess.Popen(["unshare", "-m", "bash", "-c", MOUNTS + '; exec wine "$@"', "_", target],
                     env=env, stdout=subprocess.DEVNULL,
                     stderr=open("live_patch.relay", "wb"))

    pid = None
    t0 = time.time()
    patched = set()
    dumped = False

    while time.time() - t0 < 90:
        if pid is None:
            pid = find_pid()
            if pid:
                print(f"[+] PID {pid}", flush=True)
            time.sleep(0.002)
            continue

        if not os.path.exists(f"/proc/{pid}"):
            print("[i] proceso terminado", flush=True)
            break

        try:
            with open(f"/proc/{pid}/mem", "rb+", buffering=0) as m:
                for rva, sig in TARGETS.items():
                    if rva in patched:
                        continue
                    m.seek(BASE + rva)
                    cur = m.read(16)
                    if not cur or cur == b"\x00" * len(cur):
                        continue
                    # esperar al prologo real (no ceros, no relleno)
                    if cur[:2] == b"\x00\x00":
                        continue
                    if sig and not cur.startswith(sig):
                        continue
                    # condicion cumplida -> parcheamos
                    m.seek(BASE + rva)
                    m.write(PATCH)
                    patched.add(rva)
                    print(f"[+] parcheado RVA 0x{rva:05x}  (antes: {cur[:8].hex()})", flush=True)
        except (ProcessLookupError, PermissionError, OSError) as e:
                print(f"[!] {type(e).__name__}: {e}", flush=True)
                break

        # una vez parcheado todo lo conocido, volcar la imagen resultante
        if patched and not dumped and len(patched) >= 3:
            time.sleep(1.0)
            try:
                buf = bytearray(0x1000000)
                with open(f"/proc/{pid}/mem", "rb+", buffering=0) as m:
                    for off in range(0, 0x1000000, 0x20000):
                        try:
                            m.seek(BASE + off); d = m.read(0x20000)
                            buf[off:off + len(d)] = d
                        except Exception:
                            continue
                open(out, "wb").write(bytes(buf))
                print(f"[+] imagen volcada -> {out}", flush=True)
                dumped = True
            except Exception as e:
                print(f"[!] volcado fallo: {e}", flush=True)

        time.sleep(0.002)

    print(f"\n[*] funciones parcheadas: {len(patched)} -> "
          f"{' '.join(hex(r) for r in sorted(patched))}")
    return 0 if patched else 1


if __name__ == "__main__":
    sys.exit(main())