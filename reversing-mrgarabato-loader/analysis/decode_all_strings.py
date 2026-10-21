#!/usr/bin/env python3
"""Recupera las cadenas ofuscadas de MrGarabato probando el indice inicial
del keystream y quedandose con la decodificacion de mayor calidad.

Esquema de cifrado (verificado en el desensamblado, no solo en los datos):

    plain[i] = cipher[i] ^ ((KEY0 + idx + i) & 0xFF)

El indice corre continuo DENTRO de una misma cadena y se reinicia en cada
cadena distinta.  En ByPassEmulator KEY0 = 0x53 e idx = 0; el Loader usa
`lea eax,[rcx-0x6d]` es decir 0x93+i, que equivale a idx = 0x40.  Por eso
aqui se prueban los 256 valores de idx.

Correcciones frente a la version anterior:
  * `OK` se construye con `.encode("latin1")` para obtener un set de BYTES.
    Antes era un set de *cadenas* de un solo caracter y se comparaba contra
    bytes (`b in OK`), de modo que la comprobacion era siempre False y no se
    encontraba ninguna cadena.
  * bucle de busqueda de tramos: la version anterior no avanzaba `j` cuando
    un byte no era valido, con lo que el `while j < win` exterior no
    terminaba nunca (bucle infinito).
  * la puntuacion se descompone en componentes comparables y el bonus de
    palabras clave se pondera por su especificidad.
  * precalculo de las 256 tablas de keystream para que el barrido sea
    viable sobre cientos de KB.
"""
import sys, string

KEY0 = 0x53

# set de BYTES imprimibles (bug original: era un set de str)
OK = set((string.ascii_letters + string.digits +
          "\\/._-:*,;<>()[]{}<>\"' \t%+=|@#$&!~^`?").encode("latin1"))

# caracteres que de verdad aparecen en rutas, nombres de fichero, mensajes y
# claves de registro.  Sirven para distinguir texto real de la basura que sale
# al descifrar con el indice equivocado.
COMMON = set((string.ascii_letters + string.digits +
              " \\/._-:()").encode("latin1"))

# bonus por palabra clave, ponderado por lo especifica que sea
KW = {
    "hkey_local_machine": 140, "currentcontrolset": 130, "systembiosversion": 140,
    "videobiosversion": 140, "immunitydebugger": 130, "processhacker": 130,
    "wireshark": 130, "procmon": 130, "regmon": 130, "filemon": 130,
    "autoruns": 130, "ksdumper": 130, "debugger": 130, "x64dbg": 130,
    "x32dbg": 130, "currentversion": 120, "virtualbox": 120, "sandbox": 120,
    "vmware": 110, "vbox": 110, "qemu": 110, "wine": 110, "kernel32": 110,
    "ntdll": 110, "advapi32": 110, "setupapi": 110, "hklm": 110, "hkey": 110,
    "ida": 110, "olly": 110, "dbghelp": 110, "dumper": 110, "registry": 100,
    "driver": 100, "\\\\.\\": 100, "kvm": 100, "xen": 100, "hook": 90,
    "software": 90, "hardware": 90, "microsoft": 90, "virtual": 90,
    "system": 85, "windows": 85, "biosversion": 120, "acpi": 75,
    "bios": 75, "description": 70, "version": 65, "control": 65,
    "classes": 65, "enum": 65, "service": 65, "http": 65,
    ".exe": 60, ".dll": 60, ".sys": 60, "devic": 60, "uuid": 60,
    "product": 60, "6.t": 90, "xp": 40, "7.t": 90,
}

WIN = 64          # longitud maxima de cadena considerada


def quality(s: bytes) -> int:
    """Puntua un candidato.

    Detalle importante: la longitud NO premia mucho.  Una decodificacion con
    el indice desplazado sigue siendo legible y suele absorber el bloque
    siguiente, con lo que gana en 'caracteres validos' aunque arrastre
    basura.  Por eso los caracteres raros (`^ ~ | { } @ \\ < >`) penalizan
    fuerte y el tramo que termina de forma natural se premia aparte.
    """
    if not s:
        return -10_000
    common = 0
    for c in s:
        if c in COMMON:
            common += 3
        elif c in OK:
            common -= 3
        else:
            common -= 12
    q = common + _case_score(s)
    for k, w in KW.items():
        if k.encode() in s.lower():
            q += w
    # senal decisiva frente a una clave desplazada en 0x20: los nombres de
    # fichero reales llevan la extension en minuscula ('.exe', '.dll'), y al
    # invertir todos los bits de caso salen como '.EXE'.
    if any(e in s for e in (b".exe", b".dll", b".sys", b".com", b".bat")):
        q += 90
    return q


def _case_score(s: bytes) -> int:
    """Coherencia de mayusculas/minusculas.

    Un indice equivocado no rompe la imprimibilidad: si la clave se desplaza
    en un multiplo de 0x20, lo unico que cambia es el bit de caso de cada
    letra y sale 'kSdUMPERcLIEN' en vez de 'KsDumperClient'.  El texto real es
    coherente (CamelCase, MAYUSCULAS o minusculas).
    """
    t = s.decode("latin1")
    flips = letters = 0
    prev = None
    for ch in t:
        if ch.isalpha():
            up = ch.isupper()
            if prev is not None:
                letters += 1
                if up != prev:
                    flips += 1
            prev = up
    if letters < 3:
        return 0
    ratio = flips / letters
    if ratio > 0.55:
        return -40
    if ratio > 0.35:
        return -15
    return 0


def tables(blob, win):
    """Las 256 tablas de descifrado del blob, una por indice inicial.
    El keystream es (KEY0 + idx + i) & 0xFF, luego para idx y idx+1 solo
    cambia el byte bajo: construirlo con slicing es mucho mas rapido que un
    bucle por byte."""
    out = []
    m = len(blob)
    reps = (m // win) + 2
    for idx in range(256):
        ks = bytes((KEY0 + idx + i) & 0xFF for i in range(win)) * reps
        ks = ks[:m]
        out.append(bytes(x ^ k for x, k in zip(blob, ks)))
    return out


def runs(dec, win, minlen):
    """Tramos maximos de bytes validos dentro de `dec`.
    Cuando un byte no es valido hay que avanzar igualmente, o el bucle
    exterior no termina."""
    j = 0
    while j < win:
        start = j
        while j < win and dec[j] in OK:
            j += 1
        if j - start >= minlen:
            yield start, dec[start:j]
        j += 1


def scan(img, lo, hi, minlen=5, win=WIN, align=1):
    """En cada posicion *alineada* prueba los 256 indices y devuelve el mejor
    tramo.

    `align` no es cosmetico: el pool de cadenas ofuscadas de este malware
    esta alineado a 16 bytes.  Cada bloque de 16 es un immediate de un
    `movdqu` que el codigo vuelca en un buffer de pila, y `win` se limita al
    tamano del bloque porque el pool NO guarda las cadenas de forma contigua:
    una cadena larga se compone de bloques *no adyacentes* (el segundo se
    descifra con indice+16).  Ver `extract_from_code.py`, que si resuelve esas
    cadenas por ser el unico metodo fiable para ellas.

    Que el barrido sea de 16 en 16 elimina practicamente todo el ruido: en una
    posicion desalineada el primer byte ya no corresponde a una clave que
    produzca texto.
    """
    hi = min(hi, len(img))
    lo = lo - (lo % align)
    tab = tables(img[lo:hi + win], win)
    found = []
    for off in range(lo, hi, align):
        p = off - lo
        best = None
        dec = tab[0][p:p + win]      # idx=0 es la lectura correcta (ver KEY0)
        for start, seg in runs(dec, win, minlen):
            if start:
                # Solo los tramos que empiezan aqui; si no, cada byte
                # genera una familia de decodificaciones desplazadas.
                continue
            k = p + len(seg)
            term = k < len(tab[0]) and tab[0][k] not in OK
            q = quality(seg) + (25 if term else 0)
            if best is None or q > best[0]:
                best = (q, 0, seg)
        if best and best[0] >= 40:
            found.append((off, 0, best[0], best[2]))
    return found


def _norm(s: bytes) -> str:
    """Forma normalizada para detectar duplicados: un cambio de idx desplaza
    la clave una posicion y produce texto casi identico con las letras
    cambiadas de sitio (XOR 1).  Normalizar Orden y separadores hace que
    esos impostores colisionen con la cadena buena."""
    return "".join(ch for ch in s.decode("latin1").lower()
                   if ch.isalnum())


def _soupy(s: bytes) -> bool:
    """Detecta 'sopa de letras': runs ascendentes/descendentes de 5+ letras
    followed de ASCII, tipico de un bloque cifrado al que se le aplica una
    clave equivocada.  Las cadenas reales no lo tienen."""
    t = s.decode("latin1")
    run = 1
    for i in range(1, len(t)):
        d = ord(t[i]) - ord(t[i - 1])
        if d in (1, -1):
            run += 1
            if run >= 6:
                return True
        else:
            run = 1
    return False


def merge(found):
    """Un candidato por posicion de inicio, mas deduplicado por contenido.

    El barrido byte a byte genera una familia de decodificaciones de la misma
    cadena real desplazando el indice (todas legibles, porque el keystream se
    mueve con ella).  Se conservan solo las de mayor calidad y se descarta el
    resto por colision de forma normalizada."""
    found.sort(key=lambda t: (t[0], -t[2]))
    kept, last = [], -1
    for off, idx, q, seg in found:
        if off + len(seg) <= last:
            continue
        kept.append((off, idx, q, seg))
        last = off + len(seg)
    best = {}
    for off, idx, q, seg in kept:
        k = _norm(seg)
        if not k or _soupy(seg):
            continue
        if k not in best or q > best[k][2]:
            best[k] = (off, idx, q, seg)
    out = sorted(best.values(), key=lambda t: t[0])
    # Una cadena real y su impostora por clave desplazada se diferencian en un
    # sufijo ('ksdumpercliente' vs 'ksdumperclien').  Si una forma normalizada
    # es prefijo de otra y ambas salen del mismo bloque, gana la de mayor
    # score: es la lectura completa.
    drop = set()
    for a in range(len(out)):
        for b in range(len(out)):
            if a == b:
                continue
            ka, kb = _norm(out[a][3]), _norm(out[b][3])
            if kb.startswith(ka) and len(ka) >= 4 and out[b][2] > out[a][2]:
                drop.add(a)
                break
    return [t for i, t in enumerate(out) if i not in drop]


def _dec(img, off, idx, n):
    return bytes(img[off + i] ^ ((KEY0 + idx + i) & 0xFF) for i in range(n))


def scan_blocks(img, lo, hi, align=16, minlen=5):
    """El bloque de 16 bytes exacto, sin extenderse al vecino.

    Es importante acotar al bloque: las cadenas se descifran sobre un buffer
    de pila de tamano exacto (el `cmp rcx, N` del bucle da la longitud), asi
    que los 16 bytes del immediate son toda la informacion que hay.  Al
    dejar que el tramo se coma el bloque contiguo, una clave desplazada
    tambien produce 'texto' y gana por longitud.
    """
    out = []
    for off in range(lo - (lo % align), hi, align):
        if off + align > len(img):
            break
        # El desensamblado demuestra que ByPassEmulator descifra con 0x53+i
        # (idx=0) y el Loader con 0x93+i (idx=0x40).  Asi que idx=0 es la
        # lectura correcta por construccion y no compite con el resto: el
        # brute force queda como comprobacion, no como selector.  Dejar que
        # gane el mejor score es un error, porque una clave desplazada en
        # 0x20 solo voltea el bit de caso ('kSdUMPERcLIEN') y puntua mas alto
        # por ser mas corta.
        seg = _dec(img, off, 0, align)
        q = quality(seg)
        alt = max(quality(_dec(img, off, i, align)) for i in range(1, 256))
        if q >= 120 and len(seg) >= minlen:
            out.append((off, 0, q, seg))
    return out


def collect(f, lo, hi, minlen=5):
    img = open(f, "rb").read()
    hi = min(hi, len(img))
    print(f"[*] {f}: barrido 0x{lo:x}-0x{hi:x}, 256 indices por posicion", flush=True)
    found = scan(img, lo, hi, minlen, win=16, align=16)
    print(f"    barrido alineado a 16: {len(found)} candidatos", flush=True)
    found += scan_blocks(img, lo, hi, minlen=minlen)
    print(f"    + barrido por bloques: {len(found)} en total", flush=True)
    kept = merge(found)
    print(f"[+] {len(kept)} cadenas recuperadas\n")
    print("  %-10s %-8s %-6s %s" % ("RVA", "idx", "score", "cadena"))
    for off, idx, q, seg in kept:
        print("  0x%06x   0x%02x   %5d  %s" % (off, idx, q, seg.decode("latin1")))
    return kept


if __name__ == "__main__":
    if len(sys.argv) > 1 and sys.argv[1] == "--all":
        out = []
        for f, lo, hi in (("mem_bypass.bin", 0x18000, 0x1FAFC),
                          ("mem_loader.bin", 0x22000, 0x2F000)):
            out += collect(f, lo, hi)
        # extract_from_code.py da las cadenas completas (con su longitud real)
        # para las que estan partidas entre varios immediatos; es la fuente
        # fiable y se anade al final.
        try:
            import extract_from_code as E
            for f in ("mem_bypass.bin", "mem_loader.bin"):
                img = open(f, "rb").read()
                b, secs = E.sections(img)
                for r in E.Extractor(img, b, secs).run():
                    out.append((r["rva"], 0,
                                quality(r["plain"].encode("latin1")) + 1000,
                                r["plain"].encode("latin1")))
            print("[+] + cadenas completas desde extract_from_code.py")
        except Exception as exc:
            print("[!] extract_from_code: %s" % exc)
        with open("strings_decodificadas.txt", "w") as fh:
            for off, idx, q, seg in sorted(out, key=lambda t: (t[0], -t[2])):
                fh.write("0x%06x\tidx=0x%02x\tq=%d\t%s\n" %
                         (off, idx, q, seg.decode("latin1")))
        print("\n[+] -> strings_decodificadas.txt (%d lineas)" % len(out))
    else:
        f = sys.argv[1] if len(sys.argv) > 1 else "mem_bypass.bin"
        lo = int(sys.argv[2], 16) if len(sys.argv) > 2 else 0x18000
        hi = int(sys.argv[3], 16) if len(sys.argv) > 3 else 0x1FAFC
        collect(f, lo, hi)