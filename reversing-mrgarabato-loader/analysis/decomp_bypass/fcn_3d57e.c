/* RVA 0x3d57e  tam 107 B  addr 0x14003d57e */

uint fcn.14003d57c(int64_t arg1,int64_t arg2,int64_t arg3)

{
    int16_t iVar1;
    uint *puVar2;
    int64_t iVar3;
    uint uVar4;
    
    if ((arg1 != 0) && (arg2 != 0)) {
        if (arg3 != 0) {
            iVar3 = arg1 - arg3;
            do {
                iVar1 = *arg3;
                *(iVar3 + arg3) = iVar1;
                arg3 = arg3 + 2;
                if (iVar1 == 0) break;
                arg2 = arg2 + -1;
            } while (arg2 != 0);
            if (arg2 != 0) {
                return 0;
            }
            *arg1 = 0;
            puVar2 = fcn.14003ef2c();
            uVar4 = 0x22;
            goto code_r0x00014003d5a5;
        }
        *arg1 = 0;
    }
    puVar2 = fcn.14003ef2c();
    uVar4 = 0x16;
code_r0x00014003d5a5:
    *puVar2 = uVar4;
    fcn.14003eec4();
    return uVar4;
}
