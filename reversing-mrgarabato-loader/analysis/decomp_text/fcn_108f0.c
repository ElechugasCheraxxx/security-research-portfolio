/* RVA 0x108f0  tam 216 B  addr 0x1400108f0 */

int64_t fcn.1400108f0(int64_t arg1)

{
    int64_t iVar1;
    int64_t iVar2;
    int64_t iVar3;
    
    iVar1 = fcn.140014fbb();
    iVar2 = fcn.140014fb5();
    if (iVar1 == 10000000) {
        *arg1 = iVar2 * 100;
        return arg1;
    }
    if (iVar1 == 24000000) {
        iVar1 = iVar2 + SUB168(SEXT816(-0x4d0b03f86b6f730d) * SEXT816(iVar2),8);
        iVar3 = (iVar1 >> 0x18) - (iVar1 >> 0x3f);
        iVar1 = (iVar2 + iVar3 * -24000000) * 1000000000;
        iVar1 = SUB168(SEXT816(-0x4d0b03f86b6f730d) * SEXT816(iVar1),8) + iVar1;
        *arg1 = ((iVar1 >> 0x18) - (iVar1 >> 0x3f)) + iVar3 * 1000000000;
        return arg1;
    }
    *arg1 = ((iVar2 % iVar1) * 1000000000) / iVar1 + (iVar2 / iVar1) * 1000000000;
    return arg1;
}
