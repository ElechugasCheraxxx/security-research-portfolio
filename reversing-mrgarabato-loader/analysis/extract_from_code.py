#!/usr/bin/env python3
"""Extractor EXACTO de cadenas ofuscadas a partir del codigo.

El malware usa  keystream posicional  (plain[i] = cipher[i] ^ (0x53 + i))
con indice inicial SIEMPRE 0 (verificado en el desensamblado).  Las cadenas
viven en dos sitios:

  1) .text  -> constantes inmediatas que se copian a un buffer de pila
                (patron:  c7 45 e0 <imm32> ; ... ; lea eax,[rcx+0x53];
                           xor [rax+rcx],al ; inc rcx ; cmp rcx,LEN ; jb)
  2) .rdata -> blobs descifrados in-situ (fcn_f5c0: [reg+uVar+0x58] ^= uVar+0x53)

Este script desensambla .text con capstone, localiza cada bucle XOR, recupera
el buffer que descifra y su longitud, y lo descifra.  Sin heuristicas: es el
valor exacto que el programa usara en tiempo de ejecucion.
"""
import sys, os, struct, json
import capstone
from capstone.x86 import X86_OP_MEM, X86_OP_IMM, X86_OP_REG

KEY0 = 0x53

# palabras que aparecen en cadenas reales de este malware; sirven para
# desempatar entre desplazamientos candidatos de la pila
KEYWORDS = (
    "debugger", "service", "windows", "http", "exe", "dll", "sys", "drv",
    "path", "system", "driver", "version", "virtual", "software", "hardware",
    "oracle", "vmware", "vbox", "qemu", "error", "file", "process", "hook",
    "registry", "user", "run", "currentversion", "32 bit", "64 bit",
    "network", "install", "program", "windows nt", "currentcontrolset",
)


# --------------------------------------------------------------------------- #
def sections(img):
    e = struct.unpack_from("<I", img, 0x3C)[0]
    n = struct.unpack_from("<H", img, e + 6)[0]
    optsz = struct.unpack_from("<H", img, e + 20)[0]
    base = struct.unpack_from("<Q", img, e + 24 + 24)[0]
    so = e + 24 + optsz
    out = []
    for i in range(n):
        o = so + i * 40
        nm = img[o:o + 8].rstrip(b"\x00").decode("latin1")
        vs, va, rs, ra = struct.unpack_from("<IIII", img, o + 8)
        ch = struct.unpack_from("<I", img, o + 36)[0]
        # el volcado es una imagen en memoria: offset de fichero == RVA
        if rs == 0:
            ra, rs = va, vs
        out.append(dict(name=nm, va=va, vs=vs, raw=ra, rs=rs, ch=ch))
    return base, out


def rva2off(img, secs, rva):
    for s in secs:
        if s["va"] <= rva < s["va"] + max(s["vs"], s["rs"]):
            return s["raw"] + (rva - s["va"])
    return None


def off2rva(secs, off):
    for s in secs:
        lo, hi = s["raw"], s["raw"] + s["rs"]
        if lo <= off < hi:
            return s["va"] + (off - lo)
    return None


def decode(buf, length, idx0=0):
    out = bytearray()
    for i in range(length):
        if i >= len(buf):
            break
        out.append(buf[i] ^ ((KEY0 + idx0 + i) & 0xFF))
    return bytes(out)


# --------------------------------------------------------------------------- #
class Extractor:
    def __init__(self, img, base, secs):
        self.img, self.base, self.secs = img, base, secs
        self.md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_64)
        self.md.detail = True

    def disasm_text(self):
        """Barrido lineal de .text.  .pdata esta cifrado en este payload, asi
        que no sirve de guia; usamos md.skipdata para saltar los huecos."""
        t = [s for s in self.secs if s["name"] == ".text"][0]
        code = self.img[t["raw"]:t["raw"] + t["rs"]]
        self.md.skipdata = True
        out = [i for i in self.md.disasm(code, self.base + t["va"]) if i.id != 0]
        return out, t

    # -- stack image ------------------------------------------------------- #
    @staticmethod
    def _store_imm(ins):
        """Devuelve (disp, bytes) si la instruccion es  mov [mem], imm."""
        if not ins.operands:
            return None
        d = ins.operands
        if len(d) != 2 or d[0].type != X86_OP_MEM or d[1].type != X86_OP_IMM:
            return None
        m = d[0].mem
        if m.base == 0 or m.index != 0:
            return None
        if ins.mnemonic not in ("mov", "movabs"):
            return None
        sz = d[0].size
        if sz not in (1, 2, 4, 8):
            return None
        return m.base, m.disp, sz, d[1].imm & ((1 << (sz * 8)) - 1)

    def run(self):
        insns, tsec = self.disasm_text()
        self.insns = insns
        self.byaddr = {i.address: (n, i) for n, i in enumerate(insns)}
        results = []

        # --- localizar bucles XOR ---------------------------------------- #
        for n, ins in enumerate(insns):
            if ins.mnemonic != "xor" or len(ins.operands) != 2:
                continue
            d0, d1 = ins.operands
            if d0.type != X86_OP_MEM or d0.size != 1:
                continue
            m = d0.mem
            if m.index == 0 or m.base == 0:
                continue
            # el byte que se descifra es [base + index*1 + disp]
            loop = self._match_loop(insns, n)
            if loop is None:
                continue
            looplen, start_n, end_n, idxreg = loop
            rec = self._recover(insns, start_n, end_n, m, idxreg, looplen)
            if rec is None:
                continue
            kind, blob, length, where, key0 = rec
            plain = self._best_decode(blob, length, key0)
            if len(plain) < 2:
                continue
            results.append(dict(kind=kind, where=where, rva=ins.address - self.base,
                                length=length, key0=key0,
                                cipher=blob[:len(plain)].hex(),
                                plain=plain.decode("latin1")))
        return results

    @staticmethod
    def _best_decode(blob, length, key0):
        """Si key0 es conocido se usa; si no, se prueban los 256 valores y se
        queda con el que produce la cadena mas larga de ASCII imprimible."""
        cands = [key0] if key0 is not None else list(range(256))
        best = b""
        for k in cands:
            p = decode(blob, length, k - KEY0)
            cut = 0
            while cut < len(p) and 0x20 <= p[cut] < 0x7F:
                cut += 1
            if cut > len(best):
                best = p[:cut]
        return best

    def _match_loop(self, insns, n):
        """Busca el cmp/jb que cierra el bucle que contiene la insn n.
        Devuelve (len, start_n, end_n, reg_indice) con len=None si el limite
        del bucle no es una constante (a veces viene de un registro)."""
        ins = insns[n]
        idxreg = ins.operands[0].mem.index
        for k in range(n + 1, min(n + 16, len(insns))):
            j = insns[k]
            if j.group(capstone.CS_GRP_JUMP) and j.operands and \
               j.operands[0].type == X86_OP_IMM:
                tgt = j.operands[0].imm
                if tgt <= j.address and j.address - tgt < 64:
                    ln = None
                    for m in range(n, k):
                        c = insns[m]
                        if c.mnemonic == "cmp" and len(c.operands) == 2:
                            if c.operands[1].type == X86_OP_IMM:
                                ln = c.operands[1].imm
                            break
                    start_n = self.byaddr.get(tgt, (None, None))[0]
                    if start_n is None:
                        return None
                    if ln is not None and not (0 < ln <= 4096):
                        return None
                    return ln, start_n, k, idxreg
        return None

    # -- reconstruir el buffer -------------------------------------------- #
    @staticmethod
    def _find_key(insns, start_n, idxreg):
        """El byte clave se calcula con  lea r32, [idxreg + K]  (K puede ser
        negativo: el loader usa  lea eax,[rcx-0x6d]  ==  clave 0x93+i)."""
        for m in range(start_n, min(start_n + 8, len(insns))):
            c = insns[m]
            if c.mnemonic in ("lea", "add") and len(c.operands) == 2:
                o = c.operands
                if o[1].type == X86_OP_MEM and o[1].mem.base == idxreg and \
                   o[1].mem.index == 0:
                    return o[1].mem.disp & 0xFF
        return None

    @staticmethod
    def _frame_delta(insns, at):
        """rbp - rsp en el punto `at`, resuelto hacia atras de forma simbolica.
        Necesario porque el compilador mezcla locales [rbp+x] y [rsp+y]
        (p.ej.  lea rbp,[rsp-0xc0] ; sub rsp,0x1c0  =>  rbp == rsp+0x100)."""
        RB, RS = capstone.x86.X86_REG_RBP, capstone.x86.X86_REG_RSP
        acc = 0                      # suma de ajustes hacia delante

        def soon_call(j, nxt=4):
            """un push inmediatamente seguido de call es un argumento de pila:
            el emparejamiento call/ret se anula solo"""
            return any(insns[x].mnemonic == "call" for x in
                       range(j + 1, min(j + 1 + nxt, len(insns))))

        for k in range(at, max(-1, at - 6000), -1):
            c = insns[k]
            o = c.operands
            # walking hacia atras: acumulamos el cambio que cada instruccion
            # provoca hacia DELANTE sobre (rbp - rsp)
            if c.mnemonic == "call":
                acc += 8             # el ret correspondiente lo compensa
                continue
            if c.mnemonic == "push":
                if not soon_call(k):
                    acc += 8
                continue
            if c.mnemonic == "pop":
                acc -= 8
                continue
            if c.mnemonic in ("sub", "add") and len(o) == 2 and \
               o[0].type == X86_OP_REG and o[0].reg == RS and \
               o[1].type == X86_OP_IMM:
                acc += o[1].imm if c.mnemonic == "sub" else -o[1].imm
                continue
            if c.mnemonic == "lea" and len(o) == 2 and o[0].type == X86_OP_REG and \
               o[0].reg == RB and o[1].type == X86_OP_MEM and \
               o[1].mem.base == RS and o[1].mem.index == 0:
                return o[1].mem.disp + acc
            if c.mnemonic == "mov" and len(o) == 2 and o[0].type == X86_OP_REG:
                if o[0].reg == RB and o[1].type == X86_OP_REG and o[1].reg == RS:
                    return acc
                if o[0].reg in (RB, RS):
                    return None          # no sabemos deducirlo -> abandonar
            if c.mnemonic in ("leave", "ret", "retn"):
                return None
        return None

    @staticmethod
    def _lea_hint(insns, end_n, base_reg):
        """Tras el bucle el codigo hace  lea rdx,[rbp+disp]  para pasar el
        buffer a una API de string.  Si la base del XOR era rsp, ese disp nos
        da directamente el desplazamiento rbp->rsp que buscamos."""
        for k in range(end_n + 1, min(end_n + 10, len(insns))):
            c = insns[k]
            o = c.operands
            if c.mnemonic != "lea" or len(o) != 2 or o[0].type != X86_OP_REG:
                continue
            if o[1].type != X86_OP_MEM or o[1].mem.index != 0:
                continue
            b = o[1].mem.base
            if base_reg == capstone.x86.X86_REG_RSP and \
               b == capstone.x86.X86_REG_RBP:
                return o[1].mem.disp
            if base_reg == capstone.x86.X86_REG_RBP and \
               b == capstone.x86.X86_REG_RSP:
                return -o[1].mem.disp
        return None

    def _recover(self, insns, start_n, end_n, xormem, idxreg, looplen):
        """Si la base del xor es rbp/rsp, el buffer es una variable local y sus
        bytes vienen de  mov [rbp+r], imm  (y a veces de un volcado xmm desde
        .rdata).  Reconstruimos esa imagen de pila y devolvemos los bytes.
        El binario usa una ABI de pila no estandar (el callee limpia los
        argumentos), asi que en vez de fiarse del calculo de rbp-rsp se
        puntuan los desplazamientos candidatos y se elige el mejor."""
        base_reg = xormem.base
        disp = xormem.disp
        RB, RS = capstone.x86.X86_REG_RBP, capstone.x86.X86_REG_RSP
        if base_reg not in (RB, RS):
            return None      # la base es un puntero a datos, no un registro
                              # de pila (no ocurre en este payload)

        writes = []      # (registro, disp, bytes) en ORDEN DE EJECUCION
        xmm = {}         # registro xmm -> 16 bytes conocidos
        regv = {}        # registro GPR  -> entero conocido

        def put(reg, d, bs):
            writes.append((reg, d, bs))

        # La ventana no puede cruzar el final de la cadena anterior: sus
        # escrituras a slots de pila cercanos contaminarian el buffer.
        # Se corta en la ultima llamada o en el bucle XOR previo.
        lo_i = max(0, start_n - 90)
        for m in range(start_n - 1, max(-1, start_n - 90), -1):
            c = insns[m]
            if c.mnemonic == "call" or (
                    c.mnemonic == "xor" and len(c.operands) == 2 and
                    c.operands[0].type == X86_OP_MEM and
                    c.operands[0].size == 1 and c.operands[0].mem.index):
                lo_i = m + 1
                break

        for m in range(lo_i, start_n):
            c = insns[m]
            o = c.operands
            if c.mnemonic in ("xorps", "pxor", "xorpd") and len(o) == 2 and \
               o[0].type == X86_OP_REG and o[0].reg == o[1].reg:
                xmm[int(o[0].reg)] = b"\x00" * 16
                continue
            if c.mnemonic in ("movabs", "mov") and len(o) == 2 and \
               o[0].type == X86_OP_REG and o[1].type == X86_OP_IMM:
                regv[int(o[0].reg)] = o[1].imm
                continue
            st = self._store_imm(c)
            if st and st[0] in (RB, RS):
                _, d, sz, val = st
                put(st[0], d, val.to_bytes(sz, "little"))
                continue
            if len(o) != 2:
                continue
            if o[0].type == X86_OP_MEM and o[1].type == X86_OP_REG and \
               o[0].mem.index == 0 and o[0].mem.base in (RB, RS):
                src = xmm.get(int(o[1].reg))
                if src is None and int(o[1].reg) in regv:
                    src = (regv[int(o[1].reg)] & ((1 << 64) - 1)).to_bytes(8, "little")
                if src is not None:
                    put(o[0].mem.base, o[0].mem.disp, src[:max(1, o[0].size)])
                continue
            if o[1].type == X86_OP_MEM and o[1].mem.base == capstone.x86.X86_REG_RIP:
                rva = c.address + c.size + o[1].mem.disp - self.base
                off = rva2off(self.img, self.secs, rva)
                if off is not None and o[0].type == X86_OP_REG:
                    xmm[int(o[0].reg)] = self.img[off:off + 16]
                continue

        if not writes:
            return None
        lo = disp
        need = looplen if looplen else 0
        hi0 = max((d + len(bs)) if r == base_reg else (d + len(bs))
                  for r, d, bs in writes)

        def assemble(delta):
            """aplica las escrituras en el espacio del registro del xor"""
            raw = bytearray(max(need, hi0 - lo) + 8)
            cov = bytearray(len(raw))
            for reg, d, bs in writes:
                p = d if reg == base_reg else (d + delta if reg == RB else d - delta)
                for i, b in enumerate(bs):
                    j = p + i - lo
                    if 0 <= j < len(raw):
                        raw[j] = b
                        cov[j] = 1
            return raw, cov

        def score(delta):
            """(cobertura contigua, imprimibles, calidad de texto).

            - cobertura contigua desde el inicio: descarta de inmediato los
              desplazamientos que dejan huecos en el buffer;
            - imprimibles: ruido que sale del rango 0x20-0x7E;
            - calidad: caracteres propios de rutas/nombres de fichero + bonus
              por palabras clave.  Es lo que desempata cuando dos
              desplazamientos cubren los mismos bytes pero solo uno produce
              texto real (p.ej. '...Service (32 bit).exe' frente a '...Servimvpp').
            """
            raw, cov = assemble(delta)
            run = 0
            while run < len(cov) and cov[run]:
                run += 1
            span = min(need, run) if need else run
            pr = 0
            qual = 0
            text = []
            for j in range(span):
                if not cov[j]:
                    continue
                ch = raw[j] ^ ((KEY0 + j) & 0xFF)
                if 0x20 <= ch < 0x7F:
                    pr += 1
                    c = chr(ch)
                    text.append(c)
                    if c.isalnum() or c in "\\/.:-_ (),%":
                        qual += 3
                    else:
                        qual -= 4          # '{', '|', '~'... no salen nunca
            low = "".join(text).lower()
            for k in KEYWORDS:
                if k in low:
                    qual += 60 + 4 * len(k)
            # bigramas tipicas: separadores de ruta y de palabra
            for bg in ("\\", ":", ".", "_", "-", "/"):
                qual += 6 * low.count(bg)
            return (span, pr, qual), raw

        cands = [0]
        d0 = self._frame_delta(insns, start_n)
        if d0 is not None:
            cands.append(d0)
        cands += list(range(-0x200, 0x201))
        best = None
        # `lea rdx,[rbp+X]` justo despues del bucle apunta al buffer como
        # string C: nos da el desplazamiento rbp->base de forma directa.
        hint = self._lea_hint(insns, end_n, base_reg)
        if hint is not None and hint not in cands:
            cands.insert(0, hint)
        for dl in cands:
            (span, pr, plaus), raw = score(dl)
            if span < (need or 1):
                continue
            key = (span, pr, plaus)
            if best is None or key > best[0]:
                best = (key, dl, bytes(raw))
        if best is None:
            return None
        _, delta, raw = best
        return ("stack", raw, (looplen if looplen else len(raw)),
                f"0x{self.insns[start_n].address:x}",
                self._find_key(insns, start_n, idxreg))

# --------------------------------------------------------------------------- #
def main():
    files = sys.argv[1:] or ["mem_bypass.bin", "mem_loader.bin"]
    allres = {}
    for f in files:
        img = open(f, "rb").read()
        base, secs = sections(img)
        ex = Extractor(img, base, secs)
        try:
            res = ex.run()
        except Exception as exc:
            print(f"[!] {f}: {exc}")
            continue
        allres[f] = res
        print(f"[+] {f}: {len(res)} cadenas extraidas del codigo")
        for r in sorted(res, key=lambda z: z["rva"]):
            print("  0x%06x  %-22s %r" % (r["rva"], r["where"], r["plain"]))
    return allres


if __name__ == "__main__":
    main()
