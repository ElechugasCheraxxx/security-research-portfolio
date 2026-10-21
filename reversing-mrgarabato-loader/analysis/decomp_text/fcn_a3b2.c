/* RVA 0xa3b2  tam 197 B  addr 0x14000a3b2 */

void fcn.14000a3b0(int64_t arg1,int64_t arg2)

{
    uint64_t uVar1;
    uint32_t uVar2;
    uint64_t uVar3;
    char *pcVar5;
    char *pcVar4;
    uchar auStack_58 [32];
    uchar auStack_38 [8];
    int64_t iStack_30;
    char acStack_15 [5];
    uint64_t uStack_10;
    
    uStack_10 = *0x140020600 ^ auStack_58;
    pcVar4 = acStack_15 + 2;
    uVar3 = arg2 & 0xffffffff;
    if (arg2 < 0) {
        uVar2 = -arg2;
        do {
            pcVar5 = pcVar4;
            pcVar4 = pcVar5 + -1;
            *pcVar4 = uVar2 + (uVar2 / 10) * -10 + '0';
            uVar2 = uVar2 / 10;
        } while (uVar2 != 0);
        pcVar4 = pcVar5 + -2;
        *pcVar4 = '-';
    }
    else {
        do {
            pcVar4 = pcVar4 + -1;
            uVar1 = uVar3 / 10;
            *pcVar4 = uVar3 + uVar1 * -10 + '0';
            uVar3 = uVar1;
        } while (uVar1 != 0);
    }
    iStack_30 = arg1;
    func_0x0001400011e0(arg1,pcVar4,acStack_15 + 2,auStack_38);
    fcn.1400153c0(uStack_10 ^ auStack_58);
    return;
}
