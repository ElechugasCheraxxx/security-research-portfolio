/* RVA 0x3e874  tam 15287 B  addr 0x14003e874 */

//WARNING: Control flow encountered bad instruction data

uint fcn.14003e874(void)

{
    uchar uVar1;
    uint32_t uVar2;
    code *pcVar3;
    uint in_EAX;
    int64_t iVar4;
    int64_t iVar5;
    int64_t *piVar6;
    int *piVar7;
    uint *unaff_RSI;
    int64_t iVar8;
    int64_t unaff_R12;
    uchar uVar9;
    
    if (*0x1400539e8 != -1) {
        func_0x0001401f84dc();
        in_EAX = *unaff_RSI;
        *0x1400539e8 = -1;
    }
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
                    return in_EAX;
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
