/* RVA 0x3d8d0  tam 76 B  addr 0x14003d8d0 */

void fcn.14003d8d0(int64_t arg1,int64_t arg2,int64_t arg3,int64_t arg4)

{
    int64_t in_RAX;
    int iVar1;
    
    *(in_RAX + -0x28) = 0;
    for (iVar1 = 0; iVar1 < arg3; iVar1 = iVar1 + 1) {
        (*arg4)(arg1);
        arg1 = arg1 + arg2;
    }
    return;
}
