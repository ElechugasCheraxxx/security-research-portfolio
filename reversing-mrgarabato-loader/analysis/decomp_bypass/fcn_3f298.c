/* RVA 0x3f298  tam 509 B  addr 0x14003f298 */

ulong fcn.14003f27c(int64_t arg1,int64_t arg2,int64_t arg3,int64_t arg4)

{
    int64_t iVar1;
    uint32_t *puVar2;
    int iVar3;
    uint32_t *puVar4;
    uint32_t uVar5;
    uchar *puVar6;
    uchar *puVar7;
    uint32_t uVar8;
    uint32_t uVar9;
    uint32_t uVar10;
    uint64_t uVar11;
    uint32_t uVar12;
    uint64_t uVar13;
    uint64_t auStack_78 [2];
    uchar auStack_68 [32];
    int64_t aiStack_48 [4];
    
    iVar1 = *(arg4 + 8);
    puVar2 = *(arg4 + 0x38);
    uVar13 = *arg4 - iVar1;
    if ((*(arg1 + 4) & 0x66) == 0) {
        uVar11 = *(arg4 + 0x48);
        if (*(arg4 + 0x48) < *puVar2) {
            puVar4 = puVar2 + uVar11 * 4 + 3;
            puVar6 = &stack0xffffffffffffff98;
            aiStack_48[2] = arg1;
            aiStack_48[3] = arg3;
            do {
                puVar7 = puVar6;
                if (((puVar4[-2] <= uVar13) && (uVar13 < puVar4[-1])) && (puVar4[1] != 0)) {
                    if (*puVar4 != 1) {
                        uVar9 = *puVar4;
                        *(puVar6 + -8) = 0x14003f313;
                        iVar3 = (*(uVar9 + iVar1))(puVar6 + 0x30,arg2);
                        if (iVar3 < 0) {
                            return 0;
                        }
                        if (iVar3 < 1) goto code_r0x00014003f391;
                    }
                    if ((*arg1 == -0x1f928c9d) && (*0x14004cdd8 != NULL)) {
                        *(puVar6 + -8) = 0x14003f33c;
                        iVar3 = func_0x000140043140(0x14004cdd8);
                        if (iVar3 != 0) {
                            *(puVar6 + -8) = 0x14003f34e;
                            (**0x14004cdd8)(arg1,1);
                        }
                    }
                    uVar9 = puVar4[1];
                    *(puVar6 + -8) = 0x14003f362;
                    func_0x000140043080(uVar9 + iVar1,arg2,1);
                    uVar9 = puVar4[1];
                    iVar3 = *arg1;
                    *(puVar6 + 0x28) = *(arg4 + 0x40);
                    *(puVar6 + 0x20) = *(arg4 + 0x28);
                    puVar7 = puVar6 + -8;
                    *(puVar6 + -8) = uVar11;
                    *(puVar6 + -0x10) = 0x14003f38c;
                    func_0x00014002f251(arg2,uVar9 + iVar1,arg1,iVar3);
                    *(puVar6 + -0x10) = 0x14003f391;
                    func_0x0001400430b0();
                }
code_r0x00014003f391:
                uVar9 = uVar11 + 1;
                uVar11 = uVar9;
                puVar4 = puVar4 + 4;
                puVar6 = puVar7;
            } while (uVar9 < *puVar2);
        }
    }
    else {
        uVar10 = 0;
        uVar12 = 0;
        uVar11 = *(arg4 + 0x20) - iVar1;
        uVar8 = 0;
        uVar9 = 0;
        if ((*(arg1 + 4) & 0x20) != 0) {
            uVar5 = 0;
            uVar8 = uVar10;
            uVar9 = uVar12;
            if (*puVar2 != 0) {
                puVar4 = puVar2 + 2;
                do {
                    if ((puVar4[-1] <= uVar11) && (uVar11 <= *puVar4)) {
                        uVar9 = puVar2[uVar5 * 4 + 4];
                        if (uVar9 == 0) {
                            uVar8 = puVar2[uVar5 * 4 + 3];
                            uVar9 = uVar12;
                        }
                        break;
                    }
                    uVar5 = uVar5 + 1;
                    puVar4 = puVar4 + 4;
                } while (uVar5 < *puVar2);
            }
        }
        uVar11 = *(arg4 + 0x48);
        if (*(arg4 + 0x48) < *puVar2) {
            puVar4 = puVar2 + (uVar11 + 1) * 4;
            do {
                if ((puVar4[-3] <= uVar13) && (uVar13 < puVar4[-2])) {
                    if ((uVar9 != 0) && (uVar9 == *puVar4)) {
                        return 1;
                    }
                    if ((uVar8 != 0) && (uVar8 == puVar4[-1])) {
                        return 1;
                    }
                    if (*puVar4 == 0) {
                        *(arg4 + 0x48) = uVar11 + 1;
                        (*(puVar4[-1] + iVar1))(1,arg2);
                    }
                }
                uVar10 = uVar11 + 1;
                uVar11 = uVar10;
                puVar4 = puVar4 + 4;
            } while (uVar10 < *puVar2);
        }
    }
    return 1;
}
