/* RVA 0x9536  tam 29621 B  addr 0x140009536 */

//WARNING: Control flow encountered bad instruction data

int64_t fcn.140009536(int64_t arg1,int64_t arg2,int64_t arg3)

{
    uint64_t uVar1;
    uint64_t uVar2;
    code *pcVar3;
    int64_t iVar4;
    int64_t iVar5;
    uint64_t uVar6;
    uint64_t uVar7;
    
    if (arg3 <= *(arg1 + 0x18)) {
        iVar4 = arg1;
        if (0xf < *(arg1 + 0x18)) {
            iVar4 = *arg1;
        }
        *(arg1 + 0x10) = arg3;
        fcn.140015ec4(iVar4);
        *(iVar4 + arg3) = 0;
        return arg1;
    }
    uVar7 = 0x7fffffffffffffff;
    if (0x7fffffffffffffff < arg3) {
        fcn.1400093e0(arg1,arg3,0);
        pcVar3 = swi(3);
        iVar4 = (*pcVar3)();
        return iVar4;
    }
    uVar6 = arg3 | 0xf;
    uVar2 = *(arg1 + 0x18);
    if ((uVar6 < 0x8000000000000000) && (uVar2 <= 0x7fffffffffffffff - (uVar2 >> 1))) {
        uVar1 = (uVar2 >> 1) + uVar2;
        uVar7 = uVar6;
        if (uVar6 < uVar1) {
            uVar7 = uVar1;
        }
        uVar1 = uVar7 + 1;
        if (0xfff < uVar1) {
            uVar6 = uVar7 + 0x28;
            if (uVar6 <= uVar1) {
                fcn.140009350();
                pcVar3 = swi(3);
                iVar4 = (*pcVar3)();
                return iVar4;
            }
            goto code_r0x000140002266;
        }
        if (uVar1 == 0) {
            uVar6 = 0;
        }
        else {
            uVar6 = fcn.140014fcc(uVar1);
        }
    }
    else {
        uVar6 = 0x8000000000000027;
code_r0x000140002266:
        iVar4 = fcn.140014fcc(uVar6);
        if (iVar4 == 0) goto code_r0x0001400022ff;
        uVar6 = iVar4 + 0x27U & 0xffffffffffffffe0;
        *(uVar6 - 8) = iVar4;
    }
    *(arg1 + 0x10) = arg3;
    *(arg1 + 0x18) = uVar7;
    fcn.140015ebe(uVar6,arg2,arg3);
    *(uVar6 + arg3) = 0;
    if (0xf < uVar2) {
        iVar4 = *arg1;
        uVar7 = uVar2 + 1;
        iVar5 = iVar4;
        if (0xfff < uVar7) {
            iVar5 = *(iVar4 + -8);
            uVar7 = uVar2 + 0x28;
            if (0x1f < (iVar4 - iVar5) - 8U) {
code_r0x0001400022ff:
                fcn.140191606();
    //WARNING: Bad instruction - Truncating control flow here
                halt_baddata();
            }
        }
        fcn.140015008(iVar5,uVar7);
    }
    *arg1 = uVar6;
    return arg1;
}
