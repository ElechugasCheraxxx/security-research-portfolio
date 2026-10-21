/* RVA 0x4081a  tam 71 B  addr 0x14004081a */

uint16_t fcn.140040818(int64_t arg1)

{
    uint16_t uVar1;
    int64_t aiStack_28 [2];
    int64_t iStack_18;
    char cStack_10;
    
    fcn.14003c53c(aiStack_28,0);
    uVar1 = *(*(aiStack_28[0] + 0x140) + (arg1 & 0xffU) * 2);
    if (cStack_10 != '\0') {
        *(iStack_18 + 200) = *(iStack_18 + 200) & 0xfffffffd;
    }
    return uVar1 & 0x8000;
}
