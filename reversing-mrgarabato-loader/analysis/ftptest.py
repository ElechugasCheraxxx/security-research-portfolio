#!/usr/bin/env python3
"""
ftptest.py -- cliente FTP minimo y explicito.

Devuelve codigos de respuesta reales, sin ambiguedad de lftp.
Uso: ftptest.py <host> <user> <pass> [port]
"""
import socket, sys


class FTP:
    def __init__(self, host, port=21, timeout=20):
        self.s = socket.create_connection((host, port), timeout=timeout)
        self.buf = b""
        self.banner = self.readline()

    def readline(self):
        while b"\r\n" not in self.buf:
            chunk = self.s.recv(4096)
            if not chunk:
                line = self.buf.decode("latin1", "replace")
                self.buf = b""
                return line
            self.buf += chunk
        line, self.buf = self.buf.split(b"\r\n", 1)
        return line.decode("latin1", "replace")

    def cmd(self, c):
        self.s.sendall((c + "\r\n").encode())
        return self.readline()

    def close(self):
        try:
            self.cmd("QUIT")
        except Exception:
            pass
        self.s.close()


def main():
    host = sys.argv[1]
    user = sys.argv[2]
    pw = sys.argv[3]
    port = int(sys.argv[4]) if len(sys.argv) > 4 else 21

    f = FTP(host, port)
    print("  <- %s" % f.banner)

    r = f.cmd("USER %s" % user)
    print("  -> USER %s" % user)
    print("  <- %s" % r)
    if r.startswith("331"):
        r = f.cmd("PASS %s" % pw)
        print("  -> PASS ***")
        print("  <- %s" % r)

    if r.startswith("230"):
        print("  <- %s" % f.cmd("PWD"))
        print("  <- %s" % f.cmd("TYPE I"))
        print("  RESULTADO: LOGIN OK")
        rc = 0
    else:
        print("  RESULTADO: LOGIN FALLIDO")
        rc = 1

    f.close()
    return rc


if __name__ == "__main__":
    sys.exit(main())
