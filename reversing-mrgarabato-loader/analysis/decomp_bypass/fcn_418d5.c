/* RVA 0x418d5  tam 223 B  addr 0x1400418d5 */

ulong fcn.1400418d5(void)

{
    int16_t iVar1;
    char cVar2;
    int iVar3;
    int16_t *piVar4;
    int64_t iVar5;
    ulong uVar6;
    uint8_t uVar7;
    int16_t *piVar9;
    int16_t *piVar8;
    ulong *puVar10;
    ulong *unaff_RBP;
    ulong uStack_50;
    
    piVar4 = func_0x0001402d8f52();
    if (piVar4 != NULL) {
        iVar1 = *piVar4;
        piVar8 = piVar4;
        while (iVar1 != 0) {
            do {
                piVar9 = piVar8;
                piVar8 = piVar9 + 1;
            } while (*piVar8 != 0);
            piVar8 = piVar9 + 2;
            iVar1 = *piVar8;
        }
        iVar3 = piVar8 - piVar4 >> 1;
        uVar7 = 0;
        iVar5 = func_0x0001402ad1e0(0,0,piVar4,iVar3 + 1);
        func_0x00019178d9c2(uVar7 ^ *(iVar5 + 99));
        iVar5 = func_0x000140040c50();
        if (iVar5 != 0) {
            iVar3 = func_0x00014024be93(0,0,piVar4,iVar3 + 1);
            if (iVar3 == 0) {
                fcn.14003dc60(iVar5);
            }
            uVar6 = func_0x000140186abf(piVar4);
            puVar10 = &stack0xffffffffffffffb8;
            cVar2 = '\x05';
            do {
                unaff_RBP = unaff_RBP + -1;
                puVar10 = puVar10 + -1;
                *puVar10 = *unaff_RBP;
                cVar2 = cVar2 + -1;
            } while ('\0' < cVar2);
            return uVar6;
        }
        func_0x0001402e9ea0(piVar4);
    }
    return 0;
}
