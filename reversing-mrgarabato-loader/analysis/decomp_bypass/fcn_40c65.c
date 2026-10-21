/* RVA 0x40c65  tam 105 B  addr 0x140040c65 */

int64_t fcn.140040c65(int64_t arg1)

{
    uint32_t uVar1;
    int64_t iVar2;
    uchar *puVar3;
    uint64_t uVar4;
    uint32_t uVar5;
    uint64_t auStack_30 [2];
    uchar auStack_20 [32];
    
    uVar5 = 0;
    puVar3 = &stack0xffffffffffffffe0;
    while( true ) {
        uVar1 = *0x140056850;
        uVar4 = *0x140056850;
        *(puVar3 + -8) = 0x140040c80;
        iVar2 = fcn.14003f11c(arg1);
        if (iVar2 != 0) {
            return iVar2;
        }
        if (uVar1 == 0) break;
        *(puVar3 + -8) = uVar4;
        *(puVar3 + -0x10) = 0x140040c94;
        func_0x000140238087(uVar5);
        uVar5 = uVar5 + 1000;
        if (*0x140056850 < uVar5) {
            uVar5 = 0xffffffff;
        }
        puVar3 = puVar3 + -8;
        if (uVar5 == 0xffffffff) {
            return 0;
        }
    }
    return 0;
}
