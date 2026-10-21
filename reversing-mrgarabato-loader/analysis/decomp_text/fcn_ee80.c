/* RVA 0xee80  tam 717 B  addr 0x14000ee80 */

bool fcn.14000ee70(void)

{
    int64_t *piVar1;
    int64_t iVar2;
    char cVar3;
    int iVar4;
    code *pcVar5;
    char *pcVar6;
    code *pcVar7;
    uint32_t uVar8;
    int64_t iVar9;
    uint32_t uVar10;
    uint64_t uVar11;
    code *pcVar12;
    int64_t *piVar13;
    int64_t unaff_GS_OFFSET;
    ulong uStack_28;
    ulong uStack_20;
    uint32_t uStack_18;
    
    piVar1 = **(*(*(unaff_GS_OFFSET + 0x60) + 0x18) + 0x10);
    piVar13 = piVar1;
    do {
        iVar2 = piVar13[6];
        pcVar5 = NULL;
        iVar9 = *(*(iVar2 + 0x3c) + 0x88 + iVar2) + iVar2;
        if ((iVar9 != iVar2) && (uVar11 = *(iVar9 + 0x18), *(iVar9 + 0x18) != 0)) {
            do {
                uVar10 = uVar11 - 1;
                uVar11 = uVar10;
                uVar8 = 0x811c9dc5;
                pcVar6 = *(*(iVar9 + 0x20) + uVar11 * 4 + iVar2) + iVar2;
                cVar3 = *pcVar6;
                if (cVar3 != '\0') {
                    do {
                        pcVar6 = pcVar6 + 1;
                        uVar8 = (cVar3 ^ uVar8) * 0x1000193;
                        cVar3 = *pcVar6;
                    } while (cVar3 != '\0');
                    if (uVar8 == 0x21ddcd8b) {
                        pcVar12 = *(*(iVar9 + 0x1c) + iVar2 + *(*(iVar9 + 0x24) + iVar2 + uVar11 * 2) * 4) + iVar2;
                        goto code_r0x00014000ef30;
                    }
                }
            } while (uVar10 != 0);
        }
        piVar13 = *piVar13;
    } while ((piVar13 != piVar1) && (piVar13[6] != 0));
    pcVar12 = pcVar5;
code_r0x00014000ef30:
    (*pcVar12)(0);
    piVar1 = **(*(*(unaff_GS_OFFSET + 0x60) + 0x18) + 0x10);
    piVar13 = piVar1;
    do {
        iVar2 = piVar13[6];
        iVar9 = *(*(iVar2 + 0x3c) + 0x88 + iVar2) + iVar2;
        if ((iVar9 != iVar2) && (uVar11 = *(iVar9 + 0x18), *(iVar9 + 0x18) != 0)) {
            do {
                uVar10 = uVar11 - 1;
                uVar11 = uVar10;
                uVar8 = 0x811c9dc5;
                pcVar6 = *(*(iVar9 + 0x20) + uVar11 * 4 + iVar2) + iVar2;
                cVar3 = *pcVar6;
                if (cVar3 != '\0') {
                    do {
                        pcVar6 = pcVar6 + 1;
                        uVar8 = (cVar3 ^ uVar8) * 0x1000193;
                        cVar3 = *pcVar6;
                    } while (cVar3 != '\0');
                    if (uVar8 == 0xc5f6a8e5) {
                        pcVar12 = *(*(iVar9 + 0x1c) + iVar2 + *(*(iVar9 + 0x24) + iVar2 + uVar11 * 2) * 4) + iVar2;
                        goto code_r0x00014000efe0;
                    }
                }
            } while (uVar10 != 0);
        }
        piVar13 = *piVar13;
    } while ((piVar13 != piVar1) && (piVar13[6] != 0));
    pcVar12 = pcVar5;
code_r0x00014000efe0:
    uStack_28 = *0x14001a3b0;
    uStack_20 = *0x14001a3b8;
    uStack_18 = 0x1001d17;
    pcVar7 = pcVar5;
    do {
        *(&uStack_28 + pcVar7) = *(&uStack_28 + pcVar7) ^ pcVar7 + 0x53U;
        pcVar7 = pcVar7 + 1;
    } while (pcVar7 < 0x12);
    uStack_18 = uStack_18 & 0xffffff;
    (*pcVar12)(&uStack_28);
    piVar1 = **(*(*(unaff_GS_OFFSET + 0x60) + 0x18) + 0x10);
    piVar13 = piVar1;
    do {
        iVar2 = piVar13[6];
        iVar9 = *(*(iVar2 + 0x3c) + 0x88 + iVar2) + iVar2;
        if ((iVar9 != iVar2) && (uVar11 = *(iVar9 + 0x18), *(iVar9 + 0x18) != 0)) {
            do {
                uVar10 = uVar11 - 1;
                uVar11 = uVar10;
                uVar8 = 0x811c9dc5;
                pcVar6 = *(*(iVar9 + 0x20) + uVar11 * 4 + iVar2) + iVar2;
                cVar3 = *pcVar6;
                if (cVar3 != '\0') {
                    do {
                        pcVar6 = pcVar6 + 1;
                        uVar8 = (cVar3 ^ uVar8) * 0x1000193;
                        cVar3 = *pcVar6;
                    } while (cVar3 != '\0');
                    if (uVar8 == 0x5056df37) {
                        pcVar5 = *(*(iVar9 + 0x1c) + iVar2 + *(*(iVar9 + 0x24) + iVar2 + uVar11 * 2) * 4) + iVar2;
                        goto code_r0x00014000f0cc;
                    }
                }
            } while (uVar10 != 0);
        }
        piVar13 = *piVar13;
        if ((piVar13 == piVar1) || (piVar13[6] == 0)) {
code_r0x00014000f0cc:
            iVar4 = (*pcVar5)();
            return iVar4 != 0;
        }
    } while( true );
}
