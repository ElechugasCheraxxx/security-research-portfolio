/* RVA 0x40dde  tam 57 B  addr 0x140040dde */

void fcn.140040ddc(int64_t arg1)

{
    int64_t iVar1;
    code *pcVar2;
    uchar auStack_a5 [109];
    ulong uStack_38;
    ulong uStack_30;
    
    uStack_30 = 0x140049908;
    uStack_38 = 0x140040df1;
    iVar1 = fcn.140047aa3();
    if (iVar1 != 0) {
        uStack_38 = 0x140040e05;
        pcVar2 = fcn.1401df404(iVar1,0x1400498f8);
        *(pcVar2 + -0x7b) = *(pcVar2 + -0x7b) - iVar1;
        (&stack0xffffffffffffff5b)[pcVar2] = 0;
        uStack_38 = 0x140040e0f;
        (*pcVar2)();
    }
    return;
}
