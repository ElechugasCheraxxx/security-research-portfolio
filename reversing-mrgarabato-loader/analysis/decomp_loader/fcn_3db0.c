/* RVA 0x3db0  tam 198 B  addr 0x140003db0 */

//WARNING: Instruction at (ram,0x000140003de3) overlaps instruction at (ram,0x000140003de0)
//

void fcn.140003db0(ulong *param_1,int64_t param_2)

{
    uint8_t *puVar1;
    code *pcVar2;
    int64_t iVar3;
    uint64_t uVar4;
    uint64_t uVar5;
    int *piVar6;
    ulong *puVar7;
    uchar *puVar8;
    uchar *puVar9;
    uchar *puVar10;
    ulong *unaff_RBP;
    ulong unaff_RSI;
    char cVar11;
    ulong uStack_30;
    uchar auStack_28 [32];
    
    puVar9 = &stack0xffffffffffffffd8;
    *param_1 = 0x140022960;
    if ((*(param_1 + 0xe) & 1) != 0) {
        puVar8 = &stack0xffffffffffffffd0;
        uStack_30 = 0x140022960;
        iVar3 = func_0x0001406154aa();
        if (iVar3 == 0) {
            func_0x0001405c5e8d(param_1);
            puVar8 = 0x48cb8b48;
        }
        *(puVar8 + -8) = 0x140003de0;
        uVar4 = func_0x0001404db2ba();
        unaff_RSI = 0xa5e806eb;
        puVar1 = uVar4 * 2 + -0x44;
        *puVar1 = *puVar1 & param_1;
        puVar9 = puVar8 + -8;
        puVar10 = puVar8 + -8;
        *(puVar8 + -8) = param_1;
        *(puVar8 + -0x10) = 0x140003df5;
        uVar5 = func_0x00014003bd23(param_1);
        cVar11 = uVar4 < uVar5;
        *(puVar8 + -0x10) = 0x140003e00;
        puVar7 = param_1;
        piVar6 = func_0x0001405ff2a9();
        LOCK();
        *(piVar6 + -0x7f) = puVar7;
        UNLOCK();
        *piVar6 = *piVar6 + 1;
        *piVar6 = *piVar6 + piVar6 + cVar11;
        *(param_2 + 0x18) = *(param_2 + 0x18) + (param_2 >> 8);
        iVar3 = *(piVar6 + -2);
        if (0x1f < piVar6 + (-8 - iVar3)) goto code_r0x000140003e6c;
        *(puVar8 + -0x10) = 0x140003e2d;
        fcn.14001a940(iVar3,(uVar4 - uVar5) + 0x27);
    }
    *(puVar9 + -8) = param_1;
    *(puVar9 + -0x10) = 0x140003e3e;
    func_0x0001400453b5(param_1,0,0,0);
    *(puVar9 + -0x10) = unaff_RSI;
    *(puVar9 + -0x18) = 0x140003e4c;
    func_0x0001405eaf2a(param_1,0,0);
    *(param_1 + 0xe) = *(param_1 + 0xe) & 0xfffffffe;
    param_1[0xd] = 0;
    puVar10 = puVar9 + 0x10;
    *(puVar9 + 0x10) = *(puVar9 + 0x28);
    *(puVar9 + 8) = 0x140003e6c;
    func_0x0001406084a6(param_1);
code_r0x000140003e6c:
    *(puVar10 + -8) = 0x140003e71;
    func_0x0001404fad47();
    puVar7 = puVar10 + -8;
    *(puVar10 + -8) = unaff_RBP;
    cVar11 = '\v';
    do {
        unaff_RBP = unaff_RBP + -1;
        puVar7 = puVar7 + -1;
        *puVar7 = *unaff_RBP;
        cVar11 = cVar11 + -1;
    } while ('\0' < cVar11);
    *(puVar10 + -0x68) = puVar10 + -8;
    pcVar2 = swi(3);
    (*pcVar2)();
    return;
}
