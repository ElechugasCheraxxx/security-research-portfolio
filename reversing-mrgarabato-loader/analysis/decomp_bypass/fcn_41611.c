/* RVA 0x41611  tam 438 B  addr 0x140041611 */

void fcn.140041611(int64_t arg1,int64_t arg2,int64_t arg3,int64_t arg4)

{
    bool bVar1;
    int iVar2;
    uint32_t uVar3;
    bool bVar4;
    char *pcVar5;
    char cVar6;
    int *in_stack_00000040;
    
    *in_stack_00000040 = 0;
    *arg4 = 1;
    if (arg2 != 0) {
        *arg2 = arg3;
        arg2 = arg2 + 8;
    }
    bVar1 = false;
    do {
        if (*arg1 == '\"') {
            bVar1 = !bVar1;
            cVar6 = '\"';
            pcVar5 = arg1 + 1;
        }
        else {
            *in_stack_00000040 = *in_stack_00000040 + 1;
            if (arg3 != NULL) {
                *arg3 = *arg1;
                arg3 = arg3 + 1;
            }
            cVar6 = *arg1;
            pcVar5 = arg1 + 1;
            iVar2 = func_0x0001400446c0();
            if (iVar2 != 0) {
                *in_stack_00000040 = *in_stack_00000040 + 1;
                if (arg3 != NULL) {
                    *arg3 = *pcVar5;
                    arg3 = arg3 + 1;
                }
                pcVar5 = arg1 + 2;
            }
            if (cVar6 == '\0') {
                pcVar5 = pcVar5 + -1;
                goto code_r0x0001400416ad;
            }
        }
        arg1 = pcVar5;
    } while ((bVar1) || ((cVar6 != ' ' && (cVar6 != '\t'))));
    if (arg3 != NULL) {
        *(arg3 + -1) = '\0';
    }
code_r0x0001400416ad:
    bVar1 = false;
    while (*pcVar5 != '\0') {
        for (; (*pcVar5 == ' ' || (*pcVar5 == '\t')); pcVar5 = pcVar5 + 1) {
        }
        if (*pcVar5 == '\0') break;
        if (arg2 != NULL) {
            *arg2 = arg3;
            arg2 = arg2 + 8;
        }
        *arg4 = *arg4 + 1;
        while( true ) {
            bVar4 = true;
            uVar3 = 0;
            for (; *pcVar5 == '\\'; pcVar5 = pcVar5 + 1) {
                uVar3 = uVar3 + 1;
            }
            if (*pcVar5 == '\"') {
                if ((uVar3 & 1) == 0) {
                    if ((bVar1) && (pcVar5[1] == '\"')) {
                        pcVar5 = pcVar5 + 1;
                    }
                    else {
                        bVar4 = false;
                        bVar1 = !bVar1;
                    }
                }
                uVar3 = uVar3 >> 1;
            }
            while (uVar3 != 0) {
                uVar3 = uVar3 - 1;
                if (arg3 != NULL) {
                    *arg3 = '\\';
                    arg3 = arg3 + 1;
                }
                *in_stack_00000040 = *in_stack_00000040 + 1;
            }
            cVar6 = *pcVar5;
            if ((cVar6 == '\0') || ((!bVar1 && ((cVar6 == ' ' || (cVar6 == '\t')))))) break;
            if (bVar4) {
                iVar2 = func_0x0001400446c0();
                if (arg3 == NULL) {
                    if (iVar2 != 0) {
                        pcVar5 = pcVar5 + 1;
                        *in_stack_00000040 = *in_stack_00000040 + 1;
                    }
                }
                else {
                    if (iVar2 != 0) {
                        cVar6 = *pcVar5;
                        pcVar5 = pcVar5 + 1;
                        *arg3 = cVar6;
                        arg3 = arg3 + 1;
                        *in_stack_00000040 = *in_stack_00000040 + 1;
                    }
                    *arg3 = *pcVar5;
                    arg3 = arg3 + 1;
                }
                *in_stack_00000040 = *in_stack_00000040 + 1;
            }
            pcVar5 = pcVar5 + 1;
        }
        if (arg3 != NULL) {
            *arg3 = '\0';
            arg3 = arg3 + 1;
        }
        *in_stack_00000040 = *in_stack_00000040 + 1;
    }
    if (arg2 != NULL) {
        *arg2 = 0;
    }
    *arg4 = *arg4 + 1;
    return;
}
