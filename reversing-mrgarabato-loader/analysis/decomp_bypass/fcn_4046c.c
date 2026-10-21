/* RVA 0x4046c  tam 714 B  addr 0x14004046c */

//WARNING: Variable defined which should be unmapped: var_10h

void fcn.14004046c(int64_t arg1,int64_t arg2,int64_t arg3,int64_t arg4,int32_t arg_60h,int64_t arg_68h,
                  int32_t arg_70h,int32_t arg_78h,int32_t arg_80h)

{
    uint uVar1;
    uint32_t uVar2;
    int iVar3;
    char *pcVar4;
    int64_t iVar5;
    uint *puVar6;
    uint *puVar7;
    uint64_t uVar8;
    uint64_t uVar9;
    uint *puVar10;
    uchar *puVar11;
    uchar *puVar12;
    uchar *puVar13;
    uchar *puVar14;
    uint *puVar15;
    uint32_t uVar16;
    uint64_t unaff_R13;
    int64_t var_8h;
    int64_t var_10h;
    uint32_t in_stack_00000028;
    ulong in_stack_00000030;
    int64_t var_bp_40h;
    int64_t var_48h;
    int64_t var_50h;
    uchar auStack_78 [32];
    ulong uStack_58;
    uint uStack_50;
    uint auStack_38 [2];
    uint64_t uStack_30;
    
    puVar14 = &stack0xffffffffffffff88;
    puVar11 = &stack0xffffffffffffff88;
    uStack_30 = *0x140053bd0 ^ &stack0xffffffffffffffc8;
    uVar9 = in_stack_00000028;
    puVar15 = NULL;
    auStack_38[0] = arg2;
    if (0 < in_stack_00000028) {
        pcVar4 = arg4;
        uVar16 = in_stack_00000028;
        do {
            uVar16 = uVar16 - 1;
            if (*pcVar4 == '\0') goto code_r0x0001400404c5;
            pcVar4 = pcVar4 + 1;
        } while (uVar16 != 0);
        uVar16 = 0xffffffff;
code_r0x0001400404c5:
        uVar2 = (in_stack_00000028 - uVar16) - 1;
        uVar9 = in_stack_00000028 - uVar16;
        if (in_stack_00000028 <= uVar2) {
            uVar9 = uVar2;
        }
    }
    if (var_48h == 0) {
        var_48h._0_4_ = *(*arg1 + 4);
    }
    uVar8 = var_48h;
    uStack_50 = 0;
    uStack_58 = 0;
    iVar3 = func_0x00014015fc2a(uVar8,(-(var_50h != 0) & 8U) + 1,arg4,uVar9);
    *(uVar9 - 0x18) = uVar8;
    if (iVar3 == 0) goto code_r0x000140040710;
    puVar14 = &stack0xffffffffffffff88;
    if ((0 < iVar3) && (puVar14 = &stack0xffffffffffffff88, 1 < 0xffffffffffffffe0 / unaff_R13)) {
        uVar8 = unaff_R13 * 2 + 0x10;
        if (uVar8 < 0x401) {
            iVar5 = func_0x000140044210(uVar8,0xffffffffffffffe0 % unaff_R13,0xffffffffffffff0);
            iVar5 = -iVar5;
            puVar14 = &stack0xffffffffffffff88 + iVar5;
            puVar11 = &stack0xffffffffffffff88 + iVar5;
            puVar6 = &stack0xffffffffffffffc8 + iVar5;
            if (puVar6 == NULL) goto code_r0x000140040710;
            *puVar6 = 0xcccc;
        }
        else {
            puVar6 = fcn.14003f11c(uVar8);
            puVar15 = NULL;
            puVar14 = &stack0xffffffffffffff88;
            if (puVar6 == NULL) goto code_r0x000140040586;
            *puVar6 = 0xdddd;
        }
        puVar15 = puVar6 + 4;
        puVar14 = puVar11;
    }
code_r0x000140040586:
    if (puVar15 == NULL) goto code_r0x000140040710;
    *(puVar14 + 0x28) = unaff_R13;
    *(puVar14 + 0x20) = puVar15;
    *(puVar14 + -8) = 0;
    *(puVar14 + -0x10) = 0x1400405a9;
    iVar3 = func_0x0001401d581b(var_48h,1,arg4,uVar9);
    uVar1 = auStack_38[0];
    puVar13 = puVar14 + -8;
    if (iVar3 != 0) {
        *(puVar14 + 0x20) = 0;
        *(puVar14 + 0x18) = 0;
        puVar12 = puVar14 + -0x10;
        *(puVar14 + -0x10) = uVar9;
        *(puVar14 + -0x18) = 0x1400405d0;
        puVar6 = func_0x00014021f73e(uVar1,arg3 & 0xffffffff,puVar15,unaff_R13 & 0xffffffff);
        iVar3 = puVar6;
        uVar9 = iVar3;
        puVar13 = puVar14 + -0x10;
        if (iVar3 != 0) {
            if ((arg3 & 0x400U) == 0) {
                puVar7 = puVar6;
                if (iVar3 < 1) {
code_r0x000140040688:
                    puVar10 = NULL;
                    puVar13 = puVar14 + -0x10;
                }
                else {
                    puVar7 = 0xffffffffffffffe0 / uVar9;
                    if (puVar7 < 0x2) goto code_r0x000140040688;
                    uVar8 = uVar9 * 2 + 0x10;
                    if (uVar8 < 0x401) {
                        *(puVar14 + -0x18) = 0x140040656;
                        puVar7 = func_0x000140044210(uVar8,0xffffffffffffffe0 % uVar9);
                        iVar5 = -puVar7;
                        puVar13 = puVar14 + iVar5 + -0x10;
                        puVar12 = puVar14 + iVar5 + -0x10;
                        puVar10 = puVar14 + iVar5 + 0x30;
                        if (puVar10 == NULL) goto code_r0x0001400406fd;
                        *puVar10 = 0xcccc;
code_r0x000140040682:
                        puVar10 = puVar10 + 4;
                        puVar13 = puVar12;
                    }
                    else {
                        *(puVar14 + -0x18) = 0x140040674;
                        puVar7 = fcn.14003f11c(uVar8);
                        puVar10 = NULL;
                        puVar13 = puVar14 + -0x10;
                        if (puVar7 != NULL) {
                            *puVar7 = 0xdddd;
                            puVar10 = puVar7;
                            goto code_r0x000140040682;
                        }
                    }
                }
                if (puVar10 != NULL) {
                    *(puVar13 + 0x28) = iVar3;
                    *(puVar13 + 0x20) = puVar10;
                    *(puVar13 + -8) = puVar7;
                    *(puVar13 + -0x10) = 0x1400406aa;
                    iVar3 = func_0x0001406b3dce(uVar1,arg3 & 0xffffffff,puVar15,unaff_R13 & 0xffffffff);
                    puVar14 = puVar13 + -8;
                    if (iVar3 != 0) {
                        *(puVar13 + 0x30) = 0;
                        *(puVar13 + 0x28) = 0;
                        if (var_bp_40h == 0) {
                            *(puVar13 + 0x20) = 0;
                            *(puVar13 + 0x18) = 0;
                        }
                        else {
                            *(puVar13 + 0x20) = var_bp_40h;
                            *(puVar13 + 0x18) = in_stack_00000030;
                        }
                        *(puVar13 + -0x10) = var_48h;
                        *(puVar13 + -0x18) = 0x1400406ea;
                        func_0x000140196c54(var_48h,0,puVar10,puVar6 & 0xffffffff);
                        puVar14 = puVar13 + -0x10;
                    }
                    puVar13 = puVar14;
                    if (puVar10[-4] == 0xdddd) {
                        *(puVar13 + -8) = 0x1400406fd;
                        fcn.14003dc60(puVar10 + -4);
                    }
                }
            }
            else {
                puVar13 = puVar14 + -0x10;
                if ((var_bp_40h != 0) && (puVar13 = puVar14 + -0x10, iVar3 <= var_bp_40h)) {
                    *(puVar14 + 0x18) = var_bp_40h;
                    *(puVar14 + 0x10) = in_stack_00000030;
                    puVar13 = puVar14 + -0x18;
                    *(puVar14 + -0x18) = puVar15;
                    *(puVar14 + -0x20) = 0x140040618;
                    func_0x00014024f435(uVar1,arg3 & 0xffffffff,puVar15,unaff_R13 & 0xffffffff);
                }
            }
        }
    }
code_r0x0001400406fd:
    puVar14 = puVar13;
    if (puVar15[-4] == 0xdddd) {
        *(puVar13 + -8) = 0x14004070e;
        fcn.14003dc60(puVar15 + -4);
    }
code_r0x000140040710:
    uVar9 = uStack_30 ^ &stack0xffffffffffffffc8;
    *(puVar14 + -8) = 0x14004071c;
    fcn.140042300(uVar9);
    return;
}
