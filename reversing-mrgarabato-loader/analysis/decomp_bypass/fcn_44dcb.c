/* RVA 0x44dcb  tam 170 B  addr 0x140044dcb */

int fcn.140044dc0(void)

{
    int64_t iVar1;
    int iVar2;
    int iVar3;
    uchar *puVar4;
    uchar *puVar5;
    int64_t iVar6;
    int iVar7;
    int64_t aiStack_48 [2];
    uchar auStack_38 [32];
    int aiStack_18 [4];
    
    iVar7 = 0;
    fcn.14004252c(1);
    puVar4 = &stack0xffffffffffffffc8;
    for (iVar3 = 3; *(puVar4 + 0x20) = iVar3, iVar3 < *0x1400588c0; iVar3 = iVar3 + 1) {
        iVar6 = iVar3;
        puVar5 = puVar4;
        if (*(*0x1400578a8 + iVar6 * 8) != 0) {
            if ((*(*(*0x1400578a8 + iVar6 * 8) + 0x18) & 0x83) != 0) {
                *(puVar4 + -8) = 0x140044e09;
                iVar2 = func_0x00014004547c();
                if (iVar2 != -1) {
                    iVar7 = iVar7 + 1;
                    *(puVar4 + 0x24) = iVar7;
                }
            }
            if (0x13 < iVar3) {
                iVar1 = *(*0x1400578a8 + iVar6 * 8);
                puVar5 = puVar4 + -8;
                *(puVar4 + -8) = *0x1400578a8;
                *(puVar4 + -0x10) = 0x140044e2e;
                func_0x0001402e722b(iVar1 + 0x30);
                iVar1 = *(*0x1400578a8 + iVar6 * 8);
                *(puVar4 + -0x10) = 0x140044e3e;
                fcn.14003dc60(iVar1);
                *(*0x1400578a8 + iVar6 * 8) = 0;
            }
        }
        puVar4 = puVar5;
    }
    *(puVar4 + -8) = 0x140044e58;
    fcn.14004242c(1);
    return iVar7;
}
