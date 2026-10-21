#!/usr/bin/env python3
"""Recuperador del flujo de instrucciones para codigo con desincronizacion
(junk bytes / instrucciones solapadas tipicos de protectores de VM).

Idea: en cada posicion se puede elegir empezar la siguiente instruccion en
pos, pos+1, ... pos+14. Un beam-search con heuristicas de x86-64(user mode)
encuentra el alineamiento real y, sobre todo, el LOOP DEL DISPATCHER.
"""
import sys, heapq
from capstone import *
from capstone.x86 import *

img = open(sys.argv[1], "rb").read()
BASE = 0x140000000
md = Cs(CS_ARCH_X86, CS_MODE_64)
md.detail = True
md.skipdata = False

def _consts(*names):
    """Devuelve el subconjunto de constantes X86_INS_* que existan en esta
    version de capstone (evita NameError por simbolos ausentes)."""
    out = set()
    for n in names:
        v = globals().get(n)
        if v is not None:
            out.add(v)
    return out

GOOD = _consts("X86_INS_MOV", "X86_INS_LEA", "X86_INS_CALL", "X86_INS_JMP",
               "X86_INS_RET", "X86_INS_PUSH", "X86_INS_POP", "X86_INS_ADD",
               "X86_INS_SUB", "X86_INS_CMP", "X86_INS_TEST", "X86_INS_XOR",
               "X86_INS_AND", "X86_INS_OR", "X86_INS_MOVZX", "X86_INS_MOVSX",
               "X86_INS_JE", "X86_INS_JNE", "X86_INS_JZ", "X86_INS_JNZ",
               "X86_INS_NOP", "X86_INS_INT3", "X86_INS_IMUL", "X86_INS_SHR",
               "X86_INS_SHL", "X86_INS_ROL", "X86_INS_ROR", "X86_INS_LEAVE",
               "X86_INS_CMOVNE", "X86_INS_SETNE", "X86_INS_INC", "X86_INS_DEC",
               "X86_INS_CDQE", "X86_INS_CWDE", "X86_INS_CDQO", "X86_INS_MOVSXD",
               "X86_INS_BSWAP", "X86_INS_NOT", "X86_INS_NEG", "X86_INS_MUL",
               "X86_INS_MOVQ", "X86_INS_MOVL", "X86_INS_SHL", "X86_INS_OR")
PRIV = _consts("X86_INS_OUT", "X86_INS_IN", "X86_INS_HLT", "X86_INS_CLI",
               "X86_INS_STI", "X86_INS_LGDT", "X86_INS_LIDT", "X86_INS_INVD",
               "X86_INS_RDMSR", "X86_INS_WRMSR", "X86_INS_LMSW", "X86_INS_CLTS")
IMG_LO, IMG_HI = BASE, BASE + len(img)


def decode_at(off):
    try:
        ins = list(md.disasm(img[off:off + 15], BASE + off, count=1))
        return ins[0] if ins else None
    except Exception:
        return None


def score(i, depth):
    if i is None or i.id == 0:
        return -20
    s = 0
    if i.id in PRIV:
        s -= 15                      # invalido en user mode
    if i.id in GOOD:
        s += 4
    if i.id == X86_INS_RET:
        s += 12
    if i.id in (X86_INS_INT3, X86_INS_NOP):
        s += 3
    if i.mnemonic.startswith("j") and i.id not in (X86_INS_JMP,):
        # jcc con objetivo dentro de la imagen
        try:
            t = int(i.op_str, 16)
            if IMG_LO <= t < IMG_HI:
                s += 5
            else:
                s -= 6
        except ValueError:
            s -= 2
    if i.id in (X86_INS_CALL,):
        try:
            t = int(i.op_str, 16)
            s += 6 if IMG_LO <= t < IMG_HI else -8
        except ValueError:
            s += 1
    if i.id == X86_INS_JMP and i.bytes[0] == 0xFF:   # jmp indirecto = posible dispatch
        s += 25
    if i.id in (X86_INS_CALL,) and i.bytes[0] == 0xFF:
        s += 8
    # accesos a memoria con base/index 64-bit y escala 8 -> tablas de handlers
    for op in i.operands:
        if op.type == X86_OP_MEM and op.mem.scale == 8 and op.mem.base != 0:
            s += 6
        if op.type == X86_OP_MEM and op.mem.scale == 4 and op.mem.base != 0:
            s += 2
    if i.size > 12:
        s -= 4
    return s


def resync(start, length, beam=48):
    """Beam search: devuelve la mejor secuencia de instrucciones."""
    end = start + length
    # heap: (-score, pos, path)
    beam_list = [(0, start, [])]
    best = (0, start, [])
    seen_best = -1e9
    while beam_list:
        nxt = []
        for sc, pos, path in beam_list:
            if pos >= end:
                if sc > seen_best:
                    seen_best = sc
                    best = (sc, pos, path)
                continue
            for skip in range(0, 13):
                p = pos + skip
                if p >= end:
                    break
                i = decode_at(p)
                s = sc + score(i, len(path))
                if i is None or i.id == 0:
                    continue
                np_ = path + [i]
                nxt.append((s, p + i.size, np_))
        if not nxt:
            break
        nxt.sort(key=lambda t: -t[0])
        beam_list = nxt[:beam]
        if beam_list and beam_list[0][0] > seen_best:
            seen_best = beam_list[0][0]
            best = beam_list[0]
    return best[0], best[1], best[2]


if __name__ == "__main__":
    EP = int(sys.argv[2], 16) if len(sys.argv) > 2 else 0x960917
    LEN = int(sys.argv[3], 16) if len(sys.argv) > 3 else 0x400

    print(f"[*] resync desde RVA 0x{EP:x}, longitud 0x{LEN:x}\n")
    best_sc, _pos, path = resync(EP, LEN)
    sc = best_sc
    print(f"[*] mejor flujo: score={sc}  instr={len(path)}\n")
    for i in path[:70]:
        mark = ""
        if i.id == X86_INS_RET:
            mark = "   <== RET"
        if i.id == X86_INS_JMP and i.bytes[0] == 0xFF:
            mark = "   <== JMP INDIRECTO (dispatch)"
        for op in i.operands:
            if op.type == X86_OP_MEM and op.mem.scale == 8:
                mark = mark or "   <- acceso x8 (tabla)"
        print("  0x%x  %-24s %-9s %s%s" % (i.address, i.bytes.hex(), i.mnemonic, i.op_str, mark))