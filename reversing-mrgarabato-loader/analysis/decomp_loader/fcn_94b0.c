/* RVA 0x94b0  tam 99 B  addr 0x1400094b0 */

void fcn.1400094b0(int64_t *param_1)

{
    int64_t iVar1;
    int64_t iVar2;
    code *pcVar3;
    uchar uVar4;
    int64_t iVar5;
    
    if (7 < param_1[3]) {
        iVar2 = *param_1;
        iVar1 = param_1[3] * 2;
        iVar5 = iVar2;
        if (0xfff < iVar1 + 2U) {
            iVar5 = *(iVar2 + -8);
            if (0x1f < (iVar2 - iVar5) - 8U) {
                uVar4 = fcn.14058a8ef(iVar2 - iVar5,iVar1 + 0x29);
                out(0xcc,uVar4);
                pcVar3 = swi(3);
                (*pcVar3)();
                return;
            }
        }
        fcn.14001a940(iVar5);
    }
    param_1[3] = 7;
    param_1[2] = 0;
    *param_1 = 0;
    return;
}
