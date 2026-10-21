/* RVA 0x9d72  tam 76 B  addr 0x140009d72 */

int64_t fcn.140009d72(ulong noname_0,int64_t arg1,int64_t arg2)

{
    int64_t iVar1;
    int64_t iVar2;
    
    iVar1 = fcn.14001a8a7(arg2 & 0xffffffff);
    iVar2 = -1;
    *arg1 = 0;
    *(arg1 + 8) = 0;
    *(arg1 + 0x10) = 0;
    *(arg1 + 0x18) = 0;
    do {
        iVar2 = iVar2 + 1;
    } while (*(iVar1 + iVar2) != '\0');
    fcn.140001bc0(arg1,iVar1);
    return arg1;
}
