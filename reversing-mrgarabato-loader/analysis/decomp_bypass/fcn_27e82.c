/* RVA 0x27e82  tam 133 B  addr 0x140027e82 */

void fcn.140027e78(int64_t param_1,uint16_t *param_2)

{
    uint16_t uVar1;
    ulong *puVar2;
    int64_t arg2;
    int64_t arg1;
    ulong uVar3;
    ulong unaff_RBX;
    uint64_t uVar4;
    ulong unaff_RSI;
    
    func_0x00014016b326();
    *(param_1 + 0x485740cc) = *(param_1 + 0x485740cc) + '\x01';
    uVar4 = &stack0x00000000 - 0x30;
    *(uVar4 + 0x20) = 0xfffffffffffffffe;
    *(uVar4 + 0x48) = unaff_RBX;
    *(uVar4 + 0x50) = unaff_RSI;
    puVar2 = *(param_1 + 0x28);
    if (puVar2 != NULL) {
        uVar3 = *puVar2;
        *(uVar4 - 8) = 0x140027eb0;
        fcn.14003c52c(uVar3);
        *(uVar4 - 8) = 0x140027eb8;
        func_0x00014003c534(puVar2);
    }
    if (param_2 == NULL) {
        uVar3 = 0;
    }
    else {
        *(uVar4 - 8) = 0x140027ec7;
        arg1 = func_0x00014003c76c(0x10);
        *(uVar4 + 0x40) = arg1;
        uVar3 = 0;
        if (arg1 != 0) {
            uVar1 = *param_2;
            arg2 = *(param_2 + 4);
            *(uVar4 - 8) = 0x140027ee4;
            uVar3 = fcn.140023050(arg1,arg2,uVar1 >> 1);
        }
    }
    *(param_1 + 0x28) = uVar3;
    return;
}
