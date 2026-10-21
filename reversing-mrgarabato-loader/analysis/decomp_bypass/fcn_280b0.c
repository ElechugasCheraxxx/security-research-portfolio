/* RVA 0x280b0  tam 216 B  addr 0x1400280b0 */

void fcn.1400280b0(int64_t arg1,int64_t arg2)

{
    int64_t iVar1;
    ulong *puVar2;
    uint64_t uVar3;
    uint64_t uVar4;
    uint64_t uVar5;
    
    uVar5 = *(arg1 + 0x38);
    uVar4 = uVar5;
    for (; uVar5 != 0; uVar5 = uVar5 - 1) {
        uVar4 = uVar4 - 1;
        iVar1 = *(*(arg1 + 0x28) + uVar4 * 8);
        if (*(iVar1 + 8) == (arg2 & 0xfffffffffffffffcU)) {
            if (uVar4 < *(arg1 + 0x38)) {
                uVar3 = uVar4;
                if (uVar4 < *(arg1 + 0x38) - 1) {
                    do {
                        uVar3 = uVar3 + 1;
                        *(*(arg1 + 0x28) + -8 + uVar3 * 8) = *(*(arg1 + 0x28) + uVar3 * 8);
                    } while (uVar3 < *(arg1 + 0x38) - 1U);
                }
                *(arg1 + 0x38) = *(arg1 + 0x38) + -1;
            }
            if (iVar1 != 0) {
                puVar2 = *(iVar1 + 0x28);
                if (puVar2 != NULL) {
                    fcn.14003c52c(*puVar2);
                    func_0x00014003c534(puVar2);
                }
                func_0x00014003c534(iVar1);
            }
        }
    }
    return;
}
