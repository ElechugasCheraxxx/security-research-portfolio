/* RVA 0x39a0  tam 77 B  addr 0x1400039a0 */

int64_t fcn.1400039a0(int64_t arg1,int64_t arg2)

{
    ulong uVar1;
    
    *arg1 = 0x1400188a8;
    *(arg1 + 8) = 0;
    *(arg1 + 0x10) = 0;
    fcn.140015e9a(arg2 + 8);
    *arg1 = 0x140018948;
    uVar1 = *(arg2 + 0x20);
    *(arg1 + 0x18) = *(arg2 + 0x18);
    *(arg1 + 0x20) = uVar1;
    return arg1;
}
