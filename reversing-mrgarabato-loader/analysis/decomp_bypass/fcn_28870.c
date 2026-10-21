/* RVA 0x28870  tam 31 B  addr 0x140028870 */

void fcn.140028870(ulong param_1,int64_t param_2)

{
    code *pcVar1;
    ulong uVar2;
    uchar unaff_BH;
    
    uVar2 = fcn.140171426();
    LOCK();
    *(param_2 + -0x21523f22) = unaff_BH;
    UNLOCK();
    fcn.1400312c0(uVar2);
    pcVar1 = swi(3);
    (*pcVar1)();
    return;
}
