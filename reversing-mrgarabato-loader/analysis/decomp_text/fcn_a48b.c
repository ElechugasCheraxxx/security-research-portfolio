/* RVA 0xa48b  tam 187 B  addr 0x14000a48b */

//WARNING: Instruction at (ram,0x00014000a4db) overlaps instruction at (ram,0x00014000a4d9)
//

uint64_t int.14000a48b(int64_t arg1)

{
    char *pcVar1;
    char cVar2;
    code *pcVar3;
    uint8_t *puVar4;
    uint8_t *puVar5;
    uint64_t uVar6;
    int64_t unaff_RBP;
    uint8_t *unaff_RSI;
    uint8_t uVar7;
    int8_t var_ah;
    
    puVar4 = fcn.1402260b7();
    if (puVar4 != NULL) {
        puVar5 = fcn.1402cf74c(arg1);
        uVar7 = SBORROW8(puVar4,puVar5);
        if (puVar4 < puVar5) {
            return *puVar4;
        }
        puVar5 = fcn.1401fb5ff(arg1);
        pcVar1 = unaff_RBP + -10 + puVar4 * 2;
        cVar2 = *pcVar1;
        *pcVar1 = *pcVar1 << 7;
        if (uVar7 & 1) {
            if (-1 < cVar2 << 6 && *pcVar1 != '\0') {
                pcVar3 = swi(3);
                uVar6 = (*pcVar3)();
                return uVar6;
            }
        }
        else {
            if (*pcVar1 != '\0') {
                return 0xffffffff;
            }
            unaff_RSI = *(arg1 + 0x68);
        }
        if (unaff_RSI < puVar5) {
            unaff_RSI = puVar5;
        }
        if (puVar4 < unaff_RSI) {
            *(arg1 + 0x68) = unaff_RSI;
            uVar6 = fcn.140289bef(arg1);
            return uVar6;
        }
    }
    return 0xffffffff;
}
