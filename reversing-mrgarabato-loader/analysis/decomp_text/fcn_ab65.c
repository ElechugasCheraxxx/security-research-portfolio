/* RVA 0xab65  tam 381 B  addr 0x14000ab65 */

int64_t fcn.14000ab65(int64_t arg1,int64_t arg2,int64_t arg3)

{
    uint64_t uVar1;
    code *pcVar2;
    int64_t iVar3;
    int64_t iVar4;
    uint64_t uVar5;
    uint64_t uVar6;
    uint64_t uVar7;
    int64_t iStackX_18;
    uint64_t uVar8;
    uint64_t uVar9;
    
    iVar4 = *arg1;
    iVar3 = *(arg1 + 8) - iVar4 >> 5;
    if (iVar3 == 0x7ffffffffffffff) {
        func_0x00014000d2b0();
        pcVar2 = swi(3);
        iVar4 = (*pcVar2)();
        return iVar4;
    }
    uVar1 = iVar3 + 1;
    uVar5 = *(arg1 + 0x10) - iVar4 >> 5;
    if (uVar5 <= 0x7ffffffffffffff - (uVar5 >> 1)) {
        uVar5 = (uVar5 >> 1) + uVar5;
        uVar6 = uVar1;
        if (uVar1 <= uVar5) {
            uVar6 = uVar5;
        }
        if (uVar6 < 0x800000000000000) {
            uVar5 = uVar6 * 0x20;
            if (uVar5 < 0x1000) {
                if (uVar5 == 0) {
                    uVar5 = 0;
                    iStackX_18 = arg3;
                }
                else {
                    uVar5 = fcn.140014fcc();
                }
            }
            else {
                if (uVar5 + 0x27 <= uVar5) goto code_r0x00014000acd6;
                iVar3 = fcn.140014fcc(uVar5 + 0x27);
                if (iVar3 == 0) {
                    func_0x0001402337b5();
                    pcVar2 = swi(3);
                    iVar4 = (*pcVar2)();
                    return iVar4;
                }
                uVar5 = iVar3 + 0x27U & 0xffffffffffffffe0;
                *(uVar5 - 8) = iVar3;
            }
            iVar3 = (arg2 - iVar4 & 0xffffffffffffffe0U) + uVar5;
            uVar7 = iVar3 + 0x20;
            uVar8 = uVar5;
            uVar9 = uVar7;
            fcn.140002ed0(iVar3,iStackX_18);
            iVar4 = *(arg1 + 8);
            if (arg2 == iVar4) {
                arg2 = *arg1;
                uVar7 = uVar5;
            }
            else {
                func_0x00014000aea0(*arg1,arg2,uVar5,arg1,uVar8,uVar9);
                iVar4 = *(arg1 + 8);
            }
            func_0x00014000aea0(arg2,iVar4,uVar7,arg1,uVar8,uVar9);
            func_0x00014000d1d0(arg1,uVar5,uVar1,uVar6);
            return iVar3;
        }
    }
code_r0x00014000acd6:
    fcn.140009350();
    pcVar2 = swi(3);
    iVar4 = (*pcVar2)();
    return iVar4;
}
