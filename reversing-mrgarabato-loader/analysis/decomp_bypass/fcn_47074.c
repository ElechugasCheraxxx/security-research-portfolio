/* RVA 0x47074  tam 549 B  addr 0x140047074 */

ulong fcn.140047074(int64_t arg1,int64_t arg2,int64_t arg3,int64_t arg4)

{
    uint32_t uVar1;
    int iVar2;
    int64_t iVar3;
    ulong uVar4;
    code *pcVar5;
    uint32_t *in_stack_00000028;
    int in_stack_00000030;
    ulong in_stack_00000038;
    uint8_t in_stack_00000040;
    ulong in_stack_ffffffffffffffd8;
    uint uVar6;
    ulong in_stack_ffffffffffffffe0;
    uint uVar7;
    
    uVar6 = in_stack_ffffffffffffffd8 >> 0x20;
    uVar7 = in_stack_ffffffffffffffe0 >> 0x20;
    iVar3 = fcn.14003e9d8();
    if (((((*(iVar3 + 0x2c0) != 0) || (*arg1 == -0x1f928c9d)) ||
         ((*arg1 == -0x7fffffd7 && ((*(arg1 + 0x18) == 0xf && (*(arg1 + 0x60) == 0x19930520)))))) ||
        (*arg1 == -0x7fffffda)) ||
       (((*in_stack_00000028 & 0x1fffffff) < 0x19930522 || ((in_stack_00000028[9] & 1) == 0)))) {
        if ((*(arg1 + 4) & 0x66) == 0) {
            if (in_stack_00000028[3] == 0) {
                if ((*in_stack_00000028 & 0x1fffffff) < 0x19930521) {
                    return 1;
                }
                if (in_stack_00000028[8] == 0) {
                    iVar3 = 0;
                }
                else {
                    iVar3 = fcn.140045878();
                    iVar3 = iVar3 + in_stack_00000028[8];
                }
                if (iVar3 == 0) {
                    return 1;
                }
            }
            if (((*arg1 == -0x1f928c9d) && (2 < *(arg1 + 0x18))) && (0x19930522 < *(arg1 + 0x20))) {
                if (*(*(arg1 + 0x30) + 8) == 0) {
                    pcVar5 = NULL;
                }
                else {
                    iVar3 = fcn.140045890();
                    pcVar5 = *(*(arg1 + 0x30) + 8) + iVar3;
                }
                if (pcVar5 != NULL) {
                    uVar4 = (*pcVar5)(arg1,arg2,arg3,arg4,in_stack_00000028,in_stack_00000030,in_stack_00000038,
                                      CONCAT44(uVar7,in_stack_00000040));
                    return uVar4;
                }
            }
            func_0x000140046b80(arg1,arg2,arg3,arg4,in_stack_00000028,in_stack_00000040,
                                CONCAT44(uVar6,in_stack_00000030),in_stack_00000038);
        }
        else if ((in_stack_00000028[1] != 0) && (in_stack_00000030 == 0)) {
            uVar1 = *(arg1 + 4) & 0x20;
            if ((uVar1 == 0) || (*arg1 != -0x7fffffda)) {
                if ((uVar1 == 0) || (*arg1 != -0x7fffffd7)) {
                    func_0x0001400458e0(arg2,arg4,in_stack_00000028);
                    return 1;
                }
                iVar2 = *(arg1 + 0x38);
                if ((iVar2 < -1) || (in_stack_00000028[1] <= iVar2)) {
                    fcn.14003f234();
                }
                arg2 = *(arg1 + 0x28);
            }
            else {
                iVar2 = fcn.140045e00(in_stack_00000028,arg4,*(arg3 + 0xf8));
                if ((iVar2 < -1) || (in_stack_00000028[1] <= iVar2)) {
                    fcn.14003f234();
                }
            }
            func_0x0001400460f4(arg2,arg4,in_stack_00000028,iVar2);
        }
    }
    return 1;
}
