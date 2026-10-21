/* RVA 0x44644  tam 123 B  addr 0x140044644 */

uint fcn.140044644(int64_t arg1,int64_t arg2,int64_t arg3,int64_t arg4)

{
    uint32_t uVar1;
    uint uVar2;
    int64_t iStack_28;
    int64_t iStack_20;
    int64_t iStack_18;
    char cStack_10;
    
    fcn.14003c53c(&iStack_28,arg1);
    if ((*((arg2 & 0xffU) + 0x1d + iStack_20) & arg4) == 0) {
        if (arg3 == 0) {
            uVar1 = 0;
        }
        else {
            uVar1 = *(*(iStack_28 + 0x140) + (arg2 & 0xffU) * 2) & arg3;
        }
        uVar2 = 0;
        if (uVar1 == 0) goto code_r0x00014004469c;
    }
    uVar2 = 1;
code_r0x00014004469c:
    if (cStack_10 != '\0') {
        *(iStack_18 + 200) = *(iStack_18 + 200) & 0xfffffffd;
    }
    return uVar2;
}
