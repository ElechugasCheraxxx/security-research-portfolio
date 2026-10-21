/* RVA 0x27fb6  tam 262 B  addr 0x140027fb6 */

int64_t * fcn.140027fa0(int64_t arg1,int64_t arg2,int64_t arg3,int64_t arg4)

{
    uchar auVar1 [16];
    int64_t *piVar2;
    ulong uVar3;
    int64_t iVar4;
    uint64_t uVar5;
    uint64_t uVar6;
    uint32_t in_stack_00000028;
    
    piVar2 = func_0x00014003c76c(0x38);
    if (piVar2 == NULL) {
        piVar2 = NULL;
    }
    else {
        piVar2[1] = arg4;
        *piVar2 = arg3;
        piVar2[3] = 0;
        *(piVar2 + 4) = 0;
        *(piVar2 + 2) = arg2;
        piVar2[5] = 0;
        *(piVar2 + 6) = 0;
        *(piVar2 + 0x24) = in_stack_00000028;
        if ((in_stack_00000028 >> 0x19 & 1) != 0) {
            *(piVar2 + 0x24) = in_stack_00000028 | 0xf003f;
        }
    }
    uVar5 = 0;
    iVar4 = *(arg1 + 0x30);
    if (*(arg1 + 0x38) == iVar4) {
        uVar6 = 1;
        if (iVar4 != 0) {
            uVar6 = iVar4 * 2;
        }
        auVar1._8_8_ = 0;
        auVar1._0_8_ = uVar6;
        uVar3 = SUB168(ZEXT816(8) * auVar1,0);
        if (SUB168(ZEXT816(8) * auVar1,8) != 0) {
            uVar3 = 0xffffffffffffffff;
        }
        iVar4 = fcn.14003c43c(uVar3);
        if (*(arg1 + 0x38) != 0) {
            do {
                uVar5 = uVar5 + 1;
                *(iVar4 + -8 + uVar5 * 8) = *(*(arg1 + 0x28) + -8 + uVar5 * 8);
            } while (uVar5 < *(arg1 + 0x38));
        }
        fcn.14003c52c(*(arg1 + 0x28));
        *(arg1 + 0x28) = iVar4;
        *(arg1 + 0x30) = uVar6;
    }
    *(*(arg1 + 0x28) + *(arg1 + 0x38) * 8) = piVar2;
    *(arg1 + 0x38) = *(arg1 + 0x38) + 1;
    return piVar2;
}
