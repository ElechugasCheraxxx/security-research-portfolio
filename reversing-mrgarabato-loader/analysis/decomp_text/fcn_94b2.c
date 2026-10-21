/* RVA 0x94b2  tam 127 B  addr 0x1400094b2 */

int64_t fcn.1400094b0(int64_t arg1,int64_t arg2,int64_t arg3)

{
    int64_t iVar1;
    int64_t iVar2;
    
    iVar1 = *(arg1 + 0x10);
    if (arg3 <= *(arg1 + 0x18) - iVar1) {
        *(arg1 + 0x10) = iVar1 + arg3;
        iVar2 = arg1;
        if (7 < *(arg1 + 0x18)) {
            iVar2 = *arg1;
        }
        fcn.140015ec4(iVar2 + iVar1 * 2,arg2,arg3 * 2);
        *(iVar2 + (iVar1 + arg3) * 2) = 0;
        return arg1;
    }
    iVar1 = fcn.140002620(arg1,arg3,0,arg2,arg3);
    return iVar1;
}
