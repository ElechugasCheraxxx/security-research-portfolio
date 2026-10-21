/* RVA 0x3c845  tam 257 B  addr 0x14003c845 */

int fcn.14003c845(int64_t arg1,int64_t arg2,int64_t arg3,int64_t arg4)

{
    uint16_t uVar1;
    int iVar2;
    uint *puVar3;
    uint16_t uVar4;
    int64_t aiStack_20 [2];
    int64_t iStack_10;
    char cStack_8;
    
    iVar2 = 0;
    if (arg3 != 0) {
        if ((arg1 == 0) || (arg2 == 0)) {
            puVar3 = fcn.14003ef2c();
            *puVar3 = 0x16;
            fcn.14003eec4();
            iVar2 = 0x7fffffff;
        }
        else {
            fcn.14003c53c(aiStack_20,arg4);
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
                    arg3 = arg3 + -1;
                } while (((arg3 != 0) && (uVar4 != 0)) && (uVar4 == uVar1));
            }
            else {
                do {
                    uVar4 = func_0x00014003ebf4(*arg1,aiStack_20);
                    uVar1 = func_0x00014003ebf4(*arg2,aiStack_20);
                    arg1 = arg1 + 2;
                    arg2 = arg2 + 2;
                    arg3 = arg3 + -1;
                    if ((arg3 == 0) || (uVar4 == 0)) break;
                } while (uVar4 == uVar1);
            }
            iVar2 = uVar4 - uVar1;
            if (cStack_8 != '\0') {
                *(iStack_10 + 200) = *(iStack_10 + 200) & 0xfffffffd;
            }
        }
    }
    return iVar2;
}
