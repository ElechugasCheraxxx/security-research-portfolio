/* RVA 0xf5c0  tam 3726 B  addr 0x14000f5c0 */

//WARNING: Instruction at (ram,0x0001400103d5) overlaps instruction at (ram,0x0001400103d2)
//
//WARNING: Control flow encountered bad instruction data
//WARNING: Variable defined which should be unmapped: var_10h_2
//WARNING: Variable defined which should be unmapped: var_4h_2

void fcn.14000f5c0(void)

{
    uint8_t *puVar1;
    int64_t iVar2;
    ulong *puVar3;
    code *pcVar4;
    char cVar5;
    int64_t iVar6;
    uint64_t uVar7;
    int32_t *piVar8;
    char *pcVar9;
    uint8_t uVar10;
    uint64_t uVar11;
    uchar *puVar12;
    uchar *puVar13;
    ulong *puVar14;
    ulong unaff_RSI;
    uint8_t *unaff_RDI;
    int32_t var_ch_2;
    int32_t var_10h_2;
    int8_t var_14h_2;
    int32_t var_1ch;
    int32_t var_20h;
    int8_t var_24h;
    int32_t var_2ch;
    int32_t var_bp_30h;
    int16_t var_34h;
    int32_t var_bp_38h;
    int32_t var_3ch;
    int32_t var_40h_2;
    int16_t var_44h_2;
    int8_t var_46h;
    int32_t var_bp_50h;
    int16_t var_54h;
    int32_t var_bp_58h;
    int32_t var_5ch;
    int32_t var_60h_2;
    int16_t var_64h_2;
    int8_t var_66h;
    int32_t var_bp_6ch;
    int32_t var_70h_2;
    int16_t var_74h_2;
    int8_t var_76h;
    int64_t var_78h;
    int64_t var_8ah;
    int64_t var_b0h;
    int64_t var_b8h;
    uchar auStack_1c8 [128];
    uint uStack_148;
    uint8_t auStack_140 [16];
    uint8_t auStack_130 [16];
    uint8_t auStack_120 [16];
    uint8_t auStack_110 [8];
    uint uStack_108;
    uint8_t auStack_100 [8];
    uint uStack_f8;
    uint8_t auStack_f0 [16];
    uint8_t auStack_e0 [16];
    uint8_t auStack_d0 [8];
    ulong uStack_c8;
    uint8_t auStack_c0 [16];
    uint8_t auStack_b0 [16];
    uint8_t auStack_a0 [16];
    uint8_t auStack_90 [8];
    int32_t var_80h;
    ushort uStack_84;
    uchar uStack_82;
    int32_t var_78h_2;
    int32_t var_74h;
    int8_t var_70h;
    ushort uStack_74;
    int32_t var_bp_68h;
    int32_t var_64h;
    int16_t var_60h;
    ushort uStack_64;
    uchar uStack_62;
    uint8_t auStack_60 [4];
    int32_t var_54h_2;
    uint uStack_58;
    ushort uStack_54;
    uchar uStack_52;
    int32_t var_48h;
    int32_t var_44h;
    int32_t var_40h;
    uchar uStack_44;
    uchar uStack_43;
    uchar uStack_42;
    uchar uStack_41;
    uchar uStack_40;
    uchar uStack_3f;
    uchar auStack_3e [2];
    int32_t var_34h_2;
    int8_t var_2dh;
    int32_t iStack_34;
    int32_t var_28h_2;
    int32_t var_24h_2;
    int16_t var_20h_2;
    int32_t iStack_24;
    int32_t var_18h;
    int32_t var_14h;
    int32_t var_10h;
    int8_t var_ch;
    uint64_t var_bp_8h;
    int32_t var_4h;
    int8_t var_4h_2;
    
    puVar3 = &stack0xffffffffffffff38;
    var_bp_8h = *0x140020600 ^ &stack0xfffffffffffffe38;
    puVar12 = &stack0xfffffffffffffe38;
    do {
        *(puVar12 + 0x58) = *0x14001a380;
        *(puVar12 + 0x60) = *0x14001a388;
        *(puVar12 + 0x68) = 0x100011b;
        uVar11 = 0;
        do {
            puVar12[uVar11 + 0x58] = puVar12[uVar11 + 0x58] ^ uVar11 + 0x53U;
            uVar11 = uVar11 + 1;
        } while (uVar11 < 0x12);
        puVar12[0x6b] = 0;
        *(puVar12 + -8) = 0x14000f63e;
        func_0x0001400011e0(puVar12 + 0x38,puVar12 + 0x58,puVar12 + 0x6a,puVar12 + 0x30);
        *(puVar12 + -8) = 0x14000f649;
        iVar6 = func_0x0001400109d0();
        uVar11 = *(puVar12 + 0x50);
        if (0xf < uVar11) {
            if (0xfff < uVar11 + 1) {
                iVar2 = *(*(puVar12 + 0x38) + -8);
                if (0x1f < (*(puVar12 + 0x38) - iVar2) - 8U) {
                    *(puVar12 + -8) = iVar6;
                    *(puVar12 + -0x10) = 0x1400103f6;
                    func_0x000140268be9(iVar2,uVar11 + 0x28);
                    pcVar4 = swi(3);
                    (*pcVar4)();
                    return;
                }
            }
            *(puVar12 + -8) = 0x14000f689;
            fcn.140015008();
        }
        puVar13 = puVar12;
        if (iVar6 == 0) {
            *(puVar12 + 0x58) = *0x14001a390;
            *(puVar12 + 0x60) = *0x14001a398;
            *(puVar12 + 0x68) = 0x100011b;
            uVar11 = 0;
            do {
                puVar12[uVar11 + 0x58] = puVar12[uVar11 + 0x58] ^ uVar11 + 0x53U;
                uVar11 = uVar11 + 1;
            } while (uVar11 < 0x12);
            puVar12[0x6b] = 0;
            *(puVar12 + -8) = 0x14000f6fe;
            func_0x0001400011e0(puVar12 + 0x38,puVar12 + 0x58,puVar12 + 0x6a,puVar12 + 0x30);
            *(puVar12 + -8) = 0x14000f709;
            iVar6 = func_0x0001400109d0();
            uVar11 = *(puVar12 + 0x50);
            if (0xf < uVar11) {
                if (0xfff < uVar11 + 1) {
                    iVar2 = *(*(puVar12 + 0x38) + -8);
                    if (0x1f < (*(puVar12 + 0x38) - iVar2) - 8U) {
                        *(puVar12 + -8) = iVar6;
                        *(puVar12 + -0x10) = 0x1400103fd;
                        func_0x0001402a77d1(iVar2,uVar11 + 0x28);
                        pcVar4 = swi(3);
                        (*pcVar4)();
                        return;
                    }
                }
                *(puVar12 + -8) = 0x14000f749;
                fcn.140015008();
            }
            if (iVar6 != 0) {
                *(puVar12 + -8) = 0x14000f763;
                fcn.140015e7c(0x13,1,0,&fcn.14000f5c0::var_40h + 1);
                piVar8 = &stack0xffffffffffffffcc;
                goto code_r0x00014000fe37;
            }
            *(puVar12 + 0x58) = *0x14001a4b0;
            *(puVar12 + 0x60) = *0x14001a4b8;
            *(puVar12 + 0x68) = 0x1c06;
            puVar12[0x6c] = 1;
            uVar11 = 0;
            do {
                puVar12[uVar11 + 0x58] = puVar12[uVar11 + 0x58] ^ uVar11 + 0x53U;
                uVar11 = uVar11 + 1;
            } while (uVar11 < 0x13);
            puVar12[0x6c] = 0;
            *(puVar12 + -8) = 0x14000f7be;
            func_0x0001400011e0(puVar12 + 0x38,puVar12 + 0x58,puVar12 + 0x6b,puVar12 + 0x30);
            *(puVar12 + -8) = 0x14000f7c9;
            iVar6 = func_0x0001400109d0();
            uVar11 = *(puVar12 + 0x50);
            if (0xf < uVar11) {
                if (0xfff < uVar11 + 1) {
                    iVar2 = *(*(puVar12 + 0x38) + -8);
                    uVar7 = (*(puVar12 + 0x38) - iVar2) - 8;
                    if (0x1f < uVar7) {
                        *(puVar12 + -8) = uVar7;
                        *(puVar12 + -0x10) = 0x140010404;
                        try.5.140024360.catch(iVar2,uVar11 + 0x28);
                        pcVar4 = swi(3);
                        (*pcVar4)();
                        return;
                    }
                }
                *(puVar12 + -8) = 0x14000f809;
                fcn.140015008();
            }
            if (iVar6 != 0) {
                *(puVar12 + -8) = 0x14000f823;
                fcn.140015e7c(0x13,1,0,&fcn.14000f5c0::var_40h + 2);
                piVar8 = &stack0xffffffffffffffd0;
                goto code_r0x00014000fe37;
            }
            *(puVar12 + 0x58) = *0x14001a310;
            *(puVar12 + 0x60) = *0x14001a318;
            *(puVar12 + 0x68) = 0x1e004a14;
            *(puVar12 + 0x6c) = 2;
            puVar12[0x6e] = 1;
            uVar11 = 0;
            do {
                puVar12[uVar11 + 0x58] = puVar12[uVar11 + 0x58] ^ uVar11 + 0x53U;
                uVar11 = uVar11 + 1;
            } while (uVar11 < 0x15);
            puVar12[0x6e] = 0;
            *(puVar12 + -8) = 0x14000f88e;
            func_0x0001400011e0(puVar12 + 0x38,puVar12 + 0x58,puVar12 + 0x6d,puVar12 + 0x30);
            *(puVar12 + -8) = 0x14000f899;
            iVar6 = func_0x0001400109d0();
            uVar11 = *(puVar12 + 0x50);
            if (0xf < uVar11) {
                if (0xfff < uVar11 + 1) {
                    iVar2 = *(*(puVar12 + 0x38) + -8);
                    if (0x1f < (*(puVar12 + 0x38) - iVar2) - 8U) {
                        *(puVar12 + -8) = unaff_RSI;
                        *(puVar12 + -0x10) = 0x14001040b;
                        func_0x0001402dac6e(iVar2,uVar11 + 0x28);
                        pcVar4 = swi(3);
                        (*pcVar4)();
                        return;
                    }
                }
                *(puVar12 + -8) = 0x14000f8d9;
                fcn.140015008();
            }
            if (iVar6 != 0) {
                *(puVar12 + -8) = 0x14000f8f3;
                fcn.140015e7c(0x13,1,0,&fcn.14000f5c0::var_40h + 3);
                piVar8 = &fcn.14000f5c0::var_24h_2;
                goto code_r0x00014000fe37;
            }
            *(puVar12 + 0x58) = *0x14001a420;
            *(puVar12 + 0x60) = _str.:_6__N;
            *(puVar12 + 0x68) = 6;
            puVar12[0x6a] = 1;
            uVar11 = 0;
            do {
                puVar12[uVar11 + 0x58] = puVar12[uVar11 + 0x58] ^ uVar11 + 0x53U;
                uVar11 = uVar11 + 1;
            } while (uVar11 < 0x11);
            puVar12[0x6a] = 0;
            *(puVar12 + -8) = 0x14000f94e;
            func_0x0001400011e0(puVar12 + 0x38,puVar12 + 0x58,puVar12 + 0x69,puVar12 + 0x30);
            *(puVar12 + -8) = 0x14000f959;
            iVar6 = func_0x0001400109d0();
            uVar11 = *(puVar12 + 0x50);
            if (0xf < uVar11) {
                if (0xfff < uVar11 + 1) {
                    iVar2 = *(*(puVar12 + 0x38) + -8);
                    uVar7 = (*(puVar12 + 0x38) - iVar2) - 8;
                    if (0x1f < uVar7) {
                        *(puVar12 + -8) = uVar7;
                        *(puVar12 + -0x10) = 0x140010412;
                        func_0x0001401335d0(iVar2,uVar11 + 0x28);
                        pcVar4 = swi(3);
                        (*pcVar4)();
                        return;
                    }
                }
                *(puVar12 + -8) = 0x14000f999;
                fcn.140015008();
            }
            if (iVar6 != 0) {
                *(puVar12 + -8) = 0x14000f9b3;
                fcn.140015e7c(0x13,1,0,&stack0xffffffffffffffbc);
                piVar8 = &fcn.14000f5c0::var_20h_2;
                goto code_r0x00014000fe37;
            }
            auStack_e0[0] = 0x23;
            auStack_e0[1] = 0x26;
            auStack_e0[2] = 0x3a;
            auStack_e0[3] = 0x35;
            auStack_e0[4] = 0x3a;
            auStack_e0[5] = 0x37;
            auStack_e0[6] = 0x37;
            auStack_e0[7] = 0x74;
            auStack_e0[8] = 0x3e;
            auStack_e0[9] = 0x24;
            auStack_e0[10] = 0x38;
            auStack_e0[0xb] = 0;
            auStack_e0[0xc] = 1;
            uVar11 = 0;
            do {
                (&stack0xffffffffffffff20)[uVar11] = (&stack0xffffffffffffff20)[uVar11] ^ uVar11 + 0x53U;
                uVar11 = uVar11 + 1;
            } while (uVar11 < 0xb);
            auStack_e0[0xc] = 0;
            *(puVar12 + -8) = 0x14000fa0b;
            func_0x0001400011e0(puVar12 + 0x38,&stack0xffffffffffffff20,&stack0xffffffffffffff2b,puVar12 + 0x30);
            *(puVar12 + -8) = 0x14000fa16;
            iVar6 = func_0x0001400109d0();
            uVar11 = *(puVar12 + 0x50);
            if (0xf < uVar11) {
                if (0xfff < uVar11 + 1) {
                    iVar2 = *(*(puVar12 + 0x38) + -8);
                    if (0x1f < (*(puVar12 + 0x38) - iVar2) - 8U) {
                        *(puVar12 + -8) = 0x140010418;
                        func_0x0001402a8a7a(iVar2,uVar11 + 0x28);
    //WARNING: Bad instruction - Truncating control flow here
                        halt_baddata();
                    }
                }
                *(puVar12 + -8) = 0x14000fa56;
                fcn.140015008();
            }
            if (iVar6 != 0) {
                *(puVar12 + -8) = 0x14000fa70;
                fcn.140015e7c(0x13,1,0,&stack0xffffffffffffffbd);
                piVar8 = &stack0xffffffffffffffdc;
                goto code_r0x00014000fe37;
            }
            auStack_130[0] = 0x3a;
            auStack_130[1] = 0x30;
            auStack_130[2] = 0x34;
            auStack_130[3] = 0x27;
            auStack_130[4] = 0x79;
            auStack_130[5] = 0x3d;
            auStack_130[6] = 0x21;
            auStack_130[7] = 0x3f;
            auStack_130[8] = 0;
            auStack_130[9] = 1;
            uVar11 = 0;
            do {
                (&stack0xfffffffffffffed0)[uVar11] = (&stack0xfffffffffffffed0)[uVar11] ^ uVar11 + 0x53U;
                uVar11 = uVar11 + 1;
            } while (uVar11 < 8);
            auStack_130[8] = 0;
            auStack_130[9] = 0;
            *(puVar12 + -8) = 0x14000facb;
            func_0x0001400011e0(puVar12 + 0x38,&stack0xfffffffffffffed0,&stack0xfffffffffffffed8,puVar12 + 0x30);
            *(puVar12 + -8) = 0x14000fad6;
            iVar6 = func_0x0001400109d0();
            uVar11 = *(puVar12 + 0x50);
            if (0xf < uVar11) {
                if (0xfff < uVar11 + 1) {
                    iVar2 = *(*(puVar12 + 0x38) + -8);
                    uVar7 = (*(puVar12 + 0x38) - iVar2) - 8;
                    if (0x1f < uVar7) {
                        *(puVar12 + -8) = uVar7;
                        *(puVar12 + -0x10) = 0x140010420;
                        func_0x000140196b7d(iVar2,uVar11 + 0x28);
                        pcVar4 = swi(3);
                        (*pcVar4)();
                        return;
                    }
                }
                *(puVar12 + -8) = 0x14000fb16;
                fcn.140015008();
            }
            if (iVar6 != 0) {
                *(puVar12 + -8) = 0x14000fb30;
                fcn.140015e7c(0x13,1,0,&stack0xffffffffffffffbe);
                piVar8 = &fcn.14000f5c0::var_18h;
                goto code_r0x00014000fe37;
            }
            auStack_110[0] = 0x3a;
            auStack_110[1] = 0x30;
            auStack_110[2] = 0x34;
            auStack_110[3] = 0x27;
            auStack_110[4] = 0x61;
            auStack_110[5] = 0x6c;
            auStack_110[6] = 0x77;
            auStack_110[7] = 0x3f;
            uStack_108 = 0x1003923;
            uVar11 = 0;
            do {
                (&stack0xfffffffffffffef0)[uVar11] = (&stack0xfffffffffffffef0)[uVar11] ^ uVar11 + 0x53U;
                uVar11 = uVar11 + 1;
            } while (uVar11 < 10);
            uStack_108 = uStack_108 & 0xffffff;
            *(puVar12 + -8) = 0x14000fb8b;
            func_0x0001400011e0(puVar12 + 0x38,&stack0xfffffffffffffef0,&stack0xfffffffffffffefa,puVar12 + 0x30);
            *(puVar12 + -8) = 0x14000fb96;
            iVar6 = func_0x0001400109d0();
            uVar11 = *(puVar12 + 0x50);
            if (0xf < uVar11) {
                if (0xfff < uVar11 + 1) {
                    iVar2 = *(*(puVar12 + 0x38) + -8);
                    if (0x1f < (*(puVar12 + 0x38) - iVar2) - 8U) {
                        *(puVar12 + -8) = iVar2;
                        *(puVar12 + -0x10) = 0x140010427;
                        func_0x0001401cafd6(iVar2,uVar11 + 0x28);
                        pcVar4 = swi(3);
                        (*pcVar4)();
                        return;
                    }
                }
                *(puVar12 + -8) = 0x14000fbd6;
                fcn.140015008();
            }
            if (iVar6 != 0) {
                *(puVar12 + -8) = 0x14000fbf0;
                fcn.140015e7c(0x13,1,0,&stack0xffffffffffffffbf);
                piVar8 = &fcn.14000f5c0::var_14h;
                goto code_r0x00014000fe37;
            }
            auStack_90[0] = 4;
            auStack_90[1] = 0x3d;
            auStack_90[2] = 0x27;
            auStack_90[3] = 0x33;
            auStack_90[4] = 0x24;
            auStack_90[5] = 0x30;
            auStack_90[6] = 0x38;
            auStack_90[7] = 0x28;
            var_80h = 0x26387230;
            uStack_84 = 0x3a;
            uStack_82 = 1;
            uVar11 = 0;
            do {
                (&stack0xffffffffffffff70)[uVar11] = (&stack0xffffffffffffff70)[uVar11] ^ uVar11 + 0x53U;
                uVar11 = uVar11 + 1;
            } while (uVar11 < 0xd);
            uStack_82 = 0;
            *(puVar12 + -8) = 0x14000fc4b;
            func_0x0001400011e0(puVar12 + 0x38,&stack0xffffffffffffff70,&stack0xffffffffffffff7d,puVar12 + 0x30);
            *(puVar12 + -8) = 0x14000fc56;
            iVar6 = func_0x0001400109d0();
            uVar11 = *(puVar12 + 0x50);
            if (0xf < uVar11) {
                if (0xfff < uVar11 + 1) {
                    iVar2 = *(*(puVar12 + 0x38) + -8);
                    if (0x1f < (*(puVar12 + 0x38) - iVar2) - 8U) {
                        *(puVar12 + -8) = 0x14001042d;
                        func_0x00014013d279(iVar2,uVar11 + 0x28);
    //WARNING: Bad instruction - Truncating control flow here
                        halt_baddata();
                    }
                }
                *(puVar12 + -8) = 0x14000fc96;
                fcn.140015008();
            }
            if (iVar6 != 0) {
                *(puVar12 + -8) = 0x14000fcb0;
                fcn.140015e7c(0x13,1,0,&stack0xffffffffffffffc0);
                piVar8 = &fcn.14000f5c0::var_ch;
                goto code_r0x00014000fe37;
            }
            auStack_d0[0] = 0x15;
            auStack_d0[1] = 0x3d;
            auStack_d0[2] = 0x31;
            auStack_d0[3] = 0x32;
            auStack_d0[4] = 0x3b;
            auStack_d0[5] = 0x3d;
            auStack_d0[6] = 0x2b;
            auStack_d0[7] = 0x74;
            uStack_c8._0_4_ = 0x38243e;
            uStack_c8._4_1_ = 1;
            uVar11 = 0;
            do {
                (&stack0xffffffffffffff30)[uVar11] = (&stack0xffffffffffffff30)[uVar11] ^ uVar11 + 0x53U;
                uVar11 = uVar11 + 1;
            } while (uVar11 < 0xb);
            uStack_c8._4_1_ = 0;
            *(puVar12 + -8) = 0x14000fd0b;
            func_0x0001400011e0(puVar12 + 0x38,&stack0xffffffffffffff30,&stack0xffffffffffffff3b,puVar12 + 0x30);
            *(puVar12 + -8) = 0x14000fd16;
            iVar6 = func_0x0001400109d0();
            uVar11 = *(puVar12 + 0x50);
            if (0xf < uVar11) {
                if (0xfff < uVar11 + 1) {
                    if (0x1f < (*(puVar12 + 0x38) - *(*(puVar12 + 0x38) + -8)) - 8U) {
                        *(puVar12 + -8) = uVar11 + 0x28;
                        *(puVar12 + -0x10) = 0x140010435;
                        func_0x0001400384ef();
                        pcVar4 = swi(3);
                        (*pcVar4)();
                        return;
                    }
                }
                *(puVar12 + -8) = 0x14000fd56;
                fcn.140015008();
            }
            if (iVar6 != 0) {
                *(puVar12 + -8) = 0x14000fd70;
                fcn.140015e7c(0x13,1,0,&stack0xffffffffffffffc1);
                piVar8 = &fcn.14000f5c0::var_10h;
                goto code_r0x00014000fe37;
            }
            auStack_c0[0] = 0xb;
            auStack_c0[1] = 0x31;
            auStack_c0[2] = 0x3b;
            auStack_c0[3] = 0x39;
            auStack_c0[4] = 0x24;
            auStack_c0[5] = 0x6e;
            auStack_c0[6] = 0x6d;
            auStack_c0[7] = 0x74;
            auStack_c0[8] = 0x3e;
            auStack_c0[9] = 0x24;
            auStack_c0[10] = 0x38;
            auStack_c0[0xb] = 0;
            auStack_c0[0xc] = 1;
            uVar11 = 0;
            do {
                (&stack0xffffffffffffff40)[uVar11] = (&stack0xffffffffffffff40)[uVar11] ^ uVar11 + 0x53U;
                uVar11 = uVar11 + 1;
            } while (uVar11 < 0xb);
            auStack_c0[0xc] = 0;
            *(puVar12 + -8) = 0x14000fdcb;
            func_0x0001400011e0(puVar12 + 0x38,&stack0xffffffffffffff40,&stack0xffffffffffffff4b,puVar12 + 0x30);
            *(puVar12 + -8) = 0x14000fdd6;
            iVar6 = func_0x0001400109d0();
            uVar11 = *(puVar12 + 0x50);
            if (0xf < uVar11) {
                if (0xfff < uVar11 + 1) {
                    iVar2 = *(*(puVar12 + 0x38) + -8);
                    if (0x1f < (*(puVar12 + 0x38) - iVar2) - 8U) {
                        *(puVar12 + -8) = 0x14001043b;
                        func_0x000140226055(iVar2,uVar11 + 0x28);
                        pcVar4 = swi(3);
                        (*pcVar4)();
                        return;
                    }
                }
                *(puVar12 + -8) = 0x14000fe16;
                fcn.140015008();
            }
            if (iVar6 != 0) {
                *(puVar12 + -8) = 0x14000fe30;
                fcn.140015e7c(0x13,1,0,&stack0xffffffffffffffc2);
                piVar8 = &stack0xffffffffffffffc8;
                goto code_r0x00014000fe37;
            }
            auStack_b0[0] = 0x21;
            auStack_b0[1] = 0x31;
            auStack_b0[2] = 0x32;
            auStack_b0[3] = 0x33;
            auStack_b0[4] = 0x33;
            auStack_b0[5] = 0x31;
            auStack_b0[6] = 0x2d;
            auStack_b0[7] = 0x74;
            auStack_b0[8] = 0x3e;
            auStack_b0[9] = 0x24;
            auStack_b0[10] = 0x38;
            auStack_b0[0xb] = 0;
            auStack_b0[0xc] = 1;
            uVar11 = 0;
            do {
                (&stack0xffffffffffffff50)[uVar11] = (&stack0xffffffffffffff50)[uVar11] ^ uVar11 + 0x53U;
                uVar11 = uVar11 + 1;
            } while (uVar11 < 0xb);
            auStack_b0[0xc] = 0;
            *(puVar12 + -8) = 0x14000feab;
            func_0x0001400011e0(puVar12 + 0x38,&stack0xffffffffffffff50,&stack0xffffffffffffff5b,puVar12 + 0x30);
            *(puVar12 + -8) = 0x14000feb6;
            iVar6 = func_0x0001400109d0();
            uVar11 = *(puVar12 + 0x50);
            if (0xf < uVar11) {
                if (0xfff < uVar11 + 1) {
                    iVar2 = *(*(puVar12 + 0x38) + -8);
                    uVar7 = (*(puVar12 + 0x38) - iVar2) - 8;
                    if (0x1f < uVar7) {
                        *(puVar12 + -8) = uVar7;
                        *(puVar12 + -0x10) = 0x140010443;
                        func_0x000140268d55(iVar2,uVar11 + 0x28);
                        pcVar4 = swi(3);
                        (*pcVar4)();
                        return;
                    }
                }
                *(puVar12 + -8) = 0x14000fef6;
                fcn.140015008();
            }
            if (iVar6 == 0) {
                auStack_140[0] = 0x1b;
                auStack_140[1] = 0x2c;
                auStack_140[2] = 0x11;
                auStack_140[3] = 0x78;
                auStack_140[4] = 0x32;
                auStack_140[5] = 0x20;
                auStack_140[6] = 0x3c;
                auStack_140[7] = 0;
                auStack_140[8] = 1;
                uVar11 = 0;
                do {
                    (&stack0xfffffffffffffec0)[uVar11] = (&stack0xfffffffffffffec0)[uVar11] ^ uVar11 + 0x53U;
                    uVar11 = uVar11 + 1;
                } while (uVar11 < 7);
                auStack_140[8] = 0;
                *(puVar12 + -8) = 0x14000ff4b;
                func_0x0001400011e0(puVar12 + 0x38,&stack0xfffffffffffffec0,&stack0xfffffffffffffec7,puVar12 + 0x30);
                *(puVar12 + -8) = 0x14000ff56;
                iVar6 = func_0x0001400109d0();
                uVar11 = *(puVar12 + 0x50);
                if (0xf < uVar11) {
                    if (0xfff < uVar11 + 1) {
                        iVar2 = *(*(puVar12 + 0x38) + -8);
                        if (0x1f < (*(puVar12 + 0x38) - iVar2) - 8U) {
                            *(puVar12 + -8) = 0x140010449;
                            func_0x00014016e425(iVar2,uVar11 + 0x28);
                            puVar14 = puVar12 + -8;
                            *(puVar12 + -8) = puVar3;
                            cVar5 = '\v';
                            do {
                                puVar3 = puVar3 + -1;
                                puVar14 = puVar14 + -1;
                                *puVar14 = *puVar3;
                                cVar5 = cVar5 + -1;
                            } while ('\0' < cVar5);
                            *(puVar12 + -0x68) = puVar12 + -8;
                            pcVar4 = swi(3);
                            (*pcVar4)();
                            return;
                        }
                    }
                    *(puVar12 + -8) = 0x14000ff96;
                    fcn.140015008();
                }
                if (iVar6 == 0) {
                    *(puVar12 + 0x58) = *0x14001a360;
                    *(puVar12 + 0x60) = *0x14001a368;
                    *(puVar12 + 0x68) = 0x100;
                    uVar11 = 0;
                    do {
                        puVar12[uVar11 + 0x58] = puVar12[uVar11 + 0x58] ^ uVar11 + 0x53U;
                        uVar11 = uVar11 + 1;
                    } while (uVar11 < 0x10);
                    puVar12[0x69] = 0;
                    *(puVar12 + -8) = 0x14000ffee;
                    func_0x0001400011e0(puVar12 + 0x38,puVar12 + 0x58,puVar12 + 0x68,puVar12 + 0x30);
                    *(puVar12 + -8) = 0x14000fff9;
                    iVar6 = func_0x0001400109d0();
                    if (0xf < *(puVar12 + 0x50)) {
                        *(puVar12 + -8) = 0x140010016;
                        fcn.14000d270(puVar12 + 0x38,*(puVar12 + 0x38),*(puVar12 + 0x50));
                    }
                    if (iVar6 == 0) {
                        *(puVar12 + 0x58) = *0x14001a3c0;
                        *(puVar12 + 0x60) = *0x14001a3c8;
                        *(puVar12 + 0x68) = *0x14001a4a0;
                        *(puVar12 + 0x70) = *0x14001a4a8;
                        *(puVar12 + 0x78) = 0x1f175441;
                        *(puVar12 + 0x7c) = 0x1f575103;
                        uStack_148 = 0x1001903;
                        uVar11 = 0;
                        do {
                            puVar12[uVar11 + 0x58] = puVar12[uVar11 + 0x58] ^ uVar11 + 0x53U;
                            uVar11 = uVar11 + 1;
                        } while (uVar11 < 0x2a);
                        uStack_148 = uStack_148 & 0xffffff;
                        *(puVar12 + -8) = 0x14001008c;
                        func_0x0001400011e0(puVar12 + 0x38,puVar12 + 0x58,&stack0xfffffffffffffeba,puVar12 + 0x30);
                        *(puVar12 + -8) = 0x140010097;
                        iVar6 = func_0x0001400109d0();
                        if (0xf < *(puVar12 + 0x50)) {
                            *(puVar12 + -8) = 0x1400100b4;
                            fcn.14000d270(puVar12 + 0x38,*(puVar12 + 0x38),*(puVar12 + 0x50));
                        }
                        if (iVar6 == 0) {
                            auStack_a0[0] = 0x18;
                            auStack_a0[1] = 0x27;
                            auStack_a0[2] = 0x11;
                            auStack_a0[3] = 0x23;
                            auStack_a0[4] = 0x3a;
                            auStack_a0[5] = 0x28;
                            auStack_a0[6] = 0x3c;
                            auStack_a0[7] = 0x28;
                            auStack_a0[8] = 0x75;
                            auStack_a0[9] = 0x39;
                            auStack_a0[10] = 0x25;
                            auStack_a0[0xb] = 0x3b;
                            auStack_a0[0xc] = 0;
                            auStack_a0[0xd] = 1;
                            uVar11 = 0;
                            do {
                                (&stack0xffffffffffffff60)[uVar11] = (&stack0xffffffffffffff60)[uVar11] ^ uVar11 + 0x53U
                                ;
                                uVar11 = uVar11 + 1;
                            } while (uVar11 < 0xc);
                            auStack_a0[0xc] = 0;
                            auStack_a0[0xd] = 0;
                            *(puVar12 + -8) = 0x14001010b;
                            func_0x0001400011e0(puVar12 + 0x38,&stack0xffffffffffffff60,&stack0xffffffffffffff6c,
                                                puVar12 + 0x30);
                            *(puVar12 + -8) = 0x140010116;
                            iVar6 = func_0x0001400109d0();
                            if (0xf < *(puVar12 + 0x50)) {
                                *(puVar12 + -8) = 0x140010133;
                                fcn.14000d270(puVar12 + 0x38,*(puVar12 + 0x38),*(puVar12 + 0x50));
                            }
                            if (iVar6 == 0) {
                                auStack_100[0] = 0x2b;
                                auStack_100[1] = 0x62;
                                auStack_100[2] = 0x61;
                                auStack_100[3] = 0x32;
                                auStack_100[4] = 0x35;
                                auStack_100[5] = 0x3f;
                                auStack_100[6] = 0x77;
                                auStack_100[7] = 0x3f;
                                uStack_f8 = 0x1003923;
                                uVar11 = 0;
                                do {
                                    (&stack0xffffffffffffff00)[uVar11] =
                                         (&stack0xffffffffffffff00)[uVar11] ^ uVar11 + 0x53U;
                                    uVar11 = uVar11 + 1;
                                } while (uVar11 < 10);
                                uStack_f8 = uStack_f8 & 0xffffff;
                                *(puVar12 + -8) = 0x14001018b;
                                func_0x0001400011e0(puVar12 + 0x38,&stack0xffffffffffffff00,&stack0xffffffffffffff0a,
                                                    puVar12 + 0x30);
                                *(puVar12 + -8) = 0x140010196;
                                iVar6 = func_0x0001400109d0(puVar12 + 0x38);
                                *(puVar12 + -8) = 0x1400101a3;
                                fcn.140003c00(puVar12 + 0x38);
                                if (iVar6 == 0) {
                                    *(puVar12 + 0x58) = *0x14001a420;
                                    *(puVar12 + 0x60) = _str.:_6__N;
                                    *(puVar12 + 0x68) = 6;
                                    puVar12[0x6a] = 1;
                                    uVar11 = 0;
                                    do {
                                        puVar12[uVar11 + 0x58] = puVar12[uVar11 + 0x58] ^ uVar11 + 0x53U;
                                        uVar11 = uVar11 + 1;
                                    } while (uVar11 < 0x11);
                                    puVar12[0x6a] = 0;
                                    *(puVar12 + -8) = 0x1400101fe;
                                    func_0x0001400011e0(puVar12 + 0x38,puVar12 + 0x58,puVar12 + 0x69,puVar12 + 0x30);
                                    *(puVar12 + -8) = 0x140010209;
                                    iVar6 = func_0x0001400109d0(puVar12 + 0x38);
                                    *(puVar12 + -8) = 0x140010216;
                                    fcn.140003c00(puVar12 + 0x38);
                                    if (iVar6 == 0) {
                                        *(puVar12 + 0x58) = *0x14001a400;
                                        *(puVar12 + 0x60) = *0x14001a408;
                                        *(puVar12 + 0x68) = 0x100;
                                        uVar11 = 0;
                                        do {
                                            puVar12[uVar11 + 0x58] = puVar12[uVar11 + 0x58] ^ uVar11 + 0x53U;
                                            uVar11 = uVar11 + 1;
                                        } while (uVar11 < 0x10);
                                        puVar12[0x69] = 0;
                                        puVar13 = puVar12 + -8;
                                        *(puVar12 + -8) = 0;
                                        *(puVar12 + -0x10) = 0x140010262;
                                        iVar6 = func_0x00014026b64f(0,puVar12 + 0x58);
                                        if (iVar6 == 0) {
                                            var_bp_68h = 0x3938311e;
                                            var_64h = 0xc792125;
                                            _var_60h = 0x3b2a3932;
                                            uStack_64 = 0x2d;
                                            uStack_62 = 1;
                                            uVar11 = 0;
                                            do {
                                                *(&fcn.14000f5c0::var_bp_68h + uVar11) =
                                                     *(&fcn.14000f5c0::var_bp_68h + uVar11) ^ uVar11 + 0x53U;
                                                uVar11 = uVar11 + 1;
                                            } while (uVar11 < 0xd);
                                            uStack_62 = 0;
                                            uVar10 = 0;
                                            *(puVar12 + -0x10) = 0x1400102af;
                                            iVar6 = func_0x0001402d6fb6(0,&fcn.14000f5c0::var_bp_68h);
                                            *(iVar6 + -0x7b) = *(iVar6 + -0x7b) | uVar10;
                                            *unaff_RDI = *unaff_RDI >> 5 | *unaff_RDI << 3;
                                            cVar5 = (iVar6 + -1) - (*unaff_RDI < '\0');
                                            pcVar9 = CONCAT71(iVar6 >> 8,cVar5);
                                            *pcVar9 = *pcVar9 + cVar5;
                                            var_78h_2 = 0x353a2603;
                                            var_74h = 0x7a2a2b32;
                                            _var_70h = 0x2a2e3517;
                                            uStack_74 = 0x100;
                                            uVar11 = 0;
                                            do {
                                                *(&fcn.14000f5c0::var_78h_2 + uVar11) =
                                                     *(&fcn.14000f5c0::var_78h_2 + uVar11) ^ uVar11 + 0x53U;
                                                uVar11 = uVar11 + 1;
                                            } while (uVar11 < 0xc);
                                            uStack_74 = 0;
                                            puVar13 = puVar12 + -0x10;
                                            *(puVar12 + -0x10) = puVar3;
                                            *(puVar12 + -0x18) = 0x140010300;
                                            iVar6 = func_0x0001402ca7be(0,&fcn.14000f5c0::var_78h_2);
                                            if (iVar6 == 0) {
                                                auStack_f0[0] = 0x18;
                                                auStack_f0[1] = 0x27;
                                                auStack_f0[2] = 0x11;
                                                auStack_f0[3] = 0x23;
                                                auStack_f0[4] = 0x3a;
                                                auStack_f0[5] = 0x28;
                                                auStack_f0[6] = 0x3c;
                                                auStack_f0[7] = 0x28;
                                                auStack_f0[8] = 0;
                                                auStack_f0[9] = 1;
                                                uVar11 = 0;
                                                do {
                                                    (&stack0xffffffffffffff10)[uVar11] =
                                                         (&stack0xffffffffffffff10)[uVar11] ^ uVar11 + 0x53U;
                                                    uVar11 = uVar11 + 1;
                                                } while (uVar11 < 8);
                                                auStack_f0[8] = 0;
                                                auStack_f0[9] = 0;
                                                puVar13 = puVar12 + -0x18;
                                                *(puVar12 + -0x18) = puVar3;
                                                *(puVar12 + -0x20) = 0x140010340;
                                                iVar6 = func_0x00014017cd24(0,&stack0xffffffffffffff10);
                                                if (iVar6 == 0) {
                                                    auStack_60[0] = 0x1b;
                                                    auStack_60[1] = 0;
                                                    auStack_60[2] = 1;
                                                    auStack_60[3] = 6;
                                                    var_54h_2 = 0x383c1c77;
                                                    uStack_58 = 0x3b3a3b2e;
                                                    uStack_54 = 0x2d;
                                                    uStack_52 = 1;
                                                    uVar11 = 0;
                                                    do {
                                                        (&stack0xffffffffffffffa0)[uVar11] =
                                                             (&stack0xffffffffffffffa0)[uVar11] ^ uVar11 + 0x53U;
                                                        uVar11 = uVar11 + 1;
                                                    } while (uVar11 < 0xd);
                                                    uStack_52 = 0;
                                                    puVar13 = puVar12 + -0x20;
                                                    *(puVar12 + -0x20) = puVar3;
                                                    *(puVar12 + -0x28) = 0x140010390;
                                                    iVar6 = func_0x00014022c6be(0,&stack0xffffffffffffffa0);
                                                    if (iVar6 == 0) {
                                                        auStack_120[0] = 0x1c;
                                                        auStack_120[1] = 0x38;
                                                        auStack_120[2] = 0x39;
                                                        auStack_120[3] = 0x2f;
                                                        auStack_120[4] = 0x13;
                                                        auStack_120[5] = 0x3a;
                                                        auStack_120[6] = 0x3e;
                                                        auStack_120[7] = 0;
                                                        auStack_120[8] = 1;
                                                        uVar11 = 0;
                                                        do {
                                                            (&stack0xfffffffffffffee0)[uVar11] =
                                                                 (&stack0xfffffffffffffee0)[uVar11] ^ uVar11 + 0x53U;
                                                            uVar11 = uVar11 + 1;
                                                        } while (uVar11 < 7);
                                                        auStack_120[8] = 0;
                                                        uVar10 = 0;
                                                        *(puVar12 + -0x28) = 0x1400103cf;
                                                        iVar6 = func_0x0001401915c3(0,&stack0xfffffffffffffee0);
                                                        puVar1 = iVar6 + -0x7b;
                                                        *puVar1 = *puVar1 >> (uVar10 & 7) | *puVar1 << 8 - (uVar10 & 7);
                                                        (&stack0xffffffffffffff20)[iVar6] =
                                                             (&stack0xffffffffffffff20)[iVar6] << 6;
                                                        return;
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            *(puVar13 + -8) = 0x1400103da;
            fcn.14000d2e0();
        }
        else {
            *(puVar12 + -8) = 0x14000f6a3;
            fcn.140015e7c(0x13,1,0,&fcn.14000f5c0::var_40h);
            piVar8 = &fcn.14000f5c0::var_34h_2;
code_r0x00014000fe37:
            *(puVar12 + 0x28) = piVar8;
            *(puVar12 + 0x20) = 6;
            *(puVar12 + -8) = 0x14000fe56;
            fcn.140015e82(0xc0000420,0,0,0);
        }
        _var_48h = 5000;
        *(puVar13 + -8) = 0x1400103eb;
        func_0x00014000afc0();
        puVar12 = puVar13;
    } while( true );
}
