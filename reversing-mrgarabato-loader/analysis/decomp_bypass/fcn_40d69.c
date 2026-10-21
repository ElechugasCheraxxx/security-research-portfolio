/* RVA 0x40d69  tam 112 B  addr 0x140040d69 */

int64_t fcn.140040d69(int64_t arg1,int64_t arg2)

{
    int64_t iVar1;
    uchar *puVar2;
    uint32_t uVar3;
    int64_t aiStack_30 [2];
    uchar auStack_20 [32];
    
    uVar3 = 0;
    puVar2 = &stack0xffffffffffffffe0;
    do {
        *(puVar2 + -8) = 0x140040d84;
        iVar1 = func_0x0001400442fc(arg1,arg2);
        if (iVar1 != 0) {
            return iVar1;
        }
        if (arg2 == 0) {
            return 0;
        }
        if (*0x140056850 == 0) {
            return 0;
        }
        *(puVar2 + -8) = arg2;
        *(puVar2 + -0x10) = 0x140040da1;
        func_0x000140267482(uVar3);
        uVar3 = uVar3 + 1000;
        if (*0x140056850 < uVar3) {
            uVar3 = 0xffffffff;
        }
        puVar2 = puVar2 + -8;
    } while (uVar3 != 0xffffffff);
    return 0;
}
