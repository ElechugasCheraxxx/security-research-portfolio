/* RVA 0x2e82  tam 73 B  addr 0x140002e82 */

int fcn.140002e82(int64_t arg1,int64_t arg2)

{
    int iVar1;
    ulong *puVar2;
    
    puVar2 = fcn.14000a570();
    iVar1 = fcn.14025dd96(*puVar2,arg1,7,arg2);
    if (iVar1 < 0) {
        iVar1 = -1;
    }
    return iVar1;
}
