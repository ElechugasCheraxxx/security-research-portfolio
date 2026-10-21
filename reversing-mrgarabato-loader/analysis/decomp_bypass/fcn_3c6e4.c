/* RVA 0x3c6e4  tam 394 B  addr 0x14003c6e4 */

int fcn.14003c6e4(int64_t arg1,int64_t arg2)

{
    uint16_t uVar1;
    int iVar2;
    uint *puVar3;
    uint16_t uVar4;
    int64_t aiStack_28 [2];
    int64_t iStack_18;
    char cStack_10;
    
    if (*0x140056828 == 0) {
        if ((arg1 != 0) && (arg2 != 0)) {
            arg1 = arg1 - arg2;
            do {
                uVar1 = *(arg1 + arg2);
                if ((0x40 < uVar1) && (uVar1 < 0x5b)) {
                    uVar1 = uVar1 + 0x20;
                }
                uVar4 = *arg2;
                if ((0x40 < uVar4) && (uVar4 < 0x5b)) {
                    uVar4 = uVar4 + 0x20;
                }
                arg2 = arg2 + 2;
            } while ((uVar1 != 0) && (uVar1 == uVar4));
            return uVar1 - uVar4;
        }
        puVar3 = fcn.14003ef2c();
        *puVar3 = 0x16;
        fcn.14003eec4();
        return 0x7fffffff;
    }
    fcn.14003c53c(aiStack_28,0);
    if ((arg1 == 0) || (arg2 == 0)) {
        puVar3 = fcn.14003ef2c();
        *puVar3 = 0x16;
        fcn.14003eec4();
        if (cStack_10 != '\0') {
            *(iStack_18 + 200) = *(iStack_18 + 200) & 0xfffffffd;
        }
        iVar2 = 0x7fffffff;
    }
    else {
        if (*(aiStack_28[0] + 0x14) == 0) {
            arg1 = arg1 - arg2;
            do {
                uVar1 = *(arg1 + arg2);
                if ((0x40 < uVar1) && (uVar1 < 0x5b)) {
                    uVar1 = uVar1 + 0x20;
                }
                uVar4 = *arg2;
                if ((0x40 < uVar4) && (uVar4 < 0x5b)) {
                    uVar4 = uVar4 + 0x20;
                }
                arg2 = arg2 + 2;
            } while ((uVar1 != 0) && (uVar1 == uVar4));
        }
        else {
            do {
                uVar1 = func_0x00014003ebf4(*arg1,aiStack_28);
                arg1 = arg1 + 2;
                uVar4 = func_0x00014003ebf4(*arg2,aiStack_28);
                arg2 = arg2 + 2;
                if (uVar1 == 0) break;
            } while (uVar1 == uVar4);
        }
        iVar2 = uVar1 - uVar4;
        if (cStack_10 != '\0') {
            *(iStack_18 + 200) = *(iStack_18 + 200) & 0xfffffffd;
        }
    }
    return iVar2;
}
