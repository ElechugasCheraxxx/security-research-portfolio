/* RVA 0x23000  tam 79 B  addr 0x140023000 */

int64_t fcn.140023000(int64_t arg1)

{
    ulong uVar1;
    int64_t iVar2;
    
    //[04] -r-x section size 8355840 named .7 f
    *arg1 = 0;
    *(arg1 + 8) = 0;
    uVar1 = SUB168(ZEXT816(2) * ZEXT816(1),0);
    if (SUB168(ZEXT816(2) * ZEXT816(1),8) != 0) {
        uVar1 = 0xffffffffffffffff;
    }
    iVar2 = fcn.14003c43c(uVar1);
    *arg1 = iVar2;
    *(iVar2 + *(arg1 + 8) * 2) = 0;
    return arg1;
}
