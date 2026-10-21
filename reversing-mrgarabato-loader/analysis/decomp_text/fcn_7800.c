/* RVA 0x7800  tam 1495 B  addr 0x140007800 */

//WARNING: Control flow encountered bad instruction data
//WARNING: Instruction at (ram,0x000140007b13) overlaps instruction at (ram,0x000140007b11)
//

void fcn.140007800(int64_t arg1,int64_t arg2,int64_t arg3,int64_t arg4)

{
    int64_t iVar1;
    code *pcVar2;
    int64_t *piVar3;
    int64_t iVar4;
    int64_t iVar5;
    uint64_t uVar6;
    uint64_t uVar7;
    bool bVar8;
    int64_t var_70h;
    int64_t var_80h;
    int64_t var_88h;
    int64_t var_90h;
    int64_t var_a0h;
    int64_t var_a8h;
    int64_t var_b0h;
    int64_t var_c0h;
    int64_t var_c8h;
    int64_t var_d0h;
    int64_t var_e0h;
    int64_t var_e8h;
    int64_t var_f0h;
    int64_t var_110h;
    int64_t var_130h;
    int64_t var_150h;
    int64_t var_170h;
    int64_t var_190h;
    int32_t var_1b0h;
    int64_t var_1c0h;
    int64_t var_1c8h;
    int64_t var_1d8h;
    int64_t var_1e0h;
    int64_t var_380h;
    uchar auStack_4c8 [40];
    uint64_t *puStack_4a0;
    uint uStack_498;
    int64_t iStack_490;
    ulong uStack_488;
    ulong uStack_480;
    uint64_t uStack_478;
    uchar uStack_470;
    unkbyte7 Stack_46f;
    ulong uStack_460;
    uint64_t uStack_458;
    int64_t iStack_450;
    uchar auStack_448 [240];
    uint64_t uStack_358;
    ulong uStack_350;
    int64_t iStack_348;
    uint64_t uStack_340;
    uchar uStack_338;
    unkbyte7 Stack_337;
    int64_t iStack_328;
    uint64_t uStack_320;
    ushort uStack_318;
    unkbyte6 Stack_316;
    ulong uStack_308;
    uint64_t uStack_300;
    int64_t iStack_2f8;
    int64_t iStack_2f0;
    int64_t iStack_2e8;
    uint64_t uStack_2e0;
    uchar auStack_2d8 [32];
    uchar auStack_2b8 [32];
    uchar auStack_298 [32];
    uchar auStack_278 [32];
    uchar auStack_258 [32];
    uchar auStack_238 [32];
    uint uStack_218;
    uchar auStack_208 [8];
    int64_t iStack_200;
    int64_t iStack_1f8;
    int64_t iStack_1f0;
    uint64_t uStack_1e8;
    int64_t var_80h_2;
    uint64_t uStack_48;
    
    uStack_48 = *0x140020600 ^ auStack_4c8;
    uStack_498 = 0;
    iStack_450 = arg1;
    fcn.140003030(&iStack_2f8);
    fcn.140002ed0(auStack_2d8,arg2 + 0x20);
    fcn.140002ed0(auStack_2b8,arg2 + 0x40);
    fcn.140002ed0(auStack_298,arg2 + 0x60);
    fcn.140002ed0(auStack_278,arg2 + 0x80);
    fcn.140002ed0(auStack_258,arg2 + 0xa0);
    fcn.140002ed0(auStack_238,arg2 + 0xc0);
    uStack_218 = *(arg2 + 0xe0);
    if (iStack_2e8 == 0) {
        piVar3 = fcn.140004d10(auStack_448);
        if (&iStack_2f8 != piVar3) {
            if (7 < uStack_2e0) {
                uVar6 = uStack_2e0 * 2 + 2;
                iVar5 = iStack_2f8;
                if (0xfff < uVar6) {
                    uVar6 = uStack_2e0 * 2 + 0x29;
                    iVar5 = *(iStack_2f8 + -8);
                    if (0x1f < (iStack_2f8 - iVar5) - 8U) {
                        fcn.14023dab1();
                        pcVar2 = swi(3);
                        (*pcVar2)();
                        return;
                    }
                }
                fcn.140015008(iVar5,uVar6);
            }
            iStack_2f8 = *piVar3;
            iStack_2f0 = piVar3[1];
            iStack_2e8 = piVar3[2];
            uStack_2e0 = piVar3[3];
            piVar3[2] = 0;
            piVar3[3] = 7;
            *piVar3 = 0;
        }
        fcn.140003dd0(auStack_448);
    }
    fcn.140005060(&uStack_318,&iStack_2f8,arg3);
    uStack_350 = 0;
    iStack_348 = 0;
    uStack_340 = 0xf;
    uStack_358 = 0;
    puStack_4a0 = &uStack_358;
    fcn.140007f10(&uStack_338,&iStack_2f8,&uStack_318,arg4);
    if (iStack_328 == 0) {
        fcn.140003650(auStack_208);
        auStack_208[0] = 0;
        bVar8 = iStack_348 != 0;
        if (bVar8) {
            piVar3 = fcn.140002ed0(&uStack_470,&uStack_358);
        }
        else {
            iStack_490 = 0;
            uStack_488 = 0;
            uStack_480 = 0;
            uStack_478 = 0;
            fcn.140001b90(&iStack_490,"Empty response",0xe);
            piVar3 = &iStack_490;
        }
        if (&iStack_200 != piVar3) {
            if (0xf < uStack_1e8) {
                uVar6 = uStack_1e8 + 1;
                iVar5 = iStack_200;
                if (0xfff < uVar6) {
                    uVar6 = uStack_1e8 + 0x28;
                    iVar5 = *(iStack_200 + -8);
                    if (0x1f < (iStack_200 - iVar5) - 8U) goto code_r0x000140007b0c;
                }
                fcn.140015008(iVar5,uVar6);
            }
            iStack_200 = *piVar3;
            iStack_1f8 = piVar3[1];
            iStack_1f0 = piVar3[2];
            uStack_1e8 = piVar3[3];
            piVar3[2] = 0;
            piVar3[3] = 0xf;
            *piVar3 = 0;
        }
        if (bVar8) {
            if (0xf < uStack_458) {
                uVar6 = uStack_458 + 1;
                iVar1 = CONCAT71(Stack_46f,uStack_470);
                iVar5 = iVar1;
                if (0xfff < uVar6) {
                    uVar6 = uStack_458 + 0x28;
                    iVar5 = *(iVar1 + -8);
                    if (0x1f < (iVar1 - iVar5) - 8U) {
code_r0x000140007b0c:
                        fcn.14023cc5d();
    //WARNING: Bad instruction - Truncating control flow here
                        halt_baddata();
                    }
                }
                fcn.140015008(iVar5,uVar6);
            }
            uStack_460 = *0x140018f70;
            uStack_458 = *0x140018f78;
            uStack_470 = 0;
        }
        if ((!bVar8) && (0xf < uStack_478)) {
            uVar6 = uStack_478 + 1;
            iVar5 = iStack_490;
            if (0xfff < uVar6) {
                uVar6 = uStack_478 + 0x28;
                iVar5 = *(iStack_490 + -8);
                if (0x1f < (iStack_490 - iVar5) - 8U) {
                    func_0x000140228d33();
                    pcVar2 = swi(3);
                    (*pcVar2)();
                    return;
                }
            }
            fcn.140015008(iVar5,uVar6);
        }
        fcn.1400032a0(arg1,auStack_208);
        fcn.140003fe0(auStack_208);
        if (0xf < uStack_320) {
            if (0xfff < uStack_320 + 1) {
                uVar6 = uStack_320 + 0x28;
                iVar5 = *(CONCAT71(Stack_337,uStack_338) + -8);
                if (0x1f < (CONCAT71(Stack_337,uStack_338) - iVar5) - 8U) {
code_r0x000140007d12:
                    fcn.1401cb05c(iVar5,uVar6);
                    pcVar2 = swi(3);
                    (*pcVar2)();
                    return;
                }
            }
            fcn.140015008();
        }
        iStack_328 = 0;
        uStack_320 = 0xf;
        uStack_338 = 0;
        if (0xf < uStack_340) {
            if (0xfff < uStack_340 + 1) {
                uVar7 = uStack_340 + 0x28;
                uVar6 = *(uStack_358 - 8);
                if (0x1f < (uStack_358 - uVar6) - 8) {
code_r0x000112916642:
                    uStack_320 = 0xf;
                    iStack_328 = 0;
                    uStack_338 = 0;
                    fcn.1401d601a(uVar6,uVar7);
    //WARNING: Bad instruction - Truncating control flow here
                    halt_baddata();
                }
            }
            fcn.140015008();
        }
        iStack_348 = 0;
        uStack_340 = 0xf;
        uStack_358 = uStack_358 & 0xffffffffffffff00;
        if (uStack_300 < 8) goto code_r0x000140007c82;
        iVar5 = uStack_300 * 2;
        if (0xfff < iVar5 + 2U) {
            iVar1 = *(CONCAT62(Stack_316,uStack_318) + -8);
            iVar4 = CONCAT62(Stack_316,uStack_318) - iVar1;
joined_r0x000140007dd1:
            if (0x1f < iVar4 - 8U) {
                uStack_340 = 0xf;
                iStack_348 = 0;
                fcn.1402aa137(iVar1,iVar5 + 0x29);
                pcVar2 = swi(3);
                (*pcVar2)();
                return;
            }
        }
    }
    else {
        fcn.140006bf0(arg1,&uStack_338);
        if (0xf < uStack_320) {
            uVar6 = uStack_320 + 1;
            iVar1 = CONCAT71(Stack_337,uStack_338);
            iVar5 = iVar1;
            if (0xfff < uVar6) {
                uVar6 = uStack_320 + 0x28;
                iVar5 = *(iVar1 + -8);
                if (0x1f < (iVar1 - iVar5) - 8U) goto code_r0x000140007d12;
            }
            fcn.140015008(iVar5,uVar6);
        }
        iStack_328 = 0;
        uStack_320 = 0xf;
        uStack_338 = 0;
        if (0xf < uStack_340) {
            uVar7 = uStack_340 + 1;
            uVar6 = uStack_358;
            if (0xfff < uVar7) {
                uVar7 = uStack_340 + 0x28;
                uVar6 = *(uStack_358 - 8);
                if (0x1f < (uStack_358 - uVar6) - 8) goto code_r0x000112916642;
            }
            fcn.140015008(uVar6,uVar7);
        }
        iStack_348 = 0;
        uStack_340 = 0xf;
        uStack_358 = uStack_358 & 0xffffffffffffff00;
        if (uStack_300 < 8) goto code_r0x000140007c82;
        iVar5 = uStack_300 * 2;
        if (0xfff < iVar5 + 2U) {
            iVar1 = *(CONCAT62(Stack_316,uStack_318) + -8);
            iVar4 = CONCAT62(Stack_316,uStack_318) - iVar1;
            goto joined_r0x000140007dd1;
        }
    }
    uStack_340 = 0xf;
    iStack_348 = 0;
    fcn.140015008();
code_r0x000140007c82:
    uStack_308 = *0x140018f60;
    uStack_300 = *0x140018f68;
    uStack_318 = 0;
    fcn.140003dd0(&iStack_2f8);
    fcn.1400153c0(uStack_48 ^ auStack_4c8);
    return;
}
