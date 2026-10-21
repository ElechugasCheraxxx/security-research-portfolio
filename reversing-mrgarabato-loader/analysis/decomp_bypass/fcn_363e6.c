/* RVA 0x363e6  tam 188 B  addr 0x1400363e6 */

//WARNING: Control flow encountered bad instruction data

ulong fcn.1400363e6(int64_t arg1,int64_t arg2,int64_t arg3)

{
    int16_t iVar1;
    uchar auVar2 [16];
    uint32_t uVar3;
    ulong uVar4;
    uint64_t uVar5;
    int16_t *piVar6;
    
    if (*arg1 == 0x23) {
        uVar3 = fcn.14003d570(arg1 + 2,0,10);
        if (uVar3 >> 0x10 != 0) {
            return 0;
        }
        *arg2 = uVar3 & 0xffff;
        return 1;
    }
    uVar5 = 0xffffffffffffffff;
    piVar6 = arg1;
    do {
        if (uVar5 == 0) break;
        uVar5 = uVar5 - 1;
        iVar1 = *piVar6;
        piVar6 = piVar6 + 1;
    } while (iVar1 != 0);
    uVar5 = ~uVar5;
    auVar2._8_8_ = 0;
    auVar2._0_8_ = uVar5;
    uVar4 = SUB168(ZEXT816(2) * auVar2,0);
    if (SUB168(ZEXT816(2) * auVar2,8) != 0) {
        uVar4 = 0xffffffffffffffff;
    }
    uVar4 = fcn.14003c43c(uVar4);
    *arg2 = uVar4;
    fcn.14003d57c(uVar4,uVar5,arg1);
    fcn.1401d8070(*arg2,uVar5 - 1 & 0xffffffff);
    //WARNING: Bad instruction - Truncating control flow here
    halt_baddata();
}
