/* RVA 0x364b6  tam 207 B  addr 0x1400364b6 */

ulong fcn.1400364b6(int64_t arg1,int64_t arg2)

{
    uchar auVar1 [16];
    uint32_t uVar2;
    uint uVar3;
    ulong uVar4;
    
    if (*arg1 != '#') {
        uVar4 = fcn.140287141(0,0,arg1,0xffffffff);
        if (uVar4 != 0) {
            auVar1._8_8_ = 0;
            auVar1._0_8_ = uVar4;
            uVar4 = SUB168(ZEXT816(2) * auVar1,0);
            if (SUB168(ZEXT816(2) * auVar1,8) != 0) {
                uVar4 = 0xffffffffffffffff;
            }
            uVar4 = fcn.14003c43c(uVar4);
            *arg2 = uVar4;
            uVar3 = fcn.140182148(0,0,arg1,0xffffffff);
            fcn.1401842e5(*arg2,uVar3);
            uVar4 = 1;
        }
        return uVar4;
    }
    uVar2 = fcn.14003d884(arg1 + 1,0,10);
    if (uVar2 >> 0x10 != 0) {
        return 0;
    }
    *arg2 = uVar2 & 0xffff;
    return 1;
}
