/* RVA 0x4516  tam 134 B  addr 0x140004516 */

int64_t fcn.140004516(int64_t arg1,int64_t arg2)

{
    uint64_t uVar1;
    code *pcVar2;
    ulong uVar3;
    int64_t iVar4;
    int64_t iVar5;
    
    if (arg1 != arg2) {
        uVar1 = *(arg1 + 0x18);
        if (0xf < uVar1) {
            iVar4 = *arg1;
            iVar5 = iVar4;
            if (0xfff < uVar1 + 1) {
                iVar5 = *(iVar4 + -8);
                if (0x1f < (iVar4 - iVar5) - 8U) {
                    fcn.14012b71e(iVar4 - iVar5,uVar1 + 0x28);
                    pcVar2 = swi(3);
                    iVar4 = (*pcVar2)();
                    return iVar4;
                }
            }
            fcn.140015008(iVar5);
        }
        *(arg1 + 0x18) = 0xf;
        *(arg1 + 0x10) = 0;
        *arg1 = 0;
        uVar3 = *(arg2 + 8);
        *arg1 = *arg2;
        *(arg1 + 8) = uVar3;
        uVar3 = *(arg2 + 0x18);
        *(arg1 + 0x10) = *(arg2 + 0x10);
        *(arg1 + 0x18) = uVar3;
        *(arg2 + 0x10) = 0;
        *(arg2 + 0x18) = 0xf;
        *arg2 = 0;
    }
    return arg1;
}
