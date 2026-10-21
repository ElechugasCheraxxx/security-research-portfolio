/* RVA 0x3c948  tam 152 B  addr 0x14003c948 */

uint64_t fcn.14003c948(int64_t arg1,int64_t arg2,int64_t arg3)

{
    uint *puVar1;
    uint64_t uVar2;
    uint16_t uVar3;
    uint16_t uVar4;
    
    uVar2 = 0;
    if (*0x140056828 == 0) {
        if (arg3 != 0) {
            if ((arg1 != 0) && (arg2 != 0)) {
                arg1 = arg1 - arg2;
                do {
                    uVar3 = *(arg1 + arg2);
                    if ((0x40 < uVar3) && (uVar3 < 0x5b)) {
                        uVar3 = uVar3 + 0x20;
                    }
                    uVar4 = *arg2;
                    if ((0x40 < uVar4) && (uVar4 < 0x5b)) {
                        uVar4 = uVar4 + 0x20;
                    }
                    arg2 = arg2 + 2;
                    arg3 = arg3 + -1;
                } while (((arg3 != 0) && (uVar3 != 0)) && (uVar3 == uVar4));
                return uVar3 - uVar4;
            }
            puVar1 = fcn.14003ef2c();
            *puVar1 = 0x16;
            fcn.14003eec4();
            return 0x7fffffff;
        }
    }
    else {
        uVar2 = func_0x00014003c830();
    }
    return uVar2;
}
