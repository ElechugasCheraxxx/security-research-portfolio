/* RVA 0x3170  tam 300 B  addr 0x140003170 */

int64_t fcn.140003170(int64_t arg1,ulong noname_1,ulong noname_2,int64_t arg2)

{
    uint64_t uVar1;
    code *pcVar2;
    int64_t iVar3;
    uint64_t uVar4;
    uint64_t uVar5;
    uint64_t uVar6;
    int64_t in_stack_00000060;
    ulong in_stack_00000068;
    int64_t in_stack_00000070;
    
    uVar6 = 0;
    uVar5 = 7;
    *arg1 = 0;
    *(arg1 + 8) = 0;
    *(arg1 + 0x10) = 0;
    uVar1 = in_stack_00000060 + in_stack_00000070;
    *(arg1 + 0x18) = 0;
    uVar4 = arg1;
    if (uVar1 < 8) goto code_r0x00014000324e;
    uVar5 = uVar1 | 7;
    if (uVar5 < 0x7fffffffffffffff) {
        if (uVar5 < 10) {
            uVar5 = 10;
        }
        if (0x7fffffffffffffff < uVar5 + 1) goto code_r0x000140003296;
        uVar4 = (uVar5 + 1) * 2;
        if (0xfff < uVar4) goto code_r0x00014000320e;
        if (uVar4 != 0) {
            uVar6 = fcn.140014fcc();
        }
    }
    else {
        uVar4 = 0xfffffffffffffffe;
        uVar5 = 0x7ffffffffffffffe;
code_r0x00014000320e:
        if (uVar4 + 0x27 <= uVar4) {
code_r0x000140003296:
            fcn.140009350();
            pcVar2 = swi(3);
            iVar3 = (*pcVar2)();
            return iVar3;
        }
        iVar3 = fcn.140014fcc();
        if (iVar3 == 0) {
            func_0x0001402b05a3();
            pcVar2 = swi(3);
            iVar3 = (*pcVar2)();
            return iVar3;
        }
        uVar6 = iVar3 + 0x27U & 0xffffffffffffffe0;
        *(uVar6 - 8) = iVar3;
    }
    *arg1 = uVar6;
    uVar4 = uVar6;
code_r0x00014000324e:
    *(arg1 + 0x18) = uVar5;
    *(arg1 + 0x10) = uVar1;
    fcn.140015ebe(uVar4,arg2,in_stack_00000060 * 2);
    fcn.140015ebe(in_stack_00000060 * 2 + uVar4,in_stack_00000068,in_stack_00000070 * 2);
    *(uVar4 + uVar1 * 2) = 0;
    return arg1;
}
