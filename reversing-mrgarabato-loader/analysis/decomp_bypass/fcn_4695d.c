/* RVA 0x4695d  tam 547 B  addr 0x14004695d */

void fcn.14004695d(int64_t arg1,int64_t arg2,int64_t arg3,int64_t arg4)

{
    int iVar1;
    int64_t iVar2;
    int64_t iVar3;
    int *piVar4;
    int32_t var_ch;
    uint32_t in_stack_00000040;
    ulong in_stack_00000050;
    int64_t in_stack_00000060;
    uint32_t in_stack_00000068;
    uint32_t in_stack_00000070;
    ulong in_stack_00000078;
    ulong in_stack_ffffffffffffffc8;
    uint uVar5;
    uint32_t uStack_10;
    
    uVar5 = in_stack_ffffffffffffffc8 >> 0x20;
    if (*arg1 != -0x7ffffffd) {
        iVar2 = fcn.14003e9d8();
        if (*(iVar2 + 0xe0) != 0) {
            iVar2 = fcn.14003e9d8();
            iVar3 = fcn.14003e864();
            if ((((*(iVar2 + 0xe0) != iVar3) && (*arg1 != -0x1fbcb0b3)) && (*arg1 != -0x1fbcbcae)) &&
               (iVar1 = func_0x000140045ab8(arg1,arg2,arg3,arg4,in_stack_00000060,
                                            CONCAT44(uVar5,in_stack_00000070),in_stack_00000078), iVar1 != 0)) {
                return;
            }
        }
        if (*(in_stack_00000060 + 0xc) == 0) {
            fcn.14003f234();
        }
        iVar2 = fcn.140045b0c(arg2,in_stack_00000060,in_stack_00000070,in_stack_00000068);
        if (in_stack_00000040 < uStack_10) {
            piVar4 = iVar2 + 0xc;
            do {
                if ((piVar4[-3] <= in_stack_00000068) && (in_stack_00000068 <= piVar4[-2])) {
                    iVar2 = fcn.140045878();
                    if (*(iVar2 + -0x10 + piVar4[1] + *piVar4 * 0x14) == 0) {
                        iVar2 = 0;
                    }
                    else {
                        iVar2 = fcn.140045878();
                        iVar1 = *(iVar2 + -0x10 + piVar4[1] + *piVar4 * 0x14);
                        iVar2 = fcn.140045878();
                        iVar2 = iVar2 + iVar1;
                    }
                    if (iVar2 != 0) {
                        iVar2 = fcn.140045878();
                        if (*(iVar2 + -0x10 + piVar4[1] + *piVar4 * 0x14) == 0) {
                            iVar2 = 0;
                        }
                        else {
                            iVar2 = fcn.140045878();
                            iVar1 = *(iVar2 + -0x10 + piVar4[1] + *piVar4 * 0x14);
                            iVar2 = fcn.140045878();
                            iVar2 = iVar2 + iVar1;
                        }
                        if (*(iVar2 + 0x10) != '\0') goto code_r0x000140046b51;
                    }
                    iVar2 = fcn.140045878();
                    if ((*(iVar2 + -0x14 + piVar4[1] + *piVar4 * 0x14) & 0x40) == 0) {
                        iVar2 = fcn.140045878();
                        func_0x000140046884(arg1,arg2,in_stack_00000050,arg4,in_stack_00000060,
                                            iVar2 + (*piVar4 + -1) * 0x14 + piVar4[1],0,piVar4 + -3,0);
                    }
                }
code_r0x000140046b51:
                in_stack_00000040 = in_stack_00000040 + 1;
                piVar4 = piVar4 + 5;
            } while (in_stack_00000040 < uStack_10);
        }
    }
    return;
}
