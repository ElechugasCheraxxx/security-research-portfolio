/* RVA 0x44266  tam 154 B  addr 0x140044266 */

int64_t fcn.140044260(int64_t arg1,int64_t arg2,int64_t arg3)

{
    int iVar1;
    uint *puVar2;
    int64_t iVar3;
    uchar *puVar4;
    uint64_t arg1_00;
    ulong auStack_38 [2];
    uchar auStack_28 [32];
    
    if ((arg1 == 0) || (arg2 <= 0xffffffffffffffe0U / arg1)) {
        arg1_00 = arg2 * arg1;
        puVar4 = &stack0xffffffffffffffd8;
        if (arg1_00 == 0) {
            arg1_00 = 1;
            puVar4 = &stack0xffffffffffffffd8;
        }
        do {
            if (arg1_00 < 0xffffffffffffffe1) {
                *(puVar4 + -8) = *0x1400569b8;
                *(puVar4 + -0x10) = 0x1400442bd;
                iVar3 = func_0x00014003a492(*0x1400569b8,8,arg1_00);
                puVar4 = puVar4 + -8;
                if (iVar3 != 0) {
                    return iVar3;
                }
            }
            if (*0x140057228 == 0) {
                if (arg3 == 0) {
                    return 0;
                }
                *arg3 = 0xc;
                return 0;
            }
            *(puVar4 + -8) = 0x1400442d3;
            iVar1 = fcn.14003f1dc(arg1_00);
        } while (iVar1 != 0);
        if (arg3 != 0) {
            *arg3 = 0xc;
        }
    }
    else {
        puVar2 = fcn.14003ef2c(arg1,0xffffffffffffffe0 % arg1);
        *puVar2 = 0xc;
    }
    return 0;
}
