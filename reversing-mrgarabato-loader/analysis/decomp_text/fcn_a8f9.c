/* RVA 0xa8f9  tam 379 B  addr 0x14000a8f9 */

//WARNING: Instruction at (ram,0x00014000a9f8) overlaps instruction at (ram,0x00014000a9f6)
//

int64_t fcn.14000a8f0(int64_t arg1,int64_t arg2,int64_t arg3)

{
    uint64_t uVar1;
    code *pcVar2;
    int64_t iVar3;
    int64_t iVar4;
    uint64_t uVar5;
    uint64_t uVar6;
    uint64_t uVar7;
    uint64_t uVar8;
    
    uVar8 = 0;
    uVar6 = 0xffffffffffffffff;
    do {
        uVar6 = uVar6 + 1;
    } while (*(arg2 + uVar6 * 2) != 0);
    iVar4 = *(arg3 + 0x10);
    if (0x7ffffffffffffffeU - iVar4 < uVar6) {
        fcn.1400093e0();
        pcVar2 = swi(3);
        iVar4 = (*pcVar2)();
        return iVar4;
    }
    if (7 < *(arg3 + 0x18)) {
        arg3 = *arg3;
    }
    uVar1 = iVar4 + uVar6;
    *arg1 = 0;
    *(arg1 + 8) = 0;
    uVar7 = 7;
    *(arg1 + 0x10) = 0;
    *(arg1 + 0x18) = 0;
    uVar5 = arg1;
    if (uVar1 < 8) goto code_r0x00014000aa0d;
    uVar7 = uVar1 | 7;
    if (uVar7 < 0x7fffffffffffffff) {
        if (uVar7 < 10) {
            uVar7 = 10;
        }
        if (0x7fffffffffffffff < uVar7 + 1) goto code_r0x00014000aa65;
        uVar5 = (uVar7 + 1) * 2;
        if (0xfff < uVar5) goto code_r0x00014000a9c9;
        if (uVar5 != 0) {
            uVar8 = fcn.140014fcc();
        }
    }
    else {
        uVar7 = 0x7ffffffffffffffe;
        uVar5 = 0xfffffffffffffffe;
code_r0x00014000a9c9:
        if (uVar5 + 0x27 <= uVar5) {
code_r0x00014000aa65:
            fcn.140009350();
            pcVar2 = swi(3);
            iVar4 = (*pcVar2)();
            return iVar4;
        }
        iVar3 = fcn.140014fcc(uVar5 + 0x27);
        if (iVar3 == 0) {
            iVar4 = func_0x000140233f5a();
            return iVar4;
        }
        uVar8 = iVar3 + 0x27U & 0xffffffffffffffe0;
        *(uVar8 - 8) = iVar3;
    }
    *arg1 = uVar8;
    uVar5 = uVar8;
code_r0x00014000aa0d:
    *(arg1 + 0x10) = uVar1;
    *(arg1 + 0x18) = uVar7;
    fcn.140015ebe(uVar5,arg2,uVar6 * 2);
    fcn.140015ebe(uVar6 * 2 + uVar5,arg3,iVar4 * 2);
    *(uVar5 + uVar1 * 2) = 0;
    return arg1;
}
