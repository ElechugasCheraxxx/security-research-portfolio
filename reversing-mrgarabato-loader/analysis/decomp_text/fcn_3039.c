/* RVA 0x3039  tam 290 B  addr 0x140003039 */

int64_t fcn.140003039(int64_t arg1,int64_t arg2)

{
    uint64_t uVar1;
    code *pcVar2;
    ulong uVar3;
    int64_t iVar4;
    uint64_t uVar5;
    uint64_t uVar6;
    uint64_t uVar7;
    
    uVar5 = 0;
    *arg1 = 0;
    *(arg1 + 8) = 0;
    *(arg1 + 0x10) = 0;
    *(arg1 + 0x18) = 0;
    uVar1 = *(arg2 + 0x10);
    if (7 < *(arg2 + 0x18)) {
        arg2 = *arg2;
    }
    if (0x7ffffffffffffffe < uVar1) {
        fcn.1400093e0();
        pcVar2 = swi(3);
        iVar4 = (*pcVar2)();
        return iVar4;
    }
    if (uVar1 < 8) {
        *(arg1 + 0x10) = uVar1;
        *(arg1 + 0x18) = 7;
        uVar3 = *(arg2 + 8);
        *arg1 = *arg2;
        *(arg1 + 8) = uVar3;
        return arg1;
    }
    uVar6 = uVar1 | 7;
    if (uVar6 < 0x7fffffffffffffff) {
        if (uVar6 < 10) {
            uVar6 = 10;
        }
        if (0x7fffffffffffffff < uVar6 + 1) goto code_r0x000140003155;
        uVar7 = (uVar6 + 1) * 2;
        if (uVar7 < 0x1000) {
            if (uVar7 != 0) {
                uVar5 = fcn.140014fcc();
            }
            goto code_r0x000140003120;
        }
    }
    else {
        uVar7 = 0xfffffffffffffffe;
        uVar6 = 0x7ffffffffffffffe;
    }
    if (uVar7 < uVar7 + 0x27) {
        iVar4 = fcn.140014fcc(uVar7 + 0x27);
        if (iVar4 == 0) {
            func_0x0001402987fa();
            pcVar2 = swi(3);
            iVar4 = (*pcVar2)();
            return iVar4;
        }
        uVar5 = iVar4 + 0x27U & 0xffffffffffffffe0;
        *(uVar5 - 8) = iVar4;
code_r0x000140003120:
        *arg1 = uVar5;
        *(arg1 + 0x10) = uVar1;
        *(arg1 + 0x18) = uVar6;
        fcn.140015ebe(uVar5,arg2,uVar1 * 2 + 2);
        return arg1;
    }
code_r0x000140003155:
    fcn.140009350();
    pcVar2 = swi(3);
    iVar4 = (*pcVar2)();
    return iVar4;
}
