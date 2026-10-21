#!/usr/bin/env python3
"""
c_15_rutina.py -- (a) mapa completo del final de .rdata
                 (b) busqueda de bucles byte-a-byte (XOR/ADD/SUB) en .text
"""
import numpy as np, re, struct
from capstone import Cs, CS_ARCH_X86, CS_MODE_64

RUN = "/root/mrgarabato_analysis/run/"
raw = open(RUN+"stage3/wine__w7.bin","rb").read()
img = open(RUN+"loader_solo_text.exe","rb").read()

print("="*78); print("A. VERIFICACION dump<->loader_solo_text.exe"); print("="*78)
# .text del dump empieza en RVA 0x1200 segun el desplazamiento del blob (0x227A0+0x1200)
for shift in (0, 0x200, 0x1000, 0x1200):
    a = raw[0:0x20000]; b = img[shift:shift+0x20000]
    eq = sum(1 for x,y in zip(a,b) if x==y)
    print(f"  dump[0:0x20000] vs img[0x{shift:X}:] -> {eq/len(a)*100:.2f}% iguales")

print("\n"+"="*78); print("B. MAPA DEL FINAL DE .rdata (0x22900-0x22E00)"); print("="*78)
def kind(b):
    if all(x==0 for x in b): return "ZERO    "
    if all(32<=x<127 for x in b): return "ANSI    "
    if len(b)%2==0:
        w=[b[i]|(b[i+1]<<8) for i in range(0,len(b),2)]
        if all(x==0 or 32<=x<127 for x in w): return "W16     "
    if len(b)%8==0:
        v=[struct.unpack_from("<Q",b,i)[0] for i in range(0,len(b),8)]
        if all(0x140000000<=x<0x140800000 for x in v): return "PTR64   "
    return "BIN     "
LO,HI=0x22900,0x22E00
segs=[]
for o in range(LO,HI,16):
    segs.append((o,kind(raw[o:o+16])))
i=0
while i<len(segs):
    j=i
    while j+1<len(segs) and segs[j+1][1]==segs[i][1]: j+=1
    a,bb=segs[i][0],segs[j][0]+16
    print(f"  0x{a:06X}-0x{bb-1:06X} ({bb-a:5d} B) {segs[i][1]}")
    i=j+1

print("\n  volcado legible de los bloques BIN:")
for o in range(LO,HI,16):
    b=raw[o:o+16]
    if kind(b)!="BIN     " or all(x==0 for x in b): continue
    print(f"    {o:06x}: {b.hex(' '):<47} {''.join(chr(c) if 32<=c<127 else '.' for c in b)}")

print("\n"+"="*78); print("C. BUSQUEDA DE BUCLES BYTE-A-BYTE EN .text"); print("="*78)
CODE = img[0x1000:0x1000+0x2086C]
BASE = 0x1000
md = Cs(CS_ARCH_X86, CS_MODE_64)
md.detail = False
insns = list(md.disasm(CODE, BASE))
print(f"  {len(insns)} instrucciones desensambladas en .text")

# 1) instrucciones que operan byte a byte sobre memoria con XOR/ADD/SUB
byteops = []
for ins in insns:
    m = ins.mnemonic
    if m in ("xor","add","sub","rol","ror","not","neg","inc","dec","adc","sbb"):
        if "byte ptr" in ins.op_str and "[" in ins.op_str:
            byteops.append(ins)
print(f"  operaciones byte-a-byte sobre memoria: {len(byteops)}")
for ins in byteops[:60]:
    print(f"    0x{ins.address:06X}: {ins.mnemonic:8s} {ins.op_str}")

# 2) cadenas de 3+ instrucciones consecutivas de ese tipo (patron de bucle)
print("\n  rachas de >=3 operaciones byte-a-byte consecutivas (posible bucle):")
runs=[]; cur=[]
prev=None
for ins in insns:
    isb = (ins.mnemonic in ("xor","add","sub","rol","ror","not","neg","adc","sbb")
           and "byte ptr" in ins.op_str and "[" in ins.op_str)
    if isb:
        if prev is not None and ins.address != prev + prev.size:
            if len(cur)>=3: runs.append(cur)
            cur=[]
        cur.append(ins); prev=ins
    else:
        if len(cur)>=3: runs.append(cur)
        cur=[]; prev=None
if len(cur)>=3: runs.append(cur)
print(f"    {len(runs)} rachas")
for r in runs[:40]:
    print(f"    --- en 0x{r[0].address:06X}")
    for ins in r: print(f"        {ins.address:06X}: {ins.mnemonic:8s} {ins.op_str}")

# 3) inmedatos 0x10 / 16 junto a aritmetica de bytes
print("\n  inmedatos 0x10 en .text:", sum(1 for ins in insns if ins.mnemonic=='mov' and ins.op_str.endswith(', 0x10')),
      " add ...,0x10:", sum(1 for ins in insns if ins.mnemonic=='add' and ins.op_str.endswith(', 0x10')),
      " cmp ...,0x10:", sum(1 for ins in insns if ins.mnemonic=='cmp' and ins.op_str.endswith(', 0x10')))

# 4) ¿inmediatos que codifiquen el offset de los blobs?
print("\n  inmedatos sospechosos (0x7A0/0x3A0/0xA50/0x250/0x237A0/0x23A50/0x27A0/0x2A50):")
targets={0x7A0,0x3A0,0xA50,0x250,0x27A0,0x2A50,0x237A0,0x23A50,0x1A0,0x150}
for ins in insns:
    m=re.search(r"(0x[0-9a-fA-F]+|\d+)$", ins.op_str)
    if not m: continue
    try: v=int(m.group(1),0)
    except: continue
    if v in targets:
        print(f"    0x{ins.address:06X}: {ins.mnemonic} {ins.op_str}")
