#!/usr/bin/env python3
"""
run_loader_full.py -- Ciclo completo:
  1. Lanza el loader en un PTY real
  2. Alimenta las credenciales del owner
  3. Cuando aparece el MessageBox del anti-VM, lo cierra con xdotool
  4. Deja correr y captura toda la salida

Uso: run_loader_full.py <exe>
"""
import os, sys, pty, select, time, threading, subprocess, signal

EXE = sys.argv[1]
CREDS = [b"MrGarabato\n", b"mialuciana12345\n", b"ANALISIS-PTEST\n"]
FAKE = "/tmp/opencode/fakedmi"
MOUNTS = ("for f in %s/*; do b=$(basename $f); "
          "[ -e /sys/class/dmi/id/$b ] && mount --bind $f /sys/class/dmi/id/$b 2>/dev/null; "
          "done; true" % FAKE)
env = dict(os.environ, DISPLAY=":99", WINEDEBUG="-all", TERM="xterm",
           WINEPREFIX="/tmp/opencode/wp_ldr3")

pid, fd = pty.fork()
if pid == 0:
    os.execvp("unshare", ["unshare", "-m", "bash", "-c",
                          MOUNTS + '; exec wine "$@"', "_", EXE])

os.set_blocking(fd, False)
buf = b""
sent = 0
mb_closed = False
t0 = time.time()
log = open("/tmp/loader_full.log", "wb")

def close_msgbox():
    """Cierra el MessageBox del anti-VM en el display :99."""
    for _ in range(12):
        try:
            r = subprocess.run(["xdotool", "search", "--name", "loader.exe"],
                               capture_output=True, text=True, timeout=8,
                               env=dict(os.environ, DISPLAY=":99"))
            wids = [w for w in r.stdout.split() if w.strip()]
            if wids:
                for w in wids[:2]:
                    subprocess.run(["xdotool", "windowactivate", w],
                                   capture_output=True, timeout=8,
                                   env=dict(os.environ, DISPLAY=":99"))
                    time.sleep(0.4)
                    subprocess.run(["xdotool", "key", "--window", w, "Return"],
                                   capture_output=True, timeout=8,
                                   env=dict(os.environ, DISPLAY=":99"))
                return True
        except Exception:
            pass
        time.sleep(2)
    return False

def feeder():
    global sent, mb_closed
    # fase 1: credenciales
    while sent < len(CREDS) and time.time() - t0 < 200:
        time.sleep(1.2)
        try: os.write(fd, CREDS[sent]); sent += 1
        except Exception: pass
        print("[+] credencial %d enviada" % sent, flush=True)
        time.sleep(3)
    # fase 2: esperar al MessageBox y cerrarlo
    print("[*] esperando MessageBox del anti-VM ...", flush=True)
    time.sleep(25)
    ok = close_msgbox()
    print("[+] MessageBox cerrado: %s" % ok, flush=True)
    mb_closed = True

threading.Thread(target=feeder, daemon=True).start()

while time.time() - t0 < 420:
    r, _, _ = select.select([fd], [], [], 1.0)
    if r:
        try: chunk = os.read(fd, 4096)
        except OSError: break
        if not chunk: break
        buf += chunk; log.write(chunk); log.flush()
        for l in chunk.decode("latin1","replace").splitlines():
            if l.strip() and "fixme" not in l and "err:" not in l \
               and "MESA" not in l and "DRI3" not in l:
                print("    | %s" % l.strip()[:130], flush=True)
    try:
        if os.waitpid(pid, os.WNOHANG)[0]:
            print("[i] proceso terminado", flush=True); break
    except ChildProcessError:
        break

try: os.kill(pid, signal.SIGKILL)
except Exception: pass
log.close()
print("[i] fin. log en /tmp/loader_full.log", flush=True)
