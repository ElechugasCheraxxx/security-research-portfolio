#!/usr/bin/env python3
"""
ftprw_test.py -- bateria de pruebas de LECTURA y ESCRITURA contra el servidor
FTP local.

Modelo de permisos vigente:
  * usuario autenticado `black` -> SIN chroot, `local_root=/`, de modo que la
    raiz del FTP es la raiz real del sistema. R/W sobre el arbol del
    laboratorio mediante ACL (`u:black:rwX`).
  * usuario anonimo -> chroot en `/srv/ftp/anon`, solo escribe en `/upload`.

Verifica ademas la integridad (sha256) de los ficheros transferidos.
"""
import hashlib
import os
import shutil
import socket
import sys

HOST = "192.168.64.5"
PORT = 21

# donde trabaja el usuario autenticado
LAB = "/root/mrgarabato_analysis/run"
PASS = 0
FAIL = 0


def check(desc, cond, extra=""):
    global PASS, FAIL
    if cond:
        PASS += 1
        print("  [ OK ] %s %s" % (desc, extra))
    else:
        FAIL += 1
        print("  [FAIL] %s %s" % (desc, extra))


class FTP:
    def __init__(self, host=HOST, port=PORT, timeout=25):
        self.s = socket.create_connection((host, port), timeout=timeout)
        self.buf = b""
        self.banner = self.readline()

    def readline(self):
        while b"\r\n" not in self.buf:
            chunk = self.s.recv(4096)
            if not chunk:
                line, self.buf = self.buf, b""
                return line.decode("latin1", "replace")
            self.buf += chunk
        line, self.buf = self.buf.split(b"\r\n", 1)
        return line.decode("latin1", "replace")

    def cmd(self, c):
        self.s.sendall((c + "\r\n").encode())
        return self.readline()

    def login(self, user, pw):
        r = self.cmd("USER %s" % user)
        if r.startswith("331"):
            r = self.cmd("PASS %s" % pw)
        return r

    def pasv(self):
        r = self.cmd("PASV")
        if not r.startswith("227"):
            return None
        nums = r[r.find("(") + 1:r.find(")")].split(",")
        return (nums[0] + "." + nums[1] + "." + nums[2] + "." + nums[3],
                int(nums[4]) * 256 + int(nums[5]))

    def transfer(self, cmdline, data=None):
        """Ejecuta un comando con transferencia de datos. Devuelve (resp, bytes)."""
        addr = self.pasv()
        if not addr:
            return ("227 error", b"")
        ds = socket.create_connection(addr, timeout=25)
        resp = self.cmd(cmdline)
        if not resp.startswith("150") and not resp.startswith("125"):
            # 5xx: la operacion fue rechazada, no hay datos que leer
            ds.close()
            return (resp, b"")
        payload = b""
        if data is not None:
            ds.sendall(data)
        ds.shutdown(socket.SHUT_WR)
        while True:
            try:
                chunk = ds.recv(65536)
            except socket.timeout:
                break
            if not chunk:
                break
            payload += chunk
        ds.close()
        fin = self.readline()
        return (resp + " / " + fin, payload)

    def listing(self, cmdline="NLST"):
        """LIST/NLST: abre PASV, envia el comando y devuelve la salida."""
        addr = self.pasv()
        if not addr:
            return "", "227 error"
        ds = socket.create_connection(addr, timeout=25)
        resp = self.cmd(cmdline)
        if not resp.startswith("150") and not resp.startswith("125"):
            ds.close()
            return "", resp
        payload = b""
        while True:
            try:
                chunk = ds.recv(65536)
            except socket.timeout:
                break
            if not chunk:
                break
            payload += chunk
        ds.close()
        fin = self.readline()
        return payload.decode("latin1", "replace"), resp + " / " + fin

    def close(self):
        try:
            self.cmd("QUIT")
        except Exception:
            pass
        try:
            self.s.close()
        except Exception:
            pass


def sha(b):
    return hashlib.sha256(b).hexdigest()


def sha_file(path):
    try:
        with open(path, "rb") as f:
            return hashlib.sha256(f.read()).hexdigest()
    except Exception:
        return None


def cleanup():
    """Deja el arbol limpio para que la bateria sea reproducible."""
    for p in (os.path.join(LAB, "prueba_subida.bin"),
              os.path.join(LAB, "renombrado.bin"),
              os.path.join(LAB, "dir_nuevo"),
              "/srv/ftp/anon/upload/anon_subido.bin",
              "/srv/ftp/anon/upload/anon_dir"):
        try:
            if os.path.isdir(p):
                shutil.rmtree(p)
            else:
                os.remove(p)
        except OSError:
            pass


def main():
    blob = os.urandom(200000)
    blob_sha = sha(blob)
    cleanup()

    # ---------------------------------------------------------------
    print("=" * 64)
    print(" USUARIO AUTENTICADO (black) -- raiz = / real, R/W completo")
    print("=" * 64)
    f = FTP()
    r = f.login("black", "1234")
    check("login", r.startswith("230"), "-> %s" % r)
    f.cmd("TYPE I")

    r = f.cmd("PWD")
    check("pwd es la raiz real del sistema",
          r.startswith("257") and '"' in r and r.split('"')[1] == "/",
          "-> %s" % r)

    lst, r = f.listing("NLST")
    roots = [n for n in lst.split() if n in ("etc", "root", "srv", "home")]
    check("listar la raiz (NLST) ve el arbol del sistema",
          r.startswith("150") and len(roots) >= 3,
          "-> %s" % ", ".join(sorted(roots)))

    r = f.cmd("CWD " + LAB)
    check("entrar en el arbol del laboratorio (%s)" % LAB,
          r.startswith("250"), "-> %s" % r)

    resp, got = f.transfer("STOR prueba_subida.bin", blob)
    check("subir fichero (STOR)", resp.startswith("150"), "-> %s" % resp.split(" / ")[-1])
    check("integridad de la subida (sha256 en disco)",
          sha_file(os.path.join(LAB, "prueba_subida.bin")) == blob_sha,
          "sha %s" % blob_sha[:16])

    resp, got = f.transfer("RETR prueba_subida.bin")
    check("bajar fichero (RETR)", resp.startswith("150"), "-> %s" % resp.split(" / ")[-1])
    check("integridad de la descarga", sha(got) == blob_sha,
          "sha %s" % blob_sha[:16])

    r = f.cmd("SIZE prueba_subida.bin")
    check("tamano (SIZE)", r.startswith("213"), "-> %s" % r)

    lst, r = f.listing("NLST")
    check("listar (NLST)", r.startswith("150") and "prueba_subida.bin" in lst,
          "-> %s" % r.split(" / ")[-1])

    r = f.cmd("MKD dir_nuevo")
    check("crear directorio (MKD)", r.startswith("257"), "-> %s" % r)

    r = f.cmd("RNFR prueba_subida.bin")
    ok1 = r.startswith("350")
    r2 = f.cmd("RNTO renombrado.bin")
    check("renombrar (RNFR/RNTO)", ok1 and r2.startswith("250"), "-> %s" % r2)

    r = f.cmd("DELE renombrado.bin")
    check("borrar (DELE)", r.startswith("250"), "-> %s" % r)

    r = f.cmd("RMD dir_nuevo")
    check("borrar directorio (RMD)", r.startswith("250"), "-> %s" % r)

    r = f.cmd("CWD /")
    check("cambiar de directorio", r.startswith("250"), "-> %s" % r)

    # escritura en una ruta absoluta, sin CWD previo
    resp, got = f.transfer("STOR %s/abs_subida.bin" % LAB, blob)
    check("STOR con ruta absoluta", resp.startswith("150"),
          "-> %s" % resp.split(" / ")[-1])
    check("  (fichero en disco)",
          sha_file(os.path.join(LAB, "abs_subida.bin")) == blob_sha)
    r = f.cmd("DELE %s/abs_subida.bin" % LAB)
    check("DELE con ruta absoluta", r.startswith("250"), "-> %s" % r)

    f.close()

    # ---------------------------------------------------------------
    print()
    print("=" * 64)
    print(" ANONIMO -- chroot en /srv/ftp/anon, escritura en /upload")
    print("=" * 64)
    a = FTP()
    r = a.login("anonymous", "")
    check("login anonimo", r.startswith("230"), "-> %s" % r)
    a.cmd("TYPE I")

    resp, got = a.transfer("STOR anon_subido.bin", blob)
    check("subir en la raiz del chroot (debe FALLAR por permisos)",
          not resp.startswith("150"), "-> %s" % resp.split(" / ")[-1])

    r = a.cmd("CWD upload")
    check("entrar en /upload (escribible)", r.startswith("250"), "-> %s" % r)

    resp, got = a.transfer("STOR anon_subido.bin", blob)
    check("subir dentro de /upload", resp.startswith("150"), "-> %s" % resp.split(" / ")[-1])
    check("integridad subida anonima (sha256 en disco)",
          sha_file("/srv/ftp/anon/upload/anon_subido.bin") == blob_sha,
          "sha %s" % blob_sha[:16])

    resp, got = a.transfer("RETR anon_subido.bin")
    check("bajar desde /upload", resp.startswith("150"), "-> %s" % resp.split(" / ")[-1])
    check("integridad descarga anonima", sha(got) == blob_sha, "sha %s" % blob_sha[:16])

    r = a.cmd("MKD anon_dir")
    check("crear directorio en /upload", r.startswith("257"), "-> %s" % r)

    # ---------------------------------------------------------------
    print()
    print("=" * 64)
    print(" AISLAMIENTO DEL ANONIMO (chroot)")
    print("=" * 64)
    r = a.cmd("CWD /")
    check("raiz del chroot accesible", r.startswith("250"), "-> %s" % r)
    r = a.cmd("CWD /etc")
    check("NO puede salir del chroot (/etc)", not r.startswith("250"), "-> %s" % r)
    r = a.cmd("STAT /etc/passwd")
    check("NO puede leer /etc/passwd fuera del chroot",
          "root:" not in r, "-> %s" % r[:60])
    lst, r = a.listing("NLST")
    check("la raiz del chroot anonimo no ve el sistema",
          "etc" not in lst.split() and "root" not in lst.split(),
          "-> %s" % ", ".join(sorted(lst.split())[:8]))
    a.close()

    # ---------------------------------------------------------------
    print()
    print("=" * 64)
    print(" ESTADO EN DISCO (artefactos de la prueba)")
    print("=" * 64)
    for d, names in ((LAB, ("prueba_subida.bin", "renombrado.bin",
                            "dir_nuevo", "abs_subida.bin")),
                     ("/srv/ftp/anon", ()),
                     ("/srv/ftp/anon/upload", ("anon_subido.bin",
                                               "anon_dir"))):
        if not os.path.isdir(d):
            continue
        print("  %s:" % d)
        for n in names:
            p = os.path.join(d, n)
            if os.path.isdir(p):
                print("    dir  %s" % n)
            elif os.path.exists(p):
                print("    %-22s %8d B" % (n, os.path.getsize(p)))
            else:
                print("    %-22s (ausente)" % n)

    print()
    print("=" * 64)
    print(" RESULTADO:  %d pruebas OK  /  %d fallidas" % (PASS, FAIL))
    print("=" * 64)
    return 0 if FAIL == 0 else 1


if __name__ == "__main__":
    sys.exit(main())
