#!/usr/bin/env python3
"""Sesion autenticada del panel seller MrGarabato.

Guarda la cookie PHPSESSID en panel_cookie.txt y permite descargar paginas
parciales del panel para inspeccion.

Uso:
    panel_session.py login                     -> autentica y guarda cookie
    panel_session.py get <tab> [app]           -> vuelca la parcial en stdout
    panel_session.py api                       -> vuelca tab=api (API del seller)
    panel_session.py raw <url-path> [method]   -> peticion cruda con la cookie
"""
import json
import os
import re
import sys

import requests

PANEL = "https://panel.mrgarabato.com"
SELLER = "MrGarabato"
PASSWORD = "mialuciana12345"
COOKIE_FILE = os.path.join(os.path.dirname(os.path.abspath(__file__)),
                           "panel_cookie.txt")

UA = ("Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 "
      "(KHTML, like Gecko) Chrome/124.0 Safari/537.36")


def session():
    s = requests.Session()
    s.headers.update({"User-Agent": UA,
                      "Accept": "text/html,application/xhtml+xml,*/*"})
    return s


def load_cookie(s):
    if os.path.exists(COOKIE_FILE):
        for line in open(COOKIE_FILE):
            line = line.strip()
            if not line or "\t" not in line:
                continue
            name, value = line.split("\t", 1)
            s.cookies.set(name, value, domain="panel.mrgarabato.com",
                          path="/")
    return s


def save_cookie(s):
    with open(COOKIE_FILE, "w") as fh:
        for c in s.cookies:
            fh.write("%s\t%s\n" % (c.name, c.value))
    os.chmod(COOKIE_FILE, 0o600)


def login():
    s = session()
    r = s.get(PANEL + "/login.php", timeout=45)
    token = ""
    m = re.search(r'name=["\']csrf_token["\'][^>]*value=["\']([^"\']+)',
                  r.text)
    if m:
        token = m.group(1)
    print("csrf_token extraido: %r (len=%d)" % (token, len(token)))

    r = s.post(PANEL + "/login.php",
               data={"csrf_token": token, "username": SELLER,
                     "password": PASSWORD},
               allow_redirects=False, timeout=45)
    print("POST /login.php -> %s %s" % (r.status_code,
                                        r.headers.get("Location", "")))
    if r.status_code not in (301, 302, 303) or "/dashboard" not in \
            r.headers.get("Location", ""):
        print("login fallido")
        return 1
    save_cookie(s)
    print("cookie guardada en %s" % COOKIE_FILE)
    return 0


def partial(s, tab, app=None):
    url = PANEL + "/Auth/dashboard.php?tab=%s&partial=1" % tab
    if app:
        url += "&app=%s" % app
    headers = {"X-Panel-Partial": "1", "X-Requested-With": "XMLHttpRequest",
               "Accept": "text/html, */*; q=0.01"}
    r = s.get(url, headers=headers, timeout=45)
    return r.text


def main():
    cmd = sys.argv[1] if len(sys.argv) > 1 else "login"
    if cmd == "login":
        return login()

    s = load_cookie(session())
    if cmd == "get":
        tab = sys.argv[2] if len(sys.argv) > 2 else "users"
        app = sys.argv[3] if len(sys.argv) > 3 else None
        sys.stdout.write(partial(s, tab, app))
        return 0
    if cmd == "api":
        sys.stdout.write(partial(s, "api"))
        return 0
    if cmd == "raw":
        path = sys.argv[2]
        method = sys.argv[3].upper() if len(sys.argv) > 3 else "GET"
        data = json.loads(sys.argv[4]) if len(sys.argv) > 4 else None
        url = path if path.startswith("http") else PANEL + path
        headers = {"X-Panel-Partial": "1", "X-Requested-With": "XMLHttpRequest",
                   "Accept": "application/json, text/html, */*"}
        r = s.request(method, url, json=data, data=data if method == "GET"
                      else None, headers=headers, timeout=45)
        print("HTTP %s" % r.status_code)
        sys.stdout.write(r.text)
        return 0
    print(__doc__)
    return 1


if __name__ == "__main__":
    sys.exit(main())
