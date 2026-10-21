/* RVA 0x44ca9  tam 144 B  addr 0x140044ca9 */

uint32_t fcn.140044ca9(int64_t arg1,int64_t arg2)

{
    int *piVar1;
    int64_t iVar2;
    int iVar3;
    ulong uVar4;
    int64_t iVar5;
    uchar *puVar6;
    uint32_t uVar7;
    int64_t iVar8;
    ulong uStack_28;
    uchar auStack_20 [32];
    
    puVar6 = &stack0xffffffffffffffe0;
    iVar8 = arg1 >> 5;
    iVar5 = (arg1 & 0x1f) * 0x58;
    iVar2 = *(iVar8 * 8 + 0x1400588e0);
    uVar7 = 1;
    if (*(iVar5 + 0xc + iVar2) == 0) {
        uStack_28 = 0x140044cdd;
        uVar4 = fcn.14004252c(10);
        puVar6 = &stack0xffffffffffffffe0;
        if (*(iVar5 + 0xc + iVar2) == 0) {
            puVar6 = &stack0xffffffffffffffd8;
            uStack_28 = uVar4;
            iVar3 = func_0x0001406a42de(iVar5 + 0x10 + iVar2);
            arg2 = -(iVar3 != 0);
            uVar7 = -(iVar3 != 0) & 1;
            piVar1 = iVar5 + 0xc + iVar2;
            *piVar1 = *piVar1 + 1;
        }
        *(puVar6 + -8) = 0x140044d09;
        fcn.14004242c(10);
    }
    if (uVar7 != 0) {
        iVar2 = *(iVar8 * 8 + 0x1400588e0);
        *(puVar6 + -8) = arg2;
        *(puVar6 + -0x10) = 0x140044d1c;
        func_0x0001402ce170(iVar2 + 0x10 + iVar5);
    }
    return uVar7;
}
