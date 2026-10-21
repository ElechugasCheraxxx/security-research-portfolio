/* RVA 0x37eb0  tam 136 B  addr 0x140037eb0 */

int64_t fcn.140037ea0(int64_t arg1,int64_t arg2,int64_t arg3)

{
    int16_t iVar1;
    uchar auVar2 [16];
    ulong uVar3;
    uint64_t uVar4;
    int16_t *piVar5;
    
    *arg1 = 0;
    uVar4 = 0xffffffffffffffff;
    piVar5 = arg2;
    do {
        if (uVar4 == 0) break;
        uVar4 = uVar4 - 1;
        iVar1 = *piVar5;
        piVar5 = piVar5 + 1;
    } while (iVar1 != 0);
    *(arg1 + 8) = ~uVar4 - 1;
    auVar2._8_8_ = 0;
    auVar2._0_8_ = ~uVar4;
    uVar3 = SUB168(ZEXT816(2) * auVar2,0);
    if (SUB168(ZEXT816(2) * auVar2,8) != 0) {
        uVar3 = 0xffffffffffffffff;
    }
    uVar3 = fcn.14003c43c(uVar3);
    *arg1 = uVar3;
    fcn.140041d50(uVar3,arg2,*(arg1 + 8) * 2);
    *(*arg1 + *(arg1 + 8) * 2) = 0;
    return arg1;
}
