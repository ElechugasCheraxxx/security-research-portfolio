/* RVA 0x45a24  tam 161 B  addr 0x140045a24 */

ulong fcn.140045a14(int64_t arg1,int64_t arg2,int64_t arg3,int64_t arg4)

{
    int64_t iVar1;
    int64_t iVar2;
    ulong in_stack_00000028;
    ulong in_stack_00000030;
    uint *in_stack_00000038;
    
    iVar1 = fcn.14003e9d8();
    *(iVar1 + 0x138) = arg2;
    iVar1 = *arg1;
    iVar2 = fcn.14003e9d8();
    *(iVar2 + 0x130) = *(iVar1 + 0x38);
    fcn.140047074(*arg1,arg3,arg4,in_stack_00000028,in_stack_00000030,0,0,1);
    iVar1 = fcn.14003e9d8();
    *(iVar1 + 0x138) = 0;
    *in_stack_00000038 = 1;
    return 1;
}
