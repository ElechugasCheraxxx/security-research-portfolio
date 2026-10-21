/* RVA 0x40738  tam 150 B  addr 0x140040738 */

void fcn.140040738(int64_t arg1,int64_t arg2,int64_t arg3,int64_t arg4)

{
    uint32_t *puVar1;
    int32_t unaff_EDI;
    int32_t in_stack_ffffffffffffffd8;
    int64_t in_stack_ffffffffffffffe0;
    int32_t in_stack_ffffffffffffffe8;
    uint uStack_14;
    int32_t in_stack_fffffffffffffff0;
    
    fcn.14003c53c(&stack0xffffffffffffffd8,arg1);
    fcn.14004046c(&stack0xffffffffffffffd8,arg2 & 0xffffffff,arg3 & 0xffffffff,arg4,in_stack_ffffffffffffffd8,
                  in_stack_ffffffffffffffe0,in_stack_ffffffffffffffe8,in_stack_fffffffffffffff0,unaff_EDI);
    if (in_stack_fffffffffffffff0 != '\0') {
        puVar1 = CONCAT44(uStack_14,in_stack_ffffffffffffffe8) + 200;
        *puVar1 = *puVar1 & 0xfffffffd;
    }
    return;
}
