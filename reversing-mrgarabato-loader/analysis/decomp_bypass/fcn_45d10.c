/* RVA 0x45d10  tam 240 B  addr 0x140045d10 */

//WARNING: Variable defined which should be unmapped: var_bp_30h

void fcn.140045d10(int64_t arg1,int64_t arg2,int64_t arg3,int64_t arg4)

{
    int in_stack_00000030;
    ulong *in_stack_00000040;
    uint8_t in_stack_00000048;
    int64_t var_4a0h;
    uchar auStack_5f8 [32];
    uchar *puStack_5d8;
    ulong uStack_5d0;
    uchar auStack_5c8 [32];
    ulong uStack_5a8;
    int64_t iStack_5a0;
    int64_t iStack_590;
    int64_t iStack_588;
    int64_t iStack_578;
    uint64_t uStack_570;
    ulong uStack_568;
    uchar auStack_528 [1184];
    int64_t var_80h;
    int64_t var_78h;
    int64_t var_bp_70h;
    uint64_t uStack_58;
    int64_t var_bp_30h;
    
    uStack_58 = *0x140053bd0 ^ auStack_5f8;
    fcn.140041d50(auStack_5c8,0x14004cd40,0x98);
    iStack_590 = in_stack_00000030;
    uStack_570 = in_stack_00000048;
    uStack_5d0 = in_stack_00000040[8];
    puStack_5d8 = auStack_528;
    uStack_5a8 = 0x1400463bc;
    uStack_568 = 0x19930520;
    iStack_5a0 = arg4;
    iStack_588 = arg3;
    iStack_578 = arg2;
    fcn.140045786(*arg1,*in_stack_00000040,auStack_5c8,0);
    fcn.140042300(uStack_58 ^ auStack_5f8);
    return;
}
