/* RVA 0x2ed9  tam 268 B  addr 0x140002ed9 */

//WARNING: Control flow encountered bad instruction data
//WARNING: Instruction at (ram,0x000140002fa4) overlaps instruction at (ram,0x000140002fa2)
//

int64_t fcn.140002ed9(int64_t arg1,int64_t arg2)

{
    uint64_t uVar1;
    code *pcVar2;
    ulong uVar3;
    uint64_t uVar4;
    int64_t iVar5;
    uint64_t uVar6;
    
    uVar4 = 0;
    *arg1 = 0;
    *(arg1 + 8) = 0;
    *(arg1 + 0x10) = 0;
    *(arg1 + 0x18) = 0;
    uVar1 = *(arg2 + 0x10);
    if (0xf < *(arg2 + 0x18)) {
        arg2 = *arg2;
    }
    if (0x7fffffffffffffff < uVar1) {
        func_0x0001400093e0();
        pcVar2 = swi(3);
        iVar5 = (*pcVar2)();
        return iVar5;
    }
    if (uVar1 < 0x10) {
        *(arg1 + 0x10) = uVar1;
        *(arg1 + 0x18) = 0xf;
        uVar3 = *(arg2 + 8);
        *arg1 = *arg2;
        *(arg1 + 8) = uVar3;
        return arg1;
    }
    uVar6 = uVar1 | 0xf;
    if (uVar6 < 0x8000000000000000) {
        if (uVar6 < 0x16) {
            uVar6 = 0x16;
        }
        if (uVar6 + 1 < 0x1000) {
            if (uVar6 != 0xffffffffffffffff) {
                uVar4 = func_0x000140014fcc();
            }
            goto code_r0x000140002fae;
        }
        uVar4 = uVar6 + 0x28;
        if (uVar4 <= uVar6 + 1) {
            func_0x000140009350();
            pcVar2 = swi(3);
            iVar5 = (*pcVar2)();
            return iVar5;
        }
    }
    else {
        uVar4 = 0x8000000000000027;
        uVar6 = 0x7fffffffffffffff;
    }
    iVar5 = func_0x000140014fcc(uVar4);
    if (iVar5 == 0) {
        func_0x0001406bae2f();
    //WARNING: Bad instruction - Truncating control flow here
        halt_baddata();
    }
    uVar4 = iVar5 + 0x27U & 0xffffffffffffffe0;
    *(uVar4 - 8) = iVar5;
code_r0x000140002fae:
    *arg1 = uVar4;
    *(arg1 + 0x10) = uVar1;
    *(arg1 + 0x18) = uVar6;
    func_0x000140015ebe(uVar4,arg2,uVar1 + 1);
    return arg1;
}
