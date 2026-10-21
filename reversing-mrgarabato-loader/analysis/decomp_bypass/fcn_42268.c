/* RVA 0x42268  tam 126 B  addr 0x140042268 */

void fcn.140042268(int64_t arg1,int64_t arg2,int64_t arg3,int64_t arg4)

{
    int32_t unaff_EDI;
    uchar auStackY_28 [16];
    int64_t in_stack_ffffffffffffffe8;
    int32_t in_stack_fffffffffffffff0;
    
    fcn.14003c53c(auStackY_28,arg1);
    fcn.140042108(auStackY_28,arg2 & 0xffffffff,arg3,arg4 & 0xffffffff,in_stack_ffffffffffffffe8,
                  in_stack_fffffffffffffff0,unaff_EDI);
    if (in_stack_fffffffffffffff0 != '\0') {
        *(in_stack_ffffffffffffffe8 + 200) = *(in_stack_ffffffffffffffe8 + 200) & 0xfffffffd;
    }
    return;
}
