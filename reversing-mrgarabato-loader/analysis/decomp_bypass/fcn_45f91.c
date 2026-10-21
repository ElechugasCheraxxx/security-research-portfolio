/* RVA 0x45f91  tam 270 B  addr 0x140045f91 */

int64_t fcn.140045f91(int64_t arg1,int64_t arg2,int64_t arg3)

{
    int iVar1;
    int64_t iVar2;
    int64_t iVar3;
    int64_t iVar4;
    
    iVar1 = *(arg1 + 4);
    iVar4 = 0;
    if (iVar1 == 0) {
        iVar2 = iVar4;
    }
    else {
        iVar2 = fcn.140045878();
        iVar2 = iVar1 + iVar2;
    }
    if (iVar2 != 0) {
        if (iVar1 == 0) {
            iVar1 = 0;
            iVar2 = iVar4;
        }
        else {
            iVar1 = *(arg1 + 4);
            iVar2 = fcn.140045878();
            iVar2 = iVar1 + iVar2;
        }
        if (*(iVar2 + 0x10) != '\0') {
            if (iVar1 == 0) {
                iVar2 = iVar4;
            }
            else {
                iVar2 = fcn.140045878();
                iVar2 = iVar2 + *(arg1 + 4);
            }
            iVar3 = fcn.140045890();
            if (iVar2 != iVar3 + *(arg2 + 4)) {
                if (*(arg1 + 4) == 0) {
                    iVar2 = iVar4;
                }
                else {
                    iVar2 = fcn.140045878();
                    iVar2 = iVar2 + *(arg1 + 4);
                }
                iVar3 = fcn.140045890();
                iVar1 = fcn.1400409a0(iVar2 + 0x10,iVar3 + 0x10 + *(arg2 + 4));
                if (iVar1 != 0) {
                    return 0;
                }
            }
            if ((((((*arg2 & 2) == 0) || ((*arg1 & 8) != 0)) && (((*arg3 & 1) == 0 || ((*arg1 & 1) != 0)))) &&
                (((*arg3 & 4) == 0 || ((*arg1 & 4) != 0)))) && (((*arg3 & 2) == 0 || (iVar4 = 0, (*arg1 & 2) != 0)))) {
                iVar4 = 1;
            }
            return iVar4;
        }
    }
    return 1;
}
