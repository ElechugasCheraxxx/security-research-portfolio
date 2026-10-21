/* RVA 0x40ce5  tam 110 B  addr 0x140040ce5 */

int64_t fcn.140040ce5(int64_t arg1,int64_t arg2)

{
    int64_t iVar1;
    int64_t iVar2;
    uchar *puVar3;
    uint32_t uVar4;
    int64_t aiStack_30 [2];
    uchar auStack_20 [32];
    
    uVar4 = 0;
    puVar3 = &stack0xffffffffffffffe0;
    while( true ) {
        *(puVar3 + -8) = 0x140040d03;
        iVar2 = arg2;
        iVar1 = func_0x000140044260(arg1,arg2,0);
        if (iVar1 != 0) {
            return iVar1;
        }
        if (*0x140056850 == 0) break;
        *(puVar3 + -8) = iVar2;
        *(puVar3 + -0x10) = 0x140040d1b;
        func_0x0001406abbb3(uVar4);
        uVar4 = uVar4 + 1000;
        if (*0x140056850 < uVar4) {
            uVar4 = 0xffffffff;
        }
        puVar3 = puVar3 + -8;
        if (uVar4 == 0xffffffff) {
            return 0;
        }
    }
    return 0;
}
