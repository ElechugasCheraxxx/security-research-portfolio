/* RVA 0x9cd4  tam 436 B  addr 0x140009cd4 */

//WARNING: Instruction at (ram,0x000140009e49) overlaps instruction at (ram,0x000140009e44)
//

uint64_t fcn.140009cc0(int64_t arg1,int64_t arg2)

{
    uint8_t *puVar1;
    code *pcVar2;
    uchar *puVar3;
    uchar *puVar4;
    int64_t iVar5;
    uchar *puVar6;
    int64_t iVar7;
    ulong uVar8;
    uchar *puVar9;
    uint64_t *puVar10;
    uint64_t uVar11;
    uchar *puVar12;
    int64_t iStack_58;
    uchar *puStack_50;
    int64_t iStack_48;
    
    puVar10 = arg2 & 0xffffffff;
    if ((*(arg1 + 0x70) & 2) != 0) {
        return 0xffffffff;
    }
    if (arg2 == -1) {
        return 0;
    }
    iStack_48 = 0x140009cf9;
    puVar3 = func_0x0001401b4fbf();
    iStack_48 = 0x140009d04;
    puVar4 = func_0x0001406b60fb(arg1);
    iStack_48 = arg2;
    if ((puVar3 != NULL) && (puVar3 < puVar4)) {
        puStack_50 = 0x140009d1a;
        puVar4 = func_0x00014029979f(arg1);
        uVar11 = *puVar10;
        *puVar4 = uVar11;
        *(arg1 + 0x68) = puVar3 + 1;
        return uVar11 & 0xffffffff;
    }
    puStack_50 = 0x140009d35;
    iVar5 = func_0x000140036ed8(arg1);
    puVar6 = NULL;
    if (puVar3 == NULL) {
        puVar4 = puVar6;
    }
    if (puVar4 < 0x20) {
        puVar3 = 0x20;
        puStack_50 = 0x140009d57;
        puVar6 = fcn.140014fcc(0x20);
    }
    else {
        if (puVar4 < 0x3fffffff) {
            puVar3 = puVar4 * 2;
            if (puVar3 < 0x1000) {
                if (puVar3 != NULL) {
                    puStack_50 = 0x140009d8e;
                    puVar6 = fcn.140014fcc(puVar3);
                }
                goto code_r0x000140009dc0;
            }
            puVar6 = puVar3 + 0x27;
            if (puVar6 <= puVar3) {
                puStack_50 = 0x140009e73;
                fcn.140009350();
                pcVar2 = swi(3);
                uVar11 = (*pcVar2)();
                return uVar11;
            }
        }
        else {
            puVar3 = 0x7fffffff;
            if (0x7ffffffe < puVar4) {
                return 0xffffffff;
            }
            puVar6 = 0x80000026;
        }
        puStack_50 = 0x140009dab;
        iVar7 = fcn.140014fcc();
        if (iVar7 == 0) {
            puVar9 = &stack0xffffffffffffffb0;
            puStack_50 = puVar6;
            goto code_r0x000140009e35;
        }
        puVar6 = iVar7 + 0x27U & 0xffffffffffffffe0;
        *(puVar6 + -8) = iVar7;
    }
code_r0x000140009dc0:
    puStack_50 = 0x140009dce;
    fcn.140015ebe(puVar6,iVar5,puVar4);
    puStack_50 = puVar4 + puVar6 + 1;
    *(arg1 + 0x68) = puStack_50;
    iStack_58 = 0x140009dea;
    iStack_58 = func_0x00014027e00a(arg1,puVar6,puVar4 + puVar6,puVar6 + puVar3);
    if ((*(arg1 + 0x70) & 4) == 0) {
        puVar3 = *(arg1 + 0x68);
        iStack_58 = 0x140009e04;
        uVar8 = func_0x0001406a4a22(arg1);
        puVar9 = puVar6 + 1;
        iStack_58 = puVar9 - iVar5;
        puVar6 = CONCAT71(uVar8 >> 8,*puVar6) + iStack_58;
        puVar12 = puVar3;
    }
    else {
        puVar9 = puVar6;
        puVar12 = puVar6;
    }
    func_0x0001401add55(arg1,puVar9,puVar6,puVar12);
    puVar9 = &stack0xffffffffffffffa8;
    if ((*(arg1 + 0x70) & 1) != 0) {
        fcn.1400095c0(arg1 + 0x74,iVar5,puVar4);
        puVar9 = &stack0xffffffffffffffa8;
    }
code_r0x000140009e35:
    *(arg1 + 0x70) = *(arg1 + 0x70) | 1;
    *(puVar9 + -8) = 0x140009e41;
    iVar5 = func_0x000140291d72();
    puVar1 = iVar5 + -0x78;
    *puVar1 = *puVar1 << 1 | *puVar1 < '\0';
    puVar3[0x510cebc5] = puVar3[0x510cebc5] - arg1;
    *(puVar9 + -8) = 0x140009e4f;
    func_0x0001402bfd95();
    pcVar2 = swi(3);
    uVar11 = (*pcVar2)();
    return uVar11;
}
