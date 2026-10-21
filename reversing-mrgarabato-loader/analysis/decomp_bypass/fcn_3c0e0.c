/* RVA 0x3c0e0  tam 483 B  addr 0x14003c0e0 */

void fcn.14003c0e0(int64_t arg1,int64_t arg2)

{
    uchar auVar1 [16];
    uchar auVar2 [16];
    uchar auVar3 [16];
    uint64_t uVar4;
    int64_t iVar5;
    uint *puVar6;
    ulong uVar7;
    int64_t *piVar8;
    int64_t *piVar9;
    int64_t *piVar10;
    uint64_t uVar11;
    int64_t *piVar12;
    int64_t *in_stack_00000048;
    
    iVar5 = *(arg1 + 8);
    piVar9 = NULL;
    if (*(arg1 + 0x10) == iVar5) {
        uVar11 = 1;
        if (iVar5 != 0) {
            uVar11 = iVar5 * 2;
        }
        auVar1._8_8_ = 0;
        auVar1._0_8_ = uVar11;
        uVar4 = SUB168(ZEXT816(0x10) * auVar1,0);
        if (SUB168(ZEXT816(0x10) * auVar1,8) != 0) {
            uVar4 = 0xffffffffffffffff;
        }
        iVar5 = uVar4 + 8;
        if (0xfffffffffffffff7 < uVar4) {
            iVar5 = -1;
        }
        puVar6 = fcn.14003c43c(iVar5);
        if (puVar6 == NULL) {
            piVar12 = piVar9;
        }
        else {
            *puVar6 = uVar11;
            func_0x00014003d8b8(puVar6 + 2,0x10,uVar11 & 0xffffffff,fcn.140023000,0x140023140);
            piVar12 = puVar6 + 2;
        }
        if (*(arg1 + 0x10) != 0) {
            piVar8 = piVar12;
            do {
                piVar10 = piVar8 + (*arg1 - piVar12);
                if (piVar10 != piVar8) {
                    fcn.14003c52c(*piVar8);
                    iVar5 = piVar10[1];
                    piVar8[1] = iVar5;
                    auVar2._8_8_ = 0;
                    auVar2._0_8_ = iVar5 + 1;
                    uVar7 = SUB168(ZEXT816(2) * auVar2,0);
                    if (SUB168(ZEXT816(2) * auVar2,8) != 0) {
                        uVar7 = 0xffffffffffffffff;
                    }
                    iVar5 = fcn.14003c43c(uVar7);
                    *piVar8 = iVar5;
                    fcn.140041d50(iVar5,*piVar10,piVar8[1] * 2);
                    *(*piVar8 + piVar8[1] * 2) = 0;
                }
                piVar9 = piVar9 + 1;
                piVar8 = piVar8 + 2;
            } while (piVar9 < *(arg1 + 0x10));
            arg2 = in_stack_00000048;
        }
        iVar5 = *arg1;
        if (iVar5 != 0) {
            fcn.14003ca2c(iVar5,0x10,*(iVar5 + -8),0x140023140);
            fcn.14003c52c(iVar5 + -8);
        }
        *arg1 = piVar12;
        *(arg1 + 8) = uVar11;
    }
    piVar9 = *(arg1 + 0x10) * 0x10 + *arg1;
    *(arg1 + 0x10) = *(arg1 + 0x10) + 1;
    if (arg2 != piVar9) {
        fcn.14003c52c(*piVar9);
        iVar5 = *(arg2 + 8);
        piVar9[1] = iVar5;
        auVar3._8_8_ = 0;
        auVar3._0_8_ = iVar5 + 1;
        uVar7 = SUB168(ZEXT816(2) * auVar3,0);
        if (SUB168(ZEXT816(2) * auVar3,8) != 0) {
            uVar7 = 0xffffffffffffffff;
        }
        iVar5 = fcn.14003c43c(uVar7);
        *piVar9 = iVar5;
        fcn.140041d50(iVar5,*arg2,piVar9[1] * 2);
        *(*piVar9 + piVar9[1] * 2) = 0;
    }
    return;
}
