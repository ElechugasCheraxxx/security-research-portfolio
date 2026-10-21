/* RVA 0x3c5f0  tam 242 B  addr 0x14003c5f0 */

int fcn.14003c5f0(int64_t arg1,int64_t arg2,int64_t arg3)

{
    uint16_t uVar1;
    int iVar2;
    int64_t in_RAX;
    uint *puVar3;
    uint16_t uVar4;
    int64_t aiStack_20 [2];
    int64_t iStack_10;
    char cStack_8;
    
    fcn.14003c53c(in_RAX + -0x28,arg3);
    if ((arg1 == 0) || (arg2 == 0)) {
        puVar3 = fcn.14003ef2c();
        *puVar3 = 0x16;
        fcn.14003eec4();
        if (cStack_8 != '\0') {
            *(iStack_10 + 200) = *(iStack_10 + 200) & 0xfffffffd;
        }
        iVar2 = 0x7fffffff;
    }
    else {
        if (*(aiStack_20[0] + 0x14) == 0) {
            arg1 = arg1 - arg2;
            do {
                uVar4 = *(arg1 + arg2);
                if ((0x40 < uVar4) && (uVar4 < 0x5b)) {
                    uVar4 = uVar4 + 0x20;
                }
                uVar1 = *arg2;
                if ((0x40 < uVar1) && (uVar1 < 0x5b)) {
                    uVar1 = uVar1 + 0x20;
                }
                arg2 = arg2 + 2;
            } while ((uVar4 != 0) && (uVar4 == uVar1));
        }
        else {
            do {
                uVar4 = func_0x00014003ebf4(*arg1,aiStack_20);
                arg1 = arg1 + 2;
                uVar1 = func_0x00014003ebf4(*arg2,aiStack_20);
                arg2 = arg2 + 2;
                if (uVar4 == 0) break;
            } while (uVar4 == uVar1);
        }
        iVar2 = uVar4 - uVar1;
        if (cStack_8 != '\0') {
            *(iStack_10 + 200) = *(iStack_10 + 200) & 0xfffffffd;
        }
    }
    return iVar2;
}
