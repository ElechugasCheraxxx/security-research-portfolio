/* RVA 0x9300  tam 67 B  addr 0x140009300 */

//WARNING: Control flow encountered bad instruction data

void fcn.140009300(ulong noname_0,int64_t arg1)

{
    code *pcVar1;
    int64_t iVar2;
    uint uVar3;
    uint64_t uVar4;
    int64_t in_R8;
    
    uVar4 = in_R8 * 2 + 2;
    iVar2 = arg1;
    if (0xfff < uVar4) {
        iVar2 = *(arg1 + -8);
        uVar4 = in_R8 * 2 + 0x29;
        if (0x1f < (arg1 - iVar2) - 8U) {
            fcn.14022d34c();
            pcVar1 = swi(3);
            (*pcVar1)();
            return;
        }
    }
    uVar3 = uVar4;
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
