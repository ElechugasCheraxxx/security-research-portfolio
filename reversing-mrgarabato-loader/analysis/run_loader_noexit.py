#!/usr/bin/env python3
"""
run_loader_noexit.py -- Neutraliza ExitProcess en el proceso vivo.

Ciclo:
  1. PTY con credenciales
  2. El anti-VM muestra el MessageBox -> proceso VIVO esperando
  3. Parchear ExitProcess en kernel32 del proceso para que sea `ret`
  4. Cerrar el MessageBox con xdotool
  5. El loader llama a ExitProcess -> no hace nada -> continúa

Uso: run_loader_noexit.py <exe>
"""
import os, sys, pty, select, time, threading, subprocess, signal, struct, re, glob

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
t0 = time.time()
log = open("/tmp/loader_noexit.log", "wb")


def find_loader_pid():
    for p in glob.glob("/proc/[0-9]*"):
        try:
            c = open(p + "/cmdline", "rb").read().replace(b"\0", b" ")
        except Exception:
            continue
        if b"stage_run/loader.exe" in c:
            return int(p.split("/")[-1])
    return None


def get_kernel32_base(pid):
    for line in open("/proc/%d/maps" % pid):
        if "kernel32.dll" in line:
            lo = int(line.split("-")[0], 16)
            return lo, line
    return None, None


def find_export(dllpath, base, name):
    """Localiza la direccion virtual de un export de una PE mapeada."""
    try:
        d = open(dllpath, "rb").read()
    except Exception:
        return None
    e = struct.unpack_from("<I", d, 0x3C)[0]
    if d[e:e+4] != b"PE\0\0":
        return None
    opt = e + 24
    magic = struct.unpack_from("<H", d, opt)[0]
    if magic != 0x20B:
        return None
    ddir = opt + 112          # export dir RVA
    exp_rva, exp_size = struct.unpack_from("<II", d, ddir)
    if not exp_rva:
        return None
    # secciones para convertir RVA->offset
    nsec = struct.unpack_from("<H", d, e + 6)[0]
    so = opt + struct.unpack_from("<H", d, opt + 16)[0]
    secs = []
    for i in range(nsec):
        s = so + i * 40
        nm = d[s:s+8].rstrip(b"\0").decode("latin1")
        vs, va, rs, ptr = struct.unpack_from("<IIII", d, s + 8)
        secs.append((va, vs, ptr, rs))
    def r2o(rva):
        for va, vs, ptr, rs in secs:
            if va <= rva < va + max(vs, rs):
                return ptr + (rva - va)
        return None
    eo = r2o(exp_rva)
    if eo is None:
        return None
    nfun, nnames = struct.unpack_from("<II", d, eo + 4)
    afun = struct.unpack_from("<I", d, eo + 28)[0]
    anam = struct.unpack_from("<I", d, eo + 32)[0]
    for i in range(nnames):
        nrva = struct.unpack_from("<I", d, r2o(anam) + 4 * i)[0]
        no = r2o(nrva)
        end = d.index(b"\0", no)
        if d[no:end] == name.encode():
            ordrva = struct.unpack_from("<I", d, r2o(afun) + 2 * i)[0]
            fun_rva = struct.unpack_from("<I", d, r2o(afun) + 4 * ordrva)[0]
            return base + fun_rva
    return None


def patch_exitprocess(pid):
    """Parchea ExitProcess en kernel32 con `ret` (C3)."""
    base, line = get_kernel32_base(pid)
    if not base:
        print("[!] kernel32 no encontrado en maps", flush=True)
        return False
    # ruta del fichero
    dllpath = None
    for line in open("/proc/%d/maps" % pid):
        if "kernel32.dll" in line and "/" in line:
            dllpath = line.split()[-1]
            break
    if not dllpath or not os.path.exists(dllpath):
        print("[!] ruta de kernel32 no encontrada", flush=True)
        return False
    addr = find_export(dllpath, base, "ExitProcess")
    if not addr:
        print("[!] ExitProcess no encontrado en export table", flush=True)
        return False
    print("[+] ExitProcess @ 0x%x (%s)" % (addr, dllpath), flush=True)
    try:
        with open("/proc/%d/mem" % pid, "rb+", buffering=0) as m:
            m.seek(addr)
            old = m.read(16)
            print("    bytes originales: %s" % old.hex(), flush=True)
            m.seek(addr)
            m.write(b"\xc3")            # ret
            m.seek(addr)
            new = m.read(4)
            print("    parcheado: %s" % new.hex(), flush=True)
        return True
    except Exception as e:
        print("[!] parche: %s" % e, flush=True)
        return False


def close_msgbox():
    for _ in range(15):
        try:
            r = subprocess.run(["xdotool", "search", "--name", "loader.exe"],
                               capture_output=True, text=True, timeout=8,
                               env=dict(os.environ, DISPLAY=":99"))
            wids = [w for w in r.stdout.split() if w.strip()]
            if wids:
                for w in wids[:2]:
                    subprocess.run(["xdotool", "windowactivate", w], capture_output=True,
                                   timeout=8, env=dict(os.environ, DISPLAY=":99"))
                    time.sleep(0.3)
                    subprocess.run(["xdotool", "key", "--window", w, "Return"],
                                   capture_output=True, timeout=8,
                                   env=dict(os.environ, DISPLAY=":99"))
                return True
        except Exception:
            pass
        time.sleep(2)
    return False


def feeder():
    global sent
    while sent < len(CREDS) and time.time() - t0 < 200:
        time.sleep(1.2)
        try: os.write(fd, CREDS[sent]); sent += 1
        except Exception: pass
        print("[+] credencial %d enviada" % sent, flush=True)
        time.sleep(3)
    print("[*] esperando MessageBox (15 s) ...", flush=True)
    time.sleep(15)
    lp = find_loader_pid()
    print("[+] loader pid: %s" % lp, flush=True)
    if lp:
        ok = patch_exitprocess(lp)
        print("[+] ExitProcess neutralizado: %s" % ok, flush=True)
    time.sleep(2)
    ok = close_msgbox()
    print("[+] MessageBox cerrado: %s" % ok, flush=True)


threading.Thread(target=feeder, daemon=True).start()

while time.time() - t0 < 420:
    r, _, _ = select.select([fd], [], [], 1.0)
    if r:
        try: chunk = os.read(fd, 4096)
        except OSError: break
        if not chunk: break
        buf += chunk; log.write(chunk); log.flush()
        for l in chunk.decode("latin1","replace").splitlines():
            s = l.strip()
            if s and "fixme" not in s and "err:" not in s and "MESA" not in s \
               and "DRI3" not in s and s.startswith(("+", "[", "-", ">>", "Enter", "Lice")):
                print("    | %s" % s[:130], flush=True)
    try:
        if os.waitpid(pid, os.WNOHANG)[0]:
            print("[i] proceso terminado", flush=True); break
    except ChildProcessError:
        break

try: os.kill(pid, signal.SIGKILL)
except Exception: pass
log.close()
print("[i] fin. log en /tmp/loader_noexit.log", flush=True)
