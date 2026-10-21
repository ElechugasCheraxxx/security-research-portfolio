/* RVA 0xac71  tam 391 B  addr 0x14000ac71 */

uchar * fcn.14000ac71(int64_t arg1,int64_t arg2,int64_t arg3)

{
    uint64_t uVar1;
    int64_t iVar2;
    code *pcVar3;
    int64_t iVar4;
    int64_t iVar5;
    uint64_t uVar6;
    uchar *puVar7;
    uchar *puVar8;
    ulong in_R9;
    uchar *puVar9;
    uint64_t uVar10;
    uint64_t uVar11;
    uchar *puVar12;
    
    iVar2 = *arg1;
    iVar4 = *(arg1 + 8) - iVar2;
    if (iVar4 == 0x7fffffffffffffff) {
        func_0x00014000cf10();
        pcVar3 = swi(3);
        puVar8 = (*pcVar3)();
        return puVar8;
    }
    uVar1 = iVar4 + 1;
    uVar6 = *(arg1 + 0x10) - iVar2;
    iVar4 = arg1;
    if (0x7fffffffffffffff - (uVar6 >> 1) < uVar6) {
        uVar10 = 0x7fffffffffffffff;
        uVar6 = 0x8000000000000026;
code_r0x00014000acd3:
        uVar11 = uVar10;
        iVar5 = fcn.14001a904(uVar6);
        if (iVar5 == 0) goto code_r0x00014000ade5;
        puVar8 = iVar5 + 0x27U & 0xffffffffffffffe0;
        *(puVar8 + -8) = iVar5;
    }
    else {
        uVar6 = (uVar6 >> 1) + uVar6;
        uVar10 = uVar1;
        if (uVar1 <= uVar6) {
            uVar10 = uVar6;
        }
        if (0xfff < uVar10) {
            uVar6 = uVar10 + 0x27;
            if (uVar6 <= uVar10) {
                fcn.140009490();
                pcVar3 = swi(3);
                puVar8 = (*pcVar3)();
                return puVar8;
            }
            goto code_r0x00014000acd3;
        }
        uVar11 = uVar10;
        if (uVar10 == 0) {
            puVar8 = NULL;
        }
        else {
            puVar8 = fcn.14001a904(uVar10);
        }
    }
    puVar9 = puVar8 + (arg2 - iVar2);
    *puVar9 = *arg3;
    iVar2 = *arg1;
    puVar12 = puVar8;
    if (arg2 == *(arg1 + 8)) {
        iVar5 = *(arg1 + 8) - iVar2;
        puVar7 = puVar8;
        arg2 = iVar2;
    }
    else {
        func_0x00014001b7fe(puVar8,iVar2,arg2 - iVar2,in_R9,uVar11,puVar8,iVar4);
        puVar7 = puVar9 + 1;
        iVar5 = *(arg1 + 8) - arg2;
    }
    func_0x00014001b7fe(puVar7,arg2,iVar5,in_R9,uVar11,puVar12,iVar4);
    iVar2 = *arg1;
    if (iVar2 != 0) {
        uVar6 = *(arg1 + 0x10) - iVar2;
        iVar4 = iVar2;
        if (0xfff < uVar6) {
            uVar6 = uVar6 + 0x27;
            iVar4 = *(iVar2 + -8);
            if (0x1f < (iVar2 - iVar4) - 8U) {
code_r0x00014000ade5:
                func_0x0001404f4a38();
                pcVar3 = swi(3);
                puVar8 = (*pcVar3)();
                return puVar8;
            }
        }
        fcn.14001a940(iVar4,uVar6);
    }
    *arg1 = puVar8;
    *(arg1 + 8) = puVar8 + uVar1;
    *(arg1 + 0x10) = puVar8 + uVar10;
    return puVar9;
}
