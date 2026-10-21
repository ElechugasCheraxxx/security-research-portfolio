/* RVA 0x44094  tam 353 B  addr 0x140044094 */

uint fcn.140044094(int64_t arg1,int64_t arg2,int64_t arg3,int64_t arg4)

{
    uint uVar1;
    int iVar2;
    uint *puVar3;
    uchar *puVar4;
    int64_t iStack_58;
    uchar auStack_50 [32];
    int64_t iStack_30;
    int64_t var_20h;
    int64_t iStack_20;
    int64_t var_10h;
    int8_t var_8h;
    char cStack_8;
    
    if ((arg2 == 0) || (arg3 == 0)) {
        return 0;
    }
    if (*arg2 == '\0') {
        if (arg1 == 0) {
            return 0;
        }
        *arg1 = 0;
        return 0;
    }
    iStack_58 = 0x1400440e7;
    fcn.14003c53c(&stack0xffffffffffffffe0,arg4);
    if (*(iStack_20 + 0x14) == 0) {
        if (arg1 != 0) {
            *arg1 = *arg2;
        }
code_r0x0001400440fc:
        if (cStack_8 != '\0') {
            *(_var_8h + 200) = *(_var_8h + 200) & 0xfffffffd;
        }
        return 1;
    }
    iStack_58 = 0x140044120;
    iVar2 = fcn.1400407d0(*arg2,&stack0xffffffffffffffe0);
    if (iVar2 == 0) {
        var_20h._0_4_ = arg1 != 0;
        puVar4 = &stack0xffffffffffffffa8;
        iStack_58 = iStack_20;
        iStack_30 = arg1;
        iVar2 = fcn.1406a4ef0(*(iStack_20 + 4),9,arg2);
        if (iVar2 != 0) goto code_r0x0001400440fc;
    }
    else {
        puVar4 = &stack0xffffffffffffffb0;
        if ((1 < *(iStack_20 + 0x10c)) && (puVar4 = &stack0xffffffffffffffb0, *(iStack_20 + 0x10c) <= arg3)) {
            var_20h._0_4_ = arg1 != 0;
            puVar4 = &stack0xffffffffffffffa8;
            iStack_58 = arg3;
            iStack_30 = arg1;
            iVar2 = fcn.14069eefe(*(iStack_20 + 4),9,arg2);
            if (iVar2 != 0) goto code_r0x00014004417b;
        }
        if ((*(iStack_20 + 0x10c) <= arg3) && (*(arg2 + 1) != '\0')) {
code_r0x00014004417b:
            uVar1 = *(iStack_20 + 0x10c);
            if (cStack_8 != '\0') {
                *(_var_8h + 200) = *(_var_8h + 200) & 0xfffffffd;
                return uVar1;
            }
            return uVar1;
        }
    }
    *(puVar4 + -8) = 0x1400441a0;
    puVar3 = fcn.14003ef2c();
    *puVar3 = 0x2a;
    if (cStack_8 != '\0') {
        *(_var_8h + 200) = *(_var_8h + 200) & 0xfffffffd;
    }
    return 0xffffffff;
}
