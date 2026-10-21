/* RVA 0x3c9ea  tam 64 B  addr 0x14003c9ea */

void fcn.14003c9ea(int64_t arg1,int64_t arg2,int64_t arg3,int64_t arg4)

{
    uint32_t uVar1;
    uint64_t uVar2;
    
    uVar2 = arg3 & 0xffffffff;
    while( true ) {
        uVar1 = uVar2 - 1;
        uVar2 = uVar1;
        if (uVar1 < 0) break;
        arg1 = arg1 - arg2;
        (*arg4)(arg1);
    }
    return;
}
