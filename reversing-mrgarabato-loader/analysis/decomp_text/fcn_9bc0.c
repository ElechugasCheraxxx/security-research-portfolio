/* RVA 0x9bc0  tam 78 B  addr 0x140009bc0 */

int64_t fcn.140009bc0(ulong noname_0,int64_t arg1,int64_t arg2)

{
    int64_t iVar1;
    int64_t iVar2;
    
    iVar1 = fcn.140014f73(arg2 & 0xffffffff);
    iVar2 = -1;
    *arg1 = 0;
    *(arg1 + 8) = 0;
    *(arg1 + 0x10) = 0;
    *(arg1 + 0x18) = 0;
    do {
        iVar2 = iVar2 + 1;
    } while (*(iVar1 + iVar2) != '\0');
    fcn.140001b90(arg1,iVar1);
    return arg1;
}
