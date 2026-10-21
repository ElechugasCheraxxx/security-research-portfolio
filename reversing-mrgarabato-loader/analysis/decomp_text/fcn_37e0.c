/* RVA 0x37e0  tam 435 B  addr 0x1400037e0 */

int64_t fcn.1400037e0(int64_t arg1,int64_t arg2,int64_t arg3)

{
    code *pcVar1;
    uint64_t uVar2;
    int64_t *piVar3;
    int64_t *arg1_00;
    int64_t *piVar4;
    int64_t iVar5;
    ulong ****ppppuVar6;
    uint64_t uVar7;
    ulong ****appppuStack_90 [2];
    ulong uStack_80;
    uint64_t uStack_78;
    int64_t iStack_70;
    int64_t iStack_68;
    int64_t iStack_60;
    uint64_t uStack_58;
    uchar auStack_50 [56];
    
    arg1_00 = func_0x000140002ed0(auStack_50,arg3);
    uVar2 = *arg2;
    piVar3 = *(arg2 + 8);
    iVar5 = arg1_00[2];
    if (iVar5 != 0) {
        if (arg1_00[3] - iVar5 < 2) {
            fcn.140002490(arg1_00,2,0,0x140018958);
        }
        else {
            arg1_00[2] = iVar5 + 2;
            piVar4 = arg1_00;
            if (0xf < arg1_00[3]) {
                piVar4 = *arg1_00;
            }
            *(piVar4 + iVar5) = 0x203a;
            *(piVar4 + iVar5 + 2) = 0;
        }
    }
    (**(*piVar3 + 0x10))(piVar3,appppuStack_90,uVar2 & 0xffffffff);
    ppppuVar6 = appppuStack_90;
    if (0xf < uStack_78) {
        ppppuVar6 = appppuStack_90[0];
    }
    fcn.140009420(arg1_00,ppppuVar6,uStack_80);
    if (0xf < uStack_78) {
        if (0xfff < uStack_78 + 1) {
            if (0x1f < appppuStack_90[0] + (-8 - appppuStack_90[0][-1])) {
                func_0x000140136a73();
                pcVar1 = swi(3);
                iVar5 = (*pcVar1)();
                return iVar5;
            }
        }
        fcn.140015008();
    }
    iStack_70 = *arg1_00;
    iStack_68 = arg1_00[1];
    iStack_60 = arg1_00[2];
    uStack_58 = arg1_00[3];
    arg1_00[2] = 0;
    arg1_00[3] = 0xf;
    *arg1_00 = 0;
    func_0x000140003b20(arg1,&iStack_70);
    if (0xf < uStack_58) {
        uVar7 = uStack_58 + 1;
        iVar5 = iStack_70;
        if (0xfff < uVar7) {
            uVar7 = uStack_58 + 0x28;
            iVar5 = *(iStack_70 + -8);
            if (0x1f < (iStack_70 - iVar5) - 8U) {
                func_0x00014025b026();
                pcVar1 = swi(3);
                iVar5 = (*pcVar1)();
                return iVar5;
            }
        }
        fcn.140015008(iVar5,uVar7);
    }
    *arg1 = 0x140018948;
    *(arg1 + 0x18) = uVar2;
    *(arg1 + 0x20) = piVar3;
    return arg1;
}
