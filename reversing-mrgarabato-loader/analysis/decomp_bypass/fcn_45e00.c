/* RVA 0x45e00  tam 138 B  addr 0x140045e00 */

uint fcn.140045e00(int64_t arg1,int64_t arg2,int64_t arg3)

{
    uint32_t uVar1;
    int64_t iVar2;
    uint32_t uVar3;
    int *piVar4;
    
    if (arg1 == 0) {
        fcn.14003f234();
    }
    uVar1 = *(arg1 + 0x14);
    if (*(arg1 + 0x18) + *(arg2 + 8) == 0) {
        fcn.14003f234();
    }
    uVar3 = 0;
    if (uVar1 != 0) {
        iVar2 = *(arg2 + 8);
        piVar4 = iVar2 + *(arg1 + 0x18);
        do {
            if (arg3 < *piVar4 + iVar2) break;
            uVar3 = uVar3 + 1;
            piVar4 = piVar4 + 2;
        } while (uVar3 < uVar1);
        if (uVar3 != 0) {
            return *(*(arg1 + 0x18) + (uVar3 - 1) * 8 + 4 + iVar2);
        }
    }
    return 0xffffffff;
}
