/* RVA 0x37f30  tam 322 B  addr 0x140037f30 */

int64_t fcn.140037f30(int64_t arg1,int64_t arg2)

{
    uchar auVar1 [16];
    uchar auVar2 [16];
    ulong uVar3;
    int64_t iVar4;
    int64_t iVar5;
    int16_t *piVar6;
    ulong in_R9;
    ulong uVar7;
    int64_t iStack_40;
    int64_t iStack_38;
    
    uVar7 = 0xfffffffffffffffe;
    *arg1 = 0;
    *(arg1 + 8) = 0;
    *(arg1 + 0x10) = 0;
    piVar6 = arg2;
    if (*arg2 != 0) {
        do {
            if (*piVar6 == 0x5c) {
                if (arg2 < piVar6) {
                    iVar5 = piVar6 - arg2 >> 1;
                    auVar1._8_8_ = 0;
                    auVar1._0_8_ = iVar5 + 1;
                    uVar3 = SUB168(ZEXT816(2) * auVar1,0);
                    if (SUB168(ZEXT816(2) * auVar1,8) != 0) {
                        uVar3 = 0xffffffffffffffff;
                    }
                    iStack_38 = iVar5;
                    iVar4 = fcn.14003c43c(uVar3);
                    iStack_40 = iVar4;
                    fcn.140041d50(iVar4,arg2,iVar5 * 2);
                    *(iVar5 * 2 + iVar4) = 0;
                    func_0x00014003c0d0(arg1,&iStack_40);
                    fcn.14003c52c(iVar4);
                }
                arg2 = piVar6 + 1;
            }
            piVar6 = piVar6 + 1;
        } while (*piVar6 != 0);
        if (arg2 < piVar6) {
            iVar5 = piVar6 - arg2 >> 1;
            auVar2._8_8_ = 0;
            auVar2._0_8_ = iVar5 + 1;
            uVar3 = SUB168(ZEXT816(2) * auVar2,0);
            if (SUB168(ZEXT816(2) * auVar2,8) != 0) {
                uVar3 = 0xffffffffffffffff;
            }
            iStack_38 = iVar5;
            iVar4 = fcn.14003c43c(uVar3);
            iStack_40 = iVar4;
            fcn.140041d50(iVar4,arg2,iVar5 * 2,in_R9,uVar7);
            *(iVar5 * 2 + iVar4) = 0;
            func_0x00014003c0d0(arg1,&iStack_40);
            fcn.14003c52c(iVar4);
        }
    }
    return arg1;
}
