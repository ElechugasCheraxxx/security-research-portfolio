/* RVA 0x230cb  tam 117 B  addr 0x1400230cb */

int64_t fcn.1400230c0(int64_t arg1,int64_t arg2)

{
    int64_t iVar1;
    uchar auVar2 [16];
    ulong uVar3;
    
    *arg1 = 0;
    iVar1 = *(arg2 + 8);
    *(arg1 + 8) = iVar1;
    auVar2._8_8_ = 0;
    auVar2._0_8_ = iVar1 + 1;
    uVar3 = SUB168(ZEXT816(2) * auVar2,0);
    if (SUB168(ZEXT816(2) * auVar2,8) != 0) {
        uVar3 = 0xffffffffffffffff;
    }
    uVar3 = fcn.14003c43c(uVar3);
    *arg1 = uVar3;
    fcn.140041d50(uVar3,*arg2,*(arg1 + 8) * 2);
    *(*arg1 + *(arg1 + 8) * 2) = 0;
    return arg1;
}
