/* RVA 0xa2c0  tam 239 B  addr 0x14000a2c0 */

int64_t fcn.14000a2c0(int64_t arg1,int64_t arg2)

{
    uchar *puVar1;
    uchar uVar2;
    uint32_t uVar3;
    uint64_t uVar4;
    int64_t iVar5;
    ulong uVar6;
    uchar *puVar7;
    int64_t unaff_RBP;
    int64_t unaff_RDI;
    uint64_t uStack_50;
    uchar auStack_48 [32];
    uint uStack_28;
    ulong uStack_20;
    ulong uStack_18;
    
    *arg2 = 0;
    *(arg2 + 8) = 0;
    *(arg2 + 0x10) = 0;
    *(arg2 + 0x18) = 0xf;
    *arg2 = 0;
    uStack_28 = 1;
    uStack_20 = 0;
    uStack_18 = 0;
    uVar4 = *(arg1 + 0x70) & 0xffffffffffffff22;
    if (uVar4 != '\x02') {
        uStack_50 = 0x14000a314;
        iVar5 = fcn.140028c75();
        *(unaff_RDI + 0x48 + unaff_RBP) = 0;
        return iVar5;
    }
    puVar1 = &stack0xffffffffffffffb8;
    if ((*(arg1 + 0x70) & 4) == 0) {
        puVar7 = &stack0xffffffffffffffb0;
        uStack_50 = uVar4;
        iVar5 = fcn.1406b83a2(arg1);
        puVar1 = &stack0xffffffffffffffb0;
        if (iVar5 != 0) {
            uVar3 = fcn.14024cd07(arg1);
            uVar4 = uVar3;
            uVar6 = fcn.14016dd3d(arg1);
            uVar2 = in(0x48);
            iVar5 = (CONCAT71(uVar6 >> 8,uVar2) & 0xffffffff) - uVar4;
            goto code_r0x00014000a384;
        }
    }
    puVar7 = puVar1;
    iVar5 = *(puVar7 + 0x30);
    uVar4 = *(puVar7 + 0x28);
code_r0x00014000a384:
    if (uVar4 != 0) {
        *(puVar7 + -8) = 0x14000a397;
        fcn.140009530(arg2,uVar4,iVar5);
    }
    return arg2;
}
