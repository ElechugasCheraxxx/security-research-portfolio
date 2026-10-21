/* RVA 0x4502c  tam 399 B  addr 0x14004502c */

uint64_t fcn.14004502c(int64_t arg1,int64_t arg2)

{
    uint32_t uVar1;
    uint32_t uVar2;
    int iVar3;
    int iVar4;
    uint *puVar5;
    int64_t iVar6;
    ushort auStackX_10 [4];
    
    uVar2 = fcn.140043e08(arg2);
    uVar1 = *(arg2 + 0x18);
    if ((uVar1 & 0x82) == 0) {
        puVar5 = fcn.14003ef2c();
        *puVar5 = 9;
    }
    else if ((uVar1 & 0x40) == 0) {
        iVar4 = 0;
        if ((uVar1 & 1) != 0) {
            *(arg2 + 8) = 0;
            if ((uVar1 & 0x10) == 0) {
                *(arg2 + 0x18) = uVar1 | 0x20;
                return 0xffff;
            }
            *arg2 = *(arg2 + 0x10);
            *(arg2 + 0x18) = uVar1 & 0xfffffffe;
        }
        uVar1 = *(arg2 + 0x18);
        *(arg2 + 8) = 0;
        *(arg2 + 0x18) = uVar1 & 0xffffffef | 2;
        if (((uVar1 & 0x10c) == 0) &&
           (((iVar6 = func_0x000140043bf4(), arg2 != iVar6 + 0x30 &&
             (iVar6 = func_0x000140043bf4(), arg2 != iVar6 + 0x60)) || (iVar3 = fcn.140043b94(uVar2), iVar3 == 0)))) {
            fcn.140043b40(arg2);
        }
        if ((*(arg2 + 0x18) & 0x108) == 0) {
            iVar3 = 2;
            auStackX_10[0] = arg1;
            iVar4 = func_0x000140043a60(uVar2,auStackX_10,2);
        }
        else {
            iVar3 = *arg2 - *(arg2 + 0x10);
            *arg2 = *(arg2 + 0x10) + 2;
            *(arg2 + 8) = *(arg2 + 0x24) + -2;
            if (iVar3 < 1) {
                if ((uVar2 == 0xffffffff) || (uVar2 == 0xfffffffe)) {
                    iVar6 = 0x140053b70;
                }
                else {
                    iVar6 = (uVar2 & 0x1f) * 0x58 + *((uVar2 >> 5) * 8 + 0x1400588e0);
                }
                if (((*(iVar6 + 8) & 0x20) != 0) && (iVar6 = func_0x00014004321c(uVar2,0,2), iVar6 == -1))
                goto code_r0x000140045062;
            }
            else {
                iVar4 = func_0x000140043a60(uVar2,*(arg2 + 0x10),iVar3);
            }
            **(arg2 + 0x10) = arg1;
        }
        if (iVar4 == iVar3) {
            return arg1 & 0xffff;
        }
    }
    else {
        puVar5 = fcn.14003ef2c();
        *puVar5 = 0x22;
    }
code_r0x000140045062:
    *(arg2 + 0x18) = *(arg2 + 0x18) | 0x20;
    return 0xffff;
}
