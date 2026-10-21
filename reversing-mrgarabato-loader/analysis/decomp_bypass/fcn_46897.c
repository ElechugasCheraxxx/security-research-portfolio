/* RVA 0x46897  tam 174 B  addr 0x140046897 */

void fcn.140046897(int64_t arg1,int64_t arg2,int64_t arg3,int64_t arg4)

{
    int64_t in_RAX;
    int64_t arg2_00;
    ulong in_stack_00000050;
    int64_t in_stack_00000058;
    int64_t in_stack_00000060;
    
    arg2_00 = fcn.14004578c(arg2,arg4,in_stack_00000050,in_RAX + 0x10);
    if (in_stack_00000060 != 0) {
        fcn.1400467d4(arg1,arg2_00,in_stack_00000058,in_stack_00000060);
    }
    fcn.140045878();
    fcn.140045d10(arg2,arg1,arg3,arg2_00);
    return;
}
