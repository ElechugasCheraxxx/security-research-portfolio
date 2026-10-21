#!/usr/bin/env python3
"""MITM del panel para observar el protocolo real del loader.

No fabrica respuestas: reenvia al panel real y registra todo. Solo interveniene
en dos puntos, y ambos para REDUCIR riesgo, nunca para obtener el payload:

  1. cmd.php  -> el C2 devuelve una URL que el loader descarga y EJECUTA.
                 Se sustituye por una ruta inerte, de modo que ningun
                 ejecutable remoto llega a ejecutarse.
  2. .exe/.zip -> si el loader intenta descargar un binario, se registra la
                 peticion pero se le responde 403, sin servir el fichero.

Todo lo demas pasa intacto, incluida la autenticacion real.
"""
import http.server
import ssl
import json
import os
import sys
import time
import socket
import urllib.parse
import http.client

HERE = os.path.dirname(os.path.abspath(__file__))
LOG = os.path.join(HERE, "mitm_capture.log")
CERT = "/tmp/opencode/fakedmi/c2.pem"
KEY = "/tmp/opencode/fakedmi/c2.key"

UP_HOST = "panel.mrgarabato.com"
INERT = "mitm://blocked-by-analysis"

BLOCK_EXT = (".exe", ".zip", ".rar", ".7z", ".msi", ".sys", ".dll")


def log(rec):
    with open(LOG, "a") as f:
        f.write(json.dumps(rec, ensure_ascii=False) + "\n")
    extra = rec.get("note", "")
    print("[%s] %s %s  -> %s%s" % (rec["ts"], rec["method"], rec["path"][:90],
                                   rec.get("status", "?"),
                                   ("  [" + extra + "]") if extra else ""), flush=True)


class Handler(http.server.BaseHTTPRequestHandler):
    protocol_version = "HTTP/1.1"

    def _body(self):
        n = int(self.headers.get("Content-Length") or 0)
        return self.rfile.read(n) if n else b""

    def _relay(self, method):
        path = self.path
        body = self._body()
        ts = time.strftime("%H:%M:%S")

        # --- intervencion 1: el C2 que manda ejecutar un binario ---
        if "cmd.php" in path:
            log({"ts": ts, "method": method, "path": path, "status": 200,
                 "note": "C2 BLOQUEADO -> respuesta inerte",
                 "headers": dict(self.headers.items())})
            payload = INERT.encode()
            self._reply(200, "text/plain; charset=utf-8", payload)
            return

        # --- intervencion 2: descargas de binarios ---
        low = path.lower().split("?", 1)[0]
        if low.endswith(BLOCK_EXT):
            log({"ts": ts, "method": method, "path": path, "status": 403,
                 "note": "BINARIO NO SERVIDO (peticion registrada)",
                 "headers": dict(self.headers.items())})
            self._reply(403, "text/plain", b"blocked")
            return

        # --- passthrough ---
        try:
            conn = http.client.HTTPSConnection(UP_HOST, 443, timeout=25,
                                               context=ssl._create_unverified_context())
            hdrs = {k: v for k, v in self.headers.items()
                    if k.lower() not in ("host", "connection", "content-length")}
            hdrs["Host"] = UP_HOST
            hdrs["Connection"] = "close"
            conn.request(method, path, body=body or None, headers=hdrs)
            r = conn.getresponse()
            data = r.read()
            ctype = r.getheader("Content-Type", "application/octet-stream")
            note = ""
            if "neural_login" in path or "neural_check" in path:
                try:
                    j = json.loads(data)
                    note = "respuesta: " + json.dumps(
                        {k: v for k, v in j.items() if k in
                         ("ok", "message", "subscription", "update_url", "token")},
                        ensure_ascii=False)[:220]
                except Exception:
                    pass
            log({"ts": ts, "method": method, "path": path, "status": r.status,
                 "req_headers": dict(self.headers.items()),
                 "req_body": body[:2000].decode("latin1", "replace"),
                 "resp_len": len(data), "note": note})
            extra = []
            for h in ("Content-Disposition", "X-Download-Size"):
                v = r.getheader(h)
                if v:
                    extra.append((h, v))
            self._reply(r.status, ctype, data, extra)
            conn.close()
        except Exception as e:
            if not getattr(self, "_headers_sent", False):
                log({"ts": ts, "method": method, "path": path, "status": 0,
                     "note": "ERROR upstream: %s" % e})
                self._reply(502, "text/plain", b"upstream error")

    def _reply(self, code, ctype, payload, extra=None):
        # Nunca emitir una segunda respuesta sobre una ya enviada: un cliente
        # que se desconecta a mitad provocaba antes un 502 encima del 200 y
        # corrompia la sesion de forma silenciosa.
        if getattr(self, "_headers_sent", False):
            return
        self._headers_sent = True
        try:
            self.send_response(code)
            self.send_header("Content-Type", ctype)
            self.send_header("Content-Length", str(len(payload)))
            self.send_header("Server", "nginx")
            for k, v in (extra or []):
                self.send_header(k, v)
            self.end_headers()
            if self.command != "HEAD":
                self.wfile.write(payload)
        except (BrokenPipeError, ConnectionResetError):
            pass

    def handle_one_request(self):
        self._headers_sent = False
        try:
            super().handle_one_request()
        except (BrokenPipeError, ConnectionResetError):
            self.close_connection = True

    def do_GET(self):
        self._relay("GET")

    def do_POST(self):
        self._relay("POST")

    def do_HEAD(self):
        self._relay("HEAD")

    def log_message(self, *a):
        pass


def main():
    port = int(sys.argv[1]) if len(sys.argv) > 1 else 443
    srv = http.server.ThreadingHTTPServer(("0.0.0.0", port), Handler)
    ctx = ssl.SSLContext(ssl.PROTOCOL_TLS_SERVER)
    ctx.load_cert_chain(CERT, KEY)
    srv.socket = ctx.wrap_socket(srv.socket, server_side=True)
    open(LOG, "w").close()
    print("[*] MITM en :%d  ->  https://%s" % (port, UP_HOST), flush=True)
    print("[*] C2 (cmd.php) y binarios: BLOQUEADOS. Resto: passthrough.", flush=True)
    srv.serve_forever()


if __name__ == "__main__":
    main()