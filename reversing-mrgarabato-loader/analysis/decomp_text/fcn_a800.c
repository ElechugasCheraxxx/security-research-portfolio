/* RVA 0xa800  tam 67 B  addr 0x14000a800 */

ulong fcn.14000a800(int64_t arg1,int64_t arg2)

{
    int64_t *piVar1;
    int iVar2;
    int64_t iVar3;
    
    iVar3 = -1;
    do {
        iVar3 = iVar3 + 1;
    } while (*(arg2 + iVar3) != '\0');
    piVar1 = arg1 + 0x10;
    if (0xf < *(arg1 + 0x18)) {
        arg1 = *arg1;
    }
    if (*piVar1 == iVar3) {
        iVar2 = func_0x000140015eb8(arg1);
        if (iVar2 == 0) {
            return 1;
        }
    }
    return 0;
}
