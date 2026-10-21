/* RVA 0x3f127  tam 182 B  addr 0x14003f127 */

int64_t fcn.14003f11c(int64_t arg1)

{
    uchar *puVar1;
    int iVar2;
    int64_t iVar3;
    uint *puVar4;
    uchar *puVar5;
    int64_t iVar6;
    int64_t aiStack_38 [2];
    uchar auStack_28 [32];
    
    if (arg1 < 0xffffffffffffffe1) {
        puVar1 = &stack0xffffffffffffffd8;
        iVar6 = 1;
        if (arg1 != 0) {
            puVar1 = &stack0xffffffffffffffd8;
            iVar6 = arg1;
        }
        do {
            puVar5 = puVar1;
            if (*0x1400569b8 == 0) {
                *(puVar5 + -8) = 0x14003f151;
                fcn.140042fb0();
                *(puVar5 + -8) = 0x14003f15b;
                fcn.140042d50(0x1e);
                *(puVar5 + -8) = 0x14003f165;
                func_0x000140040e18(0xff);
            }
            *(puVar5 + -8) = iVar6;
            *(puVar5 + -0x10) = 0x14003f177;
            iVar3 = func_0x00014027ea31(*0x1400569b8,0,iVar6);
            if (iVar3 != 0) goto code_r0x00014003f1c2;
            if (*0x140057228 == 0) {
                *(puVar5 + -0x10) = 0x14003f19a;
                puVar4 = fcn.14003ef2c();
                *puVar4 = 0xc;
                break;
            }
            *(puVar5 + -0x10) = 0x14003f18f;
            iVar2 = func_0x00014003f1dc(arg1);
            puVar1 = puVar5 + -8;
        } while (iVar2 != 0);
        *(puVar5 + -0x10) = 0x14003f1a5;
        puVar4 = fcn.14003ef2c();
        *puVar4 = 0xc;
    }
    else {
        func_0x00014003f1dc();
        puVar4 = fcn.14003ef2c();
        *puVar4 = 0xc;
        iVar3 = 0;
    }
code_r0x00014003f1c2:
    return iVar3;
}
