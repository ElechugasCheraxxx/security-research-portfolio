#!/usr/bin/env python3
"""
decrypt_stack_strings2.py -- Descifra las cadenas de pila del loader.

Enfoque: desensamblar el .text con capstone, localizar los bucles

    lea  eax,[rcx-0x6d]
    xor  byte [rbp|rsp + rcx + disp], al
    inc  rcx
    cmp  rcx, N
    jb   ...

y para cada uno reconstruir el buffer de pila [base+disp .. +N) rastreando
hacia atras (hasta 80 instrucciones) las escrituras:

    mov dword/word/byte ptr [rbp|rsp + D], imm
    movdqa/movdqu xmmword ptr [rbp|rsp + D], xmm0   <- constante leida de .rdata
        (con su movdqa xmm0, [rip + D2] precedente)

Descifrado: buf[j] ^ ((j - 0x6d) & 0xff)
"""
import sys, re, struct
from capstone import Cs, CS_ARCH_X86, CS_MODE_64

md = Cs(CS_ARCH_X86, CS_MODE_64)
md.detail = False
md.skipdata = True


def disasm_all(text, base_rva):
    out = []
    for ins in md.disasm(text, base_rva):
        out.append(ins)
        if len(out) > 400000:
            break
    return out


def parse_mem(op):
    """De 'dword ptr [rbp - 0x4c]' o 'dword ptr [rbp + rcx - 0x50]' devuelve
    (reg_base, disp) si es [rbp+D] o [rsp+D] plano, si no None."""
    m = re.match(r'(byte|word|dword|xmmword) ptr \[(rbp|rsp)(?: \+ rcx)? ([+-]) (0x[0-9a-f]+)\]$', op)
    if not m:
        m = re.match(r'(byte|word|dword|xmmword) ptr \[(rbp|rsp)\]$', op)
        if m:
            return m.group(2), 0
        return None
    d = int(m.group(4), 16)
    if m.group(3) == '-':
        d = -d
    return m.group(2), d


def main():
    text = open(sys.argv[1], 'rb').read()
    base_rva = int(sys.argv[3], 0) if len(sys.argv) > 3 else 0x1000
    outp = sys.argv[2]
    rdata_lo, rdata_hi = 0x21000 - base_rva, 0x2E000 - base_rva   # .rdata en coords de offset
    if rdata_lo < 0:
        rdata_lo, rdata_hi = 0, len(text)

    insns = disasm_all(text, base_rva)
    idx = {id(i): k for k, i in enumerate(insns)}

    results = {}
    for k, ins in enumerate(insns):
        if ins.mnemonic != 'lea' or not ins.op_str.startswith('eax, [rcx'):
            continue
        m = re.match(r'eax, \[rcx ([+-]) (0x[0-9a-f]+)\]$', ins.op_str)
        if not m:
            continue
        delta = int(m.group(2), 16) * (1 if m.group(1) == '+' else -1)
        # siguiente instruccion debe ser xor byte [rbp|rsp + rcx + D], al
        if k + 1 >= len(insns):
            continue
        x = insns[k + 1]
        if x.mnemonic != 'xor':
            continue
        pm = parse_mem(x.op_str.split(', ')[0] if ', ' in x.op_str else '')
        if pm is None:
            mm = re.match(r'byte ptr \[(rbp|rsp) \+ rcx ([+-]) (0x[0-9a-f]+)\], al$', x.op_str)
            if not mm:
                continue
            base = mm.group(1)
            disp = int(mm.group(3), 16) * (1 if mm.group(2) == '+' else -1)
        else:
            base, disp = pm
        # N: buscar cmp rcx,N en las siguientes 6 instrucciones
        N = None
        for j in range(k + 2, min(k + 8, len(insns))):
            if insns[j].mnemonic == 'cmp' and insns[j].op_str.startswith('rcx, '):
                try:
                    N = int(insns[j].op_str.split(', ')[1], 0)
                except Exception:
                    N = None
                break
        if not N or N > 8192:
            continue

        buf = bytearray(b'\x00' * N)
        filled = [False] * N
        # rastrear hacia atras
        ripconst = None
        for j in range(k - 1, max(-1, k - 90), -1):
            q = insns[j]
            if q.mnemonic.startswith('movdqa') or q.mnemonic.startswith('movdqu'):
                if ', xmm0' in q.op_str and '[' in q.op_str:
                    pm2 = parse_mem(q.op_str.split(', ')[0])
                    if pm2 and pm2[0] == base and pm2[1] == disp:
                        # los 16 bytes vienen del movdqa xmm0,[rip+D] anterior
                        for w in range(j - 1, max(-1, j - 12), -1):
                            z = insns[w]
                            if z.mnemonic in ('movdqa', 'movdqu') and z.op_str.startswith('xmm0, [rip'):
                                mm2 = re.search(r'rip ([+-]) (0x[0-9a-f]+)\]$', z.op_str)
                                if mm2:
                                    tgt = z.address + z.size + (int(mm2.group(2), 16) if mm2.group(1) == '+' else -int(mm2.group(2), 16))
                                    off = tgt - base_rva
                                    if 0 <= off < len(text) - 16:
                                        b = text[off:off + 16]
                                        for t2 in range(min(16, N)):
                                            buf[t2] = b[t2]; filled[t2] = True
                                break
                        break
            if q.mnemonic == 'mov' or (q.mnemonic == 'mov' and ',' in q.op_str):
                if ', ' not in q.op_str:
                    continue
                dst, src = q.op_str.split(', ', 1)
                if not dst.startswith(('byte ptr', 'word ptr', 'dword ptr')):
                    continue
                pm2 = parse_mem(dst)
                if not pm2 or pm2[0] != base:
                    continue
                d2 = pm2[1]
                if not (disp <= d2 < disp + N):
                    continue
                try:
                    v = int(src, 0)
                except Exception:
                    continue
                off2 = d2 - disp
                if dst.startswith('dword'):
                    for t2 in range(4):
                        if off2 + t2 < N:
                            buf[off2 + t2] = (v >> (8 * t2)) & 0xff; filled[off2 + t2] = True
                elif dst.startswith('word'):
                    for t2 in range(2):
                        if off2 + t2 < N:
                            buf[off2 + t2] = (v >> (8 * t2)) & 0xff; filled[off2 + t2] = True
                else:
                    if off2 < N:
                        buf[off2] = v & 0xff; filled[off2] = True
        if not any(filled):
            continue
        dec = bytes((b ^ ((jj - 0x6d) & 0xff)) for jj, b in enumerate(buf))
        results[ins.address] = dec

    pr = lambda s: sum(1 for c in s if 32 <= c < 127) / max(1, len(s))
    good = 0
    with open(outp, 'w', encoding='utf-8', errors='replace') as fh:
        for a in sorted(results):
            dec = results[a].rstrip(b'\x00')
            if len(dec) < 3 or pr(dec) < 0.8:
                continue
            try:
                s = dec.decode('ascii')
            except Exception:
                continue
            fh.write("RVA 0x%06X  %r\n" % (a, s))
            good += 1
    print("[+] bucles=%d  cadenas legibles=%d -> %s" % (len(results), good, outp))


if __name__ == '__main__':
    main()
