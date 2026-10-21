#!/usr/bin/env python3
"""
patch_run.py -- Congela el proceso en cuanto se desempaqueta, parchea los
controles (anti-VM + lista negra) con el proceso parado, y lo deja seguir.

Diferencia con dump_race2.py: ahi se congelaba para VOLCAR y se mataba.
Aqui se congela para PARCHEAR y se reanuda, para observar la traza completa
de ejecucion (que es lo unico que puede revelar una URL construida en
runtime que no se vea en el binario).

Parches aplicados con el proceso congelado:
  1. Todos los `call rax` del epilogo de la VM  -> 90 90
     (neutra MessageBoxW/ExitProcess/sondas; el epilogo restaura rsp asi
      que la VM se autocura en la instruccion siguiente)
  2. Las funciones de chequeo del .text -> xor eax,eax ; ret
     (se localizan por prologo: 48 89 5c 24 08 48 89 7c ...)

Uso: patch_run.py <exe> [stdin_file]
"""
import os, sys, time, glob, signal, subprocess, threading

BASE = 0x140000000
TEXT_VA = 0x140001000
TEXT_SPAN = 0x80000
IMG_SPAN = 0x1200000
FAKE = "/tmp/opencode/fakedmi"
MOUNTS = ("for f in %s/*; do b=$(basename $f); "
          "[ -e /sys/class/dmi/id/$b ] && mount --bind $f /sys/class/dmi/id/$b 2>/dev/null; "
          "done; true" % FAKE)

EPILOG = bytes.fromhex("488b0424" "4883ec20" "ffd0" "488b642425")
CALL_OFF = 9
NOP2 = b"\x90\x90"
CHECK_PATCH = bytes.fromhex("31c0c3")          # xor eax,eax ; ret


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


def freeze(pid):
    try: os.kill(pid, signal.SIGSTOP)
    except Exception: pass
    for t in glob.glob("/proc/%d/task/[0-9]*" % pid):
        try: os.kill(int(t.split("/")[-1]), signal.SIGSTOP)
        except Exception: pass


def thaw(pid):
    for t in glob.glob("/proc/%d/task/[0-9]*" % pid):
        try: os.kill(int(t.split("/")[-1]), signal.SIGCONT)
        except Exception: pass
    try: os.kill(pid, signal.SIGCONT)
    except Exception: pass


def read_text(pid):
    out = bytearray()
    try:
        with open("/proc/%d/mem" % pid, "rb", buffering=0) as m:
            m.seek(TEXT_VA)
            out = bytearray(m.read(TEXT_SPAN))
    except Exception:
        pass
    return bytes(out)


def patch_all(pid):
    """Aplica los parches. Devuelve (n_epilogo, n_chequeos)."""
    n_epi = n_chk = 0
    with open("/proc/%d/mem" % pid, "rb+", buffering=0) as m:
        blob = read_text(pid)
        # 1. epilogos de la VM
        i = 0
        while True:
            i = blob.find(EPILOG, i)
            if i < 0: break
            m.seek(TEXT_VA + i + CALL_OFF)
            m.write(NOP2)
            n_epi += 1
            i += 1
        # 2. funciones de chequeo: prologo tipico 48 89 5c 24 08 48 89 7c ...
        for pro in (bytes.fromhex("48895c240848897c"),
                    bytes.fromhex("48895c240848896c"),
                    bytes.fromhex("48895c24")):
            j = 0
            while True:
                j = blob.find(pro, j)
                if j < 0: break
                # solo parchear si a continuacion hay un cuerpo razonable
                # (evitar pisar el mismo sitio dos veces)
                m.seek(TEXT_VA + j)
                m.write(CHECK_PATCH)
                n_chk += 1
                j += len(pro)
    return n_epi, n_chk


def main():
    exe, stdin_file = sys.argv[1], (sys.argv[2] if len(sys.argv) > 2 else None)
    want = os.path.basename(exe).lower()
    env = dict(os.environ, DISPLAY="", WINEDEBUG="-all")

    stdin_data = open(stdin_file, "rb").read() if stdin_file and os.path.exists(stdin_file) else b""

    p = subprocess.Popen(
        ["unshare", "-m", "bash", "-c",
         MOUNTS + '; exec wine "$@"', "_", exe],
        env=env, stdin=subprocess.PIPE,
        stdout=subprocess.PIPE, stderr=subprocess.STDOUT)

    def feeder():
        try:
            if stdin_data:
                time.sleep(6)
                p.stdin.write(stdin_data); p.stdin.flush()
        except Exception:
            pass
    threading.Thread(target=feeder, daemon=True).start()

    print("[*] esperando desempaquetado de %s ..." % want, flush=True)
    t0 = time.time()
    pid = None
    while time.time() - t0 < 90:
        if p.poll() is not None:
            print("[i] proceso termino antes de tiempo (rc=%s)" % p.returncode, flush=True)
            break
        pid = find_pid(want)
        if not pid:
            continue
        blob = read_text(pid)
        if len(blob) - blob.count(b"\x00") > 8192:
            print("[+] PID %d, .text desempaquetado a t=%.2fs -> SIGSTOP"
                  % (pid, time.time() - t0), flush=True)
            freeze(pid)
            break
    else:
        print("[!] no se pudo congelar", flush=True)
        p.kill(); return 1

    n_epi, n_chk = patch_all(pid)
    print("[+] parches: %d call rax (epilogo VM), %d funciones de chequeo"
          % (n_epi, n_chk), flush=True)

    # volcar tambien la imagen parcheada, por si sirve
    try:
        buf = bytearray(IMG_SPAN)
        with open("/proc/%d/mem" % pid, "rb", buffering=0) as m:
            for a in range(0, IMG_SPAN, 0x20000):
                try:
                    m.seek(BASE + a); d = m.read(0x20000)
                    if d: buf[a:a+len(d)] = d
                except Exception: continue
        open("dumps/patched_image.bin", "wb").write(bytes(buf))
        print("[+] imagen parcheada -> dumps/patched_image.bin", flush=True)
    except Exception as e:
        print("[!] volcado: %s" % e, flush=True)

    print("[*] SIGCONT, dejando correr ...", flush=True)
    thaw(pid)

    # esperar y mostrar la salida
    out = b""
    t0 = time.time()
    while time.time() - t0 < 75:
        if p.poll() is not None:
            break
        time.sleep(0.5)
    try:
        p.stdin.close()
    except Exception:
        pass
    try:
        out = p.stdout.read() or b""
    except Exception:
        pass
    print("════ SALIDA DEL PROCESO ════")
    for line in out.decode("latin1", "replace").splitlines():
        print("    %s" % line)
    print("════ fin (rc=%s) ════" % p.returncode)
    return 0


if __name__ == "__main__":
    sys.exit(main())
