/* RVA 0x3f748  tam 77 B  addr 0x14003f748 */

void fcn.14003f748(int64_t arg1,int64_t arg2,int64_t arg3,int64_t arg4)

{
    uint32_t uVar1;
    uint64_t uVar2;
    
    uVar2 = arg2 & 0xffffffff;
    do {
        uVar1 = uVar2 - 1;
        uVar2 = uVar1;
        fcn.14003f70c(arg1 & 0xffff,arg3,arg4);
        if (*arg4 == -1) {
            return;
        }
    } while (0 < uVar1);
    return;
}
