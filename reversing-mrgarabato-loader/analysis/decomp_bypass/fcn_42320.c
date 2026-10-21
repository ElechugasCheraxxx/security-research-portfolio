/* RVA 0x42320  tam 123 B  addr 0x140042320 */

ulong fcn.140042320(void)

{
    int iVar1;
    int64_t iVar2;
    int iVar3;
    uchar *puVar4;
    uchar *puVar5;
    ulong unaff_RBP;
    int iVar6;
    int64_t *piVar7;
    ulong auStack_38 [2];
    uchar auStack_28 [32];
    
    iVar6 = 0;
    iVar3 = 0;
    piVar7 = 0x140053be0;
    puVar4 = &stack0xffffffffffffffd8;
    do {
        puVar5 = puVar4;
        if (piVar7[1] == 1) {
            iVar2 = iVar6;
            iVar6 = iVar6 + 1;
            iVar2 = iVar2 * 0x28 + 0x1400569c0;
            *piVar7 = iVar2;
            puVar5 = puVar4 + -8;
            *(puVar4 + -8) = unaff_RBP;
            *(puVar4 + -0x10) = 0x14004236b;
            iVar1 = func_0x00014029801e(iVar2,4000);
            if (iVar1 == 0) {
                *(iVar3 * 0x10 + 0x140053be0) = 0;
                return 0;
            }
        }
        iVar3 = iVar3 + 1;
        piVar7 = piVar7 + 2;
        puVar4 = puVar5;
    } while (iVar3 < 0x24);
    return 1;
}
