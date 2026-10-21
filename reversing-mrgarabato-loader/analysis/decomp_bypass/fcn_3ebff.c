/* RVA 0x3ebff  tam 202 B  addr 0x14003ebff */

//WARNING: Variable defined which should be unmapped: var_20h

uint16_t fcn.14003ebff(int64_t arg1,int64_t arg2)

{
    uint16_t uVar1;
    int iVar2;
    int16_t var_10h;
    uint16_t auStackX_10 [4];
    int64_t var_20h_2;
    uint16_t auStackX_20 [4];
    int64_t var_20h;
    int64_t iStack_20;
    int64_t var_10h_2;
    int8_t var_8h;
    char cStack_8;
    
    uVar1 = 0xffff;
    if (arg1 != -1) {
        fcn.14003c53c(&iStack_20,arg2);
        if (*(iStack_20 + 0x14) == 0) {
            if (auStackX_10[0] - 0x41 < 0x1a) {
                auStackX_10[0] = auStackX_10[0] + 0x20;
            }
            if (cStack_8 != '\0') {
                *(_var_8h + 200) = *(_var_8h + 200) & 0xfffffffd;
            }
            uVar1 = auStackX_10[0];
        }
        else {
            if (auStackX_10[0] < 0x100) {
                iVar2 = func_0x000140040be8(auStackX_10[0],1);
                if (iVar2 == 0) {
                    uVar1 = auStackX_10[0];
                }
                else {
                    uVar1 = *(*(iStack_20 + 0x148) + auStackX_10[0]);
                }
            }
            else {
                iVar2 = func_0x000140042ad8(*(iStack_20 + 0x14),0x100,auStackX_10,1,auStackX_20,1);
                uVar1 = auStackX_10[0];
                if (iVar2 != 0) {
                    uVar1 = auStackX_20[0];
                }
            }
            if (cStack_8 != '\0') {
                *(_var_8h + 200) = *(_var_8h + 200) & 0xfffffffd;
            }
        }
    }
    return uVar1;
}
