/* RVA 0x41aac  tam 464 B  addr 0x140041aac */

uint fcn.140041a9c(int64_t arg1,int64_t arg2)

{
    uint uVar1;
    int *piVar2;
    code *pcVar3;
    ulong uVar4;
    uint uVar5;
    int64_t iVar6;
    int *piVar7;
    int64_t iVar8;
    int64_t iVar9;
    
    iVar6 = fcn.14003e954();
    if (iVar6 != 0) {
        piVar2 = *(iVar6 + 0xa0);
        piVar7 = piVar2;
        do {
            if (*piVar7 == arg1) break;
            piVar7 = piVar7 + 4;
        } while (piVar7 < piVar2 + 0x30);
        if ((piVar2 + 0x30 <= piVar7) || (*piVar7 != arg1)) {
            piVar7 = NULL;
        }
        if ((piVar7 != NULL) && (pcVar3 = *(piVar7 + 2), pcVar3 != NULL)) {
            if (pcVar3 == 0x5) {
                piVar7[2] = 0;
                piVar7[3] = 0;
                return 1;
            }
            if (pcVar3 != 0x1) {
                uVar4 = *(iVar6 + 0xa8);
                *(iVar6 + 0xa8) = arg2;
                if (piVar7[1] == 8) {
                    iVar8 = 0x30;
                    do {
                        iVar9 = iVar8 + 0x10;
                        *(iVar8 + 8 + *(iVar6 + 0xa0)) = 0;
                        iVar8 = iVar9;
                    } while (iVar9 < 0xc0);
                    uVar1 = *(iVar6 + 0xb0);
                    if (*piVar7 == -0x3fffff72) {
                        *(iVar6 + 0xb0) = 0x83;
                    }
                    else if (*piVar7 == -0x3fffff70) {
                        *(iVar6 + 0xb0) = 0x81;
                    }
                    else if (*piVar7 == -0x3fffff6f) {
                        *(iVar6 + 0xb0) = 0x84;
                    }
                    else if (*piVar7 == -0x3fffff6d) {
                        *(iVar6 + 0xb0) = 0x85;
                    }
                    else if (*piVar7 == -0x3fffff73) {
                        *(iVar6 + 0xb0) = 0x82;
                    }
                    else if (*piVar7 == -0x3fffff71) {
                        *(iVar6 + 0xb0) = 0x86;
                    }
                    else if (*piVar7 == -0x3fffff6e) {
                        *(iVar6 + 0xb0) = 0x8a;
                    }
                    else if (*piVar7 == -0x3ffffd4b) {
                        *(iVar6 + 0xb0) = 0x8d;
                    }
                    else {
                        uVar5 = uVar1;
                        if (*piVar7 == -0x3ffffd4c) {
                            uVar5 = 0x8e;
                        }
                        *(iVar6 + 0xb0) = uVar5;
                    }
                    (*pcVar3)(8,*(iVar6 + 0xb0));
                    *(iVar6 + 0xb0) = uVar1;
                }
                else {
                    piVar7[2] = 0;
                    piVar7[3] = 0;
                    (*pcVar3)(piVar7[1]);
                }
                *(iVar6 + 0xa8) = uVar4;
            }
            return 0xffffffff;
        }
    }
    return 0;
}
