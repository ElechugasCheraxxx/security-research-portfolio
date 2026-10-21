/* RVA 0x9c10  tam 144 B  addr 0x140009c10 */

void fcn.140009c10(ulong noname_0,int64_t arg1,int64_t arg2)

{
    char *pcVar1;
    int64_t iVar2;
    uchar auStack_48 [40];
    char *pcStack_20;
    int64_t iStack_18;
    uint64_t uStack_10;
    
    uStack_10 = *0x140020600 ^ auStack_48;
    pcStack_20 = NULL;
    iStack_18 = func_0x000140014ed4(arg2 & 0xffffffff,&pcStack_20);
    *arg1 = 0;
    *(arg1 + 8) = 0;
    *(arg1 + 0x10) = 0;
    *(arg1 + 0x18) = 0;
    if (iStack_18 == 0) {
        pcVar1 = "unknown error";
        iVar2 = 0xd;
    }
    else {
        pcVar1 = pcStack_20;
        iVar2 = iStack_18;
    }
    fcn.140001b90(arg1,pcVar1,iVar2);
    func_0x000140014f6c(pcStack_20);
    fcn.1400153c0(uStack_10 ^ auStack_48);
    return;
}
