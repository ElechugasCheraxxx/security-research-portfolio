/* RVA 0x44a48  tam 207 B  addr 0x140044a48 */

uint fcn.140044a48(int64_t arg1,int64_t arg2,int64_t arg3,int64_t arg4)

{
    int16_t iVar1;
    uint *puVar2;
    uint uVar3;
    int64_t iVar4;
    int64_t iVar5;
    int16_t *piVar6;
    
    if (arg4 == 0) {
        if (arg1 == 0) {
            if (arg2 == 0) {
                return 0;
            }
        }
        else {
code_r0x000140044a6b:
            if (arg2 != 0) {
                if (arg4 == 0) {
                    *arg1 = 0;
                    return 0;
                }
                if (arg3 != 0) {
                    iVar4 = arg2;
                    if (arg4 == -1) {
                        iVar5 = arg1 - arg3;
                        do {
                            iVar1 = *arg3;
                            *(iVar5 + arg3) = iVar1;
                            arg3 = arg3 + 2;
                            if (iVar1 == 0) break;
                            iVar4 = iVar4 + -1;
                        } while (iVar4 != 0);
                    }
                    else {
                        piVar6 = arg1;
                        do {
                            iVar1 = *((arg3 - arg1) + piVar6);
                            *piVar6 = iVar1;
                            piVar6 = piVar6 + 1;
                            if ((iVar1 == 0) || (iVar4 = iVar4 + -1, iVar4 == 0)) break;
                            arg4 = arg4 + -1;
                        } while (arg4 != 0);
                        if (arg4 == 0) {
                            *piVar6 = 0;
                        }
                    }
                    if (iVar4 != 0) {
                        return 0;
                    }
                    if (arg4 == -1) {
                        *(arg1 + -2 + arg2 * 2) = 0;
                        return 0x50;
                    }
                    *arg1 = 0;
                    puVar2 = fcn.14003ef2c();
                    uVar3 = 0x22;
                    goto code_r0x000140044a8c;
                }
                *arg1 = 0;
            }
        }
    }
    else if (arg1 != 0) goto code_r0x000140044a6b;
    puVar2 = fcn.14003ef2c();
    uVar3 = 0x16;
code_r0x000140044a8c:
    *puVar2 = uVar3;
    fcn.14003eec4();
    return uVar3;
}
