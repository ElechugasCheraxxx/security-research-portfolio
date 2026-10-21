/* RVA 0x3cd3c  tam 121 B  addr 0x14003cd3c */

ulong fcn.14003cd3c(int64_t arg1,int64_t arg2,int64_t arg3,int64_t arg4)

{
    ulong uVar1;
    uint *puVar2;
    int64_t unaff_RDI;
    int64_t unaff_retaddr;
    ulong in_stack_00000028;
    
    if (((arg3 == 0) || (arg1 == 0)) || (arg2 == 0)) {
        puVar2 = fcn.14003ef2c();
        *puVar2 = 0x16;
    }
    else {
        uVar1 = fcn.14003cc20(0x14003f844,arg1,arg2,arg3,arg4,in_stack_00000028,unaff_RDI,unaff_retaddr);
        if (uVar1 < 0) {
            *arg1 = 0;
        }
        if (uVar1 != -2) {
            return uVar1;
        }
        puVar2 = fcn.14003ef2c();
        *puVar2 = 0x22;
    }
    fcn.14003eec4();
    return 0xffffffff;
}
