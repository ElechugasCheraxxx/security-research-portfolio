/* RVA 0xd1e0  tam 141 B  addr 0x14000d1e0 */

void fcn.14000d1e0(int64_t arg1,int64_t arg2,int64_t arg3,int64_t arg4)

{
    int64_t iVar1;
    code *pcVar2;
    int64_t iVar3;
    uint64_t uVar4;
    
    if (*arg1 != 0) {
        fcn.14000aad0(*arg1,*(arg1 + 8),arg1);
        iVar1 = *arg1;
        uVar4 = *(arg1 + 0x10) - iVar1 & 0xffffffffffffffe0;
        iVar3 = iVar1;
        if (0xfff < uVar4) {
            iVar3 = *(iVar1 + -8);
            if (0x1f < (iVar1 - iVar3) - 8U) {
                fcn.140283053(iVar1 - iVar3,uVar4 + 0x27);
                pcVar2 = swi(3);
                (*pcVar2)();
                return;
            }
        }
        fcn.140015008(iVar3);
    }
    *arg1 = arg2;
    *(arg1 + 8) = arg3 * 0x20 + arg2;
    *(arg1 + 0x10) = arg4 * 0x20 + arg2;
    return;
}
