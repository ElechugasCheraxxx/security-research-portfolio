/* RVA 0x9e8b  tam 141 B  addr 0x140009e8b */

ulong fcn.140009e80(int64_t arg1,int64_t arg2)

{
    uint64_t uVar1;
    uint64_t uVar2;
    ulong uVar3;
    
    uVar1 = func_0x0001406a9f88();
    if (uVar1 != 0) {
        uVar2 = func_0x000140253e9d(arg1);
        if ((uVar2 < uVar1) && (((arg2 == -1 || (arg2 == *(uVar1 - 1))) || ((*(arg1 + 0x70) & 2) == 0)))) {
            uVar3 = func_0x000140151cc4(arg1,0xffffffff);
            return uVar3;
        }
    }
    return 0xffffffff;
}
