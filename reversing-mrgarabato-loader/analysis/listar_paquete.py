#!/usr/bin/env python3
"""Indice del paquete de 1.6 GB del panel SIN descargarlo entero.

Fichero: https://panel.mrgarabato.com/Download/FreeFire/Requirements%20ByPass.rar
  RAR5 (52 61 72 21 1a 07 01 00), 1.598.804.135 bytes, 'Accept-Ranges: bytes'.

En RAR5 NO hay directorio central: las cabeceras van EN LINEA, intercaladas con
los datos.  Cada bloque es:

    +0   CRC32 de la cabecera            (4 bytes)
    +4   Header size                    (vint)
         Header type                    (vint)
         Header flags                   (vint)
         [Extra area size]              (vint)   si flags & 0x0001
         [Data size]                    (vint)   si flags & 0x0002
         ... campos propios del tipo ...
         [extra area]
    +    datos                           (Data size bytes)

BUG CORREGIDO (v2): el campo 'Header size' se cuenta DESDE EL CAMPO 'Header
type', NO desde el propio campo vint.  Por tanto el siguiente bloque NO esta
en pos+4+hdrsize sino en:

    pos + 4 + len(vint_hdrsize) + hdrsize   (+ data_size)

Comprobado byte a byte sobre el fichero real:
    bloque MAIN en 0x08, hdrsize=16 (1 byte)  ->  siguiente bloque en 0x1d
    (pos+4+hdrsize = 0x1c daria htype=61, invalido; 0x1d da htype=2 y una
     cabecera FILE que cierra EXACTAMENTE en su hsize, con CRC32 correcto).

Ademas se valida CADA cabecera con su CRC32, lo que permite (a) detectar
desalineaciones y (b) re-sincronizar de forma fiable tras un fallo.

Modos de uso:
    python3 listar_paquete.py headers   # recorre la cadena de cabeceras
    python3 listar_paquete.py scan      # barrido por regex (respaldo robusta)
"""
from __future__ import annotations

import argparse
import json
import os
import re
import socket
import sys
import time
import zlib

# --------------------------------------------------------------------------
# Red: en este entorno IPv6 no sale; urllib3/requests se come ~30 s por
# peticion intentando AAAA.  Forzamos A-only antes de importar requests.
# --------------------------------------------------------------------------
_orig_gai = socket.getaddrinfo


def _gai_ipv4(host, port, *a, **k):
    try:
        res = _orig_gai(host, port, *a, **k)
    except Exception:
        res = []
    out = [r for r in res if r[0] != socket.AF_INET6]
    return out or res


socket.getaddrinfo = _gai_ipv4

import requests  # noqa: E402  (import tardio, a proposito)

URL = "https://panel.mrgarabato.com/Download/FreeFire/Requirements%20ByPass.rar"
SIZE = 1598804135          # tamaño total declarado en Content-Range
OUTDIR = os.path.join(os.path.dirname(os.path.abspath(__file__)), "c2_descargas")

HEAD_MAIN, HEAD_FILE, HEAD_SERVICE, HEAD_CRYPT, HEAD_ENDARC = 1, 2, 3, 4, 5
HTYPE_NAME = {1: "MAIN", 2: "FILE", 3: "SERVICE", 4: "CRYPT", 5: "ENDARC"}

# flags de cabecera RAR5
HFL_EXTRA = 0x0001
HFL_DATA = 0x0002
HFL_SKIPUNKNOWN = 0x0004
HFL_SPLITBEFORE = 0x0008
HFL_SPLITAFTER = 0x0010
HFL_CHILD = 0x0020
HFL_INHERITED = 0x0040

# flags de fichero RAR5
FHL_DIRECTORY = 0x0001
FHL_MTIME = 0x0002
FHL_CRC32 = 0x0004
FHL_UNPSIZE_UNKNOWN = 0x0008


# --------------------------------------------------------------------------
# Transporte HTTP por rangos
# --------------------------------------------------------------------------
class RangeReader:
    """Lee tramos del fichero por peticiones Range, con cache de ventana y ritmo."""

    def __init__(self, url=URL, delay=0.12, timeout=30, retries=5):
        self.url = url
        self.delay = delay
        self.timeout = timeout
        self.retries = retries
        self.sess = requests.Session()
        self.sess.headers["User-Agent"] = "Mozilla/5.0 (Windows NT 10.0; Win64; x64)"
        self.sess.headers["Accept"] = "*/*"
        self.reqs = 0
        self.bytes = 0
        self.fallos = 0
        self._win = b""
        self._win_a = 0
        self._win_b = -1
        self._t = 0.0

    def _raw(self, pos, n):
        last = None
        for attempt in range(self.retries):
            try:
                r = self.sess.get(
                    self.url,
                    headers={"Range": "bytes=%d-%d" % (pos, pos + n - 1),
                             "Accept-Encoding": "identity"},
                    timeout=self.timeout,
                )
                if r.status_code == 206:
                    data = r.content
                    self.reqs += 1
                    self.bytes += len(data)
                    return data
                last = "HTTP %d" % r.status_code
            except Exception as e:            # noqa: BLE001
                last = repr(e)
            time.sleep(1.5 * (attempt + 1))
        raise IOError("fallo leyendo %d+%d: %s" % (pos, n, last))

    def read(self, pos, n):
        """n bytes desde pos, reutilizando la ultima ventana si cabe entera."""
        n = max(0, min(n, SIZE - pos))
        if n == 0:
            return b""
        if self._win_a <= pos and pos + n <= self._win_b:
            o = pos - self._win_a
            return self._win[o:o + n]
        # ritmo responsable
        dt = time.time() - self._t
        if dt < self.delay:
            time.sleep(self.delay - dt)
        self._t = time.time()
        data = self._raw(pos, n)
        self._win, self._win_a, self._win_b = data, pos, pos + len(data)
        return data


# --------------------------------------------------------------------------
# VINT
# --------------------------------------------------------------------------
def read_vint(buf, p):
    """Devuelve (valor, pos_siguiente, bytes_consumidos).  Lanza si se agota."""
    v = 0
    shift = 0
    n = 0
    while True:
        if p >= len(buf):
            raise EOFError("vint truncado")
        c = buf[p]
        p += 1
        n += 1
        v |= (c & 0x7F) << shift
        shift += 7
        if not (c & 0x80):
            return v, p, n
        if n >= 10:
            raise EOFError("vint demasiado largo")


def parse_common(buf, i):
    """Lee hdrsize/type/flags/[extra]/[data] desde el indice i de buf."""
    hsize, i, vn = read_vint(buf, i)
    if hsize <= 0 or hsize > (1 << 22):
        raise ValueError("hsize fuera de rango: %d" % hsize)
    htype, i, _ = read_vint(buf, i)
    if htype not in HTYPE_NAME:
        raise ValueError("htype invalido: %d" % htype)
    hflags, i, _ = read_vint(buf, i)
    extra = data = 0
    if hflags & HFL_EXTRA:
        extra, i, _ = read_vint(buf, i)
    if hflags & HFL_DATA:
        data, i, _ = read_vint(buf, i)
    return {"hdrsize": hsize, "vintlen": vn, "htype": htype, "hflags": hflags,
            "extra": extra, "data": data, "body": i}


def decode_name(raw: bytes) -> str:
    try:
        s = raw.decode("utf-8")
    except UnicodeDecodeError:
        return ""
    if any(ord(c) < 0x20 for c in s):
        return ""
    return s


def parse_header(buf, off, base=0, size=SIZE, strict_crc=True):
    """Parsea la cabecera RAR5 situada en el offset ABSOLUTO de fichero `off`.

    buf: ventana descargada, cuyo primer byte es el offset de fichero `base`.
    Devuelve dict, o None si no hay una cabecera valida ahi (CRC included).
    """
    i = off - base
    if i < 0 or i + 8 > len(buf):
        return None
    try:
        h = parse_common(buf, i + 4)
    except (EOFError, ValueError):
        return None
    hsize, vn, htype = h["hdrsize"], h["vintlen"], h["htype"]
    rel_end = i + 4 + vn + hsize          # fin de cabecera, relativo a buf
    abs_end = base + rel_end              # ... y absoluto
    h["hdr_end"] = abs_end
    h["next"] = abs_end + h["data"]
    h["pos"] = off
    if abs_end > size or h["next"] > size:
        return None
    # El CRC32 de la cabecera cubre `hsize` bytes desde el campo hdrsize.
    if strict_crc and rel_end <= len(buf):
        calc = zlib.crc32(buf[i + 4:rel_end]) & 0xFFFFFFFF
        if calc != int.from_bytes(buf[i:i + 4], "little"):
            return None
    h["crc_ok"] = True
    p = h["body"]
    h["name"] = ""
    h["unp"] = None
    h["attr"] = None
    h["cmpr"] = None
    h["dict_size"] = None
    h["mtime"] = None
    h["fflags"] = None
    h["solid"] = None
    h["method"] = None
    h["fields_end"] = None
    try:
        if htype in (HEAD_FILE, HEAD_SERVICE):
            fflags, p, _ = read_vint(buf, p)
            h["fflags"] = fflags
            if not (fflags & FHL_UNPSIZE_UNKNOWN):
                h["unp"], p, _ = read_vint(buf, p)
            h["attr"], p, _ = read_vint(buf, p)
            if fflags & FHL_MTIME:
                h["mtime"] = int.from_bytes(buf[p:p + 4], "little")
                p += 4
            if fflags & FHL_CRC32:
                h["datacrc"] = int.from_bytes(buf[p:p + 4], "little")
                p += 4
            # FILE: siempre hay 'compression info'.  SERVICE: solo si SHD_EXTSVC.
            variants = [True] if htype == HEAD_FILE else [True, False]
            for with_cmpr in variants:
                q = p
                try:
                    cmpr = hos = nl = None
                    if with_cmpr:
                        cmpr, q, _ = read_vint(buf, q)
                    hos, q, _ = read_vint(buf, q)
                    nl, q, _ = read_vint(buf, q)
                except (EOFError, ValueError):
                    continue
                if nl is None or nl > (1 << 16) or q + nl > rel_end:
                    continue
                nm = decode_name(buf[q:q + nl])
                if not nm:
                    continue
                h["cmpr"], h["hostos"], h["name"] = cmpr, hos, nm
                h["fields_end"] = base + q + nl
                break
            if h["cmpr"] is not None:
                h["solid"] = bool(h["cmpr"] & 0x40)
                h["method"] = (h["cmpr"] >> 7) & 7
                h["dict_size"] = (h["cmpr"] >> 10) & 0x0F
        elif htype == HEAD_MAIN:
            aflags, p, _ = read_vint(buf, p)
            h["aflags"] = aflags
            if aflags & 0x0002:
                h["volnum"], p, _ = read_vint(buf, p)
            h["fields_end"] = base + p
        elif htype == HEAD_CRYPT:
            p = min(p + 2 + 1 + 16 + 16, rel_end)
            h["fields_end"] = base + p
    except (EOFError, ValueError, IndexError):
        h["fields_end"] = None
    return h


# --------------------------------------------------------------------------
# Recorrido de la cadena de cabeceras
# --------------------------------------------------------------------------
def walk(rd: RangeReader, verbose=True, max_blocks=200000):
    """Recorre la cadena de cabeceras de principio a fin.

    Cada cabecera se valida con su CRC32, asi que un parseo erroneo se detecta
    al instante.  Si aun asi se pierde la alineacion, se re-sincroniza buscando
    la siguiente posicion con CRC valido dentro de una ventana de 64 KB.
    """
    entries = []
    pos = 8
    resyncs = []
    while pos < SIZE and len(entries) < max_blocks:
        buf = rd.read(pos, 4096)
        if len(buf) < 16:
            break
        h = parse_header(buf, pos, base=pos)
        if h is None:
            # ¿cabecera mas grande que el tramo leido? -> reler con el rango exacto
            need = 0
            try:
                hs, _, vn = read_vint(buf, 4)
                if 0 < hs <= (1 << 22):
                    need = 4 + vn + hs + 8
            except (EOFError, ValueError):
                pass
            if need > len(buf):
                buf = rd.read(pos, min(need, SIZE - pos))
                h = parse_header(buf, pos, base=pos)
        if h is None:
            # desalineacion: re-sincronizar por CRC32 dentro de una ventana
            win = rd.read(pos, min(1 << 16, SIZE - pos))
            newpos = None
            for cand in range(pos + 1, pos + len(win) - 16):
                if parse_header(win, cand, base=pos):
                    newpos = cand
                    break
            if newpos is None:
                if verbose:
                    print("  [DESALINEACION IRRECUPERABLE en 0x%012x]" % pos)
                resyncs.append((pos, None))
                break
            if verbose:
                print("  [resync 0x%012x -> 0x%012x (+%d)]" % (pos, newpos, newpos - pos))
            resyncs.append((pos, newpos))
            pos = newpos
            continue

        ent = {
            "pos": h["pos"], "htype": h["htype"], "name": h.get("name", ""),
            "unp": h.get("unp"), "data": h["data"], "attr": h.get("attr"),
            "hdrsize": h["hdrsize"], "extra": h["extra"],
            "fflags": h.get("fflags"), "mtime": h.get("mtime"),
            "method": h.get("method"), "solid": h.get("solid"),
            "dict_size": h.get("dict_size"), "hostos": h.get("hostos"),
            "next": h["next"],
            "dir": bool((h.get("fflags") or 0) & FHL_DIRECTORY),
        }
        entries.append(ent)
        if verbose:
            print("  0x%012x  %-7s %s" % (pos, HTYPE_NAME[h["htype"]],
                                          ent["name"] or "-"), flush=True)
        if h["htype"] == HEAD_ENDARC:
            if verbose:
                print("  [ENDARC en 0x%012x]" % pos)
            break
        if h["next"] <= pos:
            break
        pos = h["next"]
    return entries, resyncs


# --------------------------------------------------------------------------
# Barrido por regex (descubrimiento de nombres, independiente del parseo)
# --------------------------------------------------------------------------
NAME_RE = re.compile(
    rb"[\x20-\x7e]{4,300}?\.(?:exe|dll|sys|ini|bat|cmd|txt|json|cfg|dat|xml|"
    rb"inf|cat|manifest|vbs|ps1|msi|drv|ocx|cpl|scr|com|bin|reg|log)",
    re.IGNORECASE)

LOOKFOR = ("14ddg0941cvah", "34dbbmddg71c")

# Extensiones que delatan un nombre de fichero.  Se buscan sobre una copia
# en minusculas del bloque y luego se camina hacia atras para recuperar el
# nombre completo: mucho mas rapido (y sin backtracking) que un
# `[\x20-\x7e]{4,300}?\.(ext)` sobre los 8 MB enteros.
EXTS = (b"exe|dll|sys|ini|bat|cmd|txt|json|cfg|dat|xml|inf|cif|msi|apk|apks|"
        b"xapk|dex|so|png|mp4|manifest|drv|ocx|cpl|scr|com|bin|reg|log|zip|"
        b"jar|db|lua|py|vbs|ps1|7z|cab|cat|node|snk|pdb")
EXT_RE = re.compile(rb"\.(?:" + EXTS + rb")(?![a-z0-9])")

# Tokens interestinges para el analisis del loader (busqueda literal, sin
# depender de la cadena de cabeceras).
TOKEN_RE = re.compile(
    rb"14ddg0941cvah|34dbbmddg71c|14ddg0941|34dbbmddg71c|"
    rb"windivert|iqvw64e|midriver|hd-player|hdplayer|memu|memu64|"
    rb"runpe|ldrclean|injector|bstcleaner",
    re.IGNORECASE)


def _back_name(low: bytes, ext_start: int, maxlen=300, minlen=4):
    """Camina hacia atras desde el inicio de la extension y devuelve el nombre."""
    i = ext_start - 1
    lim = max(-1, ext_start - maxlen)
    while i > lim and 0x20 <= low[i] <= 0x7E:
        i -= 1
    i += 1
    if ext_start - i < minlen:
        return None
    return i


def scan_overlap(rd: RangeReader, block=8 << 20, overlap=4096, sleep=0.35,
                 verbose=True, start=0, jsonl=None):
    """Barrido con solapamiento real: se leen `block` bytes y se avanza solo
    block-overlap, de modo que un nombre partido en la frontera aparece completo
    en la lectura siguiente.  No hace falta alinear la cadena de cabeceras.

    Devuelve (hits_nombre, hits_token, n_bloques)."""
    hits = {}
    toks = {}
    pos = start
    nblocks = 0
    gaps = []
    fh = open(jsonl, "a") if jsonl else None
    while pos < SIZE:
        end = min(pos + block, SIZE)
        try:
            buf = rd.read(pos, end - pos)
        except IOError as e:
            # tramo no leido: se anota el hueco y se sigue (se informa como
            # limitacion, no se inventa contenido)
            gaps.append((pos, end, str(e)))
            rd._win_b = -1
            if verbose:
                print("  [HUECO 0x%012x-0x%012x: %s]" % (pos, end, e), flush=True)
            if end >= SIZE:
                break
            pos += block - overlap
            continue
        nblocks += 1
        low = buf.lower()
        for m in EXT_RE.finditer(low):
            i = _back_name(low, m.start())
            if i is None:
                continue
            off = pos + i
            hits.setdefault(off, buf[i:m.end()].decode("ascii", "replace"))
        for m in TOKEN_RE.finditer(low):
            s = m.group().decode("ascii", "replace")
            toks.setdefault(s, []).append(pos + m.start())
        if fh:
            for k, v in hits.items():
                fh.write('{"n":"%s","o":%d}\n' % (v, k))
            fh.flush()
        if verbose:
            print("  bloque %3d  0x%012x-0x%012x  nombres=%d tokens=%d"
                  % (nblocks, pos, end, len(hits), len(toks)), flush=True)
        if end >= SIZE:
            break
        time.sleep(sleep)
        pos += block - overlap
    if fh:
        fh.close()
    return hits, toks, nblocks, gaps


# --------------------------------------------------------------------------
# Contenido de los contenedores ZIP/APK guardados SIN COMPRIMIR dentro del RAR
# (metodo 0 => los bytes son identicos al fichero original, asi que se puede
# leer su directorio central por rangos sin descargar los ~400 MB)
# --------------------------------------------------------------------------
def _u16(b, i):
    return int.from_bytes(b[i:i + 2], "little")


def _u32(b, i):
    return int.from_bytes(b[i:i + 4], "little")


def zip_central_dir(rd: RangeReader, base, size, depth=0, max_entries=200000,
                    want=(".exe", ".dll", ".sys", ".apk", ".apks", ".xapk",
                          ".zip", ".so", ".jar", ".bat", ".ini", ".dat")):
    """Lee el directorio central de un ZIP/APK que vive en [base, base+size).

    `base` es el offset ABSOLUTO dentro del fichero RAR del byte 0 del ZIP.
    Devuelve (entradas, anidados) donde 'anidados' son los ZIP internos que
    tambien se han podido leer por rango (solo si estan STORED).
    """
    if size < 22 or size > SIZE - base:
        return [], []
    tail = rd.read(base + size - min(size, 66000), min(size, 66000))
    i = tail.rfind(b"PK\x05\x06")
    if i < 0:
        return [], []
    cd_size = _u32(tail, i + 12)
    cd_off = _u32(tail, i + 16)
    nent = _u16(tail, i + 10)
    if cd_off == 0xFFFFFFFF or cd_size == 0xFFFFFFFF:
        j = tail.rfind(b"PK\x06\x06")
        if j < 0:
            return [], []
        cd_size = int.from_bytes(tail[j + 40:j + 48], "little")
        cd_off = int.from_bytes(tail[j + 48:j + 56], "little")
        nent = int.from_bytes(tail[j + 32:j + 40], "little")
    if cd_size == 0 or cd_off >= size:
        return [], []
    cd = rd.read(base + cd_off, min(cd_size, 1 << 24))
    entries = []
    p = 0
    while p + 46 <= len(cd) and len(entries) < max_entries:
        if cd[p:p + 4] != b"PK\x01\x02":
            break
        method = _u16(cd, p + 10)
        csize = _u32(cd, p + 20)
        usize = _u32(cd, p + 24)
        nlen = _u16(cd, p + 28)
        elen = _u16(cd, p + 30)
        clen = _u16(cd, p + 32)
        lho = _u32(cd, p + 42)
        name = cd[p + 46:p + 46 + nlen].decode("utf-8", "replace")
        p += 46 + nlen + elen + clen
        entries.append({"name": name, "method": method, "csize": csize,
                        "usize": usize, "lho": lho,
                        "off": base + lho})
    # recursión: solo sobre los ZIP internos almacenados sin comprimir
    nested = []
    if depth < 2:
        for e in entries:
            ln = e["name"].lower()
            if not ln.endswith(want):
                continue
            if e["method"] != 0 or e["usize"] < 22:
                continue
            lh = rd.read(e["off"], 256)
            if lh[:4] != b"PK\x03\x04":
                continue
            nl = _u16(lh, 26)
            el = _u16(lh, 28)
            dstart = e["off"] + 30 + nl + el
            sub, sub2 = zip_central_dir(rd, dstart, e["usize"], depth + 1)
            if sub:
                nested.append({"name": e["name"], "base": dstart, "size": e["usize"],
                               "entradas": len(sub), "sub": sub})
    return entries, nested


# --------------------------------------------------------------------------
# Volcado
# --------------------------------------------------------------------------
def md_table(entries):
    rows = ["| # | offset | tipo | ruta | tam. descomprimido | datos comprimidos | dir |",
            "|---|--------|------|------|---------------------:|------------------:|:----:|"]
    i = 0
    for e in entries:
        if e["htype"] != HEAD_FILE:
            continue
        i += 1
        unp = "no determinado" if e["unp"] is None else "%d" % e["unp"]
        rows.append("| %d | 0x%012x | %s | `%s` | %s | %d | %s |" % (
            i, e["pos"], "DIR" if e["dir"] else "FILE", e["name"], unp, e["data"],
            "si" if e["dir"] else ""))
    return "\n".join(rows)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("modo", choices=["headers", "scan", "zipcd"],
                    default="headers", nargs="?")
    ap.add_argument("--delay", type=float, default=0.12)
    args = ap.parse_args()

    rd = RangeReader(delay=args.delay)
    os.makedirs(OUTDIR, exist_ok=True)

    if args.modo == "headers":
        print("Recorriendo la cadena de cabeceras RAR5 por rangos...")
        print("-" * 78)
        entries, resyncs = walk(rd)
        print("-" * 78)
        nfile = sum(1 for e in entries if e["htype"] == HEAD_FILE)
        ndir = sum(1 for e in entries if e.get("dir"))
        print("  %d bloques, %d entradas FILE (%d directorios), %d resyncs, "
              "%d peticiones, %.1f MB leidos"
              % (len(entries), nfile, ndir, len(resyncs), rd.reqs, rd.bytes / 1e6))
        with open(os.path.join(OUTDIR, "entradas.json"), "w") as f:
            json.dump({"entradas": entries, "resyncs": resyncs,
                       "requests": rd.reqs, "bytes": rd.bytes}, f, indent=1)
        return 0

    if args.modo == "zipcd":
        # Directorios centrales de los contenedores ZIP/APK que el RAR guarda
        # SIN comprimir: sus bytes son los del fichero original, asi que el
        # indice se lee por rango sin bajar los ~400 MB de cada uno.
        with open(os.path.join(OUTDIR, "entradas.json")) as f:
            ents = json.load(f)["entradas"]
        out = {}
        for e in ents:
            if e["htype"] != HEAD_FILE or e["dir"] or e["data"] == 0:
                continue
            if e["method"] != 0 or not e["name"].lower().endswith(
                    (".apks", ".xapk", ".apk", ".zip")):
                continue
            base = e["next"] - e["data"]                # offset de los datos
            print("=" * 78)
            print("%s  (offset datos 0x%012x, %d bytes)" % (e["name"], base, e["data"]))
            ents2, nested = zip_central_dir(rd, base, e["data"])
            print("  %d entradas en el directorio central" % len(ents2))
            out[e["name"]] = {"base": base, "entradas": ents2}
            for x in ents2[:20]:
                print("    %-70s m=%d %d" % (x["name"], x["method"], x["usize"]))
            if len(ents2) > 20:
                print("    ... (+%d mas)" % (len(ents2) - 20))
            for nb in nested:
                print("  ANIDADO %s -> %d entradas" % (nb["name"], nb["entradas"]))
                out.setdefault("_anidados", {})[nb["name"]] = nb["sub"]
        with open(os.path.join(OUTDIR, "zip_cd.json"), "w") as f:
            json.dump(out, f, indent=1)
        print("-" * 78)
        print("  %d peticiones, %.2f MB leidos" % (rd.reqs, rd.bytes / 1e6))
        return 0

    print("Barrido por regex en bloques de 8 MB con solape 4 KB "
          "(sin alinear la cadena de cabeceras)...")
    print("-" * 78)
    hits, toks, nb, gaps = scan_overlap(
        rd, jsonl=os.path.join(OUTDIR, "hits_regex.jsonl"))
    print("-" * 78)
    print("  %d nombres candidatos, %d tokens distintos, %d bloques leidos, "
          "%d huecos, %d peticiones, %.1f MB leidos"
          % (len(hits), len(toks), nb, len(gaps), rd.reqs, rd.bytes / 1e6))
    with open(os.path.join(OUTDIR, "hits_regex.json"), "w") as f:
        json.dump({"nombres": {str(k): v for k, v in sorted(hits.items())},
                   "tokens": {k: v for k, v in sorted(toks.items())},
                   "huecos": gaps, "requests": rd.reqs, "bytes": rd.bytes}, f, indent=1)
    print("  TOKENS:")
    for k, v in sorted(toks.items(), key=lambda kv: -len(kv[1])):
        print("    %-14s x%-6d  p.ej. 0x%012x" % (k, len(v), v[0]))
    return 0


if __name__ == "__main__":
    sys.exit(main())