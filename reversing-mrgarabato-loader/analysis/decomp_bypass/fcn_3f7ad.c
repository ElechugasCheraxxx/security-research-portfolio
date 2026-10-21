/* RVA 0x3f7ad  tam 151 B  addr 0x14003f7ad */

void fcn.14003f7ad(int64_t arg1,int64_t arg2,int64_t arg3,int64_t arg4)

{
    uint uVar1;
    uint *puVar2;
    int *piVar3;
    uint64_t uVar4;
    
    uVar4 = arg2 & 0xffffffff;
    puVar2 = fcn.14003ef2c();
    uVar1 = *puVar2;
    if (((*(arg3 + 0x18) & 0x40) == 0) || (*(arg3 + 0x10) != 0)) {
        puVar2 = fcn.14003ef2c();
        *puVar2 = 0;
        while (0 < uVar4) {
            uVar4 = uVar4 - 1;
            fcn.14003f70c(*arg1,arg3,arg4);
            arg1 = arg1 + 2;
            if (*arg4 == -1) {
                piVar3 = fcn.14003ef2c();
                if (*piVar3 != 0x2a) break;
                fcn.14003f70c(0x3f,arg3,arg4);
            }
        }
        piVar3 = fcn.14003ef2c();
        if (*piVar3 == 0) {
            puVar2 = fcn.14003ef2c();
            *puVar2 = uVar1;
        }
    }
    else {
        *arg4 = *arg4 + arg2;
    }
    return;
}
