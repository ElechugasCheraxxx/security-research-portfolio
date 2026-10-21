/* RVA 0x3f48f  tam 378 B  addr 0x14003f48f */

uint64_t fcn.14003f48f(ulong noname_0,int64_t arg1)

{
    uint32_t uVar1;
    uint32_t uVar2;
    int iVar3;
    int iVar4;
    uint *puVar5;
    int64_t iVar6;
    uint8_t auStackX_10 [24];
    
    uVar2 = func_0x000140043e08(arg1);
    uVar1 = *(arg1 + 0x18);
    if ((uVar1 & 0x82) == 0) {
        puVar5 = fcn.14003ef2c();
        *puVar5 = 9;
    }
    else if ((uVar1 & 0x40) == 0) {
        iVar4 = 0;
        if ((uVar1 & 1) != 0) {
            *(arg1 + 8) = 0;
            if ((uVar1 & 0x10) == 0) {
                *(arg1 + 0x18) = uVar1 | 0x20;
                return 0xffffffff;
            }
            *arg1 = *(arg1 + 0x10);
            *(arg1 + 0x18) = uVar1 & 0xfffffffe;
        }
        uVar1 = *(arg1 + 0x18);
        *(arg1 + 8) = 0;
        *(arg1 + 0x18) = uVar1 & 0xffffffef | 2;
        if (((uVar1 & 0x10c) == 0) &&
           (((iVar6 = func_0x000140043bf4(), arg1 != iVar6 + 0x30 &&
             (iVar6 = func_0x000140043bf4(), arg1 != iVar6 + 0x60)) ||
            (iVar3 = func_0x000140043b94(uVar2), iVar3 == 0)))) {
            func_0x000140043b40(arg1);
        }
        if ((*(arg1 + 0x18) & 0x108) == 0) {
            iVar3 = 1;
            iVar4 = func_0x000140043a60(uVar2,auStackX_10,1);
        }
        else {
            iVar3 = *arg1 - *(arg1 + 0x10);
            *arg1 = *(arg1 + 0x10) + 1;
            *(arg1 + 8) = *(arg1 + 0x24) + -1;
            if (iVar3 < 1) {
                if ((uVar2 == 0xffffffff) || (uVar2 == 0xfffffffe)) {
                    iVar6 = 0x140053b70;
                }
                else {
                    iVar6 = (uVar2 & 0x1f) * 0x58 + *((uVar2 >> 5) * 8 + 0x1400588e0);
                }
                if (((*(iVar6 + 8) & 0x20) != 0) && (iVar6 = func_0x00014004321c(uVar2,0,2), iVar6 == -1))
                goto code_r0x00014003f4b4;
            }
            else {
                iVar4 = func_0x000140043a60(uVar2,*(arg1 + 0x10),iVar3);
            }
            **(arg1 + 0x10) = auStackX_10[0];
        }
        if (iVar4 == iVar3) {
            return auStackX_10[0];
        }
    }
    else {
        puVar5 = fcn.14003ef2c();
        *puVar5 = 0x22;
    }
code_r0x00014003f4b4:
    *(arg1 + 0x18) = *(arg1 + 0x18) | 0x20;
    return 0xffffffff;
}
