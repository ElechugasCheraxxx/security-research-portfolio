/* RVA 0x11020  tam 611 B  addr 0x140011020 */

void fcn.140011020(void)

{
    int64_t *piVar1;
    int64_t iVar2;
    char cVar3;
    char *pcVar4;
    ulong uVar5;
    code *pcVar6;
    uint32_t uVar7;
    int64_t iVar8;
    int64_t *piVar9;
    uint32_t uVar10;
    uint64_t uVar11;
    int64_t unaff_GS_OFFSET;
    uchar auStack_508 [32];
    uchar auStack_4e8 [48];
    uint uStack_4b8;
    uint64_t uStack_18;
    
    uStack_18 = *0x140020600 ^ auStack_508;
    func_0x000140015eca(auStack_4e8,0,0x4d0);
    piVar1 = **(*(*(unaff_GS_OFFSET + 0x60) + 0x18) + 0x10);
    piVar9 = piVar1;
    do {
        iVar2 = piVar9[6];
        iVar8 = *(*(iVar2 + 0x3c) + 0x88 + iVar2) + iVar2;
        if ((iVar8 != iVar2) && (uVar11 = *(iVar8 + 0x18), *(iVar8 + 0x18) != 0)) {
            do {
                uVar10 = uVar11 - 1;
                uVar11 = uVar10;
                uVar7 = 0x811c9dc5;
                pcVar4 = *(*(iVar8 + 0x20) + uVar11 * 4 + iVar2) + iVar2;
                cVar3 = *pcVar4;
                if (cVar3 != '\0') {
                    do {
                        pcVar4 = pcVar4 + 1;
                        uVar7 = (cVar3 ^ uVar7) * 0x1000193;
                        cVar3 = *pcVar4;
                    } while (cVar3 != '\0');
                    if (uVar7 == 0x9bc5a608) {
                        pcVar6 = *(*(iVar8 + 0x1c) + iVar2 + *(*(iVar8 + 0x24) + iVar2 + uVar11 * 2) * 4) + iVar2;
                        goto code_r0x000140011110;
                    }
                }
            } while (uVar10 != 0);
        }
        piVar9 = *piVar9;
    } while ((piVar9 != piVar1) && (piVar9[6] != 0));
    pcVar6 = NULL;
code_r0x000140011110:
    uVar5 = (*pcVar6)();
    uStack_4b8 = 0x100010;
    piVar1 = **(*(*(unaff_GS_OFFSET + 0x60) + 0x18) + 0x10);
    piVar9 = piVar1;
    do {
        iVar2 = piVar9[6];
        iVar8 = *(*(iVar2 + 0x3c) + 0x88 + iVar2) + iVar2;
        if ((iVar8 != iVar2) && (uVar11 = *(iVar8 + 0x18), *(iVar8 + 0x18) != 0)) {
            do {
                uVar10 = uVar11 - 1;
                uVar11 = uVar10;
                uVar7 = 0x811c9dc5;
                pcVar4 = *(*(iVar8 + 0x20) + uVar11 * 4 + iVar2) + iVar2;
                cVar3 = *pcVar4;
                if (cVar3 != '\0') {
                    do {
                        pcVar4 = pcVar4 + 1;
                        uVar7 = (cVar3 ^ uVar7) * 0x1000193;
                        cVar3 = *pcVar4;
                    } while (cVar3 != '\0');
                    if (uVar7 == 0x85cca27e) {
                        pcVar6 = *(*(iVar8 + 0x1c) + iVar2 + *(*(iVar8 + 0x24) + iVar2 + uVar11 * 2) * 4) + iVar2;
                        goto code_r0x0001400111d0;
                    }
                }
            } while (uVar10 != 0);
        }
        piVar9 = *piVar9;
        if ((piVar9 == piVar1) || (piVar9[6] == 0)) {
            pcVar6 = NULL;
code_r0x0001400111d0:
            (*pcVar6)(uVar5,auStack_4e8);
            fcn.1400153c0(uStack_18 ^ auStack_508);
            return;
        }
    } while( true );
}
