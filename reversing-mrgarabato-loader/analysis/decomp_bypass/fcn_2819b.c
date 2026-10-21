/* RVA 0x2819b  tam 210 B  addr 0x14002819b */

void fcn.14002819b(int64_t arg1,int64_t arg2,int64_t arg3)

{
    int64_t *piVar1;
    ulong *puVar2;
    uint64_t uVar3;
    uint64_t uVar4;
    uint64_t uVar5;
    
    uVar5 = *(arg1 + 0x38);
    uVar4 = uVar5;
    for (; uVar5 != 0; uVar5 = uVar5 - 1) {
        uVar4 = uVar4 - 1;
        piVar1 = *(*(arg1 + 0x28) + uVar4 * 8);
        if ((*piVar1 == arg2) && (((arg3 & 0xfffffffffffffffcU) == 0 || (piVar1[1] == (arg3 & 0xfffffffffffffffcU))))) {
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
            if (piVar1 != NULL) {
                puVar2 = piVar1[5];
                if (puVar2 != NULL) {
                    fcn.14003c52c(*puVar2);
                    func_0x00014003c534(puVar2);
                }
                func_0x00014003c534(piVar1);
            }
        }
    }
    return;
}
