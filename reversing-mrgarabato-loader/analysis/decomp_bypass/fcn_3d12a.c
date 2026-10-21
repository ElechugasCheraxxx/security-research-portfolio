/* RVA 0x3d12a  tam 97 B  addr 0x14003d12a */

uint fcn.14003d128(int64_t arg1,int64_t arg2,int64_t arg3)

{
    char cVar1;
    uint *puVar2;
    uint uVar3;
    int64_t iVar4;
    
    if ((arg1 != 0) && (arg2 != 0)) {
        if (arg3 != 0) {
            iVar4 = arg1 - arg3;
            do {
                cVar1 = *arg3;
                *(arg3 + iVar4) = cVar1;
                arg3 = arg3 + 1;
                if (cVar1 == '\0') break;
                arg2 = arg2 + -1;
            } while (arg2 != 0);
            if (arg2 != 0) {
                return 0;
            }
            *arg1 = 0;
            puVar2 = fcn.14003ef2c();
            uVar3 = 0x22;
            goto code_r0x00014003d14a;
        }
        *arg1 = 0;
    }
    puVar2 = fcn.14003ef2c();
    uVar3 = 0x16;
code_r0x00014003d14a:
    *puVar2 = uVar3;
    fcn.14003eec4();
    return uVar3;
}
