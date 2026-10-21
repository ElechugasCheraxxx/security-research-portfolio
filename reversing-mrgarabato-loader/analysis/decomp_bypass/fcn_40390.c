/* RVA 0x40390  tam 223 B  addr 0x140040390 */

//WARNING: Variable defined which should be unmapped: var_20h

uint32_t fcn.14004038d(int64_t arg1,int64_t arg2,int64_t arg3,ulong noname_3,ulong noname_4,int8_t arg_38h)

{
    int iVar1;
    ulong uVar2;
    int64_t var_20h_2;
    uint16_t auStackX_20 [4];
    uchar uStack0000000000000038;
    uchar uStack0000000000000039;
    uchar in_stack_0000003a;
    int64_t var_20h;
    int64_t iStack_20;
    int64_t var_10h;
    int8_t var_8h;
    char cStack_8;
    
    iVar1 = arg1;
    fcn.14003c53c(&iStack_20,arg3);
    if (iVar1 + 1U < 0x101) {
        auStackX_20[0] = *(*(iStack_20 + 0x140) + iVar1 * 2);
    }
    else {
        iVar1 = func_0x0001400407d0(iVar1 >> 8 & 0xff,&iStack_20);
        if (iVar1 == 0) {
            uStack0000000000000039 = 0;
            uVar2 = 1;
            uStack0000000000000038 = arg1;
        }
        else {
            in_stack_0000003a = 0;
            uVar2 = 2;
            uStack0000000000000038 = arg1 >> 8;
            uStack0000000000000039 = arg1;
        }
        iVar1 = fcn.140042268(&iStack_20,1,&stack0x00000038,uVar2,auStackX_20,*(iStack_20 + 4),*(iStack_20 + 0x14)
                              ,1);
        if (iVar1 == 0) {
            if (cStack_8 != '\0') {
                *(_var_8h + 200) = *(_var_8h + 200) & 0xfffffffd;
            }
            return 0;
        }
    }
    if (cStack_8 != '\0') {
        *(_var_8h + 200) = *(_var_8h + 200) & 0xfffffffd;
    }
    return auStackX_20[0] & arg2;
}
