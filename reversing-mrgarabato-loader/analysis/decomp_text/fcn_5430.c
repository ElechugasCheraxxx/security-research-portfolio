/* RVA 0x5430  tam 798 B  addr 0x140005430 */

void fcn.140005430(int64_t arg1,int64_t arg2)

{
    int64_t *piVar1;
    uint8_t uVar2;
    int64_t iVar3;
    int64_t iVar4;
    uint8_t *puVar5;
    uint64_t uVar7;
    uint64_t uVar6;
    char *arg3;
    uchar auStack_50 [32];
    uint64_t uStack_30;
    uint uStack_20;
    int64_t iStack_18;
    char acStack_10 [8];
    uint64_t uStack_8;
    
    uStack_8 = *0x140020600 ^ auStack_50;
    *arg1 = 0;
    *(arg1 + 8) = 0;
    *(arg1 + 0x10) = 0;
    *(arg1 + 0x18) = 0xf;
    *arg1 = 0;
    uStack_20 = 1;
    piVar1 = arg2 + 0x10;
    iStack_18 = arg1;
    func_0x000140009f10(0,*piVar1 + 8);
    if (0xf < *(arg2 + 0x18)) {
        arg2 = *arg2;
    }
    puVar5 = arg2 + *piVar1;
    do {
        if (arg2 == puVar5) {
            fcn.1400153c0(uStack_8 ^ auStack_50);
            return;
        }
        uVar2 = *arg2;
        if (uVar2 == 9) {
            iVar4 = *(arg1 + 0x10);
            if (*(arg1 + 0x18) - iVar4 < 2) {
                arg3 = 0x140018b70;
code_r0x0001400056f5:
                uStack_30 = 2;
code_r0x000140005703:
                fcn.140002490(arg1,uStack_30,0,arg3);
            }
            else {
                *(arg1 + 0x10) = iVar4 + 2;
                iVar3 = arg1;
                if (0xf < *(arg1 + 0x18)) {
                    iVar3 = *arg1;
                }
                *(iVar3 + iVar4) = 0x745c;
                *(iVar3 + 2 + iVar4) = 0;
            }
        }
        else if (uVar2 == 10) {
            iVar4 = *(arg1 + 0x10);
            if (*(arg1 + 0x18) - iVar4 < 2) {
                arg3 = 0x140018b68;
                goto code_r0x0001400056f5;
            }
            *(arg1 + 0x10) = iVar4 + 2;
            iVar3 = arg1;
            if (0xf < *(arg1 + 0x18)) {
                iVar3 = *arg1;
            }
            *(iVar3 + iVar4) = 0x6e5c;
            *(iVar3 + 2 + iVar4) = 0;
        }
        else if (uVar2 == 0xd) {
            iVar4 = *(arg1 + 0x10);
            if (*(arg1 + 0x18) - iVar4 < 2) {
                arg3 = 0x140018b6c;
                goto code_r0x0001400056f5;
            }
            *(arg1 + 0x10) = iVar4 + 2;
            iVar3 = arg1;
            if (0xf < *(arg1 + 0x18)) {
                iVar3 = *arg1;
            }
            *(iVar3 + iVar4) = 0x725c;
            *(iVar3 + 2 + iVar4) = 0;
        }
        else if (uVar2 == 0x22) {
            iVar4 = *(arg1 + 0x10);
            if (*(arg1 + 0x18) - iVar4 < 2) {
                arg3 = 0x140018b64;
                goto code_r0x0001400056f5;
            }
            *(arg1 + 0x10) = iVar4 + 2;
            iVar3 = arg1;
            if (0xf < *(arg1 + 0x18)) {
                iVar3 = *arg1;
            }
            *(iVar3 + iVar4) = 0x225c;
            *(iVar3 + 2 + iVar4) = 0;
        }
        else if (uVar2 == 0x5c) {
            iVar4 = *(arg1 + 0x10);
            if (*(arg1 + 0x18) - iVar4 < 2) {
                arg3 = 0x140018b60;
                goto code_r0x0001400056f5;
            }
            *(arg1 + 0x10) = iVar4 + 2;
            iVar3 = arg1;
            if (0xf < *(arg1 + 0x18)) {
                iVar3 = *arg1;
            }
            *(iVar3 + iVar4) = 0x5c5c;
            *(iVar3 + 2 + iVar4) = 0;
        }
        else if (uVar2 < 0x20) {
            func_0x000140002e70(acStack_10,"\\u%04x");
            uVar7 = 0xffffffffffffffff;
            do {
                uVar6 = uVar7 + 1;
                iVar4 = uVar7 + 1;
                uVar7 = uVar6;
            } while (acStack_10[iVar4] != '\0');
            iVar4 = *(arg1 + 0x10);
            if (*(arg1 + 0x18) - iVar4 < uVar6) {
                arg3 = acStack_10;
                uStack_30 = uVar6;
                goto code_r0x000140005703;
            }
            *(arg1 + 0x10) = iVar4 + uVar6;
            iVar3 = arg1;
            if (0xf < *(arg1 + 0x18)) {
                iVar3 = *arg1;
            }
            fcn.140015ec4(iVar3 + iVar4,acStack_10,uVar6);
            *(iVar3 + iVar4 + uVar6) = 0;
        }
        else {
            uVar7 = *(arg1 + 0x10);
            if (uVar7 < *(arg1 + 0x18)) {
                *(arg1 + 0x10) = uVar7 + 1;
                iVar4 = arg1;
                if (0xf < *(arg1 + 0x18)) {
                    iVar4 = *arg1;
                }
                *(iVar4 + uVar7) = uVar2;
                *(iVar4 + 1 + uVar7) = 0;
            }
            else {
                fcn.140002bc0(arg1,1,0,uVar2);
            }
        }
        arg2 = arg2 + 1;
    } while( true );
}
