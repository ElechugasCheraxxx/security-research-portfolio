/* RVA 0x3d42  tam 42 B  addr 0x140003d42 */

//WARNING: Control flow encountered bad instruction data

void fcn.140003d40(int64_t arg1)

{
    int64_t iVar1;
    uint uVar2;
    
    fcn.140001f10(arg1,arg1,*(*arg1 + 8));
    uVar2 = 0x60;
    fcn.1402c63c2(*arg1);
    fcn.1400292d0();
    fcn.1402df79d();
    fcn.140163b48();
    iVar1 = fcn.1402722af();
    LOCK();
    *(iVar1 + -0x18) = uVar2;
    UNLOCK();
    //WARNING: Bad instruction - Truncating control flow here
    halt_baddata();
}
