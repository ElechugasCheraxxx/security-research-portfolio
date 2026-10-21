/* RVA 0x30f60  tam 98 B  addr 0x140030f60 */

int64_t fcn.140030f60(int64_t arg1)

{
    code *pcVar1;
    int64_t iVar2;
    ulong auStackX_8 [4];
    ulong auStack_28 [5];
    
    if (arg1 == 0) {
        return 0;
    }
    if ((arg1 < 0x8000000000000000) && (iVar2 = func_0x00014003c76c(arg1 * 2), iVar2 != 0)) {
        return iVar2;
    }
    auStackX_8[0] = 0;
    fcn.14003d240(auStack_28,auStackX_8);
    auStack_28[0] = 0x140049418;
    fcn.14003dbcc(auStack_28,0x1400517f0);
    pcVar1 = swi(3);
    iVar2 = (*pcVar1)();
    return iVar2;
}
