/* RVA 0x3ce58  tam 191 B  addr 0x14003ce58 */

uint fcn.14003ce58(int64_t arg1,int64_t arg2,int64_t arg3,int64_t arg4)

{
    char cVar1;
    uint *puVar2;
    uint uVar3;
    int64_t iVar4;
    int64_t iVar5;
    char *pcVar6;
    
    if (arg4 == 0) {
        if (arg1 == 0) {
            if (arg2 == 0) {
                return 0;
            }
        }
        else {
code_r0x00014003ce7b:
            if (arg2 != 0) {
                if (arg4 == 0) {
                    *arg1 = 0;
                    return 0;
                }
                if (arg3 != 0) {
                    iVar4 = arg2;
                    if (arg4 == -1) {
                        iVar5 = arg1 - arg3;
                        do {
                            cVar1 = *arg3;
                            *(arg3 + iVar5) = cVar1;
                            arg3 = arg3 + 1;
                            if (cVar1 == '\0') break;
                            iVar4 = iVar4 + -1;
                        } while (iVar4 != 0);
                    }
                    else {
                        pcVar6 = arg1;
                        do {
                            cVar1 = pcVar6[arg3 - arg1];
                            *pcVar6 = cVar1;
                            pcVar6 = pcVar6 + 1;
                            if ((cVar1 == '\0') || (iVar4 = iVar4 + -1, iVar4 == 0)) break;
                            arg4 = arg4 + -1;
                        } while (arg4 != 0);
                        if (arg4 == 0) {
                            *pcVar6 = '\0';
                        }
                    }
                    if (iVar4 != 0) {
                        return 0;
                    }
                    if (arg4 == -1) {
                        *(arg1 + -1 + arg2) = 0;
                        return 0x50;
                    }
                    *arg1 = 0;
                    puVar2 = fcn.14003ef2c();
                    uVar3 = 0x22;
                    goto code_r0x00014003ce9a;
                }
                *arg1 = 0;
            }
        }
    }
    else if (arg1 != 0) goto code_r0x00014003ce7b;
    puVar2 = fcn.14003ef2c();
    uVar3 = 0x16;
code_r0x00014003ce9a:
    *puVar2 = uVar3;
    fcn.14003eec4();
    return uVar3;
}
