/* RVA 0xc0b0  tam 215 B  addr 0x14000c0b0 */

void fcn.14000c0b0(int64_t arg1)

{
    int64_t iVar1;
    int iVar2;
    ulong uVar3;
    int64_t iVar5;
    int64_t iVar4;
    uchar auStack_168 [32];
    uint uStack_148;
    uchar auStack_144 [40];
    char acStack_11c [260];
    uint64_t uStack_18;
    
    uStack_18 = *0x140020600 ^ auStack_168;
    func_0x000140015eca(auStack_144,0,300);
    uStack_148 = 0x130;
    uVar3 = func_0x000140014e9d(2);
    iVar2 = func_0x000140014eaf(uVar3,&uStack_148);
    while (iVar2 != 0) {
        iVar5 = -1;
        do {
            iVar4 = iVar5 + 1;
            iVar1 = iVar5 + 1;
            iVar5 = iVar4;
        } while (acStack_11c[iVar1] != '\0');
        iVar5 = arg1;
        if (0xf < *(arg1 + 0x18)) {
            iVar5 = *arg1;
        }
        if ((*(arg1 + 0x10) == iVar4) && (iVar2 = func_0x000140015eb8(iVar5,acStack_11c), iVar2 == 0)) break;
        iVar2 = func_0x000140014eb5(uVar3,&uStack_148);
    }
    fcn.1400153c0(uStack_18 ^ auStack_168);
    return;
}
