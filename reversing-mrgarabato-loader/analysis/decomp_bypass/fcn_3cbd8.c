/* RVA 0x3cbd8  tam 346 B  addr 0x14003cbd8 */

//WARNING: Possible PIC construction at 0x00014003cb6b: Changing call to branch
//WARNING: Removing unreachable block (ram,0x00014003cb70)
//WARNING: Removing unreachable block (ram,0x00014003cb76)

int fcn.14003cbd8(int64_t arg1,int64_t arg2)

{
    uint8_t uVar1;
    int iVar2;
    int iVar3;
    uint *puVar4;
    uint32_t uVar5;
    uint32_t uVar6;
    int64_t aiStack_28 [2];
    int64_t iStack_18;
    char cStack_10;
    
    if (*0x140056828 == 0) {
        if ((arg1 == 0) || (arg2 == 0)) {
            puVar4 = fcn.14003ef2c();
            *puVar4 = 0x16;
            fcn.14003eec4();
            return 0x7fffffff;
        }
code_r0x00014003cac7:
        do {
            uVar1 = *arg1;
            uVar6 = uVar1;
            arg1 = arg1 + 1;
            if (uVar1 - 0x41 < 0x1a) {
                uVar6 = uVar1 + 0x20;
            }
            uVar1 = *arg2;
            uVar5 = uVar1;
            arg2 = arg2 + 1;
            if (uVar1 - 0x41 < 0x1a) {
                uVar5 = uVar1 + 0x20;
            }
        } while ((uVar6 != 0) && (uVar6 == uVar5));
        return uVar6 - uVar5;
    }
    fcn.14003c53c(aiStack_28,0);
    if ((arg1 == 0) || (arg2 == 0)) {
        puVar4 = fcn.14003ef2c();
        *puVar4 = 0x16;
        fcn.14003eec4();
        if (cStack_10 != '\0') {
            *(iStack_18 + 200) = *(iStack_18 + 200) & 0xfffffffd;
        }
        iVar2 = 0x7fffffff;
    }
    else {
        if (*(aiStack_28[0] + 0x14) == 0) goto code_r0x00014003cac7;
        arg1 = arg1 - arg2;
        do {
            iVar2 = func_0x00014003cfb8(*(arg2 + arg1),aiStack_28);
            iVar3 = func_0x00014003cfb8(*arg2,aiStack_28);
            arg2 = arg2 + 1;
            if (iVar2 == 0) break;
        } while (iVar2 == iVar3);
        iVar2 = iVar2 - iVar3;
        if (cStack_10 != '\0') {
            *(iStack_18 + 200) = *(iStack_18 + 200) & 0xfffffffd;
        }
    }
    return iVar2;
}
