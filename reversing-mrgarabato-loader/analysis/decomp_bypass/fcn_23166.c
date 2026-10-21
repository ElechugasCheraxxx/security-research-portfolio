/* RVA 0x23166  tam 174 B  addr 0x140023166 */

int64_t fcn.140023150(int64_t arg1,int64_t arg2,int64_t arg3)

{
    int64_t iVar1;
    uchar auVar2 [16];
    ulong uVar3;
    int64_t iVar4;
    
    iVar1 = arg3 + *(arg1 + 8);
    auVar2._8_8_ = 0;
    auVar2._0_8_ = iVar1 + 1;
    uVar3 = SUB168(ZEXT816(2) * auVar2,0);
    if (SUB168(ZEXT816(2) * auVar2,8) != 0) {
        uVar3 = 0xffffffffffffffff;
    }
    iVar4 = fcn.14003c43c(uVar3);
    fcn.140041d50(iVar4,*arg1,*(arg1 + 8) * 2);
    fcn.140041d50(iVar4 + *(arg1 + 8) * 2,arg2,arg3 * 2);
    *(iVar4 + iVar1 * 2) = 0;
    fcn.14003c52c(*arg1);
    *arg1 = iVar4;
    *(arg1 + 8) = iVar1;
    return arg1;
}
