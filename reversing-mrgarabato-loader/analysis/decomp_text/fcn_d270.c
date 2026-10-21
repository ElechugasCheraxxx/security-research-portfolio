/* RVA 0xd270  tam 64 B  addr 0x14000d270 */

//WARNING: Control flow encountered bad instruction data

void fcn.14000d270(ulong noname_0,int64_t arg1,int64_t arg2)

{
    code *pcVar1;
    int64_t iVar2;
    uint uVar3;
    uint64_t uVar4;
    
    uVar4 = arg2 + 1;
    iVar2 = arg1;
    if (0xfff < uVar4) {
        iVar2 = *(arg1 + -8);
        uVar4 = arg2 + 0x28;
        if (0x1f < (arg1 - iVar2) - 8U) {
            fcn.1401a8006();
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
