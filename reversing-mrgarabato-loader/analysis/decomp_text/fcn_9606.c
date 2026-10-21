/* RVA 0x9606  tam 178 B  addr 0x140009606 */

//WARNING: Control flow encountered bad instruction data

int * fcn.1400095c0(ulong noname_0,int64_t arg1,int64_t arg2)

{
    int iVar1;
    int64_t iVar2;
    uint uVar3;
    
    iVar2 = arg1;
    if (0xfff < arg2) {
        iVar2 = *(arg1 + -8);
        arg2 = arg2 + 0x27;
        if (0x1f < (arg1 - iVar2) - 8U) {
            fcn.14012593e();
            func_0x000188cd62cd();
            if (arg2 == 0) {
                *arg1 = 0;
                *(arg1 + 8) = 0x40020120;
                *(arg1 + 0xc) = 1;
                return arg1;
            }
            iVar1 = fcn.140014f79(arg2 & 0xffffffff);
            if (iVar1 != 0) {
                *arg1 = iVar1;
                *(arg1 + 8) = 0x40020120;
                *(arg1 + 0xc) = 1;
                return arg1;
            }
            *arg1 = arg2;
            *(arg1 + 8) = 0x40020130;
            *(arg1 + 0xc) = 1;
            return arg1;
        }
    }
    uVar3 = arg2;
    fcn.1402c63c2(iVar2);
    fcn.1400292d0();
    fcn.1402df79d();
    fcn.140163b48();
    iVar2 = fcn.1402722af();
    LOCK();
    *(iVar2 + -0x18) = uVar3;
    UNLOCK();
    //WARNING: Bad instruction - Truncating control flow here
    halt_baddata();
}
