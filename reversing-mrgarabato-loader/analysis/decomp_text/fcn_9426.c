/* RVA 0x9426  tam 131 B  addr 0x140009426 */

int64_t fcn.140009420(int64_t arg1,int64_t arg2,int64_t arg3)

{
    int64_t iVar1;
    int64_t iVar2;
    
    iVar2 = *(arg1 + 0x10);
    if (arg3 <= *(arg1 + 0x18) - iVar2) {
        *(arg1 + 0x10) = iVar2 + arg3;
        iVar1 = arg1;
        if (0xf < *(arg1 + 0x18)) {
            iVar1 = *arg1;
        }
        fcn.140015ec4(iVar1 + iVar2,arg2,arg3);
        *(iVar1 + iVar2 + arg3) = 0;
        return arg1;
    }
    iVar2 = fcn.140002490(arg1,arg3,0,arg2);
    return iVar2;
}
