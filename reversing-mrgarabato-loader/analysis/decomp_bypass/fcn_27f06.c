/* RVA 0x27f06  tam 153 B  addr 0x140027f06 */

//WARNING: Possible PIC construction at 0x000140027f42: Changing call to branch

uint64_t fcn.140027f06(int64_t arg1)

{
    uchar uVar1;
    int64_t iVar2;
    uint uVar3;
    uint64_t uVar4;
    uint *puVar5;
    ulong *puVar6;
    ulong uVar7;
    uint64_t uVar8;
    uchar *puVar9;
    int64_t in_R8;
    char in_R9B;
    ulong uStack_28;
    int64_t iStack_20;
    
    uVar8 = 0;
    if (*(arg1 + 0x38) != 0) {
        do {
            iVar2 = *(*(arg1 + 0x28) + uVar8 * 8);
            if (iVar2 != 0) {
                puVar6 = *(iVar2 + 0x28);
                if (puVar6 != NULL) {
                    uStack_28 = 0x140027f3f;
                    uVar4 = fcn.14003c52c(*puVar6);
                    puVar9 = &stack0xffffffffffffffd8;
                    uStack_28 = 0x140027f47;
                    goto code_r0x00014003c534;
                }
                uStack_28 = 0x140027f4f;
                func_0x00014003c534(iVar2);
            }
            uVar8 = uVar8 + 1;
        } while (uVar8 < *(arg1 + 0x38));
    }
    *(arg1 + 0x30) = 0;
    *(arg1 + 0x38) = 0;
    uStack_28 = 0x140027f7b;
    fcn.14003c52c(*(arg1 + 0x28));
    *(arg1 + 0x28) = 0;
    uStack_28 = 0x140027f8b;
    uVar4 = func_0x0001401ffe5d();
    LOCK();
    uVar1 = *(uVar4 - 0x75);
    *(uVar4 - 0x75) = arg1;
    puVar6 = CONCAT71(arg1 >> 8,uVar1);
    UNLOCK();
    *(in_R8 + -0x75) = *(in_R8 + -0x75) - in_R9B;
    uVar4 = uVar4 & 0xffffffffffffff40;
    puVar9 = iStack_20 + 0x28;
code_r0x00014003c534:
    if (puVar6 != NULL) {
        *(puVar9 + -8) = uVar8;
        uVar7 = 0;
        *(puVar9 + -0x30) = *0x1400569b8;
        *(puVar9 + -0x38) = 0x14003dc7c;
        uVar4 = fcn.14002e131(*0x1400569b8,0,puVar6);
        if (uVar4 == 0) {
            *(puVar9 + -0x38) = 0x14003dc85;
            puVar5 = fcn.14003ef2c();
            *(puVar9 + -0x38) = uVar7;
            *(puVar9 + -0x40) = 0x14003dc8e;
            uVar3 = fcn.1406b54b7();
            *(puVar9 + -0x40) = 0x14003dc95;
            uVar4 = fcn.14003eee4(uVar3);
            *puVar5 = uVar4;
        }
    }
    return uVar4;
}
