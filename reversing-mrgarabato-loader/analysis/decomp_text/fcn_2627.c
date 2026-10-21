/* RVA 0x2627  tam 452 B  addr 0x140002627 */

int64_t fcn.140002627(int64_t arg1,int64_t arg2,ulong noname_2,int64_t arg3)

{
    uint64_t uVar1;
    ushort *puVar2;
    uint64_t uVar3;
    code *pcVar4;
    int64_t iVar5;
    int64_t iVar6;
    uint64_t uVar7;
    uint64_t uVar8;
    uint64_t uVar9;
    int64_t in_stack_00000048;
    
    iVar6 = *(arg1 + 0x10);
    uVar9 = 0x7ffffffffffffffe;
    if (0x7ffffffffffffffeU - iVar6 < arg2) {
        func_0x0001400093e0();
        pcVar4 = swi(3);
        iVar6 = (*pcVar4)();
        return iVar6;
    }
    uVar8 = 0;
    uVar3 = *(arg1 + 0x18);
    uVar7 = arg2 + iVar6 | 7;
    if (uVar7 < 0x7fffffffffffffff) {
        if (0x7ffffffffffffffe - (uVar3 >> 1) < uVar3) {
            uVar7 = 0xfffffffffffffffe;
            goto code_r0x0001400026db;
        }
        uVar1 = (uVar3 >> 1) + uVar3;
        uVar9 = uVar7;
        if (uVar7 < uVar1) {
            uVar9 = uVar1;
        }
        if (0x7fffffffffffffff < uVar9 + 1) goto code_r0x0001400027e5;
        uVar7 = (uVar9 + 1) * 2;
        if (0xfff < uVar7) goto code_r0x0001400026db;
        if (uVar7 != 0) {
            uVar8 = func_0x000140014fcc();
        }
    }
    else {
        uVar7 = 0xfffffffffffffffe;
code_r0x0001400026db:
        if (uVar7 + 0x27 <= uVar7) {
code_r0x0001400027e5:
            func_0x000140009350();
            pcVar4 = swi(3);
            iVar6 = (*pcVar4)();
            return iVar6;
        }
        iVar5 = func_0x000140014fcc(uVar7 + 0x27);
        if (iVar5 == 0) goto code_r0x000140002797;
        uVar8 = iVar5 + 0x27U & 0xffffffffffffffe0;
        *(uVar8 - 8) = iVar5;
    }
    *(arg1 + 0x10) = arg2 + iVar6;
    iVar5 = iVar6 * 2 + uVar8;
    *(arg1 + 0x18) = uVar9;
    puVar2 = uVar8 + (in_stack_00000048 + iVar6) * 2;
    if (uVar3 < 8) {
        func_0x000140015ebe(uVar8,arg1);
        func_0x000140015ebe(iVar5,arg3,in_stack_00000048 * 2);
        *puVar2 = 0;
    }
    else {
        iVar6 = *arg1;
        func_0x000140015ebe(uVar8,iVar6);
        func_0x000140015ebe(iVar5,arg3,in_stack_00000048 * 2);
        uVar9 = uVar3 * 2 + 2;
        *puVar2 = 0;
        iVar5 = iVar6;
        if (0xfff < uVar9) {
            iVar5 = *(iVar6 + -8);
            uVar9 = uVar3 * 2 + 0x29;
            if (0x1f < (iVar6 - iVar5) - 8U) {
code_r0x000140002797:
                func_0x0001402cfd28();
                pcVar4 = swi(3);
                iVar6 = (*pcVar4)();
                return iVar6;
            }
        }
        func_0x000140015008(iVar5,uVar9);
    }
    *arg1 = uVar8;
    return arg1;
}
