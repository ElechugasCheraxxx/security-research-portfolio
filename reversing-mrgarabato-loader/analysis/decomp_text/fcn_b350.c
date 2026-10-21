/* RVA 0xb350  tam 271 B  addr 0x14000b350 */

int64_t fcn.14000b350(int64_t arg1,ulong noname_1,ulong noname_2,int64_t arg2)

{
    uint64_t uVar1;
    code *pcVar2;
    uint64_t uVar3;
    int64_t iVar4;
    uint64_t uVar5;
    uint64_t uVar6;
    int64_t in_stack_00000060;
    ulong in_stack_00000068;
    int64_t in_stack_00000070;
    
    uVar5 = 0;
    uVar6 = 0xf;
    *arg1 = 0;
    *(arg1 + 8) = 0;
    *(arg1 + 0x10) = 0;
    uVar1 = in_stack_00000060 + in_stack_00000070;
    *(arg1 + 0x18) = 0;
    uVar3 = arg1;
    if (uVar1 < 0x10) goto code_r0x00014000b418;
    uVar6 = uVar1 | 0xf;
    if (uVar6 < 0x8000000000000000) {
        if (uVar6 < 0x16) {
            uVar6 = 0x16;
        }
        if (0xfff < uVar6 + 1) {
            uVar3 = uVar6 + 0x28;
            if (uVar3 <= uVar6 + 1) {
                fcn.140009350();
                pcVar2 = swi(3);
                iVar4 = (*pcVar2)();
                return iVar4;
            }
            goto code_r0x00014000b3ba;
        }
        if (uVar6 != 0xffffffffffffffff) {
            uVar5 = fcn.140014fcc();
        }
    }
    else {
        uVar3 = 0x8000000000000027;
        uVar6 = 0x7fffffffffffffff;
code_r0x00014000b3ba:
        iVar4 = fcn.140014fcc(uVar3);
        if (iVar4 == 0) {
            func_0x000140292104();
            pcVar2 = swi(3);
            iVar4 = (*pcVar2)();
            return iVar4;
        }
        uVar5 = iVar4 + 0x27U & 0xffffffffffffffe0;
        *(uVar5 - 8) = iVar4;
    }
    *arg1 = uVar5;
    uVar3 = uVar5;
code_r0x00014000b418:
    *(arg1 + 0x10) = uVar1;
    *(arg1 + 0x18) = uVar6;
    fcn.140015ebe(uVar3,arg2,in_stack_00000060);
    fcn.140015ebe(in_stack_00000060 + uVar3,in_stack_00000068,in_stack_00000070);
    *(uVar3 + uVar1) = 0;
    return arg1;
}
