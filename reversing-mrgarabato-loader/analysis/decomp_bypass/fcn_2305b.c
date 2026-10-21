/* RVA 0x2305b  tam 112 B  addr 0x14002305b */

int64_t fcn.140023050(int64_t arg1,int64_t arg2,int64_t arg3)

{
    uchar auVar1 [16];
    ulong uVar2;
    
    *(arg1 + 8) = arg3;
    *arg1 = 0;
    auVar1._8_8_ = 0;
    auVar1._0_8_ = arg3 + 1;
    uVar2 = SUB168(ZEXT816(2) * auVar1,0);
    if (SUB168(ZEXT816(2) * auVar1,8) != 0) {
        uVar2 = 0xffffffffffffffff;
    }
    uVar2 = fcn.14003c43c(uVar2);
    *arg1 = uVar2;
    fcn.140041d50(uVar2,arg2,*(arg1 + 8) * 2);
    *(*arg1 + *(arg1 + 8) * 2) = 0;
    return arg1;
}
