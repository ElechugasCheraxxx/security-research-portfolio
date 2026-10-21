/* RVA 0x29b6  tam 522 B  addr 0x1400029b6 */

int64_t fcn.1400029b0(int64_t arg1,int64_t arg2,ulong noname_2,int64_t arg3)

{
    uint64_t uVar1;
    uint64_t uVar2;
    int64_t iVar3;
    code *pcVar4;
    int64_t iVar5;
    int64_t iVar6;
    int64_t iVar7;
    uint64_t uVar8;
    uint64_t uVar9;
    ulong in_stack_00000028;
    int64_t in_stack_00000030;
    
    uVar9 = 0x7ffffffffffffffe;
    iVar7 = *(arg1 + 0x10);
    if (0x7ffffffffffffffeU - iVar7 < arg2) {
        func_0x0001400093e0();
        pcVar4 = swi(3);
        iVar7 = (*pcVar4)();
        return iVar7;
    }
    uVar2 = *(arg1 + 0x18);
    uVar8 = arg2 + iVar7 | 7;
    if (uVar8 < 0x7fffffffffffffff) {
        if (0x7ffffffffffffffe - (uVar2 >> 1) < uVar2) {
            uVar8 = 0xfffffffffffffffe;
            goto code_r0x000140002a76;
        }
        uVar1 = (uVar2 >> 1) + uVar2;
        uVar9 = uVar8;
        if (uVar8 < uVar1) {
            uVar9 = uVar1;
        }
        if (0x7fffffffffffffff < uVar9 + 1) goto code_r0x000140002bb4;
        uVar8 = (uVar9 + 1) * 2;
        if (0xfff < uVar8) goto code_r0x000140002a76;
        if (uVar8 == 0) {
            uVar8 = 0;
        }
        else {
            uVar8 = func_0x000140014fcc();
        }
    }
    else {
        uVar8 = 0xfffffffffffffffe;
code_r0x000140002a76:
        if (uVar8 + 0x27 <= uVar8) {
code_r0x000140002bb4:
            func_0x000140009350();
            pcVar4 = swi(3);
            iVar7 = (*pcVar4)();
            return iVar7;
        }
        iVar6 = func_0x000140014fcc(uVar8 + 0x27);
        if (iVar6 == 0) goto code_r0x000140002b56;
        uVar8 = iVar6 + 0x27U & 0xffffffffffffffe0;
        *(uVar8 - 8) = iVar6;
    }
    *(arg1 + 0x10) = arg2 + iVar7;
    *(arg1 + 0x18) = uVar9;
    iVar5 = arg3 * 2;
    iVar6 = (iVar7 - arg3) * 2 + 2;
    iVar7 = uVar8 + (in_stack_00000030 + arg3) * 2;
    if (uVar2 < 8) {
        func_0x000140015ebe(uVar8,arg1,iVar5);
        func_0x000140015ebe(iVar5 + uVar8,in_stack_00000028,in_stack_00000030 * 2);
        func_0x000140015ebe(iVar7,iVar5 + arg1,iVar6);
    }
    else {
        iVar3 = *arg1;
        func_0x000140015ebe(uVar8,iVar3,iVar5);
        func_0x000140015ebe(iVar5 + uVar8,in_stack_00000028,in_stack_00000030 * 2);
        func_0x000140015ebe(iVar7,iVar5 + iVar3,iVar6);
        iVar7 = iVar3;
        if ((0xfff < uVar2 * 2 + 2) && (iVar7 = *(iVar3 + -8), 0x1f < (iVar3 - iVar7) - 8U)) {
code_r0x000140002b56:
            func_0x000140176262();
            pcVar4 = swi(3);
            iVar7 = (*pcVar4)();
            return iVar7;
        }
        func_0x000140015008(iVar7);
    }
    *arg1 = uVar8;
    return arg1;
}
