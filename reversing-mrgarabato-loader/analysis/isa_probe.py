#!/usr/bin/env python3
"""isa_probe.py — determina si stage2_code.bin contiene una VM de ISA ACOTADA
(tabla de handlers acotada) o un decodificador de ISA ABIERTA (x86 completo).

Criterios:
  ACOTADA  -> tabla de punteros a codigo, indexada por un opcode;
              dispatch con multiplicacion por tamano de entrada (idx*N)
  ABIERTA  -> decodificacion de prefijos/ModRM/SIB de x86 (and 7, shr 3,
              tests contra 0xC0/0x40/0x00/0x0F...), sin tabla acotada
"""
import sys, struct, collections
from capstone import *
from capstone.x86 import X86_OP_REG, X86_OP_MEM, X86_OP_IMM

d = open(sys.argv[1] if len(sys.argv) > 1 else 'stage2_code.bin','rb').read()
BASE = 0
md = Cs(CS_ARCH_X86, CS_MODE_64); md.detail = True; md.skipdata = True

# chi2 correcto
c = collections.Counter(d); n = len(d); E = n/256
chi2 = sum((c.get(i,0)-E)**2/E for i in range(256))
H = -sum((v/n)*__import__('math').log2(v/n) for v in c.values())
print(f"archivo: {n} B   entropia={H:.3f}   chi2={chi2:,.0f}   (cifrado ~0-400)")

# desensamblado lineal (los handlers de VM son bloques planos)
ins = list(md.disasm(d, BASE))
print(f"instrucciones desensambladas: {len(ins)}  ({len(ins)*100//n}% del total)")

# 1) saltos indirectos  -> jmp/call con registro o memoria
ind_jmp = [i for i in ins if i.mnemonic in ('jmp','call')
           and i.operands and i.operands[0].type in (X86_OP_REG, X86_OP_MEM)]
print(f"\nsaltos/llamadas indirectos: {len(ind_jmp)}")
tgt_regs = collections.Counter()
for i in ind_jmp:
    o = i.operands[0]
    tgt_regs[i.mnemonic + ' ' + i.op_str] += 1
for k,v in tgt_regs.most_common(12): print(f"   {v:>4}x  {k}")

# 2) indices multiplicados (dispatch de tabla acotada):  imul/shl + reg, REG
scaled = [i for i in ins if i.mnemonic in ('imul','shl','lea','sal','sbb')]
mult = [i for i in scaled if ',' in i.op_str and
        any(t in i.op_str for t in ('* 4','* 8','*8','*4','* 16','* 0x10','*2','* 2','*16','* 2','* 32','* 0x20'))]
print(f"\noperaciones con escala x2..x32 (indice de tabla): {len(mult)}")
for i in mult[:10]: print(f"   0x{i.address:x}: {i.mnemonic} {i.op_str}")

# 3) decodificacion de ModRM/SIB -> ISA ABIERTA (x86)
xmldec = [i for i in ins if i.mnemonic in ('and','shr','sar','shl','or','xor')
          and any(t in i.op_str for t in ('7','0x7','0x1f','0x3f','0xc0','0x40','0x0f','0x1F','0x3F'))]
print(f"\noperaciones de mascarado de ModRM/prefijos (0x7/0x1F/0x3F/0xC0...): {len(xmldec)}")
for i in xmldec[:10]: print(f"   0x{i.address:x}: {i.mnemonic} {i.op_str}")

# 4) tablas de punteros a codigo candidatas
print(f"\ntablas de punteros (8 bytes dentro del rango del propio archivo):")
hits=[]
for off in range(0, n-8*16, 8):
    vals=[struct.unpack_from('<Q', d, off+8*k)[0] for k in range(16)]
    if all(BASE <= v < BASE+n for v in vals) and len(set(vals))==16:
        run=0; good=True
        while True:
            p=off+8*run
            if p+8>n: break
            v=struct.unpack_from('<Q', d, p)[0]
            if BASE <= v < BASE+n: run+=1
            else: break
        if run>=8: hits.append((off,run))
merged=[]
for o,r in hits:
    if merged and o <= merged[-1][0]+merged[-1][1]*8: 
        merged[-1]=(merged[-1][0], merged[-1][1]+r)
    else: merged.append((o,r))
merged=[(o,r) for o,r in merged if r>=8]
print(f"   candidatas: {len(merged)}")
for o,r in merged[:12]:
    v=struct.unpack_from('<Q',d,o)[0]
    print(f"   offset 0x{o:06x}  {r:>4} entradas  stride 8  -> 0x{v:x}")
if merged:
    best=max(merged,key=lambda t:t[1])
    print(f"\n   >>> la mayor: offset 0x{best[0]:06x}, {best[1]} entradas")
    print(f"   >>> si la usa el dispatch, la ISA tiene {best[1]} opcodes (ACOTADA)")
    for k in range(min(best[1],12)):
        print(f"        [{k:>3}] 0x{struct.unpack_from('<Q',d,best[0]+8*k)[0]:x}")
