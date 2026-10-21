/* RVA 0x45997  tam 124 B  addr 0x140045997 */

void fcn.140045997(int64_t arg1,int64_t arg2,int64_t arg3,int64_t arg4)

{
    int64_t iVar1;
    int64_t aiStackX_10 [3];
    
    aiStackX_10[0] = arg2;
    iVar1 = fcn.14003e9d8();
    *(iVar1 + 0x128) = *(arg4 + 8);
    iVar1 = fcn.14003e9d8();
    *(iVar1 + 0x130) = *(arg1 + 0x38);
    iVar1 = fcn.14003e9d8();
    fcn.140047074(arg1,aiStackX_10,arg3,arg4,**(arg4 + 0x38) + *(iVar1 + 0x128),0,0,0);
    return;
}
