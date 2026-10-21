/* RVA 0x3c470  tam 54 B  addr 0x14003c470 */

void fcn.14003c470(int64_t arg1)

{
    code *pcVar1;
    int64_t aiStackX_8 [4];
    ulong auStack_28 [5];
    
    aiStackX_8[0] = arg1;
    fcn.14003d240(auStack_28,aiStackX_8);
    auStack_28[0] = 0x140049400;
    fcn.14003dbcc(auStack_28,0x140051720);
    pcVar1 = swi(3);
    (*pcVar1)();
    return;
}
