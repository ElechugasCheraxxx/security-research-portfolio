/* RVA 0x1a7fc  tam 107 B  addr 0x14001a7fc */

void fcn.14001a7fc(uint param_1,ulong param_2)

{
    int iVar1;
    uint unaff_retaddr;
    uchar auStackX_8 [32];
    
    func_0x000140546344();
    func_0x0001405a3c1a();
    iVar1 = func_0x0001400469be(L"!x-sys-default-locale",0x20000001,auStackX_8);
    if (iVar1 == 0) {
        unaff_retaddr = 0;
    }
    func_0x0001405c5304(0x1300,0,param_1,unaff_retaddr,param_2,0,0);
    return;
}
