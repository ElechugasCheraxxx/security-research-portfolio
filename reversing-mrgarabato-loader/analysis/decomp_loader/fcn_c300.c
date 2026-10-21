/* RVA 0xc300  tam 2155 B  addr 0x14000c300 */

//WARNING: Control flow encountered bad instruction data
//WARNING: Instruction at (ram,0x00014000c8da) overlaps instruction at (ram,0x00014000c8d8)
//
//WARNING: Variable defined which should be unmapped: var_8h
//WARNING: Variable defined which should be unmapped: var_10h

void fcn.14000c300(void)

{
    uint64_t uVar1;
    code *pcVar2;
    bool bVar3;
    bool bVar4;
    ulong uVar5;
    ulong uVar6;
    uchar *puVar7;
    char cVar8;
    int iVar9;
    int64_t iVar10;
    uint64_t uVar11;
    uint64_t uVar12;
    uchar *puVar13;
    ulong *puVar14;
    uint8_t uVar15;
    uchar *puVar16;
    uchar *puVar17;
    uint64_t uVar18;
    uchar *puVar19;
    uint64_t uVar20;
    uchar *puVar21;
    uint8_t *puVar22;
    int64_t iVar23;
    uint uVar24;
    uint uVar25;
    uint uVar26;
    uint uVar27;
    int64_t var_110h;
    uchar *puStack_250;
    uchar auStack_240 [24];
    ulong uStack_228;
    uint8_t auStack_218 [8];
    uchar *puStack_210;
    ulong uStack_208;
    ulong uStack_200;
    uint64_t uStack_1f8;
    uchar auStack_1f0 [8];
    uchar *puStack_1e8;
    ulong uStack_1e0;
    uint64_t uStack_1d8;
    uint64_t uStack_1d0;
    uchar *puStack_1c0;
    ulong uStack_1b8;
    uint64_t uStack_1b0;
    uint64_t uStack_1a8;
    uchar *puStack_1a0;
    ulong uStack_198;
    int64_t iStack_190;
    uint64_t uStack_188;
    ulong uStack_180;
    ulong uStack_178;
    ulong uStack_170;
    ulong uStack_168;
    ulong uStack_148;
    ulong uStack_140;
    uchar auStack_138 [48];
    uchar auStack_108 [128];
    int64_t var_80h;
    int64_t var_70h;
    int64_t var_68h;
    int64_t var_60h;
    int64_t var_50h;
    int64_t var_48h;
    int64_t var_40h;
    int64_t var_30h;
    int64_t var_28h;
    int64_t var_bp_20h;
    int64_t var_10h;
    int64_t var_8h;
    
    puVar13 = &stack0xfffffffffffffec0;
    puVar16 = &stack0xfffffffffffffdc0;
    var_28h = *0x14002f500 ^ &stack0xfffffffffffffdc0;
    if (*0x14002f9b8 != '\0') goto code_r0x00014000cb17;
    puVar16 = &stack0xfffffffffffffdb8;
    puVar19 = &stack0xfffffffffffffdb8;
    puStack_250 = 0x14000c345;
    func_0x00014059f1dd(puVar13,0x104);
    puStack_1a0 = NULL;
    uStack_198 = 0;
    iStack_190 = 0;
    uStack_188 = 0;
    iVar23 = -1;
    do {
        iVar23 = iVar23 + 1;
    } while (puVar13[iVar23] != '\0');
    puStack_250 = 0x14000c376;
    fcn.140001bc0(&stack0xfffffffffffffe60,puVar13);
    iVar23 = iStack_190;
    puVar7 = puStack_1a0;
    uVar20 = 0x7fffffffffffffff - iStack_190;
    puVar17 = &stack0xfffffffffffffdb8;
    if (0xd < uVar20) {
        puVar17 = &stack0xfffffffffffffe60;
        if (0xf < uStack_188) {
            puVar17 = puStack_1a0;
        }
        puStack_1c0 = NULL;
        uStack_1b8 = 0;
        uStack_1b0 = 0;
        uStack_1a8 = 0;
        uVar1 = iStack_190 + 0xe;
        uVar18 = 0xf;
        puVar21 = &stack0xfffffffffffffe40;
        if (uVar1 < 0x10) {
code_r0x00014000c43e:
            puStack_250 = 0x14000c454;
            uStack_1b0 = uVar1;
            uStack_1a8 = uVar18;
            fcn.14001b7f8(puVar21,puVar17,iVar23);
            *(puVar21 + iVar23) = str.WinDivert.dll._0_8_;
            *(puVar21 + iVar23 + 8) = str.WinDivert.dll._8_4_;
            *(puVar21 + iVar23 + 0xc) = str.WinDivert.dll._12_2_;
            puVar21[uVar1] = 0;
            uVar1 = uStack_188;
            puVar17 = &stack0xfffffffffffffdb8;
            if (uVar20 < 0x10) goto code_r0x00014000cb65;
            puVar17 = &stack0xfffffffffffffe60;
            if (0xf < uStack_188) {
                puVar17 = puVar7;
            }
            puStack_1e8 = NULL;
            uStack_1e0 = 0;
            puVar21 = NULL;
            uStack_1d8 = 0;
            uStack_1d0 = 0;
            uVar20 = iVar23 + 0x10;
            uVar18 = 0xf;
            puVar16 = &stack0xfffffffffffffe18;
            if (0xf < uVar20) {
                uVar18 = uVar20 | 0xf;
                if (0x7fffffffffffffff < uVar18) {
                    uVar18 = 0x7fffffffffffffff;
                    uVar11 = 0x8000000000000027;
code_r0x00014000c4eb:
                    puStack_250 = 0x14000c4f3;
                    iVar10 = fcn.14001a904(uVar11);
                    puVar16 = &stack0xfffffffffffffdb8;
                    if (iVar10 == 0) goto code_r0x00014000ca6e;
                    puVar21 = iVar10 + 0x27U & 0xffffffffffffffe0;
                    *(puVar21 + -8) = iVar10;
code_r0x00014000c540:
                    puVar16 = puVar21;
                    puStack_1e8 = puVar21;
                    goto code_r0x00014000c545;
                }
                if (uVar18 < 0x16) {
                    uVar18 = 0x16;
                }
                if (uVar18 + 1 < 0x1000) {
                    if (uVar18 != 0xffffffffffffffff) {
                        puStack_250 = 0x14000c53d;
                        puVar21 = fcn.14001a904();
                    }
                    goto code_r0x00014000c540;
                }
                uVar11 = uVar18 + 0x28;
                puVar16 = &stack0xfffffffffffffdb8;
                if (uVar18 + 1 < uVar11) goto code_r0x00014000c4eb;
                goto code_r0x00014000cb53;
            }
code_r0x00014000c545:
            puStack_250 = 0x14000c55d;
            uStack_1d8 = uVar20;
            uStack_1d0 = uVar18;
            fcn.14001b7f8(puVar16,puVar17,iVar23);
            *(puVar16 + iVar23) = str.WinDivert64.sys._0_8_;
            *(puVar16 + iVar23 + 8) = str.WinDivert64.sys._8_8_;
            puVar16[uVar20] = 0;
            puStack_210 = NULL;
            uStack_208 = 0;
            uStack_200 = 0;
            uStack_1f8 = 0;
            puStack_250 = 0x14000c595;
            fcn.140001bc0(&stack0xfffffffffffffdf0,
                          "https://panel.mrgarabato.com/Download/Paquete/MrGarabato/Profesional/pack/MrGarabato/FakeLag/WinDivert.dll"
                          ,0x6a);
            puVar16 = &stack0xfffffffffffffe40;
            if (0xf < uStack_1a8) {
                puVar16 = puStack_1c0;
            }
            puVar17 = &stack0xfffffffffffffdf0;
            if (0xf < uStack_1f8) {
                puVar17 = puStack_210;
            }
            uStack_228 = 0;
            puStack_250 = 0x14000c5c5;
            iVar9 = func_0x00014001b7c8(0,puVar17,puVar16,0);
            if (iVar9 < 0) {
code_r0x00014000c5e6:
                bVar3 = false;
            }
            else {
                puVar16 = &stack0xfffffffffffffe40;
                if (0xf < uStack_1a8) {
                    puVar16 = puStack_1c0;
                }
                puStack_250 = 0x14000c5dc;
                iVar9 = func_0x00014048a1f7(puVar16);
                if (iVar9 == 0) goto code_r0x00014000c5e6;
                bVar3 = true;
            }
            if (0xf < uStack_1f8) {
                if (0xfff < uStack_1f8 + 1) {
                    if (0x1f < puStack_210 + (-8 - *(puStack_210 + -8))) {
                        puStack_250 = 0x14000c622;
                        func_0x0001404be100(*(puStack_210 + -8),uStack_1f8 + 0x28);
                    }
                }
                puStack_250 = 0x14000c629;
                fcn.14001a940();
            }
            puStack_210 = NULL;
            uStack_208 = 0;
            uStack_200 = 0;
            uStack_1f8 = 0;
            puStack_250 = 0x14000c651;
            fcn.140001bc0(&stack0xfffffffffffffdf0,
                          "https://panel.mrgarabato.com/Download/Paquete/MrGarabato/Profesional/pack/MrGarabato/FakeLag/WinDivert64.sys"
                          ,0x6c);
            puVar16 = &stack0xfffffffffffffe18;
            if (0xf < uStack_1d0) {
                puVar16 = puStack_1e8;
            }
            puVar17 = &stack0xfffffffffffffdf0;
            if (0xf < uStack_1f8) {
                puVar17 = puStack_210;
            }
            uStack_228 = 0;
            puStack_250 = 0x14000c682;
            iVar9 = func_0x00014001b7c8(0,puVar17,puVar16,0);
            if (iVar9 < 0) {
code_r0x00014000c6a5:
                bVar4 = false;
                puVar16 = puVar19;
            }
            else {
                puVar16 = &stack0xfffffffffffffe18;
                if (0xf < uStack_1d0) {
                    puVar16 = puStack_1e8;
                }
                puVar19 = &stack0xfffffffffffffdb0;
                puStack_250 = puVar17;
                iVar9 = func_0x00014055997e(puVar16);
                if (iVar9 == 0) goto code_r0x00014000c6a5;
                bVar4 = true;
                puVar16 = &stack0xfffffffffffffdb0;
            }
            uVar20 = *(puVar16 + 0x50);
            if (0xf < uVar20) {
                uVar18 = uVar20 + 1;
                if ((0xfff < uVar20 + 1) &&
                   (uVar18 = uVar20 + 0x28, 0x1f < (*(puVar16 + 0x38) - *(*(puVar16 + 0x38) + -8)) - 8U)) {
                    *(puVar16 + -8) = 0x14000c6e0;
                    func_0x00014061246e();
                    pcVar2 = swi(3);
                    (*pcVar2)();
                    return;
                }
                uVar20 = uVar18;
                *(puVar16 + -8) = 0x14000c6e7;
                fcn.14001a940();
            }
            if ((!bVar3) || (!bVar4)) {
                *(puVar16 + -8) = 0x14000ca32;
                func_0x00014054768f(0,"No se pudieron descargar los archivos necesarios para FakeLag.\n",str.Instalaci
                                    ,0x10);
            }
            else {
                iVar23 = *(puVar16 + 0x70);
                if (0x7fffffffffffffffU - iVar23 < 0x38) {
                    *(puVar16 + -8) = 0x14000cb4c;
                    fcn.140009520();
                    goto code_r0x00014000cb4d;
                }
                puVar13 = puVar16 + 0x60;
                if (0xf < *(puVar16 + 0x78)) {
                    puVar13 = *(puVar16 + 0x60);
                }
                *(puVar16 + 0x38) = 0;
                *(puVar16 + 0x40) = 0;
                *(puVar16 + 0x48) = 0;
                *(puVar16 + 0x50) = 0;
                uVar18 = iVar23 + 0x38;
                uVar11 = 0xf;
                puVar22 = puVar16 + 0x38;
                if (0xf < uVar18) {
                    uVar11 = uVar18 | 0xf;
                    if (uVar11 < 0x8000000000000000) {
                        if (uVar11 < 0x16) {
                            uVar11 = 0x16;
                        }
                        if (0xfff < uVar11 + 1) {
                            uVar12 = uVar11 + 0x28;
                            if (uVar11 + 1 < uVar12) goto code_r0x00014000c769;
                            goto code_r0x00014000cb59;
                        }
                        if (uVar11 == 0xffffffffffffffff) {
                            puVar22 = NULL;
                        }
                        else {
                            *(puVar16 + -8) = 0x14000c7be;
                            puVar22 = fcn.14001a904();
                        }
                    }
                    else {
                        uVar11 = 0x7fffffffffffffff;
                        uVar12 = 0x8000000000000027;
code_r0x00014000c769:
                        *(puVar16 + -8) = 0x14000c771;
                        iVar10 = fcn.14001a904(uVar12);
                        if (iVar10 == 0) {
                            *(puVar16 + -8) = uVar20;
                            *(puVar16 + -0x10) = 0x14000c7b3;
                            func_0x00014057fc84();
                            pcVar2 = swi(3);
                            (*pcVar2)();
                            return;
                        }
                        puVar22 = iVar10 + 0x27U & 0xffffffffffffffe0;
                        *(puVar22 + -8) = iVar10;
                    }
                    *(puVar16 + 0x38) = puVar22;
                }
                *(puVar16 + 0x48) = uVar18;
                *(puVar16 + 0x50) = uVar11;
                *puVar22 = str.sc_create_MiDriver_type_kernel_start_demand_binPath__._0_8_;
                *(puVar22 + 8) = str.sc_create_MiDriver_type_kernel_start_demand_binPath__._8_8_;
                *(puVar22 + 0x10) = str.sc_create_MiDriver_type_kernel_start_demand_binPath__._16_4_;
                *(puVar22 + 0x14) = str.sc_create_MiDriver_type_kernel_start_demand_binPath__._20_4_;
                *(puVar22 + 0x18) = str.sc_create_MiDriver_type_kernel_start_demand_binPath__._24_4_;
                *(puVar22 + 0x1c) = str.sc_create_MiDriver_type_kernel_start_demand_binPath__._28_4_;
                *(puVar22 + 0x20) = str.sc_create_MiDriver_type_kernel_start_demand_binPath__._32_8_;
                *(puVar22 + 0x28) = str.sc_create_MiDriver_type_kernel_start_demand_binPath__._40_8_;
                *(puVar22 + 0x30) = str.sc_create_MiDriver_type_kernel_start_demand_binPath__._48_8_;
                *(puVar16 + -8) = 0x14000c810;
                fcn.14001b7f8(puVar22 + 0x38,puVar13,iVar23);
                puVar22[uVar18] = 0;
                uVar20 = *(puVar16 + 0x48);
                if (*(puVar16 + 0x50) == uVar20) {
                    *(puVar16 + 0x20) = 1;
                    *(puVar16 + -8) = 0x14000c870;
                    puVar14 = func_0x0001400024c0(puVar16 + 0x38,1,0,0x140022950);
                }
                else {
                    *(puVar16 + 0x48) = uVar20 + 1;
                    puVar13 = puVar16 + 0x38;
                    if (0xf < *(puVar16 + 0x50)) {
                        puVar13 = *(puVar16 + 0x38);
                    }
                    *(puVar13 + uVar20) = 0x22;
                    puVar14 = puVar16 + 0x38;
                }
                uStack_180 = 0;
                uStack_178 = 0;
                uStack_170 = 0;
                uStack_168 = 0;
                uStack_180 = *puVar14;
                uStack_178 = puVar14[1];
                uVar24 = *(puVar14 + 2);
                uVar25 = *(puVar14 + 0x14);
                uVar26 = *(puVar14 + 3);
                uVar27 = *(puVar14 + 0x1c);
                uStack_170 = puVar14[2];
                uStack_168 = puVar14[3];
                puVar14[2] = 0;
                puVar14[3] = 0xf;
                *puVar14 = 0;
                uVar20 = *(puVar16 + 0x50);
                if (0xf < uVar20) {
                    uVar18 = uVar20 + 1;
                    iVar23 = *(puVar16 + 0x38);
                    iVar10 = iVar23;
                    if (0xfff < uVar18) {
                        uVar18 = uVar20 + 0x28;
                        iVar10 = *(iVar23 + -8);
                        if (0x1f < (iVar23 - iVar10) - 8U) {
                            *(puVar16 + -8) = 0x14000c8d8;
                            func_0x0001405d50c4();
    //WARNING: Bad instruction - Truncating control flow here
                            halt_baddata();
                        }
                    }
                    *(puVar16 + -8) = 0x14000c8df;
                    fcn.14001a940(iVar10,uVar18);
                }
                *(puVar16 + 0x48) = *0x140022ea0;
                *(puVar16 + 0x50) = *0x140022ea8;
                puVar16[0x38] = 0;
                *(puVar16 + -8) = 0x14000c906;
                func_0x00014000b750(puVar16 + 0x30,&stack0xfffffffffffffe80,5000);
                uVar15 = 0xf4;
                *(puVar16 + -8) = 0x14000c910;
                func_0x000140548235();
                *puVar22 = *puVar22 & uVar15;
                *(puVar16 + -8) = puVar22;
                *puVar22 = *puVar22 >> 1 | *puVar22 << 7;
                puVar13 = uStack_140;
                *(puVar16 + -0x10) = puVar22;
                puVar16 = &stack0xfffffffffffffec8;
                *(uStack_140 + -0x10) = uVar24;
                *(uStack_140 + -0xc) = uVar25;
                *(uStack_140 + -8) = uVar26;
                *(uStack_140 + -4) = uVar27;
                puVar17 = uStack_140 + -0x20;
                uStack_140 = 0x14000c936;
                fcn.140001bc0(puVar17,"sc start MiDriver",0x11);
                uStack_140 = 0x14000c94b;
                cVar8 = func_0x00014000b750(&stack0xfffffffffffffef8,puVar13 + -0x20,5000);
                if (cVar8 == '\0') {
                    uStack_140 = 0x14000c96a;
                    func_0x000140577285(0,str.No_se_pudo_iniciar_el_driver_WinDivert._nFakeLag_podr,"Advertencia",
                                        0x30);
    //WARNING: Bad instruction - Truncating control flow here
                    halt_baddata();
                }
                *0x14002f9b8 = '\x01';
                uVar20 = *(puVar13 + -8);
                if (0xf < uVar20) {
                    uVar18 = uVar20 + 1;
                    iVar23 = *(puVar13 + -0x20);
                    iVar10 = iVar23;
                    if (0xfff < uVar18) {
                        uVar18 = uVar20 + 0x28;
                        iVar10 = *(iVar23 + -8);
                        uStack_140 = (iVar23 - iVar10) - 8;
                        if (0x1f < uStack_140) {
                            uStack_148 = 0x14000c9af;
                            func_0x0001400452f0();
                            pcVar2 = swi(3);
                            (*pcVar2)();
                            return;
                        }
                    }
                    uStack_140 = 0x14000c9b5;
                    fcn.14001a940(iVar10,uVar18);
                }
                uVar6 = *0x140022ea8;
                uVar5 = *0x140022ea0;
                *(puVar13 + -0x10) = *0x140022ea0;
                *(puVar13 + -8) = uVar6;
                puVar13[-0x20] = 0;
                uVar20 = *(puVar13 + -0x28);
                if (0xf < uVar20) {
                    uVar18 = uVar20 + 1;
                    if ((0xfff < uVar18) &&
                       (uVar18 = uVar20 + 0x28, 0x1f < (*(puVar13 + -0x40) - *(*(puVar13 + -0x40) + -8)) - 8U)) {
                        uStack_148 = 0x14000c9fe;
                        func_0x0001404f0182();
                        pcVar2 = swi(3);
                        (*pcVar2)();
                        return;
                    }
                    uStack_140 = 0x14000ca04;
                    fcn.14001a940(uVar5,uVar18);
                }
                uVar5 = *0x140022ea8;
                *(puVar13 + -0x30) = *0x140022ea0;
                *(puVar13 + -0x28) = uVar5;
                puVar13[-0x40] = 0;
            }
            uVar20 = *(puVar16 + 0x78);
            if (0xf < uVar20) {
                uVar18 = uVar20 + 1;
                iVar23 = *(puVar16 + 0x60);
                iVar10 = iVar23;
                if (0xfff < uVar18) {
                    uVar18 = uVar20 + 0x28;
                    iVar10 = *(iVar23 + -8);
                    if (0x1f < (iVar23 - iVar10) - 8U) {
code_r0x00014000ca6e:
                        *(puVar16 + -8) = 0x14000ca73;
                        func_0x0001400c32cb();
                        pcVar2 = swi(3);
                        (*pcVar2)();
                        return;
                    }
                }
                *(puVar16 + -8) = 0x14000ca7a;
                fcn.14001a940(iVar10,uVar18);
            }
            *(puVar16 + 0x70) = 0;
            *(puVar16 + 0x78) = 0xf;
            puVar16[0x60] = 0;
            uVar20 = *(puVar13 + -0x68);
            if (0xf < uVar20) {
                uVar12 = uVar20 + 1;
                uVar18 = *(puVar13 + -0x80);
                uVar11 = uVar18;
                if (0xfff < uVar12) {
                    uVar12 = uVar20 + 0x28;
                    uVar11 = *(uVar18 - 8);
                    if (0x1f < (uVar18 - uVar11) - 8) {
code_r0x00014000cabf:
                        *(puVar16 + -8) = uVar11;
                        *(puVar16 + -0x10) = 0x14000cac5;
                        fcn.140539a47();
                        pcVar2 = swi(3);
                        (*pcVar2)();
                        return;
                    }
                }
                *(puVar16 + -8) = 0x14000cacb;
                fcn.14001a940(uVar11,uVar12);
            }
            *(puVar13 + -0x70) = *0x140022ea0;
            *(puVar13 + -0x68) = *0x140022ea8;
            puVar13[-0x80] = 0;
            if (0xf < uVar1) {
                uVar20 = uVar1 + 1;
                puVar17 = puVar7;
                if (0xfff < uVar20) {
                    uVar20 = uVar1 + 0x28;
                    puVar17 = *(puVar7 + -8);
                    if (0x1f < puVar7 + (-8 - puVar17)) {
                        *(puVar16 + -8) = 0x14000cb0d;
                        func_0x000140585c26(*0x140022ea0,uVar20);
                        uVar20 = 0xcc;
                    }
                }
                *(puVar16 + -8) = 0x14000cb17;
                fcn.14001a940(puVar17,uVar20);
            }
code_r0x00014000cb17:
            uVar20 = *(puVar13 + 0x110);
            *(puVar16 + -8) = 0x14000cb26;
            func_0x00014001ad00(uVar20 ^ puVar16);
            return;
        }
        uVar18 = uVar1 | 0xf;
        if (0x7fffffffffffffff < uVar18) {
            uVar18 = 0x7fffffffffffffff;
            uVar11 = 0x8000000000000027;
code_r0x00014000c3e7:
            puStack_250 = 0x14000c3ef;
            iVar10 = fcn.14001a904();
            puVar16 = &stack0xfffffffffffffdb8;
            if (iVar10 == 0) goto code_r0x00014000cabf;
            puVar21 = iVar10 + 0x27U & 0xffffffffffffffe0;
            *(puVar21 + -8) = iVar10;
code_r0x00014000c43a:
            puStack_1c0 = puVar21;
            goto code_r0x00014000c43e;
        }
        if (uVar18 < 0x16) {
            uVar18 = 0x16;
        }
        if (uVar18 + 1 < 0x1000) {
            if (uVar18 == 0xffffffffffffffff) {
                puVar21 = NULL;
            }
            else {
                puStack_250 = 0x14000c433;
                puVar21 = fcn.14001a904();
            }
            goto code_r0x00014000c43a;
        }
        uVar11 = uVar18 + 0x28;
        if (uVar18 + 1 < uVar11) goto code_r0x00014000c3e7;
code_r0x00014000cb4d:
        *(puVar16 + -8) = 0x14000cb52;
        fcn.140009490();
code_r0x00014000cb53:
        *(puVar16 + -8) = 0x14000cb58;
        fcn.140009490();
code_r0x00014000cb59:
        *(puVar16 + -8) = 0x14000cb5e;
        fcn.140009490();
        puVar17 = puVar16;
    }
    *(puVar17 + -8) = 0x14000cb64;
    fcn.140009520();
code_r0x00014000cb65:
    *(puVar17 + -8) = 0x14000cb6a;
    fcn.140009520();
    pcVar2 = swi(3);
    (*pcVar2)();
    return;
}
