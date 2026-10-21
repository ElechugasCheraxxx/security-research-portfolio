#!/usr/bin/env python3
"""
trace_vm.py -- traza el dispatch del interprete VM de MrGarabato.

Mecanismo descubierto (ver INFORME_EMULACION.md):
    r10 = puntero al flujo de operandos nativos (8 bytes cada uno)
    rsi = puntero al flujo de bytecode codificado (byte a byte, XOR r9)
    r9b = clave XOR de decodificacion
    rbp = "PC" de la VM = direccion absoluta del handler actual
    r8  = indice/descriptor de la pila de la VM
    [rsp+r8] = pila de la VM

Bucle de dispatch (604 instrucciones nativas por op):
    mov  rdi,[r10] ; add r10,8 ; movzx r8d,byte[rsi] ; xor r8b,r9b ; ...
    mov  [rsp+r8],rdi
    sub  rsi,4 ; mov edx,[rsi] ; xor edx,r9d
    dec edx ; rol edx,3 ; not edx ; add edx,0x34f107eb
    add  rbp,rdx ; jmp rbp          <== evento de dispatch

Este script hookea cada instruccion, detecta los `jmp <reg64>` indirectos
(sitios de dispatch) y registra (destino, estado de la VM).
"""
import sys, os, struct, collections, json, argparse

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
from emulate_vm import (VMEmu, BASE, SIZE_OF_IMAGE, md, region, half, M_CODE_LO, M_CODE_HI)

# Snapshot de registros en cada dispatch. OJO: el orden aqui es el de la
# CODIFICACION x86-64 en modo register-direct (mod=11), que NO es el estandar:
#   0=rax 1=rcx 2=rdx 3=rbx 4=rsp 5=rbp 6=rsi 7=rdi
# y con REX.B -> 8..15 siguen la misma permutacion (r8 r9 r10 r11 r12 r13 r14 r15)
REGNAMES = ['rax', 'rcx', 'rdx', 'rbx', 'rsp', 'rbp', 'rsi', 'rdi',
            'r8', 'r9', 'r10', 'r11', 'r12', 'r13', 'r14', 'r15']
from unicorn.x86_const import *


class DispatchTracer:
    def __init__(self, emu):
        self.emu = emu
        self.uc = emu.uc
        self.events = []          # (src_rip, target, snapshot)
        self.n = 0
        self.regids = [self.regid(rn) for rn in REGNAMES]

    def hook(self, uc, addr, size, _):
        self.n += 1
        b = bytes(uc.mem_read(addr, 4))
        i = 0
        rexB = 0
        while i < 2 and 0x40 <= b[i] <= 0x4F:          # prefijos REX
            rexB = (b[i] >> 0) & 1
            i += 1
        if i >= len(b) or b[i] != 0xFF:
            return None
        modrm = b[i + 1]
        if ((modrm >> 3) & 7) != 4:                    # /4 = JMP r/m64
            return None
        if (modrm >> 6) & 3 != 3:                      # solo registro-directo
            return None
        ridx = (modrm & 7) | (rexB << 3)
        tgt = uc.reg_read(self.regids[ridx])
        if not (BASE <= tgt < BASE + SIZE_OF_IMAGE):
            return None
        snap = {rn: uc.reg_read(self.regids[k]) for k, rn in enumerate(REGNAMES)}
        rn = REGNAMES[ridx]
        # dispatch real de la VM: salta con rbp/r13 y el PC resultante cae
        # dentro del interprete
        if rn in ('rbp', 'r13') and (BASE + M_CODE_LO) <= tgt < (BASE + M_CODE_HI):
            self.events.append((addr, tgt, snap, rn))
        return None

    @staticmethod
    def regid(name):
        from unicorn import x86_const as x
        return getattr(x, 'UC_X86_REG_' + name.upper())


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--start', default='960917')
    ap.add_argument('--steps', type=int, default=300000)
    ap.add_argument('--out', default='vm_trace.txt')
    ap.add_argument('--json', default='vm_trace.json')
    a = ap.parse_args()

    emu = VMEmu()
    tr = DispatchTracer(emu)
    emu.uc.hook_add(__import__('unicorn').UC_HOOK_CODE, tr.hook)

    start = BASE + int(a.start, 16)
    print(f"[*] emulando desde 0x{start:x}, {a.steps} pasos ...", flush=True)
    err = emu.run(start, count=a.steps)
    print(f"[*] fin: {err}  pasos={emu.steps}  dispatches={len(tr.events)}")

    # ---- informe ----
    by_src = collections.Counter(s for s, _, _, _ in tr.events)
    targets = collections.Counter(t for _, t, _, _ in tr.events)
    print("\n[*] sitios de dispatch (instruccion que hace el salto indirecto):")
    for s, c in by_src.most_common(20):
        r = s - BASE
        ins = list(md.disasm(emu.img[r:r + 16], s, count=1))
        txt = "%s %s" % (ins[0].mnemonic, ins[0].op_str) if ins else "?"
        print("   0x%012x  x%-6d  %s" % (s, c, txt))

    print("\n[*] TOP 40 handlers mas visitados:")
    for t, c in targets.most_common(40):
        r = t - BASE
        ins = list(md.disasm(emu.img[r:r + 16], t, count=1))
        txt = "%s %s" % (ins[0].mnemonic, ins[0].op_str) if ins else "?"
        print("   0x%012x [rva %08x] x%-6d %s" % (t, r, c, txt))

    print("\n[*] handlers distintos: %d" % len(targets))

    # ---- volcado de la traza ----
    with open(os.path.join(HERE, a.out), "w") as f:
        f.write("# traza del dispatch de la VM -- MrGarabato\n")
        f.write("# inicio=0x%x pasos=%d eventos=%d\n" % (start, emu.steps, len(tr.events)))
        f.write("# idx rva_handler rva_origen reg rbp r10 rsi r9 r8 r13\n")
        for i, (s, t, snap, rn) in enumerate(tr.events):
            f.write("%6d  0x%08x  0x%08x  %-4s rbp=%012x r10=%012x rsi=%012x r9=%012x r8=%012x r13=%012x\n" % (
                i, t - BASE, s - BASE, rn, snap['rbp'], snap['r10'], snap['rsi'],
                snap['r9'], snap['r8'], snap['r13']))
    print("[+] traza -> %s" % a.out)

    with open(os.path.join(HERE, a.json), "w") as f:
        json.dump([[hex(s), hex(t)] for s, t, _, _ in tr.events], f)


if __name__ == '__main__':
    main()