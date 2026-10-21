/* RVA 0x460a0  tam 81 B  addr 0x1400460a0 */

ulong fcn.1400460a0(int64_t arg1)

{
    int *piVar1;
    code *pcVar2;
    int64_t iVar3;
    ulong uVar4;
    
    piVar1 = *arg1;
    if ((*piVar1 == -0x1fbcbcae) || (*piVar1 == -0x1fbcb0b3)) {
        iVar3 = fcn.14003e9d8();
        if (0 < *(iVar3 + 0x100)) {
            iVar3 = fcn.14003e9d8();
            *(iVar3 + 0x100) = *(iVar3 + 0x100) + -1;
        }
    }
    else if (*piVar1 == -0x1f928c9d) {
        iVar3 = fcn.14003e9d8();
        *(iVar3 + 0x100) = 0;
        fcn.14003f210();
        pcVar2 = swi(3);
        uVar4 = (*pcVar2)();
        return uVar4;
    }
    return 0;
}
