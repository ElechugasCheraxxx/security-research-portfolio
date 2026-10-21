/* RVA 0x3cdd0  tam 133 B  addr 0x14003cdd0 */

uint fcn.14003cdd0(int64_t arg1,int64_t arg2,int64_t arg3)

{
    int16_t iVar1;
    uint *puVar2;
    int16_t *piVar3;
    int64_t iVar4;
    uint uVar5;
    
    if ((arg1 != 0) && (arg2 != 0)) {
        piVar3 = arg1;
        if (arg3 == 0) {
            *arg1 = 0;
        }
        else {
            do {
                if (*piVar3 == 0) break;
                piVar3 = piVar3 + 1;
                arg2 = arg2 + -1;
            } while (arg2 != 0);
            if (arg2 != 0) {
                iVar4 = piVar3 - arg3;
                do {
                    iVar1 = *arg3;
                    *(iVar4 + arg3) = iVar1;
                    arg3 = arg3 + 2;
                    if (iVar1 == 0) break;
                    arg2 = arg2 + -1;
                } while (arg2 != 0);
                if (arg2 != 0) {
                    return 0;
                }
                *arg1 = 0;
                puVar2 = fcn.14003ef2c();
                uVar5 = 0x22;
                goto code_r0x00014003cdf9;
            }
            *arg1 = 0;
        }
    }
    puVar2 = fcn.14003ef2c();
    uVar5 = 0x16;
code_r0x00014003cdf9:
    *puVar2 = uVar5;
    fcn.14003eec4();
    return uVar5;
}
