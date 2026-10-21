/* RVA 0x2490  tam 398 B  addr 0x140002490 */

int64_t fcn.140002490(int64_t arg1,int64_t arg2,ulong noname_2,int64_t arg3)

{
    uint64_t uVar1;
    uint64_t uVar2;
    int64_t iVar3;
    code *pcVar4;
    int64_t iVar5;
    int64_t iVar6;
    uint64_t uVar7;
    uint64_t uVar8;
    int64_t in_stack_00000028;
    
    iVar6 = *(arg1 + 0x10);
    uVar8 = 0x7fffffffffffffff;
    if (0x7fffffffffffffffU - iVar6 < arg2) {
        func_0x0001400093e0();
        pcVar4 = swi(3);
        iVar6 = (*pcVar4)();
        return iVar6;
    }
    uVar7 = arg2 + iVar6 | 0xf;
    uVar2 = *(arg1 + 0x18);
    if ((uVar7 < 0x8000000000000000) && (uVar2 <= 0x7fffffffffffffff - (uVar2 >> 1))) {
        uVar1 = (uVar2 >> 1) + uVar2;
        uVar8 = uVar7;
        if (uVar7 < uVar1) {
            uVar8 = uVar1;
        }
        uVar1 = uVar8 + 1;
        if (0xfff < uVar1) {
            uVar7 = uVar8 + 0x28;
            if (uVar7 <= uVar1) {
                func_0x000140009350();
                pcVar4 = swi(3);
                iVar6 = (*pcVar4)();
                return iVar6;
            }
            goto code_r0x00014000252e;
        }
        if (uVar1 == 0) {
            uVar7 = 0;
        }
        else {
            uVar7 = func_0x000140014fcc(uVar1);
        }
    }
    else {
        uVar7 = 0x8000000000000027;
code_r0x00014000252e:
        iVar5 = func_0x000140014fcc(uVar7);
        if (iVar5 == 0) goto code_r0x0001400025cb;
        uVar7 = iVar5 + 0x27U & 0xffffffffffffffe0;
        *(uVar7 - 8) = iVar5;
    }
    *(arg1 + 0x10) = arg2 + iVar6;
    iVar5 = uVar7 + iVar6;
    *(arg1 + 0x18) = uVar8;
    if (uVar2 < 0x10) {
        func_0x000140015ebe(uVar7,arg1,iVar6);
        func_0x000140015ebe(iVar5,arg3,in_stack_00000028);
        *(iVar5 + in_stack_00000028) = 0;
    }
    else {
        iVar3 = *arg1;
        func_0x000140015ebe(uVar7,iVar3,iVar6);
        func_0x000140015ebe(iVar5,arg3,in_stack_00000028);
        uVar8 = uVar2 + 1;
        *(iVar5 + in_stack_00000028) = 0;
        iVar6 = iVar3;
        if (0xfff < uVar8) {
            iVar6 = *(iVar3 + -8);
            uVar8 = uVar2 + 0x28;
            if (0x1f < (iVar3 - iVar6) - 8U) {
code_r0x0001400025cb:
                func_0x0001401628a5();
                pcVar4 = swi(3);
                iVar6 = (*pcVar4)();
                return iVar6;
            }
        }
        func_0x000140015008(iVar6,uVar8);
    }
    *arg1 = uVar7;
    return arg1;
}
