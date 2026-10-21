/* RVA 0x423a4  tam 34 B  addr 0x1400423a4 */

//WARNING: Control flow encountered bad instruction data

ulong fcn.1400423a4(void)

{
    uchar uVar1;
    uint32_t uVar2;
    code *pcVar3;
    ulong in_RAX;
    int64_t iVar4;
    int64_t iVar5;
    int64_t *piVar6;
    int *piVar7;
    int64_t iVar8;
    int64_t unaff_R12;
    uchar uVar9;
    
    iVar8 = 0x24;
    piVar6 = 0x140053be0;
    iVar4 = 0x24;
    while ((iVar5 = *piVar6, iVar5 == 0 ||
           (uVar2 = piVar6[1] - 1, uVar9 = (POPCOUNT(uVar2 & 0xff) & 1U) == 0, uVar2 == 0))) {
        piVar6 = piVar6 + 2;
        iVar4 = iVar4 + -1;
        if (iVar4 == 0) {
            piVar7 = 0x140053be8;
            while ((*(piVar7 + -2) == 0 || (*piVar7 != 1))) {
                piVar7 = piVar7 + 4;
                iVar8 = iVar8 + -1;
                if (iVar8 == 0) {
                    return in_RAX;
                }
            }
            func_0x000140029dba();
    //WARNING: Bad instruction - Truncating control flow here
            halt_baddata();
        }
    }
    iVar4 = func_0x000140287880();
    LOCK();
    uVar1 = *(iVar4 + -0x75);
    *(iVar4 + -0x75) = iVar5;
    UNLOCK();
    pcVar3 = swi(0xe8);
    iVar4 = (*pcVar3)(uVar1);
    if (uVar9) {
    //WARNING: Bad instruction - Truncating control flow here
        halt_baddata();
    }
    *(unaff_R12 + iVar4 * 8) = 0;
    return 0;
}
