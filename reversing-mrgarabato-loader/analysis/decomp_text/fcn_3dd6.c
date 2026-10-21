/* RVA 0x3dd6  tam 522 B  addr 0x140003dd6 */

void fcn.140003dd6(int64_t arg1)

{
    uint64_t uVar1;
    code *pcVar2;
    int64_t iVar3;
    int64_t iVar4;
    int64_t iVar5;
    uint64_t uVar6;
    
    uVar1 = *(arg1 + 0xd8);
    if (0xf < uVar1) {
        iVar3 = *(arg1 + 0xc0);
        uVar6 = uVar1 + 1;
        iVar4 = iVar3;
        if (0xfff < uVar6) {
            iVar4 = *(iVar3 + -8);
            uVar6 = uVar1 + 0x28;
            iVar3 = iVar3 - iVar4;
            if (0x1f < iVar3 - 8U) goto code_r0x000140003fd8;
        }
        fcn.140015008(iVar4,uVar6);
    }
    *(arg1 + 0xd8) = 0xf;
    *(arg1 + 0xd0) = 0;
    *(arg1 + 0xc0) = 0;
    uVar1 = *(arg1 + 0xb8);
    if (0xf < uVar1) {
        iVar3 = *(arg1 + 0xa0);
        uVar6 = uVar1 + 1;
        iVar4 = iVar3;
        if (0xfff < uVar6) {
            iVar4 = *(iVar3 + -8);
            uVar6 = uVar1 + 0x28;
            iVar3 = iVar3 - iVar4;
            if (0x1f < iVar3 - 8U) goto code_r0x000140003fd8;
        }
        fcn.140015008(iVar4,uVar6);
    }
    *(arg1 + 0xb0) = 0;
    *(arg1 + 0xb8) = 0xf;
    *(arg1 + 0xa0) = 0;
    uVar1 = *(arg1 + 0x98);
    if (0xf < uVar1) {
        iVar3 = *(arg1 + 0x80);
        uVar6 = uVar1 + 1;
        iVar4 = iVar3;
        if (0xfff < uVar6) {
            iVar4 = *(iVar3 + -8);
            uVar6 = uVar1 + 0x28;
            iVar3 = iVar3 - iVar4;
            if (0x1f < iVar3 - 8U) goto code_r0x000140003fd8;
        }
        fcn.140015008(iVar4,uVar6);
    }
    *(arg1 + 0x90) = 0;
    *(arg1 + 0x98) = 0xf;
    *(arg1 + 0x80) = 0;
    uVar1 = *(arg1 + 0x78);
    if (0xf < uVar1) {
        iVar3 = *(arg1 + 0x60);
        uVar6 = uVar1 + 1;
        iVar4 = iVar3;
        if (0xfff < uVar6) {
            iVar4 = *(iVar3 + -8);
            uVar6 = uVar1 + 0x28;
            iVar3 = iVar3 - iVar4;
            if (0x1f < iVar3 - 8U) goto code_r0x000140003fd8;
        }
        fcn.140015008(iVar4,uVar6);
    }
    *(arg1 + 0x70) = 0;
    *(arg1 + 0x78) = 0xf;
    *(arg1 + 0x60) = 0;
    uVar1 = *(arg1 + 0x58);
    if (0xf < uVar1) {
        iVar3 = *(arg1 + 0x40);
        uVar6 = uVar1 + 1;
        iVar4 = iVar3;
        if (0xfff < uVar6) {
            iVar4 = *(iVar3 + -8);
            uVar6 = uVar1 + 0x28;
            iVar3 = iVar3 - iVar4;
            if (0x1f < iVar3 - 8U) goto code_r0x000140003fd8;
        }
        fcn.140015008(iVar4,uVar6);
    }
    *(arg1 + 0x50) = 0;
    *(arg1 + 0x58) = 0xf;
    *(arg1 + 0x40) = 0;
    uVar6 = *(arg1 + 0x38);
    if (0xf < uVar6) {
        iVar3 = *(arg1 + 0x20);
        iVar4 = iVar3;
        if (0xfff < uVar6 + 1) {
            iVar4 = *(iVar3 + -8);
            uVar6 = uVar6 + 0x28;
            iVar3 = iVar3 - iVar4;
            if (0x1f < iVar3 - 8U) {
code_r0x000140003fd8:
                func_0x000140238bf9(iVar3,uVar6);
                pcVar2 = swi(3);
                (*pcVar2)();
                return;
            }
        }
        fcn.140015008(iVar4);
    }
    *(arg1 + 0x30) = 0;
    *(arg1 + 0x38) = 0xf;
    *(arg1 + 0x20) = 0;
    if (7 < *(arg1 + 0x18)) {
        iVar4 = *arg1;
        iVar3 = *(arg1 + 0x18) * 2;
        iVar5 = iVar4;
        if (0xfff < iVar3 + 2U) {
            iVar5 = *(iVar4 + -8);
            if (0x1f < (iVar4 - iVar5) - 8U) {
                fcn.1402307a6(iVar4 - iVar5,iVar3 + 0x29);
                func_0x00010ccd60a1();
                pcVar2 = swi(3);
                (*pcVar2)();
                return;
            }
        }
        fcn.140015008(iVar5);
    }
    *(arg1 + 0x18) = 7;
    *(arg1 + 0x10) = 0;
    *arg1 = 0;
    return;
}
