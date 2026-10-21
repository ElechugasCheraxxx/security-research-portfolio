/* RVA 0xf1e0  tam 984 B  addr 0x14000f1e0 */

void fcn.14000f1e0(ulong noname_0,int64_t arg1)

{
    int64_t *piVar1;
    char cVar2;
    int iVar3;
    ulong uVar4;
    int64_t iVar5;
    code *pcVar6;
    char *pcVar7;
    uint32_t uVar8;
    int64_t iVar9;
    uint32_t uVar10;
    uint64_t uVar11;
    int64_t *piVar12;
    code *pcVar13;
    int64_t unaff_GS_OFFSET;
    uchar auStack_178 [32];
    uint auStack_158 [11];
    uchar auStack_12c [260];
    uint64_t uStack_28;
    
    uStack_28 = *0x140020600 ^ auStack_178;
    auStack_158[0] = 0x130;
    piVar1 = **(*(*(unaff_GS_OFFSET + 0x60) + 0x18) + 0x10);
    piVar12 = piVar1;
    do {
        iVar5 = piVar12[6];
        pcVar13 = NULL;
        iVar9 = *(*(iVar5 + 0x3c) + 0x88 + iVar5) + iVar5;
        if ((iVar9 != iVar5) && (uVar11 = *(iVar9 + 0x18), *(iVar9 + 0x18) != 0)) {
            do {
                uVar10 = uVar11 - 1;
                uVar11 = uVar10;
                uVar8 = 0x811c9dc5;
                pcVar7 = *(*(iVar9 + 0x20) + uVar11 * 4 + iVar5) + iVar5;
                cVar2 = *pcVar7;
                if (cVar2 != '\0') {
                    do {
                        pcVar7 = pcVar7 + 1;
                        uVar8 = (cVar2 ^ uVar8) * 0x1000193;
                        cVar2 = *pcVar7;
                    } while (cVar2 != '\0');
                    if (uVar8 == 0x185776b5) {
                        pcVar6 = *(*(iVar9 + 0x1c) + iVar5 + *(*(iVar9 + 0x24) + iVar5 + uVar11 * 2) * 4) + iVar5;
                        goto code_r0x00014000f2c0;
                    }
                }
            } while (uVar10 != 0);
        }
        piVar12 = *piVar12;
    } while ((piVar12 != piVar1) && (piVar12[6] != 0));
    pcVar6 = pcVar13;
code_r0x00014000f2c0:
    uVar4 = (*pcVar6)(2);
    piVar1 = **(*(*(unaff_GS_OFFSET + 0x60) + 0x18) + 0x10);
    piVar12 = piVar1;
    do {
        iVar5 = piVar12[6];
        iVar9 = *(*(iVar5 + 0x3c) + 0x88 + iVar5) + iVar5;
        if ((iVar9 != iVar5) && (uVar11 = *(iVar9 + 0x18), *(iVar9 + 0x18) != 0)) {
            do {
                uVar10 = uVar11 - 1;
                uVar11 = uVar10;
                uVar8 = 0x811c9dc5;
                pcVar7 = *(*(iVar9 + 0x20) + uVar11 * 4 + iVar5) + iVar5;
                cVar2 = *pcVar7;
                if (cVar2 != '\0') {
                    do {
                        pcVar7 = pcVar7 + 1;
                        uVar8 = (cVar2 ^ uVar8) * 0x1000193;
                        cVar2 = *pcVar7;
                    } while (cVar2 != '\0');
                    if (uVar8 == 0xa4c8c8f) {
                        pcVar6 = *(*(iVar9 + 0x1c) + iVar5 + *(*(iVar9 + 0x24) + iVar5 + uVar11 * 2) * 4) + iVar5;
                        goto code_r0x00014000f380;
                    }
                }
            } while (uVar10 != 0);
        }
        piVar12 = *piVar12;
    } while ((piVar12 != piVar1) && (piVar12[6] != 0));
    pcVar6 = pcVar13;
code_r0x00014000f380:
    iVar3 = (*pcVar6)(uVar4,auStack_158);
    if (iVar3 == 1) {
        do {
            piVar1 = **(*(*(unaff_GS_OFFSET + 0x60) + 0x18) + 0x10);
            piVar12 = piVar1;
            do {
                iVar5 = piVar12[6];
                iVar9 = *(*(iVar5 + 0x3c) + 0x88 + iVar5) + iVar5;
                if ((iVar9 != iVar5) && (uVar11 = *(iVar9 + 0x18), *(iVar9 + 0x18) != 0)) {
                    do {
                        uVar10 = uVar11 - 1;
                        uVar11 = uVar10;
                        uVar8 = 0x811c9dc5;
                        pcVar7 = *(*(iVar9 + 0x20) + uVar11 * 4 + iVar5) + iVar5;
                        cVar2 = *pcVar7;
                        if (cVar2 != '\0') {
                            do {
                                pcVar7 = pcVar7 + 1;
                                uVar8 = (cVar2 ^ uVar8) * 0x1000193;
                                cVar2 = *pcVar7;
                            } while (cVar2 != '\0');
                            if (uVar8 == 0x15eec872) {
                                pcVar6 = *(*(iVar9 + 0x1c) + iVar5 + *(*(iVar9 + 0x24) + iVar5 + uVar11 * 2) * 4) +
                                         iVar5;
                                goto code_r0x00014000f440;
                            }
                        }
                    } while (uVar10 != 0);
                }
                piVar12 = *piVar12;
            } while ((piVar12 != piVar1) && (piVar12[6] != 0));
            pcVar6 = pcVar13;
code_r0x00014000f440:
            iVar3 = (*pcVar6)(uVar4,auStack_158);
            if (iVar3 != 1) goto code_r0x00014000f4bd;
            iVar5 = func_0x000140015ed0(auStack_12c,arg1);
        } while (iVar5 == 0);
    }
    else {
code_r0x00014000f4bd:
        piVar1 = **(*(*(unaff_GS_OFFSET + 0x60) + 0x18) + 0x10);
        piVar12 = piVar1;
        do {
            iVar5 = piVar12[6];
            iVar9 = *(*(iVar5 + 0x3c) + 0x88 + iVar5) + iVar5;
            if ((iVar9 != iVar5) && (uVar11 = *(iVar9 + 0x18), *(iVar9 + 0x18) != 0)) {
                do {
                    uVar10 = uVar11 - 1;
                    uVar11 = uVar10;
                    uVar8 = 0x811c9dc5;
                    pcVar7 = *(*(iVar9 + 0x20) + uVar11 * 4 + iVar5) + iVar5;
                    cVar2 = *pcVar7;
                    if (cVar2 != '\0') {
                        do {
                            pcVar7 = pcVar7 + 1;
                            uVar8 = (cVar2 ^ uVar8) * 0x1000193;
                            cVar2 = *pcVar7;
                        } while (cVar2 != '\0');
                        if (uVar8 == 0xfaba0065) {
                            pcVar13 = *(*(iVar9 + 0x1c) + iVar5 + *(*(iVar9 + 0x24) + iVar5 + uVar11 * 2) * 4) + iVar5;
                            goto code_r0x00014000f583;
                        }
                    }
                } while (uVar10 != 0);
            }
            piVar12 = *piVar12;
        } while ((piVar12 != piVar1) && (piVar12[6] != 0));
code_r0x00014000f583:
        (*pcVar13)(uVar4);
    }
    fcn.1400153c0(uStack_28 ^ auStack_178);
    return;
}
