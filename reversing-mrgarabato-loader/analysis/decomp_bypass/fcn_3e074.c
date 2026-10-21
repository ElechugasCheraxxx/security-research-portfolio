/* RVA 0x3e074  tam 617 B  addr 0x14003e074 */

//WARNING: Control flow encountered bad instruction data

void fcn.14003e074(int64_t arg1,int64_t arg2)

{
    uint8_t uVar1;
    uint32_t uVar2;
    uint32_t *puVar3;
    uint32_t uVar4;
    uint64_t uVar5;
    uint8_t *puVar6;
    ushort *puVar7;
    uint uVar8;
    uint64_t uVar9;
    int64_t iVar10;
    uint8_t *puVar11;
    uint8_t *puVar12;
    uint8_t *puVar13;
    uchar auStack_40 [32];
    uchar auStack_20 [24];
    uint64_t uStack_8;
    
    uStack_8 = *0x140053bd0 ^ auStack_40;
    uVar2 = fcn.14003dfd8(arg1);
    uVar5 = 0;
    uVar8 = 0;
    puVar11 = uVar2;
    if (uVar2 == 0) {
        fcn.14003dca0(arg2);
    }
    else {
        puVar3 = 0x1400534b0;
        uVar9 = uVar5;
        do {
            if (*puVar3 == uVar2) {
                fcn.14003f620(arg2 + 0x1c,0,0x101);
                puVar13 = 0x1400534a8;
                iVar10 = 4;
                puVar11 = uVar9 * 0x30 + 0x1400534c0;
                do {
                    uVar1 = *puVar11;
                    puVar6 = puVar11;
                    while ((uVar1 != 0 && (puVar6[1] != 0))) {
                        uVar5 = *puVar6;
                        if (*puVar6 <= puVar6[1]) {
                            puVar12 = uVar5 + 0x1d + arg2;
                            do {
                                uVar4 = uVar5 + 1;
                                uVar5 = uVar4;
                                *puVar12 = *puVar12 | *puVar13;
                                puVar12 = puVar12 + 1;
                            } while (uVar4 <= puVar6[1]);
                        }
                        puVar6 = puVar6 + 2;
                        uVar1 = *puVar6;
                    }
                    puVar11 = puVar11 + 8;
                    puVar13 = puVar13 + 1;
                    iVar10 = iVar10 + -1;
                } while (iVar10 != 0);
                *(arg2 + 4) = uVar2;
                *(arg2 + 8) = 1;
                if (uVar2 == 0x3a4) {
                    uVar8 = 0x411;
                }
                else if (uVar2 == 0x3a8) {
                    uVar8 = 0x804;
                }
                else if (uVar2 == 0x3b5) {
                    uVar8 = 0x412;
                }
                else if (uVar2 == 0x3b6) {
                    uVar8 = 0x404;
                }
                *(arg2 + 0xc) = uVar8;
                puVar7 = arg2 + 0x10;
                iVar10 = 6;
                do {
                    *puVar7 = *((uVar9 * 0x30 - arg2) + 0x1400534a4 + puVar7);
                    puVar7 = puVar7 + 1;
                    iVar10 = iVar10 + -1;
                } while (iVar10 != 0);
                func_0x00014003dd2c(arg2);
                goto code_r0x00014003e2bc;
            }
            uVar4 = uVar5 + 1;
            uVar5 = uVar4;
            uVar9 = uVar9 + 1;
            puVar3 = puVar3 + 0xc;
        } while (uVar4 < 5);
        if ((uVar2 != 65000) && (uVar2 != 0xfde9)) {
            func_0x00014014102a(puVar11 & 0xffff);
            func_0x000140226ece(uVar2,auStack_20);
            in(0x85);
            *puVar11 = *puVar11 >> 4 | *puVar11 << 4;
    //WARNING: Bad instruction - Truncating control flow here
            halt_baddata();
        }
    }
code_r0x00014003e2bc:
    fcn.140042300(uStack_8 ^ auStack_40);
    return;
}
