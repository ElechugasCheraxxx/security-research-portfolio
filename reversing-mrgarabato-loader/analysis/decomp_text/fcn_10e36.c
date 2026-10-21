/* RVA 0x10e36  tam 504 B  addr 0x140010e36 */

void fcn.140010e20(void)

{
    int64_t *piVar1;
    int64_t iVar2;
    char *pcVar3;
    ulong uVar4;
    char cVar5;
    uint32_t uVar6;
    int64_t iVar7;
    code *pcVar8;
    uint32_t uVar9;
    uint64_t uVar10;
    int64_t *piVar11;
    code *pcVar12;
    int64_t unaff_GS_OFFSET;
    uchar auStack_38 [32];
    uint auStack_18 [2];
    uint64_t uStack_10;
    
    uStack_10 = *0x140020600 ^ auStack_38;
    pcVar12 = NULL;
    auStack_18[0] = 0;
    piVar1 = **(*(*(unaff_GS_OFFSET + 0x60) + 0x18) + 0x10);
    piVar11 = piVar1;
    do {
        iVar2 = piVar11[6];
        iVar7 = *(*(iVar2 + 0x3c) + 0x88 + iVar2) + iVar2;
        if ((iVar7 != iVar2) && (uVar10 = *(iVar7 + 0x18), *(iVar7 + 0x18) != 0)) {
            do {
                uVar9 = uVar10 - 1;
                uVar10 = uVar9;
                uVar6 = 0x811c9dc5;
                pcVar3 = *(*(iVar7 + 0x20) + uVar10 * 4 + iVar2) + iVar2;
                cVar5 = *pcVar3;
                if (cVar5 != '\0') {
                    do {
                        pcVar3 = pcVar3 + 1;
                        uVar6 = (cVar5 ^ uVar6) * 0x1000193;
                        cVar5 = *pcVar3;
                    } while (cVar5 != '\0');
                    if (uVar6 == 0x4cfe97c1) {
                        pcVar8 = *(*(iVar7 + 0x1c) + iVar2 + *(*(iVar7 + 0x24) + iVar2 + uVar10 * 2) * 4) + iVar2;
                        goto code_r0x000140010f00;
                    }
                }
            } while (uVar9 != 0);
        }
        piVar11 = *piVar11;
    } while ((piVar11 != piVar1) && (piVar11[6] != 0));
    pcVar8 = pcVar12;
code_r0x000140010f00:
    piVar1 = **(*(*(unaff_GS_OFFSET + 0x60) + 0x18) + 0x10);
    piVar11 = piVar1;
    do {
        iVar2 = piVar11[6];
        iVar7 = *(*(iVar2 + 0x3c) + 0x88 + iVar2) + iVar2;
        if ((iVar7 != iVar2) && (uVar10 = *(iVar7 + 0x18), *(iVar7 + 0x18) != 0)) {
            do {
                uVar9 = uVar10 - 1;
                uVar10 = uVar9;
                uVar6 = 0x811c9dc5;
                pcVar3 = *(*(iVar7 + 0x20) + uVar10 * 4 + iVar2) + iVar2;
                cVar5 = *pcVar3;
                if (cVar5 != '\0') {
                    do {
                        pcVar3 = pcVar3 + 1;
                        uVar6 = (cVar5 ^ uVar6) * 0x1000193;
                        cVar5 = *pcVar3;
                    } while (cVar5 != '\0');
                    if (uVar6 == 0x6dd8a845) {
                        pcVar12 = *(*(iVar7 + 0x1c) + iVar2 + *(*(iVar7 + 0x24) + iVar2 + uVar10 * 2) * 4) + iVar2;
                        goto code_r0x000140010fdf;
                    }
                }
            } while (uVar9 != 0);
        }
        piVar11 = *piVar11;
        if ((piVar11 == piVar1) || (piVar11[6] == 0)) {
code_r0x000140010fdf:
            uVar4 = (*pcVar12)();
            (*pcVar8)(uVar4,auStack_18);
            fcn.1400153c0(uStack_10 ^ auStack_38);
            return;
        }
    } while( true );
}
