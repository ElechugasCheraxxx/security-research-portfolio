/* RVA 0x42ad8  tam 93 B  addr 0x140042ad8 */

void fcn.140042ad8(int64_t arg1,int64_t arg2,int64_t arg3,int64_t arg4)

{
    int iVar1;
    ulong in_stack_00000028;
    uint in_stack_00000030;
    
    iVar1 = arg4;
    if (0 < iVar1) {
        iVar1 = fcn.140044820(arg3,iVar1);
    }
    fcn.14016ba08(arg1 & 0xffffffff,arg2 & 0xffffffff,arg3,iVar1,in_stack_00000028,in_stack_00000030);
    return;
}
