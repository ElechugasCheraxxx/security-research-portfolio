#!/usr/bin/env python3
"""
run_loader_pty.py -- Lanza el loader bajo Wine en un PTY real, con las
credenciales escritas en el terminal, y registra todo lo que imprime.

ReadConsole de Windows exige una consola real: un pipe o un fichero no
sirven. Un pty si.

Uso: run_loader_pty.py <exe>
"""
import os, sys, pty, select, time, threading, subprocess, glob, signal

EXE = sys.argv[1]
CREDS = [
    b"MrGarabato\n",
    b"mialuciana12345\n",
    b"ANALISIS-PTEST\n",
]

FAKE = "/tmp/opencode/fakedmi"
MOUNTS = ("for f in %s/*; do b=$(basename $f); "
          "[ -e /sys/class/dmi/id/$b ] && mount --bind $f /sys/class/dmi/id/$b 2>/dev/null; "
          "done; true" % FAKE)

env = dict(os.environ, DISPLAY=":99", WINEDEBUG="-all",
           TERM="xterm", WINEPREFIX="/tmp/opencode/wp_ldr2")

pid, fd = pty.fork()
if pid == 0:
    os.execvp("unshare", ["unshare", "-m", "bash", "-c",
                          MOUNTS + '; exec wine "$@"', "_", EXE])

os.set_blocking(fd, False)
buf = b""
sent = 0
t0 = time.time()
log = open("/tmp/loader_pty.log", "wb")

# hilo que busca el prompt y va alimentando credenciales
def feeder():
    global sent
    while sent < len(CREDS) and time.time() - t0 < 240:
        time.sleep(1)
        try:
            low = buf[-400:].lower()
        except Exception:
            continue
        # en cuanto haya un prompt o pasen 30 s, envia la siguiente linea
        if (b"user" in low or b"usuario" in low or b"login" in low
                or b":" in low[-20:] or (time.time()-t0) > 30*(sent+1)):
            try:
                os.write(fd, CREDS[sent]); sent += 1
                print("[+] credencial %d enviada" % sent, flush=True)
            except Exception:
                pass

threading.Thread(target=feeder, daemon=True).start()

while time.time() - t0 < 240:
    r, _, _ = select.select([fd], [], [], 1.0)
    if r:
        try:
            chunk = os.read(fd, 4096)
        except OSError:
            break
        if not chunk:
            break
        buf += chunk
        log.write(chunk); log.flush()
        line = chunk.decode("latin1", "replace")
        for l in line.splitlines():
            if l.strip():
                print("    | %s" % l.strip()[:120], flush=True)
    # si el proceso murio, salir
    try:
        if os.waitpid(pid, os.WNOHANG)[0]:
            print("[i] proceso terminado", flush=True)
            break
    except ChildProcessError:
        break

try: os.kill(pid, signal.SIGKILL)
except Exception: pass
log.close()
print("[i] fin. log completo en /tmp/loader_pty.log", flush=True)
