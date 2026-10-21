/* RVA 0xcf40  tam 239 B  addr 0x14000cf40 */

void fcn.14000cf40(int64_t arg1,int64_t arg2,int64_t arg3)

{
    int *piVar1;
    uint32_t uVar2;
    char cVar3;
    uint16_t uVar4;
    int16_t iVar5;
    int64_t iVar6;
    uint16_t uVar7;
    int iVar8;
    ulong *puVar9;
    uchar *puVar10;
    uchar *puVar11;
    ulong *unaff_RBP;
    ulong *puVar12;
    int16_t iVar13;
    int iVar14;
    int in_R9D;
    uint8_t uVar15;
    uchar auStack_10a4 [3908];
    uchar *puStack_160;
    ulong uStack_70;
    uchar auStack_60 [40];
    uchar auStack_38 [24];
    uint64_t uStack_20;
    
    uStack_20 = *0x140020600 ^ &stack0xffffffffffffff98;
    uVar7 = arg2;
    iVar8 = &stack0xffffffffffffffc8;
    iVar14 = arg3;
    uStack_70 = 0x14000cf6b;
    func_0x0001401b4fae();
    puVar10 = &stack0xffffffffffffffa0;
    iVar6 = arg1;
    uVar4 = func_0x0001401de4f5();
    iVar5 = 0;
    puVar12 = unaff_RBP;
    if (iVar6 != 0) {
        iVar14 = -0x74cddbac;
        puVar9 = &stack0xffffffffffffff98;
        puVar12 = &stack0xffffffffffffff98;
        cVar3 = '\x1e';
        do {
            unaff_RBP = unaff_RBP + -1;
            puVar9 = puVar9 + -1;
            *puVar9 = *unaff_RBP;
            cVar3 = cVar3 + -1;
        } while ('\0' < cVar3);
        puStack_160 = &stack0xffffffffffffff98;
        puVar10 = &stack0xffffffffffffef5c;
        uVar4 = uVar4 & 0xff30;
        iVar5 = iVar6 >> 0x10;
    }
    iVar13 = iVar14;
    *(puVar10 + 0x22) = iVar13;
    *(puVar10 + 0x20) = uVar7;
    if (uVar7 < uVar4) {
        uVar4 = uVar7;
    }
    *(puVar10 + 0x2c) = uVar4 - 1;
    if (iVar13 < iVar5) {
        iVar5 = iVar13;
    }
    uVar2 = *(puVar10 + 0x20);
    *(puVar10 + 0x2e) = iVar5 + -1;
    *(puVar10 + 0x28) = 0;
    if (iVar14 * uVar7 < iVar8 * in_R9D) {
        *(puVar10 + -8) = 0x14000cfd4;
        func_0x00014020f655(arg1,1,puVar10 + 0x28);
        return;
    }
    uVar15 = iVar8 * in_R9D < iVar14 * uVar7;
    puVar11 = puVar10;
    if (uVar15) {
        *(puVar10 + -8) = 0x14000d006;
        iVar6 = arg1;
        func_0x0001402bf112(arg1,uVar2);
        piVar1 = puVar12 + iVar6 * 4 + 0x44;
        *piVar1 = (*piVar1 - iVar6) - uVar15;
        puVar11 = puVar10 + -8;
        *(puVar10 + -8) = uVar2;
        *(puVar10 + -0x10) = 0x14000d01a;
        func_0x000140039749(arg1,1);
    }
    *(puVar11 + -8) = 0x14000d027;
    fcn.1400153c0(*(puVar11 + 0x48) ^ puVar11);
    return;
}
