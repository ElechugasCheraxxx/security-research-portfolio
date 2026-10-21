/* RVA 0x7f10  tam 3871 B  addr 0x140007f10 */

//WARNING: Instruction at (ram,0x000140008fd8) overlaps instruction at (ram,0x000140008fd6)
//
//WARNING: Variable defined which should be unmapped: var_10h
//WARNING: Variable defined which should be unmapped: var_20h
//WARNING: Variable defined which should be unmapped: var_28h
//WARNING: Variable defined which should be unmapped: var_30h
//WARNING: Removing unreachable block (ram,0x000140009146)

void fcn.140007f10(uint64_t *param_1,ulong param_2,ulong *param_3,ulong param_4,ulong param_5,ulong *param_6)

{
    char *pcVar1;
    code *pcVar2;
    int iVar3;
    uint uVar4;
    uint32_t uVar5;
    int64_t iVar6;
    uint64_t uVar7;
    ulong uVar8;
    int64_t iVar9;
    int64_t iVar10;
    uint8_t *puVar11;
    uint64_t uVar12;
    uint64_t uVar13;
    ulong *unaff_RBX;
    uchar *puVar14;
    uchar *puVar15;
    uint64_t uVar16;
    uint8_t *unaff_RDI;
    uint64_t unaff_R15;
    uint8_t uVar17;
    ulong extraout_XMM0_Qa;
    ulong extraout_XMM0_Qa_00;
    int64_t var_8h;
    int64_t var_10h_2;
    int32_t var_18h;
    int64_t var_20h_2;
    uint64_t uStackX_20;
    int64_t var_50h_2;
    int64_t var_60h_2;
    int64_t var_68h;
    int64_t var_98h;
    int64_t var_a8h;
    int64_t var_b0h;
    int64_t var_e0h;
    int64_t var_2e0h;
    int64_t var_12e0h;
    uint32_t in_stack_ffffffff9383fc88;
    uint32_t in_stack_ffffffffc183fc88;
    uint8_t *puStack_13b0;
    ulong uStack_13a8;
    uint auStack_1380 [2];
    ulong uStack_1378;
    ulong uStack_1370;
    ulong uStack_1368;
    uchar *puStack_1360;
    ulong uStack_1358;
    ulong uStack_1350;
    ulong uStack_1348;
    ulong uStack_1340;
    ulong uStack_1338;
    uchar *puStack_1330;
    ulong uStack_1328;
    ulong uStack_1320;
    ulong uStack_1318;
    uint64_t uStack_1308;
    uint64_t uStack_1300;
    uint64_t uStack_12f8;
    uint64_t auStack_12e8 [4];
    int aiStack_12c8 [2];
    ushort uStack_12c0;
    unkbyte6 Stack_12be;
    uint64_t uStack_12a8;
    int64_t aiStack_12a0 [4];
    uint uStack_1280;
    uint uStack_127c;
    uint64_t uStack_1278;
    uint64_t uStack_1270;
    uchar auStack_1258 [512];
    uchar auStack_1058 [4056];
    ulong auStack_80 [2];
    ulong uStack_70;
    int64_t var_60h;
    uint64_t uStack_60;
    int64_t var_50h;
    ulong uStack_50;
    int64_t var_40h;
    int64_t var_30h;
    int64_t var_28h;
    int64_t var_20h;
    int64_t var_10h;
    
    puVar14 = &stack0xffffffffffffffc0;
    var_40h = 0x140007f2f;
    iVar6 = func_0x000140015360();
    iVar6 = -iVar6;
    var_50h = *0x140020600 ^ &stack0xffffffffffffffc0 + iVar6;
    aiStack_12a0[1] = 0;
    aiStack_12a0[2] = 0;
    aiStack_12a0[3] = 7;
    aiStack_12a0[0] = 0;
    auStack_12e8[1] = 0;
    auStack_12e8[2] = 0;
    auStack_12e8[3] = 7;
    auStack_12e8[0] = 0;
    uStack_1370 = 0;
    uStack_1368 = 0;
    uStack_1350 = 0;
    uStack_1348 = 0;
    uStack_1340 = 0;
    uStack_1338 = 0;
    uStack_1320 = 0;
    uStack_1318 = 0;
    uStack_1378 = 0x68;
    puStack_1360 = &stack0xffffffffffffeda8;
    uStack_1358 = 0x100;
    puStack_1330 = &stack0xffffffffffffefa8;
    uStack_1328 = 0x800;
    if (7 < param_3[3]) {
        param_3 = *param_3;
    }
    *(&fcn.140007f10::var_40h + iVar6) = 0x140007ffc;
    func_0x0001402b43bf(param_3,0,0,&stack0xffffffffffffec88);
    *unaff_RDI = *unaff_RDI >> 5 | *unaff_RDI << 3;
    if (uStack_1320 < 0xb) {
        *(&fcn.140007f10::var_40h + iVar6) = 0x140008055;
        func_0x0001400021e0(param_6,0xb,0,"Invalid URL");
    }
    else {
        unaff_RBX = param_6;
        if (0xf < uStack_1320) {
            unaff_RBX = *param_6;
        }
        param_6[2] = 0xb;
        *(&fcn.140007f10::var_40h + iVar6) = 0x140008039;
        fcn.140015ec4(unaff_RBX,"Invalid URL",0xb);
        *(unaff_RBX + 0xb) = 0;
    }
    *param_1 = 0;
    param_1[1] = 0;
    param_1[2] = 0;
    param_1[3] = 0xf;
    *param_1 = 0;
    if (auStack_12e8[3] < 8) {
code_r0x0001400080b0:
        auStack_12e8[2] = 0;
        auStack_12e8[0] = auStack_12e8[0] & 0xffffffffffff0000;
        auStack_12e8[3] = 7;
        puVar15 = &stack0xffffffffffffffc0 + iVar6;
        if (aiStack_12a0[3] < 8) goto code_r0x0001400092c1;
        if (0xfff < aiStack_12a0[3] * 2 + 2U) {
            iVar9 = *(aiStack_12a0[0] + -8);
            if (0x1f < (aiStack_12a0[0] - iVar9) - 8U) {
                *(&fcn.140007f10::var_40h + iVar6) = 0;
                *(&stack0xffffffffffffffb0 + iVar6) = 0x140008e29;
                uVar8 = func_0x000140025ad1(iVar9,aiStack_12a0[3] * 2 + 0x29);
                *(&stack0xffffffffffffffb0 + iVar6) = uVar8;
                *(&fcn.140007f10::var_50h + iVar6) = 0x140008e35;
                iVar3 = func_0x00014002dbcd(extraout_XMM0_Qa,0);
                if (iVar3 == 0) {
                    *(&fcn.140007f10::var_50h + iVar6) = 0;
                    *(&stack0xffffffffffffffa0 + iVar6) = 0x140008e43;
                    uVar4 = func_0x0001401c24d5();
                    *(&stack0xffffffffffffffa0 + iVar6) = 0x140008e4f;
                    uVar8 = func_0x00014000a3b0(&fcn.140007f10::var_10h_2 + iVar6,uVar4);
                    *(&stack0xffffffffffffffa0 + iVar6) = 0x140008e64;
                    uVar8 = func_0x0001400017b0(&fcn.140007f10::var_10h + iVar6,"WinHttpReceiveResponse failed: ",
                                                uVar8);
                    *(&stack0xffffffffffffffa0 + iVar6) = 0x140008e6f;
                    func_0x000140004510(param_6,uVar8);
                    uVar12 = *(&fcn.140007f10::var_8h + iVar6);
                    if (0xf < uVar12) {
                        uVar13 = uVar12 + 1;
                        iVar9 = *(&fcn.140007f10::var_10h + iVar6);
                        iVar10 = iVar9;
                        if (0xfff < uVar13) {
                            uVar13 = uVar12 + 0x28;
                            iVar10 = *(iVar9 + -8);
                            uVar12 = (iVar9 - iVar10) - 8;
                            if (0x1f < uVar12) {
                                *(&stack0xffffffffffffffa0 + iVar6) = uVar12;
                                *(&fcn.140007f10::var_60h + iVar6) = 0x140008ea9;
                                func_0x0001402d67b6();
                                pcVar2 = swi(3);
                                (*pcVar2)();
                                return;
                            }
                        }
                        *(&stack0xffffffffffffffa0 + iVar6) = 0x140008eaf;
                        fcn.140015008(iVar10,uVar13);
                    }
                    *(&stack0xfffffffffffffff8 + iVar6) = *0x140018f70;
                    *(&fcn.140007f10::var_8h + iVar6) = *0x140018f78;
                    *(&fcn.140007f10::var_10h + iVar6) = 0;
                    uVar12 = *(&stack0x00000020 + iVar6);
                    if (0xf < uVar12) {
                        uVar13 = uVar12 + 1;
                        if ((0xfff < uVar13) &&
                           (uVar13 = uVar12 + 0x28,
                           0x1f < (*(&fcn.140007f10::var_10h_2 + iVar6) - *(*(&fcn.140007f10::var_10h_2 + iVar6) + -8))
                                  - 8U)) {
                            *(&stack0xffffffffffffffa0 + iVar6) = unaff_RBX;
                            *(&fcn.140007f10::var_60h + iVar6) = 0x140008efc;
                            func_0x0001402a3f35();
                            pcVar2 = swi(3);
                            (*pcVar2)();
                            return;
                        }
                        *(&stack0xffffffffffffffa0 + iVar6) = 0x140008f02;
                        fcn.140015008(*0x140018f70,uVar13);
                    }
                    *(&stack0xffffffffffffffa0 + iVar6) = unaff_RDI;
                    *(&fcn.140007f10::var_60h + iVar6) = 0x140008f0b;
                    func_0x000140295ec2();
                    *(&fcn.140007f10::var_60h + iVar6) = 0;
                    *(&stack0xffffffffffffff90 + iVar6) = 0x140008f14;
                    func_0x000140213161();
                    puVar14 = &stack0xffffffffffffff90;
                    *(puVar14 + iVar6) = uStack_13a8;
                    *(&stack0xffffffffffffff88 + iVar6) = 0x140008f1e;
                    func_0x000140133288();
                    *param_1 = 0;
                    param_1[1] = 0;
                    param_1[2] = unaff_R15;
                    param_1[3] = 0xf;
                    *param_1 = 0;
                    if (7 < uStack_12a8) {
                        uVar12 = uStack_12a8 * 2 + 2;
                        iVar10 = CONCAT62(Stack_12be,uStack_12c0);
                        iVar9 = iVar10;
                        if (0xfff < uVar12) {
                            uVar12 = uStack_12a8 * 2 + 0x29;
                            iVar9 = *(iVar10 + -8);
                            if (0x1f < (iVar10 - iVar9) - 8U) {
                                *(&stack0xffffffffffffff88 + iVar6) = unaff_RBX;
                                *(&stack0xffffffffffffff80 + iVar6) = 0x140008f79;
                                func_0x0001401a4e44();
                                pcVar2 = swi(3);
                                (*pcVar2)();
                                return;
                            }
                        }
                        *(&stack0xffffffffffffff88 + iVar6) = 0x140008f7f;
                        fcn.140015008(iVar9,uVar12);
                    }
                    uStack_12c0 = unaff_R15;
                    puVar15 = puVar14 + iVar6;
                    if (7 < auStack_12e8[3]) {
                        uVar12 = auStack_12e8[3] * 2 + 2;
                        uVar13 = auStack_12e8[0];
                        if (0xfff < uVar12) {
                            uVar12 = auStack_12e8[3] * 2 + 0x29;
                            uVar13 = *(auStack_12e8[0] - 8);
                            uVar7 = (auStack_12e8[0] - uVar13) - 8;
                            if (0x1f < uVar7) goto code_r0x000140008fd1;
                        }
                        *(&stack0xffffffffffffff88 + iVar6) = 0x140008fdd;
                        fcn.140015008(uVar13,uVar12);
                        puVar15 = puVar14 + iVar6;
                    }
                }
                else {
                    uStack_127c = unaff_R15;
                    uStack_1280 = 4;
                    *(&fcn.140007f10::var_20h + iVar6) = unaff_R15;
                    *(&fcn.140007f10::var_28h + iVar6) = &stack0xffffffffffffed80;
                    *(&fcn.140007f10::var_50h + iVar6) = 0x14000901b;
                    func_0x0001401267bb(extraout_XMM0_Qa_00,0x20000013,0,&stack0xffffffffffffed84);
                    uStack_1270 = 0;
                    uStack_1278 = 0;
                    uVar12 = unaff_R15;
                    do {
                        aiStack_12c8[0] = unaff_R15;
                        *(&fcn.140007f10::var_50h + iVar6) = 0x140009050;
                        func_0x000140039855(unaff_RDI,&stack0xffffffffffffed38);
                        *in_stack_ffffffff9383fc88 = *in_stack_ffffffff9383fc88 + in_stack_ffffffff9383fc88;
                        if (aiStack_12c8[0] == 0) break;
                        uVar5 = aiStack_12c8[0] + 1;
                        uVar7 = uVar5;
                        uStack_1308 = 0;
                        uStack_1300 = 0;
                        unaff_RDI = puStack_13b0;
                        uVar13 = unaff_R15;
                        uStack_12f8 = unaff_R15;
                        if (uVar5 != 0) {
                            if (uVar7 < 0x1000) {
                                *(&fcn.140007f10::var_50h + iVar6) = 0x1400090bf;
                                unaff_R15 = fcn.140014fcc(uVar7);
code_r0x0001400090c2:
                                uVar13 = unaff_R15 + uVar7;
                                *(&fcn.140007f10::var_50h + iVar6) = 0x1400090de;
                                uStack_1308 = unaff_R15;
                                uStack_12f8 = uVar13;
                                func_0x000140015eca(unaff_R15,0,uVar7);
                                uVar16 = unaff_R15;
                                uStack_1300 = uVar13;
                                goto code_r0x0001400090ef;
                            }
                            if (uVar5 + 0x27 <= uVar7) {
                                *(&fcn.140007f10::var_50h + iVar6) = 0x1400092ec;
                                fcn.140009350();
                                *(&fcn.140007f10::var_50h + iVar6) = 0x1400092f2;
                                fcn.1400093e0();
                                pcVar2 = swi(3);
                                (*pcVar2)();
                                return;
                            }
                            *(&fcn.140007f10::var_50h + iVar6) = 0x1400090a0;
                            iVar9 = fcn.140014fcc();
                            if (iVar9 != 0) {
                                unaff_R15 = iVar9 + 0x27U & 0xffffffffffffffe0;
                                *(unaff_R15 - 8) = iVar9;
                                goto code_r0x0001400090c2;
                            }
code_r0x0001400091c7:
                            *(&fcn.140007f10::var_50h + iVar6) = 0x1400091cc;
                            func_0x0001401cc0ab();
                            if (unaff_R15 != 0) {
                                *(&fcn.140007f10::var_50h + iVar6) = 0x1400091e5;
                                func_0x0001400095c0(&stack0xffffffffffffecf8,unaff_R15,uVar13 - unaff_R15);
                            }
                            unaff_R15 = 0;
                            break;
                        }
                        uVar16 = 0;
code_r0x0001400090ef:
                        auStack_1380[0] = 0;
                        *(&fcn.140007f10::var_50h + iVar6) = 0x140009104;
                        puVar11 = puStack_13b0;
                        uVar5 = func_0x000140277f54(puStack_13b0,uVar16,aiStack_12c8[0],&stack0xffffffffffffec80);
                        uVar5 = uVar5 ^ in_stack_ffffffffc183fc88;
                        *uVar5 = *uVar5 + uVar5;
                        pcVar1 = uVar7 + 0x75 + puVar11 * 4;
                        *pcVar1 = *pcVar1 + uVar5;
                        if (0xf - uVar12 < uVar13) {
                            *(&fcn.140007f10::var_28h + iVar6) = uVar13;
                            *(&fcn.140007f10::var_50h + iVar6) = 0x140009180;
                            fcn.140002490(&stack0xffffffffffffed88,uVar13,0,unaff_R15);
                        }
                        else {
                            *(&fcn.140007f10::var_50h + iVar6) = 0x14000915f;
                            fcn.140015ec4(&stack0xffffffffffffed88 + uVar12,unaff_R15,uVar13);
                            (&stack0xffffffffffffed88 + uVar12)[uVar13] = 0;
                            uVar12 = uVar12 + uVar13;
                        }
                        if (unaff_R15 != 0) {
                            uVar16 = (uVar13 - unaff_R15) - unaff_R15;
                            uVar7 = unaff_R15;
                            if (0xfff < uVar16) {
                                uVar16 = uVar16 + 0x27;
                                uVar7 = *(unaff_R15 - 8);
                                unaff_R15 = unaff_R15 - uVar7;
                                if (0x1f < unaff_R15 - 8) goto code_r0x0001400091c7;
                            }
                            *(&fcn.140007f10::var_50h + iVar6) = 0x1400091b5;
                            fcn.140015008(uVar7,uVar16);
                        }
                        unaff_R15 = 0;
                    } while (aiStack_12c8[0] != 0);
                    *(&fcn.140007f10::var_50h + iVar6) = 0x1400091f4;
                    iVar9 = func_0x00014015675a(unaff_RDI);
                    uVar5 = *(iVar9 + -0x75);
                    *(&fcn.140007f10::var_50h + iVar6) = 0x1400091fe;
                    func_0x0001401b7e76(unaff_RDI | uVar5);
                    *(&fcn.140007f10::var_50h + iVar6) = 0x140009208;
                    func_0x00014011d067(uStack_13a8);
                    *param_1 = uStack_1278;
                    param_1[1] = uStack_1270;
                    param_1[2] = uVar12;
                    param_1[3] = 0xf;
                    uStack_1278 = uStack_1278 & 0xffffffffffffff00;
                    *(&stack0xffffffffffffffb0 + iVar6) = 0x140009247;
                    fcn.140003c00(&stack0xffffffffffffed88);
                    if (7 < uStack_12a8) {
                        *(&stack0xffffffffffffffb0 + iVar6) = 0x140009262;
                        func_0x000140009300(&stack0xffffffffffffed40,CONCAT62(Stack_12be,uStack_12c0));
                    }
                    uStack_12c0 = unaff_R15;
                    puVar15 = &fcn.140007f10::var_40h + iVar6;
                    if (7 < auStack_12e8[3]) {
                        *(&stack0xffffffffffffffb0 + iVar6) = 0x140009290;
                        func_0x000140009300(&stack0xffffffffffffed18,auStack_12e8[0]);
                        puVar15 = &fcn.140007f10::var_40h + iVar6;
                    }
                }
                goto code_r0x000140009290;
            }
        }
        *(&fcn.140007f10::var_40h + iVar6) = 0x140008364;
        fcn.140015008();
        puVar15 = &stack0xffffffffffffffc0 + iVar6;
    }
    else {
        uVar12 = auStack_12e8[3] * 2 + 2;
        uVar13 = auStack_12e8[0];
        if (uVar12 < 0x1000) {
code_r0x0001400080ab:
            *(&fcn.140007f10::var_40h + iVar6) = 0x1400080b0;
            fcn.140015008(uVar13,uVar12);
            goto code_r0x0001400080b0;
        }
        uVar12 = auStack_12e8[3] * 2 + 0x29;
        uVar13 = *(auStack_12e8[0] - 8);
        uVar7 = (auStack_12e8[0] - uVar13) - 8;
        if (uVar7 < 0x20) goto code_r0x0001400080ab;
code_r0x000140008fd1:
        uVar17 = uVar7 < 0x1f;
        *(puVar14 + iVar6 + -8) = 0x140008fd6;
        iVar3 = func_0x00014002496d();
        uVar5 = (iVar3 + 0x3fd41734) - uVar17;
        *uVar5 = *uVar5 + uVar5;
        puVar15 = puVar14 + iVar6;
code_r0x000140009290:
        auStack_12e8[3] = 7;
        auStack_12e8[0] = CONCAT62(auStack_12e8[0]._2_6_,unaff_R15);
        auStack_12e8[2] = unaff_R15;
        if (7 < aiStack_12a0[3]) {
            *(puVar15 + -8) = 0x1400092c1;
            func_0x000140009300(&stack0xffffffffffffed60,aiStack_12a0[0]);
        }
    }
code_r0x0001400092c1:
    *(puVar15 + -8) = 0x1400092d3;
    fcn.1400153c0(var_50h ^ puVar15);
    return;
}
