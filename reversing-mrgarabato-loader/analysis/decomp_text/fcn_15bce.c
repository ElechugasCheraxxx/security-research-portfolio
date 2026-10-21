/* RVA 0x15bce  tam 91 B  addr 0x140015bce */

ulong fcn.140015bc8(int64_t arg1)

{
    int *piVar1;
    code *pcVar2;
    ulong *puVar3;
    ulong uVar4;
    
    piVar1 = *arg1;
    if ((*piVar1 == -0x1f928c9d) && (piVar1[6] == 4)) {
        if ((piVar1[8] + 0xe66cfae0U < 3) || (piVar1[8] == 0x1994000)) {
            puVar3 = func_0x000140015edc();
            *puVar3 = piVar1;
            uVar4 = *(arg1 + 8);
            puVar3 = func_0x000140015ee2();
            *puVar3 = uVar4;
            func_0x000140015f7e();
            pcVar2 = swi(3);
            uVar4 = (*pcVar2)();
            return uVar4;
        }
    }
    return 0;
}
