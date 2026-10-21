/* RVA 0xd030  tam 302 B  addr 0x14000d030 */

void fcn.14000d030(int64_t arg1)

{
    code *pcVar1;
    int iVar2;
    int64_t iVar3;
    uchar *puVar4;
    ulong uStack_110;
    int64_t iStack_108;
    uchar auStack_f8 [24];
    ulong uStack_e0;
    uint uStack_d8;
    uint uStack_d0;
    ulong uStack_c8;
    ulong uStack_c0;
    uchar *puStack_b8;
    uchar *puStack_b0;
    uchar auStack_a8 [32];
    uint auStack_88 [2];
    ulong uStack_80;
    ulong uStack_78;
    ulong uStack_70;
    ulong uStack_68;
    ulong uStack_60;
    ulong uStack_58;
    ulong uStack_50;
    ulong uStack_48;
    ulong uStack_40;
    ulong uStack_38;
    ulong uStack_30;
    ulong uStack_28;
    uint64_t uStack_18;
    
    uStack_18 = *0x140020600 ^ &stack0xffffffffffffff08;
    auStack_88[0] = 0x68;
    uStack_80 = 0;
    uStack_78 = 0;
    uStack_50 = 0x100000000;
    uStack_48 = 0;
    uStack_70 = 0;
    uStack_68 = 0;
    uStack_60 = 0;
    uStack_58 = 0;
    uStack_40 = 0;
    uStack_38 = 0;
    uStack_30 = 0;
    uStack_28 = 0;
    puStack_b0 = &stack0xffffffffffffff58;
    puStack_b8 = &stack0xffffffffffffff78;
    uStack_c0 = 0;
    uStack_c8 = 0;
    uStack_d0 = 0x8000000;
    uStack_d8 = 0;
    puVar4 = &stack0xffffffffffffff00;
    iStack_108 = 0x14000d0ce;
    iVar2 = func_0x000140037d30(0,0,0,0);
    if (iVar2 == 0) {
        if (0xf < *(arg1 + 0x18)) {
            arg1 = *arg1;
        }
        uStack_d8 = 0;
        uStack_e0 = 0;
        iVar3 = 0;
        iStack_108 = 0x14000d113;
        func_0x0001402b1e03(0,"open",arg1,0);
        if (iVar3 == 0) {
            pcVar1 = swi(3);
            (*pcVar1)();
            return;
        }
    }
    else {
        uStack_110 = 0x14000d0dd;
        iStack_108 = arg1;
        uStack_110 = func_0x0001402870fe(puStack_b0);
        puVar4 = &stack0xfffffffffffffef0;
        func_0x0001401d0e06(puStack_b0);
    }
    *(puVar4 + -8) = 0x14000d12b;
    fcn.1400153c0(*(puVar4 + 0xe0) ^ puVar4);
    return;
}
