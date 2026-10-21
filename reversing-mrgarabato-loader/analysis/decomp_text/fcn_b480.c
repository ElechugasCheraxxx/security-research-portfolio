/* RVA 0xb480  tam 56 B  addr 0x14000b480 */

int64_t fcn.14000b480(int64_t arg1,int64_t arg2)

{
    int64_t iVar1;
    
    *arg1 = 0;
    *(arg1 + 8) = 0;
    *(arg1 + 0x10) = 0;
    *(arg1 + 0x18) = 0;
    iVar1 = -1;
    do {
        iVar1 = iVar1 + 1;
    } while (*(arg2 + iVar1 * 2) != 0);
    fcn.140001c90();
    return arg1;
}
