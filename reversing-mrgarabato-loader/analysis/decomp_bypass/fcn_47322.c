/* RVA 0x47322  tam 64 B  addr 0x140047322 */

uint64_t fcn.140047320(int64_t arg1,int64_t arg2)

{
    uint64_t uVar1;
    
    *(arg2 + 0x38) = arg1;
    *(arg2 + 0x28) = arg1;
    *(arg2 + 0x30) = **(arg2 + 0x28);
    if (**(arg2 + 0x30) == -0x1f928c9d) {
        uVar1 = fcn.14003f210();
    }
    else {
        *(arg2 + 0x20) = 0;
        uVar1 = *(arg2 + 0x20);
    }
    return uVar1;
}
