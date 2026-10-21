/* RVA 0x9ab6  tam 264 B  addr 0x140009ab6 */

int64_t fcn.140009ab6(int64_t arg1,int64_t arg2,int64_t arg3,int64_t arg4)

{
    uint64_t uVar1;
    uint64_t uVar2;
    code *pcVar3;
    int64_t iVar4;
    
    uVar2 = *(arg1 + 0x10);
    if (uVar2 < arg2) {
        fcn.140009400();
        pcVar3 = swi(3);
        iVar4 = (*pcVar3)();
        return iVar4;
    }
    if (arg4 <= *(arg1 + 0x18) - uVar2) {
        *(arg1 + 0x10) = uVar2 + arg4;
        iVar4 = arg1;
        if (7 < *(arg1 + 0x18)) {
            iVar4 = *arg1;
        }
        uVar1 = iVar4 + arg2 * 2;
        if ((uVar1 < arg3 + arg4 * 2) && (arg3 <= iVar4 + uVar2 * 2)) {
            if (arg3 < uVar1) {
                iVar4 = uVar1 - arg3 >> 1;
            }
            else {
                iVar4 = 0;
            }
        }
        else {
            iVar4 = arg4;
        }
        fcn.140015ec4(arg4 * 2 + uVar1,uVar1,(uVar2 - arg2) * 2 + 2);
        fcn.140015ebe(uVar1,arg3,iVar4 * 2);
        fcn.140015ebe(iVar4 * 2 + uVar1,arg3 + (iVar4 + arg4) * 2,(arg4 - iVar4) * 2);
        return arg1;
    }
    iVar4 = fcn.1400029b0(arg1,arg4,0,arg2);
    return iVar4;
}
