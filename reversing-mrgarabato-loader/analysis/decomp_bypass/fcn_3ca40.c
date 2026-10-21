/* RVA 0x3ca40  tam 93 B  addr 0x14003ca40 */

void fcn.14003ca2c(int64_t arg1,int64_t arg2,int64_t arg3,int64_t arg4)

{
    uint32_t uVar1;
    uint64_t uVar2;
    
    uVar2 = arg3;
    arg1 = uVar2 * arg2 + arg1;
    while( true ) {
        uVar1 = uVar2 - 1;
        uVar2 = uVar1;
        if (uVar1 < 0) break;
        arg1 = arg1 - arg2;
        (*arg4)(arg1);
    }
    return;
}
