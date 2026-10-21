#!/usr/bin/env python3
"""Desensambla hacia atras desde un ancla conocida (final de instruccion),
intentando todos los inicios posibles y eligiendo el que produce un
stream que termina exactamente en el ancla con una instruccion de 2 bytes
call reg (ff d0..ff d7)."""
import sys
from capstone import *
data=open('mem_bypass.bin','rb').read()
md=Cs(CS_ARCH_X86,CS_MODE_64); md.detail=False

def decode_to(end, maxback=0x600):
    """devuelve (instrucciones, offset_inicio) para el desensamblado que
    termina exactamente en `end` con ff d0..d7"""
    best=None
    for start in range(max(0,end-maxback), end-1):
        blob=data[start:end]
        ins=list(md.disasm(blob, 0x140000000+start))
        if not ins: continue
        if ins[-1].address+ins[-1].size != 0x140000000+end: continue
        if ins[-1].bytes[0]!=0xFF or not (0xd0<=ins[-1].bytes[1]<=0xd7): continue
        # penaliza secuencias invalidas (basura)
        bad=0
        for i in ins[:-1]:
            if i.mnemonic in ('db','.byte'): bad+=1
        score=len(ins)-bad*100
        if best is None or score>best[0]: best=(score,start,ins)
    return best

if __name__=='__main__':
    for arg in sys.argv[1:]:
        rva=int(arg,16)
        r=decode_to(rva)
        if not r: print(f"--- RVA {rva:X}: sin desensamblado valido"); continue
        _,start,ins=r
        print(f"--- RVA {rva:X}: {len(ins)} insns desde 0x{start:X}")
        for i in ins: print(f"  {i.address-BASE:08X}  {i.bytes.hex():<22s} {i.mnemonic:8s} {i.op_str}")
