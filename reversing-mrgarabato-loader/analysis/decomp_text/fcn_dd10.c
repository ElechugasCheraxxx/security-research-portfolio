/* RVA 0xdd10  tam 1027 B  addr 0x14000dd10 */

void fcn.14000dd10(void)

{
    int64_t *piVar1;
    char *pcVar2;
    int64_t iVar3;
    char cVar4;
    code *pcVar5;
    code *pcVar6;
    uint32_t uVar7;
    int iVar8;
    int64_t iVar9;
    uint32_t uVar10;
    uint64_t uVar11;
    ulong ****ppppuVar12;
    char *pcVar13;
    int64_t *piVar14;
    code *pcVar15;
    code *pcVar16;
    int64_t unaff_GS_OFFSET;
    int64_t var_c0h;
    int64_t var_1d0h;
    uchar *puStack_300;
    uchar auStack_2f8 [24];
    ulong uStack_2e0;
    uchar *puStack_2d8;
    uint *puStack_2d0;
    uchar auStack_2c0 [8];
    ulong ****ppppuStack_2b8;
    ulong uStack_2b0;
    ulong uStack_2a8;
    uint64_t uStack_2a0;
    uchar uStack_298;
    ulong ****ppppuStack_290;
    ulong uStack_288;
    ulong uStack_278;
    uint64_t uStack_270;
    uchar uStack_268;
    int64_t iStack_260;
    uint auStack_258 [6];
    char acStack_23d [5];
    uchar auStack_238 [256];
    uchar auStack_138 [176];
    int64_t var_80h;
    int8_t var_bp_70h;
    int64_t var_bp_68h;
    int32_t var_60h;
    int64_t var_43h;
    uint64_t uStack_28;
    
    uStack_28 = *0x140020600 ^ auStack_2f8;
    pcVar16 = NULL;
    puStack_300 = auStack_138;
    func_0x000140158494(0,puStack_300,0x104);
    piVar1 = **(*(*(unaff_GS_OFFSET + 0x60) + 0x18) + 0x10);
    piVar14 = piVar1;
    do {
        iVar3 = piVar14[6];
        iVar9 = *(*(iVar3 + 0x3c) + 0x88 + iVar3) + iVar3;
        if ((iVar9 != iVar3) && (uVar11 = *(iVar9 + 0x18), *(iVar9 + 0x18) != 0)) {
            do {
                uVar10 = uVar11 - 1;
                uVar11 = uVar10;
                pcVar2 = *(*(iVar9 + 0x20) + uVar11 * 4 + iVar3) + iVar3;
                uVar7 = 0x811c9dc5;
                cVar4 = *pcVar2;
                if (cVar4 != '\0') {
                    do {
                        pcVar2 = pcVar2 + 1;
                        uVar7 = (cVar4 ^ uVar7) * 0x1000193;
                        cVar4 = *pcVar2;
                    } while (cVar4 != '\0');
                    if (uVar7 == 0x57949ea7) {
                        pcVar15 = *(*(iVar9 + 0x1c) + iVar3 + *(*(iVar9 + 0x24) + iVar3 + uVar11 * 2) * 4) + iVar3;
                        goto code_r0x00014000de0f;
                    }
                }
            } while (uVar10 != 0);
        }
        piVar14 = *piVar14;
    } while ((piVar14 != piVar1) && (piVar14[6] != 0));
    pcVar15 = pcVar16;
code_r0x00014000de0f:
    piVar1 = **(*(*(unaff_GS_OFFSET + 0x60) + 0x18) + 0x10);
    piVar14 = piVar1;
    do {
        iVar3 = piVar14[6];
        iVar9 = *(*(iVar3 + 0x3c) + 0x88 + iVar3) + iVar3;
        if ((iVar9 != iVar3) && (uVar11 = *(iVar9 + 0x18), *(iVar9 + 0x18) != 0)) {
            do {
                uVar10 = uVar11 - 1;
                uVar11 = uVar10;
                pcVar2 = *(iVar3 + uVar11 * 4 + *(iVar9 + 0x20)) + iVar3;
                uVar7 = 0x811c9dc5;
                cVar4 = *pcVar2;
                if (cVar4 != '\0') {
                    do {
                        pcVar2 = pcVar2 + 1;
                        uVar7 = (cVar4 ^ uVar7) * 0x1000193;
                        cVar4 = *pcVar2;
                    } while (cVar4 != '\0');
                    if (uVar7 == 0xe971d8a3) {
                        pcVar6 = *(*(iVar9 + 0x1c) + iVar3 + *(*(iVar9 + 0x24) + iVar3 + uVar11 * 2) * 4) + iVar3;
                        goto code_r0x00014000debf;
                    }
                }
            } while (uVar10 != 0);
        }
        piVar14 = *piVar14;
        if ((piVar14 == piVar1) || (piVar14[6] == 0)) {
            pcVar6 = pcVar16;
code_r0x00014000debf:
            ppppuStack_2b8 = *0x14001a450;
            uStack_2b0 = *0x14001a458;
            uStack_2a8 = *0x14001a2f0;
            uStack_2a0 = *0x14001a2f8;
            pcVar5 = pcVar16;
            do {
                *(&ppppuStack_2b8 + pcVar5) = *(&ppppuStack_2b8 + pcVar5) ^ pcVar5 + 0x53U;
                pcVar5 = pcVar5 + 1;
            } while (pcVar5 < 0x1f);
            uStack_298 = 0;
            (*pcVar6)(0xffffffff80000001,&ppppuStack_2b8,&iStack_260);
            if (iStack_260 != 0) {
                pcVar6 = pcVar16;
                do {
                    auStack_258[0] = 0x100;
                    pcVar2 = acStack_23d + 2;
                    iVar8 = pcVar6;
                    if (iVar8 < 0) {
                        uVar7 = -iVar8;
                        do {
                            pcVar13 = pcVar2;
                            pcVar2 = pcVar13 + -1;
                            *pcVar2 = uVar7 + (uVar7 / 10) * -10 + '0';
                            uVar7 = uVar7 / 10;
                        } while (uVar7 != 0);
                        pcVar2 = pcVar13 + -2;
                        *pcVar2 = '-';
                    }
                    else {
                        do {
                            pcVar2 = pcVar2 + -1;
                            pcVar5 = pcVar6 / 10;
                            *pcVar2 = pcVar6 + pcVar5 * -10 + '0';
                            pcVar6 = pcVar5;
                        } while (pcVar5 != 0);
                    }
                    func_0x0001400011e0(&ppppuStack_2b8,pcVar2,acStack_23d + 2,auStack_2c0);
                    ppppuVar12 = &ppppuStack_2b8;
                    if (0xf < uStack_2a0) {
                        ppppuVar12 = ppppuStack_2b8;
                    }
                    ppppuStack_290 = *0x14001a450;
                    uStack_288 = *0x14001a458;
                    uStack_278 = *0x14001a2f0;
                    uStack_270 = *0x14001a2f8;
                    pcVar6 = pcVar16;
                    do {
                        *(&ppppuStack_290 + pcVar6) = *(&ppppuStack_290 + pcVar6) ^ pcVar6 + 0x53U;
                        pcVar6 = pcVar6 + 1;
                    } while (pcVar6 < 0x1f);
                    uStack_268 = 0;
                    puStack_2d0 = auStack_258;
                    puStack_2d8 = auStack_238;
                    uStack_2e0 = 0;
                    (*pcVar15)(0xffffffff80000001,&ppppuStack_290,ppppuVar12,0xffff);
                    if (0xf < uStack_2a0) {
                        if (0xfff < uStack_2a0 + 1) {
                            if (0x1f < ppppuStack_2b8 + (-8 - ppppuStack_2b8[-1])) {
                                func_0x00014003afcd(ppppuStack_2b8[-1],uStack_2a0 + 0x28);
                                pcVar16 = swi(3);
                                (*pcVar16)();
                                return;
                            }
                        }
                        fcn.140015008();
                    }
                    iVar3 = func_0x000140015ed0(auStack_238,auStack_138);
                } while ((iVar3 == 0) && (pcVar6 = iVar8 + 1U, iVar8 + 1U < 10));
            }
            fcn.1400153c0(uStack_28 ^ &puStack_300);
            return;
        }
    } while( true );
}
