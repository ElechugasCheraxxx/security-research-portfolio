/* RVA 0xb526  tam 200 B  addr 0x14000b526 */

int64_t fcn.14000b526(int64_t arg1,int64_t arg2,int64_t arg3)

{
    code *pcVar1;
    uint64_t uVar2;
    int64_t iVar3;
    int64_t aiStack_30 [6];
    
    aiStack_30[2] = 0;
    aiStack_30[3] = 0;
    aiStack_30[4] = 0;
    aiStack_30[5] = 0;
    iVar3 = -1;
    do {
        iVar3 = iVar3 + 1;
    } while (*(arg3 + iVar3) != '\0');
    aiStack_30[0] = arg1;
    fcn.140001b90(aiStack_30 + 2,arg3);
    aiStack_30[0] = CONCAT44(aiStack_30[0]._4_4_,arg2);
    aiStack_30[1] = 0x140020130;
    fcn.1400037e0(arg1,aiStack_30,aiStack_30 + 2);
    if (0xf < aiStack_30[5]) {
        uVar2 = aiStack_30[5] + 1;
        iVar3 = aiStack_30[2];
        if (0xfff < uVar2) {
            uVar2 = aiStack_30[5] + 0x28;
            iVar3 = *(aiStack_30[2] + -8);
            if (0x1f < (aiStack_30[2] - iVar3) - 8U) {
                fcn.14013b01c();
                pcVar1 = swi(3);
                iVar3 = (*pcVar1)();
                return iVar3;
            }
        }
        fcn.140015008(iVar3,uVar2);
    }
    *arg1 = 0x140019060;
    return arg1;
}
