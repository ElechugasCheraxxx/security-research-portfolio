/* RVA 0x156cc  tam 113 B  addr 0x1400156cc */

//WARNING: Instruction at (ram,0x000140015731) overlaps instruction at (ram,0x000140015729)
//

void fcn.1400156c8(int64_t arg1)

{
    ulong uVar1;
    ulong uVar2;
    ulong unaff_retaddr;
    uchar auStackX_8 [8];
    uchar auStackX_10 [24];
    
    fcn.1401691dc();
    uVar1 = *(arg1 + 0xf8);
    uVar2 = fcn.1402067bb(uVar1,&stack0x00000000,0);
    out(0x48,uVar2);
    if (uVar2 != 0) {
        *0x48b17c02ff83c7ff = fcn.140047c4a(0,unaff_retaddr,uVar1,uVar2,arg1,auStackX_10,auStackX_8,0);
    }
    return;
}
