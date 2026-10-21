/* RVA 0x3e623  tam 377 B  addr 0x14003e623 */

void fcn.14003e618(int64_t arg1)

{
    int *piVar1;
    int iVar2;
    uint uVar3;
    uint *puVar4;
    int64_t iVar5;
    ulong *puVar6;
    
    if ((((*(arg1 + 0x128) != 0) && (*(arg1 + 0x128) != 0x140053e30)) && (*(arg1 + 0x110) != NULL)) &&
       (**(arg1 + 0x110) == 0)) {
        piVar1 = *(arg1 + 0x120);
        if ((piVar1 != NULL) && (*piVar1 == 0)) {
            fcn.14003dc60(piVar1);
            func_0x0001400429cc(*(arg1 + 0x128));
        }
        piVar1 = *(arg1 + 0x118);
        if ((piVar1 != NULL) && (*piVar1 == 0)) {
            fcn.14003dc60(piVar1);
            func_0x000140042960(*(arg1 + 0x128));
        }
        fcn.14003dc60(*(arg1 + 0x110));
        fcn.14003dc60(*(arg1 + 0x128));
    }
    if ((*(arg1 + 0x130) != NULL) && (**(arg1 + 0x130) == 0)) {
        fcn.14003dc60(*(arg1 + 0x138) + -0xfe);
        fcn.14003dc60(*(arg1 + 0x148) + -0x80);
        fcn.14003dc60(*(arg1 + 0x150) + -0x80);
        fcn.14003dc60(*(arg1 + 0x130));
    }
    if ((*(arg1 + 0x158) != 0x1400535b0) && (*(*(arg1 + 0x158) + 0x160) == 0)) {
        func_0x000140042570();
        fcn.14003dc60(*(arg1 + 0x158));
    }
    puVar6 = arg1 + 0x58;
    iVar5 = 6;
    do {
        if (((puVar6[-2] != 0x1400535a4) && (piVar1 = *puVar6, piVar1 != NULL)) && (*piVar1 == 0)) {
            fcn.14003dc60(piVar1);
        }
        if (((puVar6[-1] != 0) && (piVar1 = puVar6[1], piVar1 != NULL)) && (*piVar1 == 0)) {
            fcn.14003dc60(piVar1);
        }
        puVar6 = puVar6 + 4;
        iVar5 = iVar5 + -1;
    } while (iVar5 != 0);
    if ((arg1 != 0) && (iVar2 = fcn.14002e131(*0x1400569b8,0,arg1), iVar2 == 0)) {
        puVar4 = fcn.14003ef2c();
        uVar3 = fcn.1406b54b7();
        uVar3 = fcn.14003eee4(uVar3);
        *puVar4 = uVar3;
    }
    return;
}
