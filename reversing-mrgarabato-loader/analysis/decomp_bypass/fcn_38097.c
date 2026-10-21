/* RVA 0x38097  tam 819 B  addr 0x140038097 */

int64_t fcn.140038080(int64_t arg1,int64_t arg2,int64_t arg3)

{
    int16_t iVar1;
    uchar auVar2 [16];
    uchar auVar3 [16];
    uchar auVar4 [16];
    ulong *puVar5;
    ulong *puVar6;
    ulong uVar7;
    int64_t iVar8;
    ulong *puVar9;
    ulong *puVar10;
    int64_t iVar11;
    uint64_t uVar12;
    ulong *puVar13;
    ulong *puVar14;
    int16_t *piVar15;
    int16_t *piVar16;
    int16_t *piVar17;
    ulong *puVar18;
    uint64_t uVar19;
    ulong *puVar20;
    uint64_t uVar21;
    bool bVar22;
    ulong *puStack_70;
    int64_t aiStack_68 [2];
    uint64_t uStack_58;
    
    puVar13 = NULL;
    puStack_70 = NULL;
    puVar14 = puVar13;
    puVar5 = puVar13;
    if (*(arg1 + 0x10) != 0) {
        puVar18 = puVar13;
        puVar6 = puVar13;
        puVar20 = puVar13;
        do {
            puVar9 = 0x1;
            iVar11 = *arg1;
            puVar5 = puVar18;
            if (puVar13 == puVar14) {
                if (puVar14 != NULL) {
                    puVar9 = puVar14 * 2;
                }
                auVar2._8_8_ = 0;
                auVar2._0_8_ = puVar9;
                uVar7 = SUB168(ZEXT816(8) * auVar2,0);
                if (SUB168(ZEXT816(8) * auVar2,8) != 0) {
                    uVar7 = 0xffffffffffffffff;
                }
                puVar5 = fcn.14003c43c(uVar7);
                if (puVar13 != NULL) {
                    puVar14 = puVar5;
                    puVar10 = puVar13;
                    do {
                        *puVar14 = *((puVar18 - puVar5) + puVar14);
                        puVar14 = puVar14 + 1;
                        puVar10 = puVar10 + -1;
                    } while (puVar10 != NULL);
                }
                fcn.14003c52c(puVar18);
                puVar14 = puVar9;
            }
            puVar5[puVar13] = puVar6 + iVar11;
            puVar13 = puVar13 + 1;
            puVar20 = puVar20 + 1;
            puVar6 = puVar6 + 2;
            puVar18 = puVar5;
        } while (puVar20 < *(arg1 + 0x10));
        puStack_70 = puVar13;
    }
    uVar19 = 0;
    fcn.140037f30(aiStack_68,arg3);
    bVar22 = uStack_58 == 0;
    if (!bVar22) {
        uVar12 = uStack_58;
        puVar13 = puVar5;
        uVar21 = uVar19;
        do {
            puVar18 = uVar21 + aiStack_68[0];
            piVar16 = *puVar18;
            iVar11 = 2;
            piVar15 = piVar16;
            piVar17 = 0x14004beb8;
            do {
                if (iVar11 == 0) break;
                iVar11 = iVar11 + -1;
                bVar22 = *piVar15 == *piVar17;
                piVar15 = piVar15 + 1;
                piVar17 = piVar17 + 1;
            } while (bVar22);
            puVar5 = puVar13;
            if (!bVar22) {
                iVar11 = 3;
                piVar15 = 0x14004bebc;
                do {
                    if (iVar11 == 0) break;
                    iVar11 = iVar11 + -1;
                    bVar22 = *piVar16 == *piVar15;
                    piVar16 = piVar16 + 1;
                    piVar15 = piVar15 + 1;
                } while (bVar22);
                if (bVar22) {
                    if (puStack_70 != NULL) {
                        puStack_70 = puStack_70 + -1;
                    }
                }
                else {
                    if (puStack_70 == puVar14) {
                        if (puVar14 == NULL) {
                            puVar14 = 0x1;
                        }
                        else {
                            puVar14 = puVar14 * 2;
                        }
                        auVar3._8_8_ = 0;
                        auVar3._0_8_ = puVar14;
                        uVar7 = SUB168(ZEXT816(8) * auVar3,0);
                        if (SUB168(ZEXT816(8) * auVar3,8) != 0) {
                            uVar7 = 0xffffffffffffffff;
                        }
                        puVar5 = fcn.14003c43c(uVar7);
                        if (puStack_70 != NULL) {
                            puVar6 = puStack_70;
                            puVar20 = puVar5;
                            do {
                                *puVar20 = *((puVar13 - puVar5) + puVar20);
                                puVar20 = puVar20 + 1;
                                puVar6 = puVar6 + -1;
                            } while (puVar6 != NULL);
                        }
                        fcn.14003c52c(puVar13);
                    }
                    puVar5[puStack_70] = puVar18;
                    puStack_70 = puStack_70 + 1;
                    uVar12 = uStack_58;
                }
            }
            uVar19 = uVar19 + 1;
            uVar21 = uVar21 + 0x10;
            bVar22 = uVar19 == uVar12;
            puVar13 = puVar5;
        } while (uVar19 < uVar12);
    }
    puVar14 = NULL;
    *arg2 = 0;
    *(arg2 + 8) = 0;
    uVar7 = SUB168(ZEXT816(2) * ZEXT816(1),0);
    if (SUB168(ZEXT816(2) * ZEXT816(1),8) != 0) {
        uVar7 = 0xffffffffffffffff;
    }
    iVar11 = fcn.14003c43c(uVar7);
    *arg2 = iVar11;
    *(iVar11 + *(arg2 + 8) * 2) = 0;
    if (puStack_70 != NULL) {
        do {
            if (puVar14 != NULL) {
                iVar11 = *(arg2 + 8) + 1;
                auVar4._8_8_ = 0;
                auVar4._0_8_ = *(arg2 + 8) + 2;
                uVar7 = SUB168(ZEXT816(2) * auVar4,0);
                if (SUB168(ZEXT816(2) * auVar4,8) != 0) {
                    uVar7 = 0xffffffffffffffff;
                }
                iVar8 = fcn.14003c43c(uVar7);
                fcn.140041d50(iVar8,*arg2,*(arg2 + 8) * 2);
                *(iVar8 + *(arg2 + 8) * 2) = *0x14004bec4;
                *(iVar8 + iVar11 * 2) = 0;
                fcn.14003c52c(*arg2);
                *arg2 = iVar8;
                *(arg2 + 8) = iVar11;
            }
            uVar19 = 0xffffffffffffffff;
            piVar16 = *puVar5[puVar14];
            do {
                if (uVar19 == 0) break;
                uVar19 = uVar19 - 1;
                iVar1 = *piVar16;
                piVar16 = piVar16 + 1;
            } while (iVar1 != 0);
            fcn.140023150(arg2,*puVar5[puVar14],~uVar19 - 1);
            puVar14 = puVar14 + 1;
        } while (puVar14 < puStack_70);
    }
    if (aiStack_68[0] != 0) {
        func_0x00014003ca2c(aiStack_68[0],0x10,*(aiStack_68[0] + -8),0x140023140);
        fcn.14003c52c(aiStack_68[0] + -8);
    }
    fcn.14003c52c(puVar5);
    return arg2;
}
