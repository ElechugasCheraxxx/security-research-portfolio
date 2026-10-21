/* RVA 0xafce  tam 17 B  addr 0x14000afce */

void fcn.14000afce(int64_t arg1)

{
    int64_t iVar1;
    int64_t iVar2;
    uint64_t uVar3;
    int64_t iVar4;
    int64_t iVar5;
    int64_t iStackX_20;
    
    fcn.1400108f0(&iStackX_20);
    arg1 = *arg1;
    iVar4 = iStackX_20;
    if (0 < arg1) {
        iVar4 = 0x7fffffffffffffff;
        if (iStackX_20 < arg1 * -1000000 + 0x7fffffffffffffff) {
            iVar4 = iStackX_20 + arg1 * 1000000;
        }
    }
    while( true ) {
        iVar1 = fcn.140014fbb();
        iVar2 = fcn.140014fb5();
        if (iVar1 == 10000000) {
            iVar2 = iVar2 * 100;
        }
        else {
            if (iVar1 == 24000000) {
                iVar1 = iVar2 + SUB168(SEXT816(-0x4d0b03f86b6f730d) * SEXT816(iVar2),8);
                iVar5 = (iVar1 >> 0x18) - (iVar1 >> 0x3f);
                iVar1 = (iVar2 + iVar5 * -24000000) * 1000000000;
                iVar1 = iVar1 + SUB168(SEXT816(-0x4d0b03f86b6f730d) * SEXT816(iVar1),8);
                iVar2 = (iVar1 >> 0x18) - (iVar1 >> 0x3f);
            }
            else {
                iVar5 = iVar2 / iVar1;
                iVar2 = ((iVar2 % iVar1) * 1000000000) / iVar1;
            }
            iVar2 = iVar2 + iVar5 * 1000000000;
        }
        if (iVar4 <= iVar2) break;
        iVar2 = iVar4 - iVar2;
        if (iVar2 < 86400000000000) {
            uVar3 = iVar2 / 1000000;
            if (uVar3 * 1000000 < iVar2) {
                uVar3 = uVar3 + 1;
            }
            fcn.140014fc4(uVar3 & 0xffffffff);
        }
        else {
            fcn.140014fc4(86400000);
        }
    }
    return;
}
