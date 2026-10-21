/* RVA 0x96f5  tam 241 B  addr 0x1400096f5 */

int64_t fcn.1400096f5(int64_t arg1,int64_t arg2,int64_t arg3)

{
    uint64_t *puVar1;
    int64_t iVar2;
    char cVar3;
    uint64_t uVar4;
    int iVar5;
    int64_t iVar6;
    uint64_t uVar7;
    
    uVar4 = *(arg2 + 0x10);
    if (0xf < *(arg2 + 0x18)) {
        arg2 = *arg2;
    }
    puVar1 = arg1 + 0x10;
    if (0xf < *(arg1 + 0x18)) {
        arg1 = *arg1;
    }
    if ((uVar4 <= *puVar1) && (uVar7 = *puVar1 - uVar4, arg3 <= uVar7)) {
        if (uVar4 == 0) {
            return arg3;
        }
        iVar2 = uVar7 + arg1;
        cVar3 = *arg2;
        iVar6 = func_0x000140015eb2(arg1 + arg3,cVar3,(iVar2 + 1) - (arg1 + arg3));
        while( true ) {
            if (iVar6 == 0) {
                return -1;
            }
            iVar5 = func_0x000140015eb8(iVar6,arg2,uVar4);
            if (iVar5 == 0) break;
            iVar6 = func_0x000140015eb2(iVar6 + 1,cVar3,(iVar2 + 1) - (iVar6 + 1));
        }
        return iVar6 - arg1;
    }
    return -1;
}
