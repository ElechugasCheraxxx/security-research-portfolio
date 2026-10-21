/* RVA 0x45b0c  tam 297 B  addr 0x140045b0c */

int64_t fcn.140045b0c(ulong noname_0,int64_t arg1,ulong noname_2,int64_t arg2)

{
    uint32_t uVar1;
    int iVar2;
    uint32_t uVar3;
    int *piVar4;
    uint32_t uVar5;
    int64_t iVar6;
    int64_t iVar7;
    uint32_t *in_stack_00000028;
    int *in_stack_00000030;
    int64_t in_stack_00000038;
    
    uVar1 = *(arg1 + 0xc);
    iVar6 = 0;
    iVar2 = func_0x000140045e8c(arg1,in_stack_00000038);
    if (uVar1 == 0) {
        fcn.14003f234();
    }
    *in_stack_00000030 = -1;
    *in_stack_00000028 = 0xffffffff;
    uVar5 = uVar1;
    if (uVar1 != 0) {
        piVar4 = *(arg1 + 0x10) + uVar1 * 0x14 + -0xc + *(in_stack_00000038 + 8);
        do {
            if ((piVar4[-1] < iVar2) && (iVar2 <= *piVar4)) break;
            piVar4 = piVar4 + -5;
            uVar5 = uVar5 - 1;
        } while (uVar5 != 0);
    }
    if (uVar5 != 0) {
        iVar6 = *(arg1 + 0x10) + (uVar5 - 1) * 0x14 + *(in_stack_00000038 + 8);
    }
    uVar5 = 0;
    if (uVar1 != 0) {
        iVar7 = 0;
        do {
            piVar4 = *(arg1 + 0x10) + *(in_stack_00000038 + 8) + iVar7;
            if ((((iVar6 == 0) || ((*(iVar6 + 4) < *piVar4 && (piVar4[1] <= *(iVar6 + 8))))) && (*piVar4 <= arg2)) &&
               (arg2 <= piVar4[1])) {
                uVar3 = *in_stack_00000028;
                if (*in_stack_00000028 == 0xffffffff) {
                    uVar3 = uVar5;
                }
                *in_stack_00000028 = uVar3;
                *in_stack_00000030 = uVar5 + 1;
            }
            uVar5 = uVar5 + 1;
            iVar7 = iVar7 + 0x14;
        } while (uVar5 < uVar1);
        if (*in_stack_00000028 != 0xffffffff) {
            return *(arg1 + 0x10) + *in_stack_00000028 * 0x14 + *(in_stack_00000038 + 8);
        }
    }
    *in_stack_00000028 = 0;
    *in_stack_00000030 = 0;
    return 0;
}
