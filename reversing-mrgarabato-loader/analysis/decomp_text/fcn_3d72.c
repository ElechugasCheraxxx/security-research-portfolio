/* RVA 0x3d72  tam 89 B  addr 0x140003d72 */

void fcn.140003d70(int64_t arg1)

{
    int64_t iVar1;
    int64_t iVar2;
    uint64_t uVar3;
    
    iVar1 = *arg1;
    if (iVar1 != 0) {
        uVar3 = *(arg1 + 0x10) - iVar1;
        iVar2 = iVar1;
        if (0xfff < uVar3) {
            iVar2 = *(iVar1 + -8);
            if (0x1f < (iVar1 - iVar2) - 8U) {
                fcn.140160c2a(iVar1 - iVar2,uVar3 + 0x27);
                return;
            }
        }
        fcn.140015008(iVar2);
        *arg1 = 0;
        *(arg1 + 8) = 0;
        *(arg1 + 0x10) = 0;
    }
    return;
}
