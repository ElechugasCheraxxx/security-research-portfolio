/* RVA 0x3c76  tam 189 B  addr 0x140003c76 */

//WARNING: Instruction at (ram,0x000140003d2c) overlaps instruction at (ram,0x000140003d2b)
//

void fcn.140003c76(int64_t arg1,int64_t arg2)

{
    code *pcVar1;
    int64_t iVar2;
    int64_t iVar3;
    uchar *puVar4;
    ulong unaff_RSI;
    uint64_t uVar5;
    uint64_t uStack_40;
    int64_t iStack_38;
    int64_t iStack_30;
    int64_t iStack_28;
    uchar auStack_20 [32];
    
    puVar4 = &stack0xffffffffffffffe0;
    *arg1 = 0x140018a30;
    if ((*(arg1 + 0x70) & 1) != 0) {
        iStack_30 = 0x140003c93;
        iStack_28 = arg2;
        iVar2 = fcn.1402acaf6();
        if (iVar2 == 0) {
            iStack_30 = 0x140003ca8;
            iVar2 = fcn.1402c630a(arg1);
            *(iVar2 + -0x75) = *(iVar2 + -0x75) + -1;
            return;
        }
        iStack_38 = 0x140003ca1;
        iStack_30 = arg1;
        iVar2 = fcn.14028998f();
        puVar4 = &stack0xffffffffffffffc8;
        uStack_40 = 0x140003cb5;
        iStack_38 = arg2;
        iVar3 = fcn.14016de8b(arg1);
        uVar5 = iVar2 - iVar3;
        uStack_40 = 0x140003cc0;
        iVar3 = fcn.140228e4d(arg1);
        iVar2 = iVar3;
        if (0xfff < uVar5) {
            iVar2 = *(iVar3 + -8);
            uVar5 = uVar5 + 0x27;
            if (0x1f < (iVar3 - iVar2) - 8U) {
                puVar4 = &stack0xffffffffffffffc0;
                uStack_40 = uVar5;
                goto code_r0x000140003ced;
            }
        }
        uStack_40 = 0x140003ced;
        fcn.140015008(iVar2,uVar5);
    }
code_r0x000140003ced:
    *(puVar4 + -8) = unaff_RSI;
    *(puVar4 + -0x10) = 0x140003cfe;
    fcn.14003b623(arg1,0,0,0);
    *(puVar4 + -0x10) = arg1;
    *(puVar4 + -0x18) = 0x140003d0c;
    fcn.14016e695(arg1,0,0);
    *(arg1 + 0x70) = *(arg1 + 0x70) & 0xfffffffe;
    *(arg1 + 0x68) = 0;
    *(puVar4 + 0x10) = 0x140003d2b;
    fcn.1402cddd3(arg1);
    *(puVar4 + 0x10) = 0x140003d32;
    fcn.14003984a();
    pcVar1 = swi(3);
    (*pcVar1)();
    return;
}
