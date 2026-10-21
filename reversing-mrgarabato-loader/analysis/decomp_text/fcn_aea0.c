/* RVA 0xaea0  tam 121 B  addr 0x14000aea0 */

ulong * fcn.14000aea0(int64_t arg1,int64_t arg2,int64_t arg3,int64_t arg4)

{
    ulong *puVar1;
    ulong uVar2;
    int64_t iVar3;
    ulong *puVar4;
    
    if (arg1 != arg2) {
        iVar3 = arg3 - arg1;
        puVar4 = arg1 + 0x18;
        do {
            *arg3 = 0;
            *(arg3 + 8) = 0;
            *(puVar4 + iVar3 + -8) = 0;
            puVar1 = puVar4 + 1;
            *(puVar4 + iVar3) = 0;
            uVar2 = puVar4[-2];
            *arg3 = puVar4[-3];
            *(arg3 + 8) = uVar2;
            uVar2 = *puVar4;
            *(arg3 + 0x10) = puVar4[-1];
            *(arg3 + 0x18) = uVar2;
            puVar4[-1] = 0;
            arg3 = arg3 + 0x20;
            *puVar4 = 0xf;
            *(puVar4 + -3) = 0;
            puVar4 = puVar4 + 4;
        } while (puVar1 != arg2);
    }
    func_0x00014000aad0(arg3,arg3,arg4);
    return arg3;
}
