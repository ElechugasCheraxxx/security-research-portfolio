/* RVA 0x44e6c  tam 121 B  addr 0x140044e6c */

ulong fcn.140044e6c(int64_t arg1)

{
    uint uVar1;
    int iVar2;
    ulong uVar3;
    int iVar4;
    
    uVar3 = 0;
    if ((((*(arg1 + 0x18) & 3) == 2) && ((*(arg1 + 0x18) & 0x108) != 0)) && (iVar4 = *arg1 - *(arg1 + 0x10), 0 < iVar4)
       ) {
        uVar1 = fcn.140043e08(arg1);
        iVar2 = func_0x000140043a60(uVar1,*(arg1 + 0x10),iVar4);
        if (iVar2 == iVar4) {
            uVar3 = 0;
            if (*(arg1 + 0x18) < '\0') {
                *(arg1 + 0x18) = *(arg1 + 0x18) & 0xfffffffd;
            }
        }
        else {
            *(arg1 + 0x18) = *(arg1 + 0x18) | 0x20;
            uVar3 = 0xffffffff;
        }
    }
    *(arg1 + 8) = 0;
    *arg1 = *(arg1 + 0x10);
    return uVar3;
}
