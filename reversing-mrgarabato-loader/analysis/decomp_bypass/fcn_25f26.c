/* RVA 0x25f26  tam 167 B  addr 0x140025f26 */

void fcn.140025f26(int64_t arg1,int64_t arg2)

{
    uchar auVar1 [16];
    ulong uVar2;
    int64_t iVar3;
    uint64_t uVar4;
    uint64_t uVar5;
    
    iVar3 = *(arg1 + 8);
    if (*(arg1 + 0x10) == iVar3) {
        uVar4 = 1;
        if (iVar3 != 0) {
            uVar4 = iVar3 * 2;
        }
        auVar1._8_8_ = 0;
        auVar1._0_8_ = uVar4;
        uVar2 = SUB168(ZEXT816(8) * auVar1,0);
        if (SUB168(ZEXT816(8) * auVar1,8) != 0) {
            uVar2 = 0xffffffffffffffff;
        }
        iVar3 = fcn.14003c43c(uVar2);
        uVar5 = 0;
        if (*(arg1 + 0x10) != 0) {
            do {
                uVar5 = uVar5 + 1;
                *(iVar3 + -8 + uVar5 * 8) = *(*arg1 + -8 + uVar5 * 8);
            } while (uVar5 < *(arg1 + 0x10));
        }
        fcn.14003c52c(*arg1);
        *arg1 = iVar3;
        *(arg1 + 8) = uVar4;
    }
    *(*arg1 + *(arg1 + 0x10) * 8) = *arg2;
    *(arg1 + 0x10) = *(arg1 + 0x10) + 1;
    return;
}
