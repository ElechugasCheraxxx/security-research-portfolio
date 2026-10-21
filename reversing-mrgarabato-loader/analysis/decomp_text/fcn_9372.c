/* RVA 0x9372  tam 102 B  addr 0x140009372 */

void fcn.140009370(int64_t arg1)

{
    int64_t iVar1;
    int64_t iVar2;
    code *pcVar3;
    int64_t iVar4;
    
    if (7 < *(arg1 + 0x18)) {
        iVar2 = *arg1;
        iVar1 = *(arg1 + 0x18) * 2;
        iVar4 = iVar2;
        if (0xfff < iVar1 + 2U) {
            iVar4 = *(iVar2 + -8);
            if (0x1f < (iVar2 - iVar4) - 8U) {
                fcn.1402307a6(iVar2 - iVar4,iVar1 + 0x29);
                func_0x00010ccd60a1();
                pcVar3 = swi(3);
                (*pcVar3)();
                return;
            }
        }
        fcn.140015008(iVar4);
    }
    *(arg1 + 0x18) = 7;
    *(arg1 + 0x10) = 0;
    *arg1 = 0;
    return;
}
