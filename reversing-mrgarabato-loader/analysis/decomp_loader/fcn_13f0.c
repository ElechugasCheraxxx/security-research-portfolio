/* RVA 0x13f0  tam 397 B  addr 0x1400013f0 */

//WARNING: Control flow encountered bad instruction data

uint64_t fcn.1400013f0(ulong param_1,ulong param_2)

{
    uint64_t uVar1;
    uint32_t uVar2;
    int iVar3;
    int64_t in_RAX;
    uint64_t uVar4;
    uint64_t uVar5;
    int64_t iVar6;
    uint64_t unaff_RBX;
    uchar *puVar7;
    uchar *puVar8;
    uint32_t *unaff_RSI;
    uchar unaff_R12B;
    ulong auStack_28 [3];
    
    puVar7 = &stack0xfffffffffffffff8;
    if (in_RAX < 2) {
        uVar4 = unaff_RBX;
    }
    else {
        puVar7 = &stack0xfffffffffffffff0;
        iVar6 = func_0x0001404af2f6(*(*unaff_RSI + 4) + unaff_RSI);
        uVar4 = iVar6 - 1;
    }
    iVar3 = *(*unaff_RSI + 4);
    *(puVar7 + -8) = param_2;
    *(puVar7 + -0x10) = 0x140001420;
    uVar2 = func_0x00014060bd4b(iVar3 + unaff_RSI);
    if ((uVar2 & 0x1c0) != 0x40) {
        puVar8 = puVar7 + -8;
        if (unaff_RBX != 0) goto code_r0x0001400014fe;
        if (0 < uVar4) {
            iVar3 = *(*unaff_RSI + 4);
            *(puVar7 + -0x10) = *unaff_RSI;
            *(puVar7 + -0x18) = 0x14000144d;
            func_0x0001404e8779(iVar3 + unaff_RSI);
            iVar3 = *(*unaff_RSI + 4);
            *(puVar7 + -0x18) = 0x14000145f;
            uVar4 = func_0x00014050e24b(iVar3 + unaff_RSI);
            return uVar4;
        }
    }
    iVar3 = *(*unaff_RSI + 4);
    *(puVar7 + -0x10) = param_2;
    *(puVar7 + -0x18) = 0x140001492;
    uVar5 = func_0x0001404face2(iVar3 + unaff_RSI);
    *(puVar7 + -0x18) = 0x14000149e;
    iVar3 = func_0x00014053f3e6(uVar5,unaff_R12B);
    *(uVar5 + 4) = *(uVar5 + 4) - (unaff_RBX >> 8);
    uVar1 = unaff_RBX;
    if (iVar3 == -1) {
        uVar1 = uVar5;
    }
    unaff_RBX = uVar1 & 0xffffffff;
    *(puVar7 + 0x60) = uVar1;
    puVar8 = puVar7 + -0x10;
    if ((uVar1 == 0) && (puVar8 = puVar7 + -0x10, 0 < uVar4)) {
        iVar3 = *(*unaff_RSI + 4);
        *(puVar7 + -0x18) = 0x1400014c8;
        func_0x0001404af2d8(iVar3 + unaff_RSI);
    //WARNING: Bad instruction - Truncating control flow here
        halt_baddata();
    }
code_r0x0001400014fe:
    iVar6 = *(*unaff_RSI + 4) + unaff_RSI;
    *(puVar8 + -8) = 0x14000151f;
    func_0x00014003d08b(iVar6,0);
    if (iVar6 == 1) {
        iVar3 = *(*unaff_RSI + 4);
        *(puVar8 + -8) = 0x140001534;
        func_0x0001406008e1(iVar3 + unaff_RSI,unaff_RBX & 0xffffffff,0);
    //WARNING: Bad instruction - Truncating control flow here
        halt_baddata();
    }
    return unaff_RSI & 0xffffffff;
}
