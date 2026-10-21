/* RVA 0x46300  tam 211 B  addr 0x140046300 */

uchar fcn.1400462e8(int64_t arg1,int64_t arg2)

{
    code *pcVar1;
    uchar uVar2;
    int iVar3;
    int64_t iVar4;
    int64_t iVar5;
    int iVar6;
    int iVar7;
    uchar uVar8;
    int *piVar9;
    
    if (arg2 == 0) {
        fcn.14003f234();
        fcn.14003f210();
        pcVar1 = swi(3);
        uVar2 = (*pcVar1)();
        return uVar2;
    }
    iVar7 = 0;
    uVar8 = 0;
    uVar2 = 0;
    if (0 < *arg2) {
        do {
            iVar4 = fcn.140045890();
            piVar9 = iVar4 + 4 + *(*(arg1 + 0x30) + 0xc);
            iVar4 = fcn.140045890();
            iVar6 = *(iVar4 + *(*(arg1 + 0x30) + 0xc));
            uVar8 = uVar2;
            if (0 < iVar6) {
                do {
                    iVar4 = fcn.140045890();
                    iVar3 = *piVar9;
                    iVar5 = fcn.140045878();
                    iVar3 = fcn.140045f7c(*(arg2 + 4) + iVar5 + iVar7 * 0x14,iVar4 + iVar3,*(arg1 + 0x30));
                    if (iVar3 != 0) {
                        uVar8 = 1;
                        break;
                    }
                    iVar6 = iVar6 + -1;
                    piVar9 = piVar9 + 1;
                } while (0 < iVar6);
            }
            iVar7 = iVar7 + 1;
            uVar2 = uVar8;
        } while (iVar7 < *arg2);
    }
    return uVar8;
}
