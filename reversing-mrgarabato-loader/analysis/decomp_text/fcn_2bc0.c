/* RVA 0x2bc0  tam 351 B  addr 0x140002bc0 */

//WARNING: Control flow encountered bad instruction data

int64_t fcn.140002bc0(int64_t arg1,int64_t arg2,ulong noname_2,int64_t arg3)

{
    uint64_t uVar1;
    uint64_t uVar2;
    code *pcVar3;
    int64_t iVar4;
    int64_t iVar5;
    uint64_t uVar6;
    uint64_t uVar7;
    
    iVar5 = *(arg1 + 0x10);
    uVar7 = 0x7fffffffffffffff;
    if (0x7fffffffffffffffU - iVar5 < arg2) {
        func_0x0001400093e0();
        pcVar3 = swi(3);
        iVar5 = (*pcVar3)();
        return iVar5;
    }
    uVar2 = *(arg1 + 0x18);
    uVar6 = arg2 + iVar5 | 0xf;
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
                func_0x000140009350();
                pcVar3 = swi(3);
                iVar5 = (*pcVar3)();
                return iVar5;
            }
            goto code_r0x000140002c59;
        }
        if (uVar1 == 0) {
            uVar6 = 0;
        }
        else {
            uVar6 = func_0x000140014fcc(uVar1);
        }
    }
    else {
        uVar6 = 0x8000000000000027;
code_r0x000140002c59:
        iVar4 = func_0x000140014fcc(uVar6);
        if (iVar4 == 0) goto code_r0x000140002cdc;
        uVar6 = iVar4 + 0x27U & 0xffffffffffffffe0;
        *(uVar6 - 8) = iVar4;
    }
    *(arg1 + 0x10) = arg2 + iVar5;
    *(arg1 + 0x18) = uVar7;
    if (uVar2 < 0x10) {
        func_0x000140015ebe(uVar6,arg1,iVar5);
        *(uVar6 + iVar5) = arg3;
        *(uVar6 + 1 + iVar5) = 0;
    }
    else {
        iVar4 = *arg1;
        func_0x000140015ebe(uVar6,iVar4,iVar5);
        uVar7 = uVar2 + 1;
        *(uVar6 + iVar5) = arg3;
        *(uVar6 + 1 + iVar5) = 0;
        iVar5 = iVar4;
        if (0xfff < uVar7) {
            iVar5 = *(iVar4 + -8);
            uVar7 = uVar2 + 0x28;
            if (0x1f < (iVar4 - iVar5) - 8U) {
code_r0x000140002cdc:
                func_0x00014023554e();
    //WARNING: Bad instruction - Truncating control flow here
                halt_baddata();
            }
        }
        func_0x000140015008(iVar5,uVar7);
    }
    *arg1 = uVar6;
    return arg1;
}
