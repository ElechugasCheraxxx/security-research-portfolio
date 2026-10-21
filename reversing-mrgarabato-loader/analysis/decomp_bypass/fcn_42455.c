/* RVA 0x42455  tam 254 B  addr 0x140042455 */

//WARNING: Instruction at (ram,0x000140042516) overlaps instruction at (ram,0x000140042514)
//

uint32_t fcn.14004242c(int64_t arg1)

{
    ulong uVar1;
    int iVar2;
    uint32_t uVar3;
    int64_t iVar4;
    uint64_t arg1_00;
    uint *puVar5;
    ulong unaff_RSI;
    ulong unaff_RDI;
    ulong unaff_R13;
    uint8_t uVar6;
    float10 in_ST0;
    int64_t unaff_retaddr;
    
    iVar2 = *(arg1 * 0x10 + 0x140053be0);
    iVar4 = func_0x000140158e27();
    *(iVar4 + -0x77) = in_ST0;
    *(unaff_retaddr + 0x10) = unaff_RSI;
    *(unaff_retaddr + 0x18) = unaff_RDI;
    *(unaff_retaddr + -8) = unaff_R13;
    if (*0x1400569b8 == 0) {
        *(unaff_retaddr + -0x30) = 0x140042470;
        fcn.140042fb0();
        *(unaff_retaddr + -0x30) = 0x140042478;
        fcn.140042d50(0x1e);
        *(unaff_retaddr + -0x30) = 0x140042482;
        fcn.140040e18(0xff);
    }
    if (*(iVar2 * 0x10 + 0x140053be0) == 0) {
        *(unaff_retaddr + -0x30) = 0x1400424a5;
        arg1_00 = func_0x000140040c50(0x28);
        if (arg1_00 == 0) {
            *(unaff_retaddr + -0x30) = 0x1400424b2;
            puVar5 = fcn.14003ef2c();
            *puVar5 = 0xc;
            uVar3 = 0;
        }
        else {
            *(unaff_retaddr + -0x30) = 0x1400424c6;
            fcn.14004252c(10);
            uVar6 = 0;
            if (*(iVar2 * 0x10 + 0x140053be0) == 0) {
                *(unaff_retaddr + -0x30) = 0x1400424dc;
                func_0x0001402cc11c(arg1_00,4000);
                *(unaff_retaddr + -0x30) = 0x1400424e9;
                fcn.14003dc60(arg1_00 & 0xffffffff);
                *(unaff_retaddr + -0x30) = 0x1400424ee;
                puVar5 = fcn.14003ef2c();
                *puVar5 = 0xc;
                uVar6 = 0;
            }
            else {
                *(unaff_retaddr + -0x30) = 0x140042504;
                fcn.14003dc60(arg1_00);
            }
            uVar1 = *0x140053c80;
            *(unaff_retaddr + -0x30) = 0x140042511;
            iVar2 = func_0x000140220b1c(uVar1);
            uVar3 = (iVar2 + 0x74b77c15) - uVar6 & 0xffffff30;
        }
    }
    else {
        uVar3 = 1;
    }
    return uVar3;
}
