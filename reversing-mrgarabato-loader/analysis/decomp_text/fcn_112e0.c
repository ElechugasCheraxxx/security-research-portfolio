/* RVA 0x112e0  tam 213 B  addr 0x1400112e0 */

void fcn.1400112e0(int64_t arg1,int64_t arg2)

{
    uint64_t uVar1;
    uint64_t uVar2;
    char *pcVar4;
    char *pcVar3;
    uchar auStack_58 [32];
    uchar auStack_38 [8];
    int64_t iStack_30;
    char acStack_15 [5];
    uint64_t uStack_10;
    
    uStack_10 = *0x140020600 ^ auStack_58;
    pcVar3 = acStack_15 + 2;
    if (arg2 < 0) {
        uVar2 = -arg2;
        do {
            pcVar4 = pcVar3;
            pcVar3 = pcVar4 + -1;
            uVar1 = uVar2 / 10;
            *pcVar3 = uVar2 + uVar1 * -10 + '0';
            uVar2 = uVar1;
        } while (uVar1 != 0);
        pcVar3 = pcVar4 + -2;
        *pcVar3 = '-';
    }
    else {
        do {
            pcVar3 = pcVar3 + -1;
            uVar2 = arg2 / 10;
            *pcVar3 = arg2 + uVar2 * -10 + '0';
            arg2 = uVar2;
        } while (uVar2 != 0);
    }
    iStack_30 = arg1;
    func_0x0001400011e0(arg1,pcVar3,acStack_15 + 2,auStack_38);
    fcn.1400153c0(uStack_10 ^ auStack_58);
    return;
}
