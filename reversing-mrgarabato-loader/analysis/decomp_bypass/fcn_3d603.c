/* RVA 0x3d603  tam 619 B  addr 0x14003d603 */

//WARNING: Variable defined which should be unmapped: var_bp_8h
//WARNING: Variable defined which should be unmapped: var_10h
//WARNING: Variable defined which should be unmapped: var_bp_20h

uint32_t fcn.14003d5e8(int64_t arg1,int64_t arg2,int64_t arg3,int64_t arg4,int32_t arg_50h)

{
    uint16_t uVar1;
    uint8_t *puVar2;
    uint32_t uVar3;
    uint *puVar4;
    uint32_t uVar5;
    int iVar6;
    uint8_t *puVar7;
    uint32_t uVar8;
    int64_t iVar9;
    uint8_t uVar10;
    uint64_t uVar11;
    uint32_t in_stack_00000028;
    int64_t aiStack_48 [2];
    int64_t iStack_38;
    char cStack_30;
    int64_t var_bp_20h;
    int64_t var_10h;
    int8_t var_bp_8h;
    
    uVar11 = arg4 & 0xffffffff;
    fcn.14003c53c(aiStack_48,arg1);
    if (arg3 != 0) {
        *arg3 = arg2;
    }
    if ((arg2 == 0) || ((iVar6 = arg4, iVar6 != 0 && ((iVar6 < 2 || (0x24 < iVar6)))))) {
        puVar4 = fcn.14003ef2c();
        *puVar4 = 0x16;
        fcn.14003eec4();
        goto code_r0x00014003d826;
    }
    uVar10 = *arg2;
    uVar8 = 0;
    iVar9 = aiStack_48[0];
    puVar2 = arg2;
    while( true ) {
        puVar7 = puVar2 + 1;
        if (*(iVar9 + 0x10c) < 2) {
            uVar3 = *(*(iVar9 + 0x140) + uVar10 * 2) & 8;
        }
        else {
            uVar3 = func_0x000140040384(uVar10,8,aiStack_48);
            iVar9 = aiStack_48[0];
        }
        if (uVar3 == 0) break;
        uVar10 = *puVar7;
        puVar2 = puVar7;
    }
    if (uVar10 == 0x2d) {
        in_stack_00000028 = in_stack_00000028 | 2;
code_r0x00014003d6b4:
        uVar10 = *puVar7;
        puVar7 = puVar2 + 2;
    }
    else if (uVar10 == 0x2b) goto code_r0x00014003d6b4;
    if (((iVar6 < 0) || (iVar6 == 1)) || (0x24 < iVar6)) {
        if (arg3 != 0) {
            *arg3 = arg2;
        }
code_r0x00014003d826:
        if (cStack_30 != '\0') {
            *(iStack_38 + 200) = *(iStack_38 + 200) & 0xfffffffd;
        }
        return 0;
    }
    if (iVar6 == 0) {
        if (uVar10 != 0x30) {
            uVar11 = 10;
            goto code_r0x00014003d722;
        }
        if ((*puVar7 != 0x78) && (*puVar7 != 0x58)) {
            uVar11 = 8;
            goto code_r0x00014003d722;
        }
        uVar11 = 0x10;
    }
    else if ((iVar6 != 0x10) || (uVar10 != 0x30)) goto code_r0x00014003d722;
    if ((*puVar7 == 0x78) || (*puVar7 == 0x58)) {
        uVar10 = puVar7[1];
        puVar7 = puVar7 + 2;
    }
code_r0x00014003d722:
    do {
        uVar1 = *(*(iVar9 + 0x140) + uVar10 * 2);
        uVar3 = in_stack_00000028;
        if ((uVar1 & 4) == 0) {
            if ((uVar1 & 0x103) == 0) {
code_r0x00014003d785:
                puVar7 = puVar7 + -1;
                if ((uVar3 & 8) == 0) {
                    if (arg3 != 0) {
                        puVar7 = arg2;
                    }
                    uVar8 = 0;
                }
                else if (((uVar3 & 4) != 0) ||
                        (((uVar3 & 1) == 0 &&
                         ((((uVar3 & 2) != 0 && (0x80000000 < uVar8)) || (((uVar3 & 2) == 0 && (0x7fffffff < uVar8))))))
                        )) {
                    puVar4 = fcn.14003ef2c();
                    *puVar4 = 0x22;
                    if ((uVar3 & 1) == 0) {
                        uVar8 = ((uVar3 & 2) != 0) + 0x7fffffff;
                    }
                    else {
                        uVar8 = 0xffffffff;
                    }
                }
                if (arg3 != 0) {
                    *arg3 = puVar7;
                }
                if ((uVar3 & 2) != 0) {
                    uVar8 = -uVar8;
                }
                if (cStack_30 != '\0') {
                    *(iStack_38 + 200) = *(iStack_38 + 200) & 0xfffffffd;
                }
                return uVar8;
            }
            iVar6 = uVar10;
            if (uVar10 + 0x9f < 0x1a) {
                iVar6 = iVar6 + -0x20;
            }
            uVar5 = iVar6 - 0x37;
        }
        else {
            uVar5 = uVar10 - 0x30;
        }
        if (uVar11 <= uVar5) goto code_r0x00014003d785;
        uVar3 = 0xffffffff / uVar11;
        if ((uVar8 < uVar3) || ((uVar8 == uVar3 && (uVar5 <= 0xffffffff % uVar11)))) {
            uVar8 = uVar8 * uVar11 + uVar5;
            in_stack_00000028 = in_stack_00000028 | 8;
        }
        else {
            uVar3 = in_stack_00000028 | 0xc;
            in_stack_00000028 = in_stack_00000028 | 0xc;
            if (arg3 == 0) goto code_r0x00014003d785;
        }
        uVar10 = *puVar7;
        puVar7 = puVar7 + 1;
    } while( true );
}
