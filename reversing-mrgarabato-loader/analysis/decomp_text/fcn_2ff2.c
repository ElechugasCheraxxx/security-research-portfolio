/* RVA 0x2ff2  tam 55 B  addr 0x140002ff2 */

int64_t fcn.140002ff0(int64_t arg1,int64_t arg2)

{
    int64_t iVar1;
    
    *arg1 = 0;
    *(arg1 + 8) = 0;
    *(arg1 + 0x10) = 0;
    *(arg1 + 0x18) = 0;
    iVar1 = -1;
    do {
        iVar1 = iVar1 + 1;
    } while (*(arg2 + iVar1) != '\0');
    fcn.140001b90();
    return arg1;
}
