/* RVA 0x6bd0  tam 350 B  addr 0x140006bd0 */

void fcn.140006bd0(int64_t arg1,int64_t arg2)

{
    code *pcVar1;
    uint8_t extraout_AH;
    char *pcVar2;
    int64_t iVar3;
    int64_t iVar4;
    ulong ****ppppuVar5;
    uchar auStack_58 [40];
    ulong ****ppppuStack_30;
    ulong uStack_28;
    ulong uStack_20;
    uint64_t uStack_18;
    uint64_t uStack_10;
    
    uStack_10 = *0x14002f500 ^ auStack_58;
    if ((1 < *(arg1 + 0x10)) && (1 < *(arg2 + 0x10))) {
        iVar3 = arg1;
        if (0xf < *(arg1 + 0x18)) {
            iVar3 = *arg1;
        }
        iVar4 = *(arg1 + 0x10) - 1;
        if (*(iVar4 + iVar3) == '}') {
            pcVar2 = arg2;
            if (0xf < *(arg2 + 0x18)) {
                pcVar2 = *arg2;
            }
            if (*pcVar2 == '{') {
                *(arg1 + 0x10) = iVar4;
                iVar3 = arg1;
                if (0xf < *(arg1 + 0x18)) {
                    iVar3 = *arg1;
                }
                *(iVar3 + iVar4) = 0;
                ppppuStack_30 = NULL;
                uStack_28 = 0;
                uStack_20 = 0;
                uStack_18 = 0;
                if (*(arg2 + 0x10) == 0) {
                    func_0x000140009540();
                    pcVar1 = swi(3);
                    (*pcVar1)();
                    return;
                }
                iVar4 = *(arg2 + 0x10) + -1;
                iVar3 = -1;
                if (iVar4 != -1) {
                    iVar3 = iVar4;
                }
                if (0xf < *(arg2 + 0x18)) {
                    arg2 = *arg2;
                }
                fcn.140001bc0(&ppppuStack_30,arg2 + 1,iVar3);
                iVar3 = arg1;
                if (0xf < *(arg1 + 0x18)) {
                    iVar3 = *arg1;
                }
                if (*(*(arg1 + 0x10) + -1 + iVar3) != '{') {
                    func_0x0001400046e0(arg1,0x2c);
                }
                ppppuVar5 = &ppppuStack_30;
                if (0xf < uStack_18) {
                    ppppuVar5 = ppppuStack_30;
                }
                func_0x000140009560(arg1,ppppuVar5,uStack_20);
                if (0xf < uStack_18) {
                    ppppuVar5 = ppppuStack_30;
                    if (0xfff < uStack_18 + 1) {
                        ppppuVar5 = ppppuStack_30[-1];
                        if (0x1f < ppppuStack_30 + (-8 - ppppuVar5)) {
                            func_0x0001404aca11(ppppuVar5,uStack_18 + 0x28);
                            ppppuVar5 = ppppuVar5 | extraout_AH;
                        }
                    }
                    fcn.14001a940(ppppuVar5);
                }
            }
        }
    }
    func_0x00014001ad00(uStack_10 ^ auStack_58);
    return;
}
