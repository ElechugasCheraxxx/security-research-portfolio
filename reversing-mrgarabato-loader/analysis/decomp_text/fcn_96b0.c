/* RVA 0x96b0  tam 63 B  addr 0x1400096b0 */

ulong fcn.1400096b0(int64_t arg1,int64_t arg2,int64_t arg3)

{
    int *piVar1;
    uchar auStack_18 [16];
    
    piVar1 = (**(*arg1 + 0x18))(arg1,auStack_18,arg2 & 0xffffffff);
    if ((*(*(piVar1 + 2) + 8) == *(*(arg3 + 8) + 8)) && (*piVar1 == *arg3)) {
        return 1;
    }
    return 0;
}
