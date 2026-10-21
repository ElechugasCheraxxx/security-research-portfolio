/* RVA 0x43140  tam 65 B  addr 0x140043140 */

uint64_t fcn.140043140(int64_t arg1)

{
    uint64_t uVar1;
    ulong in_RDX;
    int64_t iVar2;
    
    iVar2 = 0x140022000;
    uVar1 = func_0x0001400430c0(0x140022000,in_RDX,arg1);
    if (uVar1 != 0) {
        iVar2 = func_0x0001400430f0(iVar2,arg1 - iVar2);
        uVar1 = 0;
        if (iVar2 != 0) {
            uVar1 = ~(*(iVar2 + 0x24) >> 0x1f) & 1;
        }
    }
    return uVar1;
}
