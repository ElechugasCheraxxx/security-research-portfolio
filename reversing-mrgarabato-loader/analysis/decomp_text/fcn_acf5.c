/* RVA 0xacf5  tam 423 B  addr 0x14000acf5 */

ulong * fcn.14000acf5(int64_t arg1,int64_t arg2,int64_t arg3)

{
    uint64_t uVar1;
    code *pcVar2;
    uint uVar3;
    uint uVar4;
    uint uVar5;
    int64_t iVar6;
    uint64_t uVar7;
    int64_t iVar8;
    ulong *puVar9;
    uint64_t uVar10;
    ulong *puVar11;
    ulong *puVar12;
    uint *puStackX_18;
    ulong *puVar13;
    ulong *puVar14;
    
    iVar8 = *arg1;
    iVar6 = *(arg1 + 8) - iVar8 >> 5;
    if (iVar6 == 0x7ffffffffffffff) {
        func_0x00014000d2b0();
        pcVar2 = swi(3);
        puVar9 = (*pcVar2)();
        return puVar9;
    }
    uVar1 = iVar6 + 1;
    uVar7 = *(arg1 + 0x10) - iVar8 >> 5;
    if (uVar7 <= 0x7ffffffffffffff - (uVar7 >> 1)) {
        uVar7 = (uVar7 >> 1) + uVar7;
        uVar10 = uVar1;
        if (uVar1 <= uVar7) {
            uVar10 = uVar7;
        }
        if (uVar10 < 0x800000000000000) {
            uVar7 = uVar10 * 0x20;
            if (uVar7 < 0x1000) {
                if (uVar7 == 0) {
                    puVar9 = NULL;
                    puStackX_18 = arg3;
                }
                else {
                    puVar9 = fcn.140014fcc();
                }
            }
            else {
                if (uVar7 + 0x27 <= uVar7) goto code_r0x00014000ae90;
                iVar6 = fcn.140014fcc(uVar7 + 0x27);
                if (iVar6 == 0) {
                    func_0x00014021a64c();
                    pcVar2 = swi(3);
                    puVar9 = (*pcVar2)();
                    return puVar9;
                }
                puVar9 = iVar6 + 0x27U & 0xffffffffffffffe0;
                puVar9[-1] = iVar6;
            }
            puVar11 = (arg2 - iVar8 & 0xffffffffffffffe0U) + puVar9;
            puVar12 = puVar11 + 4;
            *puVar11 = 0;
            puVar11[1] = 0;
            puVar11[2] = 0;
            puVar11[3] = 0;
            uVar3 = puStackX_18[1];
            uVar4 = puStackX_18[2];
            uVar5 = puStackX_18[3];
            *puVar11 = *puStackX_18;
            *(puVar11 + 4) = uVar3;
            *(puVar11 + 1) = uVar4;
            *(puVar11 + 0xc) = uVar5;
            uVar3 = puStackX_18[5];
            uVar4 = puStackX_18[6];
            uVar5 = puStackX_18[7];
            *(puVar11 + 2) = puStackX_18[4];
            *(puVar11 + 0x14) = uVar3;
            *(puVar11 + 3) = uVar4;
            *(puVar11 + 0x1c) = uVar5;
            *(puStackX_18 + 4) = 0;
            *(puStackX_18 + 6) = 0xf;
            *puStackX_18 = 0;
            iVar8 = *(arg1 + 8);
            puVar14 = puVar12;
            if (arg2 == iVar8) {
                arg2 = *arg1;
                puVar12 = puVar9;
                puVar13 = puVar11;
            }
            else {
                func_0x00014000aea0(*arg1,arg2,puVar9,arg1,puVar11,puVar12);
                iVar8 = *(arg1 + 8);
                puVar13 = puVar9;
            }
            func_0x00014000aea0(arg2,iVar8,puVar12,arg1,puVar13,puVar14);
            func_0x00014000d1d0(arg1,puVar9,uVar1,uVar10);
            return puVar11;
        }
    }
code_r0x00014000ae90:
    fcn.140009350();
    pcVar2 = swi(3);
    puVar9 = (*pcVar2)();
    return puVar9;
}
