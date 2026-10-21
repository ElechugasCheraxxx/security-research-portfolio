/* RVA 0x3cfc6  tam 323 B  addr 0x14003cfc6 */

uint64_t fcn.14003cfc3(int64_t arg1,int64_t arg2)

{
    uint32_t uVar1;
    int iVar2;
    uint64_t uVar3;
    uint *puVar4;
    uint32_t uVar5;
    uint uVar6;
    int8_t var_10h;
    int8_t var_11h;
    int8_t var_12h;
    uchar uStackX_10;
    uchar uStackX_11;
    uchar uStackX_12;
    int64_t var_20h_2;
    uint8_t uStackX_20;
    uchar uStackX_21;
    int64_t var_20h;
    int64_t iStack_20;
    int64_t var_10h_2;
    int8_t var_8h;
    char cStack_8;
    
    uVar5 = arg1;
    fcn.14003c53c(&iStack_20,arg2);
    if (uVar5 < 0x100) {
        if (*(iStack_20 + 0x10c) < 2) {
            uVar1 = *(*(iStack_20 + 0x140) + uVar5 * 2) & 1;
        }
        else {
            uVar1 = func_0x000140040384(arg1 & 0xffffffff,1,&iStack_20);
        }
        if (uVar1 == 0) {
code_r0x00014003d023:
            if (cStack_8 != '\0') {
                *(_var_8h + 200) = *(_var_8h + 200) & 0xfffffffd;
            }
            return arg1 & 0xffffffff;
        }
        uVar3 = *(*(iStack_20 + 0x148) + uVar5);
    }
    else {
        if ((*(iStack_20 + 0x10c) < 2) || (iVar2 = func_0x0001400407d0(uVar5 >> 8 & 0xff,&iStack_20), iVar2 == 0)) {
            puVar4 = fcn.14003ef2c();
            uVar6 = 1;
            *puVar4 = 0x2a;
            uStackX_11 = 0;
            uStackX_10 = arg1;
        }
        else {
            uStackX_12 = 0;
            uVar6 = 2;
            uStackX_10 = arg1 >> 8;
            uStackX_11 = arg1;
        }
        iVar2 = fcn.140040738(&iStack_20,*(iStack_20 + 0x14),0x100,&uStackX_10,uVar6,&uStackX_20,3,
                              *(iStack_20 + 4),1);
        if (iVar2 == 0) goto code_r0x00014003d023;
        uVar3 = uStackX_20;
        if (iVar2 != 1) {
            uVar3 = CONCAT11(uStackX_20,uStackX_21);
        }
    }
    if (cStack_8 != '\0') {
        *(_var_8h + 200) = *(_var_8h + 200) & 0xfffffffd;
    }
    return uVar3;
}
