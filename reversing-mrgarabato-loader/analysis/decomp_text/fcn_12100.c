/* RVA 0x12100  tam 401 B  addr 0x140012100 */

void fcn.1400120f0(void)

{
    int64_t *piVar1;
    int64_t iVar2;
    char *pcVar3;
    char cVar4;
    code *pcVar5;
    uint32_t uVar6;
    int64_t iVar7;
    uint32_t uVar8;
    uint64_t uVar9;
    code *pcVar10;
    int64_t *piVar11;
    int64_t unaff_GS_OFFSET;
    uchar auStack_68 [32];
    ulong *puStack_48;
    ulong uStack_38;
    ulong uStack_30;
    uint uStack_28;
    uint uStack_24;
    ushort uStack_20;
    uchar uStack_1e;
    ulong uStack_18;
    uint64_t uStack_10;
    
    uStack_10 = *0x140020600 ^ auStack_68;
    pcVar5 = NULL;
    uStack_18 = 0;
    piVar1 = **(*(*(unaff_GS_OFFSET + 0x60) + 0x18) + 0x10);
    piVar11 = piVar1;
    do {
        iVar2 = piVar11[6];
        iVar7 = *(*(iVar2 + 0x3c) + 0x88 + iVar2) + iVar2;
        if ((iVar7 != iVar2) && (uVar9 = *(iVar7 + 0x18), *(iVar7 + 0x18) != 0)) {
            do {
                uVar8 = uVar9 - 1;
                uVar9 = uVar8;
                uVar6 = 0x811c9dc5;
                pcVar3 = *(*(iVar7 + 0x20) + uVar9 * 4 + iVar2) + iVar2;
                cVar4 = *pcVar3;
                if (cVar4 != '\0') {
                    do {
                        pcVar3 = pcVar3 + 1;
                        uVar6 = (cVar4 ^ uVar6) * 0x1000193;
                        cVar4 = *pcVar3;
                    } while (cVar4 != '\0');
                    if (uVar6 == 0xdf6a51c) {
                        pcVar10 = *(*(iVar7 + 0x1c) + iVar2 + *(*(iVar7 + 0x24) + iVar2 + uVar9 * 2) * 4) + iVar2;
                        goto code_r0x0001400121d0;
                    }
                }
            } while (uVar8 != 0);
        }
        piVar11 = *piVar11;
        if ((piVar11 == piVar1) || (piVar11[6] == 0)) {
            pcVar10 = pcVar5;
code_r0x0001400121d0:
            uStack_38 = *0x14001a470;
            uStack_30 = *0x14001a478;
            uStack_28 = 0x30393027;
            uStack_24 = 0x35312725;
            uStack_20 = 0x34;
            do {
                *(&uStack_38 + pcVar5) = *(&uStack_38 + pcVar5) ^ pcVar5 + 0x53U;
                pcVar5 = pcVar5 + 1;
            } while (pcVar5 < 0x19);
            puStack_48 = &uStack_18;
            uStack_1e = 0;
            (*pcVar10)(0xffffffff80000002,&uStack_38,0,0x20019);
            fcn.1400153c0(uStack_10 ^ auStack_68);
            return;
        }
    } while( true );
}
