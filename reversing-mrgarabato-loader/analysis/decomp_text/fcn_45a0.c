/* RVA 0x45a0  tam 86 B  addr 0x1400045a0 */

int64_t fcn.1400045a0(int64_t arg1,int64_t arg2)

{
    uint64_t uVar1;
    int64_t iVar2;
    
    uVar1 = *(arg1 + 0x10);
    if (uVar1 < *(arg1 + 0x18)) {
        *(arg1 + 0x10) = uVar1 + 1;
        iVar2 = arg1;
        if (0xf < *(arg1 + 0x18)) {
            iVar2 = *arg1;
        }
        *(iVar2 + uVar1) = arg2;
        *(iVar2 + 1 + uVar1) = 0;
        return arg1;
    }
    fcn.140002bc0(arg1,1,0,arg2 & 0xff);
    return arg1;
}
