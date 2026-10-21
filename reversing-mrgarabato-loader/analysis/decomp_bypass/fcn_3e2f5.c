/* RVA 0x3e2f5  tam 457 B  addr 0x14003e2f5 */

int fcn.14003e2f5(int64_t arg1)

{
    int64_t iVar1;
    int *piVar2;
    int iVar3;
    int iVar4;
    int64_t iVar5;
    int *arg1_00;
    uint *puVar6;
    int iVar7;
    
    iVar4 = -1;
    iVar5 = func_0x00014003e9d8();
    func_0x00014003df1c();
    iVar1 = *(iVar5 + 0xb8);
    iVar3 = fcn.14003dfd8(arg1 & 0xffffffff);
    if (iVar3 == *(iVar1 + 4)) {
        iVar4 = 0;
    }
    else {
        arg1_00 = func_0x000140040c50(0x220);
        iVar7 = 0;
        if (arg1_00 != NULL) {
            fcn.140041d50(arg1_00,*(iVar5 + 0xb8),0x220);
            *arg1_00 = 0;
            iVar4 = func_0x00014003e068(iVar3,arg1_00);
            if (iVar4 == 0) {
                piVar2 = *(iVar5 + 0xb8);
                LOCK();
                *piVar2 = *piVar2 + -1;
                UNLOCK();
                if ((*piVar2 == 0) && (*(iVar5 + 0xb8) != 0x140053070)) {
                    fcn.14003dc60(*(iVar5 + 0xb8));
                }
                *(iVar5 + 0xb8) = arg1_00;
                LOCK();
                *arg1_00 = *arg1_00 + 1;
                UNLOCK();
                if (((*(iVar5 + 200) & 2) == 0) && ((*0x1400535a0 & 1) == 0)) {
                    func_0x00014004252c(0xd);
                    *0x140056814 = arg1_00[1];
                    *0x140056818 = arg1_00[2];
                    *0x14005681c = arg1_00[3];
                    for (iVar3 = 0; iVar3 < 5; iVar3 = iVar3 + 1) {
                        *(iVar3 * 2 + 0x140056808) = *(arg1_00 + iVar3 * 2 + 0x10);
                    }
                    for (iVar3 = 0; iVar3 < 0x101; iVar3 = iVar3 + 1) {
                        *(iVar3 + 0x140053290) = *(iVar3 + 0x1c + arg1_00);
                    }
                    for (; piVar2 = *0x1400534a0, iVar7 < 0x100; iVar7 = iVar7 + 1) {
                        *(iVar7 + 0x1400533a0) = *(iVar7 + 0x11d + arg1_00);
                    }
                    LOCK();
                    **0x1400534a0 = **0x1400534a0 + -1;
                    UNLOCK();
                    if ((*piVar2 == 0) && (*0x1400534a0 != 0x140053070)) {
                        fcn.14003dc60(*0x1400534a0);
                    }
                    LOCK();
                    *0x1400534a0 = arg1_00;
                    *arg1_00 = *arg1_00 + 1;
                    UNLOCK();
                    fcn.14004242c(0xd);
                }
            }
            else if (iVar4 == -1) {
                if (arg1_00 != 0x140053070) {
                    fcn.14003dc60(arg1_00);
                }
                puVar6 = fcn.14003ef2c();
                *puVar6 = 0x16;
            }
        }
    }
    return iVar4;
}
