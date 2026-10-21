/* RVA 0x3cf1a  tam 131 B  addr 0x14003cf1a */

uint32_t fcn.14003cf18(int64_t arg1)

{
    uint32_t uVar1;
    int64_t aiStack_28 [2];
    int64_t iStack_18;
    char cStack_10;
    
    if (*0x140056828 == 0) {
        uVar1 = *(*0x1400539b0 + arg1 * 2) & 0x107;
    }
    else {
        fcn.14003c53c(aiStack_28,0);
        if (*(aiStack_28[0] + 0x10c) < 2) {
            uVar1 = *(*(aiStack_28[0] + 0x140) + arg1 * 2) & 0x107;
        }
        else {
            uVar1 = func_0x000140040384(arg1 & 0xffffffff,0x107,aiStack_28);
        }
        if (cStack_10 != '\0') {
            *(iStack_18 + 200) = *(iStack_18 + 200) & 0xfffffffd;
        }
    }
    return uVar1;
}
