/* RVA 0xb6e0  tam 92 B  addr 0x14000b6e0 */

void fcn.14000b6e0(int64_t arg1)

{
    int64_t iVar1;
    code *pcVar2;
    int64_t iVar3;
    uint64_t uVar4;
    
    iVar1 = *arg1;
    if (iVar1 != 0) {
        uVar4 = *(arg1 + 0x10) - iVar1 & 0xfffffffffffffff8;
        iVar3 = iVar1;
        if (0xfff < uVar4) {
            iVar3 = *(iVar1 + -8);
            if (0x1f < (iVar1 - iVar3) - 8U) {
                fcn.1401cec9e(iVar1 - iVar3,uVar4 + 0x27);
                pcVar2 = swi(3);
                (*pcVar2)();
                return;
            }
        }
        fcn.140015008(iVar3);
        *arg1 = 0;
        *(arg1 + 8) = 0;
        *(arg1 + 0x10) = 0;
    }
    return;
}
