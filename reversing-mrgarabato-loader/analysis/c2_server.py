#!/usr/bin/env python3
"""C2 local emulado: responde por endpoint y registra TODO lo que llega.

Sirve para observar el protocolo real del loader sin tocar la infraestructura del
atacante. Todo el trafico sale hacia 127.0.0.1 porque fake_dmi_net.sh monta un
/etc/hosts falso dentro del namespace de montaje.

Rutas servidas:
  GET  /Download/cmd.php?t=...     -> text/plain, una URL (como el C2 real)
  POST /Auth/api/neural_login.php  -> application/json, respuesta de login fabricada
  GET  /c2_local/<fichero>         -> octet-stream, simula la descarga de un payload
  *                                 -> 404

Todo lo Demas se registra igual, para no perder peticiones inesperadas.
"""
import http.server
import ssl
import json
import os
import sys
import time
import base64

HERE = os.path.dirname(os.path.abspath(__file__))
LOG = os.path.join(HERE, "c2_capture.log")
STATE = os.path.join(HERE, "c2_response.txt")
PAYLOADS = os.path.join(HERE, "c2_payloads")

CORS = [("Access-Control-Allow-Origin", "*"),
        ("Access-Control-Allow-Headers", "*"),
        ("Access-Control-Allow-Methods", "*")]

# Valores que el panel realpondria. Se ajustan en c2_response.txt sin tocar codigo.
DEFAULT_LOGIN = {
    "status": "ok",
    "message": "Bienvenido",
    "token": "ANALISISLOCAL0000000000000000000000",
    "user": "analisis",
    "username": "analisis",
    "subscription": "activa",
    "subscription_level": "Profesional",
    "expiry_date": "2030-01-01",
    "last_login": "2026-10-18 00:00:00",
    "created_at": "2026-01-01 00:00:00",
    "hwid": "ANALISIS-HWID",
    "hwid_affected": "false",
    "update_url": "https://panel.mrgarabato.com/c2_local/14ddg0941cvah.exe",
}


def login_response():
    try:
        base = json.load(open(STATE))
    except Exception:
        base = dict(DEFAULT_LOGIN)
    if isinstance(base, dict) and "update_url" in base:
        return json.dumps(base).encode()
    return json.dumps(base).encode()


class Handler(http.server.BaseHTTPRequestHandler):
    protocol_version = "HTTP/1.1"

    # ---------- registro ----------
    def _read_body(self):
        body = b""
        n = int(self.headers.get("Content-Length") or 0)
        if n:
            body = self.rfile.read(n)
        return body

    def _log(self, tag, body=b"", note=""):
        rec = {
            "ts": time.strftime("%Y-%m-%d %H:%M:%S"),
            "tag": tag,
            "method": self.command,
            "path": self.path,
            "version": self.request_version,
            "headers": dict(self.headers.items()),
            "body_len": len(body),
            "body_head": body[:8000].decode("latin1", "replace"),
            "note": note,
        }
        with open(LOG, "a") as f:
            f.write(json.dumps(rec, indent=2, ensure_ascii=False) + "\n")
        print("[%s] %s %s%s  (cuerpo %d B)"
              % (rec["ts"], self.command, self.path,
                 ("  <- " + note) if note else "", len(body)), flush=True)
        return rec

    def _send(self, code, ctype, payload, extra=None):
        self.send_response(code)
        self.send_header("Content-Type", ctype)
        self.send_header("Content-Length", str(len(payload)))
        self.send_header("Server", "nginx")
        for k, v in CORS:
            self.send_header(k, v)
        for k, v in (extra or []):
            self.send_header(k, v)
        self.end_headers()
        if self.command != "HEAD":
            self.wfile.write(payload)

    # ---------- logica de rutas ----------
    def _route(self, body):
        p = self.path.split("?", 1)[0]

        # 1) endpoint de actualizacion -> una URL, como text/plain
        if "cmd.php" in p:
            try:
                url = open(STATE).read().strip()
            except Exception:
                url = "https://panel.mrgarabato.com/Download/Paquete/execute"
            self._send(200, "text/plain; charset=utf-8", url.encode())
            return

        # 2) login -> JSON fabricado
        if "neural_login" in p:
            self._send(200, "application/json", login_response())
            return

        # 2b) heartbeat -> OK
        if "neural_check" in p:
            self._send(200, "application/json",
                       json.dumps({"ok": True, "message": "OK"}).encode())
            return

        # 3) descarga de payload desde el disco local
        if "/c2_local/" in p:
            name = os.path.basename(p.split("/c2_local/", 1)[1])
            fp = os.path.join(PAYLOADS, name)
            if name and os.path.isfile(fp):
                data = open(fp, "rb").read()
                self._send(200, "application/octet-stream", data,
                           [("Content-Disposition",
                             'attachment; filename="%s"' % name)])
                return
            self._send(404, "text/plain", b"not found")
            return

        # 4) cualquier otra cosa: 404 pero registrada
        self._send(404, "text/plain", b"not found")

    def do_GET(self):
        self._log("GET", b"")
        self._route(b"")

    def do_POST(self):
        body = self._read_body()
        self._log("POST", body)
        self._route(body)

    def do_HEAD(self):
        self._log("HEAD")
        self._route(b"")

    def do_OPTIONS(self):
        self._send(200, "text/plain", b"")

    def log_message(self, *a):
        pass


def main():
    port = int(sys.argv[1]) if len(sys.argv) > 1 else 8443
    cert = sys.argv[2] if len(sys.argv) > 2 else "/tmp/opencode/fakedmi/c2.pem"
    key = sys.argv[3] if len(sys.argv) > 3 else "/tmp/opencode/fakedmi/c2.key"
    os.makedirs(PAYLOADS, exist_ok=True)
    srv = http.server.ThreadingHTTPServer(("0.0.0.0", port), Handler)
    ctx = ssl.SSLContext(ssl.PROTOCOL_TLS_SERVER)
    ctx.load_cert_chain(cert, key)
    srv.socket = ctx.wrap_socket(srv.socket, server_side=True)
    open(LOG, "w").close()
    print("[*] C2 local en 0.0.0.0:%d  log -> %s" % (port, LOG), flush=True)
    print("[*] rutas: cmd.php | neural_login.php | /c2_local/<f>", flush=True)
    srv.serve_forever()


if __name__ == "__main__":
    main()