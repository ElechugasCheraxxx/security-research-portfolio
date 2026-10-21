/* RVA 0x44307  tam 211 B  addr 0x140044307 */

int64_t fcn.1400442fc(int64_t arg1,int64_t arg2)

{
    uchar *puVar1;
    uchar *puVar2;
    int iVar3;
    uint uVar4;
    int64_t iVar5;
    uint *puVar6;
    uchar *puVar7;
    int64_t aiStack_38 [2];
    uchar auStack_28 [32];
    
    puVar7 = &stack0xffffffffffffffd8;
    if (arg1 == 0) {
        iVar5 = fcn.14003f11c(arg2);
    }
    else {
        puVar2 = &stack0xffffffffffffffd8;
        if (arg2 == 0) {
            fcn.14003dc60(arg1);
        }
        else {
            do {
                puVar1 = puVar2;
                if (0xffffffffffffffe0 < arg2) {
                    *(puVar7 + -8) = 0x14004437d;
                    fcn.14003f1dc(arg2);
                    *(puVar7 + -8) = 0x140044382;
                    puVar6 = fcn.14003ef2c();
                    *puVar6 = 0xc;
                    goto code_r0x000140044388;
                }
                if (arg2 == 0) {
                    arg2 = 1;
                }
                *(puVar1 + -8) = 0x140044352;
                iVar5 = func_0x000140217d2e(*0x1400569b8,0,arg1,arg2);
                puVar7 = puVar1 + -8;
                *(puVar1 + -8) = iVar5;
                if (iVar5 != 0) {
                    return iVar5;
                }
                if (*0x140057228 == 0) {
                    *(puVar1 + -0x10) = 0x1400443b8;
                    puVar6 = fcn.14003ef2c();
                    *(puVar1 + -0x10) = 0x1400443c0;
                    uVar4 = func_0x000140239ca4();
                    *arg1 = _pe_dos_header;
                    *(puVar1 + -0x10) = 0x1400443c8;
                    uVar4 = fcn.14003eee4(uVar4);
                    *puVar6 = uVar4;
                    return 4;
                }
                *(puVar1 + -0x10) = 0x14004436b;
                iVar3 = fcn.14003f1dc(arg2);
                puVar2 = puVar1 + -8;
            } while (iVar3 != 0);
            *(puVar1 + -0x10) = 0x14004439f;
            puVar6 = fcn.14003ef2c();
            *(puVar1 + -0x10) = 0x1400443a7;
            uVar4 = func_0x000140176a15();
            *(puVar1 + -8) = 0x1400443af;
            uVar4 = fcn.14003eee4(uVar4);
            *puVar6 = uVar4;
        }
code_r0x000140044388:
        iVar5 = 0;
    }
    return iVar5;
}
