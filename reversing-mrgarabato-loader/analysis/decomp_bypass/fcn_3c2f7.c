/* RVA 0x3c2f7  tam 268 B  addr 0x14003c2f7 */

void fcn.14003c2f7(int64_t arg1,int64_t arg2)

{
    int64_t iVar1;
    uchar auVar2 [16];
    ulong uVar3;
    int64_t iVar4;
    uint64_t uVar5;
    uint64_t uVar6;
    uint64_t uVar7;
    
    iVar4 = *(arg1 + 8);
    if (*(arg1 + 0x10) == iVar4) {
        uVar6 = 1;
        if (iVar4 != 0) {
            uVar6 = iVar4 * 2;
        }
        auVar2._8_8_ = 0;
        auVar2._0_8_ = uVar6;
        uVar3 = SUB168(ZEXT816(0x18) * auVar2,0);
        if (SUB168(ZEXT816(0x18) * auVar2,8) != 0) {
            uVar3 = 0xffffffffffffffff;
        }
        iVar4 = fcn.14003c43c(uVar3);
        uVar7 = 0;
        if (iVar4 == 0) {
            iVar4 = 0;
        }
        else if (-1 < uVar6 + -1) {
            fcn.14003f620(iVar4,0,(uVar6 & 0xffffffff) * 0x18);
        }
        if (*(arg1 + 0x10) != 0) {
            uVar5 = uVar7;
            do {
                iVar1 = *arg1;
                uVar7 = uVar7 + 1;
                *(uVar5 + iVar4) = *(uVar5 + iVar1);
                *(uVar5 + 8 + iVar4) = *(uVar5 + 8 + iVar1);
                *(uVar5 + 0x10 + iVar4) = *(uVar5 + 0x10 + iVar1);
                uVar5 = uVar5 + 0x18;
            } while (uVar7 < *(arg1 + 0x10));
        }
        fcn.14003c52c(*arg1);
        *arg1 = iVar4;
        *(arg1 + 8) = uVar6;
    }
    iVar4 = *(arg1 + 0x10);
    iVar1 = *arg1;
    *(iVar1 + iVar4 * 0x18) = *arg2;
    *(iVar1 + 8 + iVar4 * 0x18) = *(arg2 + 8);
    *(iVar1 + 0x10 + iVar4 * 0x18) = *(arg2 + 0x10);
    *(arg1 + 0x10) = *(arg1 + 0x10) + 1;
    return;
}
