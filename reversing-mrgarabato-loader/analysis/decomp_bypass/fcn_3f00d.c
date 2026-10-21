/* RVA 0x3f00d  tam 232 B  addr 0x14003f00d */

//WARNING: Instruction at (ram,0x00014003f074) overlaps instruction at (ram,0x00014003f073)
//

int64_t fcn.14003eff8(int64_t arg1)

{
    ulong uVar1;
    uint uVar2;
    uint64_t uVar3;
    uint *puVar4;
    int64_t iVar5;
    ulong in_RDX;
    uint64_t uVar6;
    int64_t iVar7;
    uchar *puVar8;
    uchar *puVar9;
    uchar *puVar10;
    uint64_t unaff_RSI;
    int64_t unaff_RDI;
    uint *unaff_R12;
    uchar uVar11;
    uchar auStack_38 [32];
    
    uVar11 = SBORROW8(&stack0xffffffffffffffe8,0x20);
    puVar10 = &stack0xffffffffffffffc8;
    func_0x000140040e30();
    uVar3 = func_0x00014026ab25(*0x140058af0);
    uVar1 = *0x140058ae8;
    if (uVar11) {
        uVar6 = in_RDX + uVar3;
code_r0x00014003f073:
        if (uVar6 + uVar3 < uVar3) {
code_r0x00014003f08e:
            iVar7 = 0;
            if (unaff_RSI + 0x20 < unaff_RSI) goto code_r0x00014003f0e0;
            *(puVar10 + -8) = 0x14003f09f;
            iVar5 = func_0x000140040d54();
            if (iVar5 == 0) goto code_r0x00014003f0e0;
        }
        else {
            *(puVar10 + -8) = 0x14003f083;
            iVar5 = func_0x000140040d54();
            if (iVar5 == 0) goto code_r0x00014003f08e;
        }
        puVar4 = iVar5 + (unaff_RDI >> 3) * 8;
        *(puVar10 + -8) = iVar5;
        *(puVar10 + -0x10) = 0x14003f0b5;
        *0x140058af0 = fcn.1402a6706();
        puVar9 = puVar10;
    }
    else {
        puVar8 = uVar3 & 0xffffffff;
        puVar10 = puVar8 + -8;
        *(puVar8 + -8) = in_RDX;
        *(puVar8 + -0x10) = 0x14003f037;
        puVar4 = func_0x00014011f210(uVar1);
        if (puVar4 < unaff_R12) {
code_r0x00014003f0de:
            iVar7 = 0;
            goto code_r0x00014003f0e0;
        }
        unaff_RDI = puVar4 - unaff_R12;
        if (unaff_RDI + 8U < 8) goto code_r0x00014003f0de;
        *(puVar8 + -0x10) = 0x14003f05f;
        uVar3 = func_0x000140042ce8();
        unaff_RSI = uVar3;
        puVar9 = puVar8;
        if (uVar3 < unaff_RDI + 8U) {
            uVar6 = 0x1000;
            puVar10 = puVar8 + -8;
            if (uVar3 < 0x1000) {
                uVar6 = uVar3;
                puVar10 = puVar8 + -8;
            }
            goto code_r0x00014003f073;
        }
    }
    *(puVar9 + -0x10) = 0x14003f0c4;
    fcn.1401716ad(arg1);
    uVar2 = in(0x48);
    *puVar4 = uVar2;
    puVar10 = puVar9 + -0x10;
    *(puVar9 + -0x10) = unaff_RSI;
    *(puVar9 + -0x18) = 0x14003f0d2;
    *0x140058ae8 = fcn.14022d4ef(puVar4 + 2);
    iVar7 = arg1;
code_r0x00014003f0e0:
    *(puVar10 + -8) = 0x14003f0e5;
    fcn.140040e3c();
    return iVar7;
}
