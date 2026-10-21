/* RVA 0x43e3e  tam 497 B  addr 0x140043e3e */

void fcn.140043e3e(int64_t arg1,int64_t arg2)

{
    int *piVar1;
    int iVar2;
    uint32_t uVar3;
    int iVar4;
    int64_t iVar5;
    char *pcVar6;
    int64_t iVar7;
    uchar auStack_40 [32];
    int iStack_20;
    char acStack_1c [12];
    uint64_t uStack_10;
    
    uStack_10 = *0x140053bd0 ^ auStack_40;
    if ((*(arg2 + 0x18) & 0x40) == 0) {
        iVar2 = fcn.140043e08(arg2);
        iVar5 = 0x140053b70;
        if ((iVar2 == -1) || (iVar2 = fcn.140043e08(arg2), iVar2 == -2)) {
            iVar7 = 0x140053b70;
        }
        else {
            iVar2 = fcn.140043e08(arg2);
            uVar3 = fcn.140043e08(arg2);
            iVar7 = (uVar3 & 0x1f) * 0x58 + *((iVar2 >> 5) * 8 + 0x1400588e0);
        }
        if ((*(iVar7 + 0x38) & 0x7f) != 2) {
            iVar2 = fcn.140043e08(arg2);
            if ((iVar2 == -1) || (iVar2 = fcn.140043e08(arg2), iVar2 == -2)) {
                iVar7 = 0x140053b70;
            }
            else {
                iVar2 = fcn.140043e08(arg2);
                uVar3 = fcn.140043e08(arg2);
                iVar7 = (uVar3 & 0x1f) * 0x58 + *((iVar2 >> 5) * 8 + 0x1400588e0);
            }
            if ((*(iVar7 + 0x38) & 0x7f) != 1) {
                iVar2 = fcn.140043e08(arg2);
                if ((iVar2 != -1) && (iVar2 = fcn.140043e08(arg2), iVar2 != -2)) {
                    iVar2 = fcn.140043e08(arg2);
                    uVar3 = fcn.140043e08(arg2);
                    iVar5 = (uVar3 & 0x1f) * 0x58 + *((iVar2 >> 5) * 8 + 0x1400588e0);
                }
                if ((*(iVar5 + 8) & 0x80) != 0) {
                    iVar2 = func_0x000140045380(&iStack_20,acStack_1c,5,arg1 & 0xffff);
                    iVar4 = 0;
                    if ((iVar2 == 0) && (0 < iStack_20)) {
                        pcVar6 = acStack_1c;
                        do {
                            piVar1 = arg2 + 8;
                            *piVar1 = *piVar1 + -1;
                            if (*piVar1 < 0) {
                                uVar3 = func_0x00014003f47c(*pcVar6,arg2);
                            }
                            else {
                                **arg2 = *pcVar6;
                                uVar3 = **arg2;
                                *arg2 = *arg2 + 1;
                            }
                            if (uVar3 == 0xffffffff) break;
                            iVar4 = iVar4 + 1;
                            pcVar6 = pcVar6 + 1;
                        } while (iVar4 < iStack_20);
                    }
                    goto code_r0x00014004400f;
                }
                goto code_r0x000140043fe6;
            }
        }
        iVar2 = *(arg2 + 8) + -2;
        *(arg2 + 8) = iVar2;
        if (iVar2 < 0) {
code_r0x000140044004:
            func_0x00014004502c(arg1 & 0xffff,arg2);
            goto code_r0x00014004400f;
        }
        **arg2 = arg1;
    }
    else {
code_r0x000140043fe6:
        iVar2 = *(arg2 + 8) + -2;
        *(arg2 + 8) = iVar2;
        if (iVar2 < 0) goto code_r0x000140044004;
        **arg2 = arg1;
    }
    *arg2 = *arg2 + 2;
code_r0x00014004400f:
    fcn.140042300(uStack_10 ^ auStack_40);
    return;
}
