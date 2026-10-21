/* RVA 0xb4c0  tam 87 B  addr 0x14000b4c0 */

int64_t fcn.14000b4c0(int64_t arg1,int64_t arg2)

{
    ulong uVar1;
    ulong uVar2;
    
    *arg1 = 0x1400188a8;
    *(arg1 + 8) = 0;
    *(arg1 + 0x10) = 0;
    fcn.140015e9a(arg2 + 8);
    *arg1 = 0x140018948;
    uVar1 = *(arg2 + 0x18);
    uVar2 = *(arg2 + 0x20);
    *arg1 = 0x140019060;
    *(arg1 + 0x18) = uVar1;
    *(arg1 + 0x20) = uVar2;
    return arg1;
}
