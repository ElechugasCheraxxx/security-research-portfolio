/* RVA 0xaf60  tam 449 B  addr 0x14000af60 */

uint64_t fcn.14000af60(int64_t arg1)

{
    ushort uVar1;
    int64_t iVar2;
    int64_t iVar3;
    uint64_t uVar4;
    int64_t iVar5;
    int64_t *unaff_RDI;
    int64_t iVar6;
    uchar uVar7;
    int64_t iStackX_8;
    
    uVar7 = CARRY8(*(*arg1 + 4),arg1);
    uVar1 = fcn.14028483d(*(*arg1 + 4) + arg1,10);
    fcn.1406b8299(arg1,uVar1);
    fcn.14023db1b(arg1);
    if (!uVar7) {
        fcn.1400108f0();
        iVar3 = *unaff_RDI;
        iVar5 = iStackX_8;
        if (0 < iVar3) {
            iVar5 = 0x7fffffffffffffff;
            if (iStackX_8 < iVar3 * -1000000 + 0x7fffffffffffffff) {
                iVar5 = iStackX_8 + iVar3 * 1000000;
            }
        }
        while( true ) {
            iVar2 = fcn.140014fbb();
            iVar3 = fcn.140014fb5();
            if (iVar2 == 10000000) {
                uVar4 = iVar3 * 100;
            }
            else {
                if (iVar2 == 24000000) {
                    iVar2 = iVar3 + SUB168(SEXT816(-0x4d0b03f86b6f730d) * SEXT816(iVar3),8);
                    iVar6 = (iVar2 >> 0x18) - (iVar2 >> 0x3f);
                    iVar3 = (iVar3 + iVar6 * -24000000) * 1000000000;
                    iVar3 = iVar3 + SUB168(SEXT816(-0x4d0b03f86b6f730d) * SEXT816(iVar3),8);
                    iVar2 = (iVar3 >> 0x18) - (iVar3 >> 0x3f);
                }
                else {
                    iVar6 = iVar3 / iVar2;
                    iVar2 = ((iVar3 % iVar2) * 1000000000) / iVar2;
                }
                uVar4 = iVar2 + iVar6 * 1000000000;
            }
            if (iVar5 <= uVar4) break;
            iVar3 = iVar5 - uVar4;
            if (iVar3 < 86400000000000) {
                uVar4 = iVar3 / 1000000;
                if (uVar4 * 1000000 < iVar3) {
                    uVar4 = uVar4 + 1;
                }
                fcn.140014fc4(uVar4 & 0xffffffff);
            }
            else {
                fcn.140014fc4(86400000);
            }
        }
        return uVar4;
    }
    return arg1 & 0xffffffff;
}
