/* RVA 0x15da6  tam 165 B  addr 0x140015da6 */

//WARNING: Instruction at (ram,0x000140015e37) overlaps instruction at (ram,0x000140015e36)
//

int64_t fcn.140015da0(int64_t arg1)

{
    int *piVar1;
    int iVar2;
    uint32_t uVar3;
    uint32_t uVar4;
    int iVar5;
    int64_t iVar6;
    
    fcn.140015eca(arg1 + 0x28);
    *(arg1 + 0x50) = 0;
    *(arg1 + 0x58) = 0;
    iVar6 = arg1 + 0x28;
    *(arg1 + 0x5c) = 0;
    *(arg1 + 0x10) = sym.MZ__wlaXGQ1DzJg_TsuQK_b_3i_____KU_:FSG7k__d8o_9_0XVxaJW_h__M_O_rD_AIw_rbfNxBH__j__CEYL_0;
    *(arg1 + 8) = sym.MZ__wlaXGQ1DzJg_TsuQK_b_3i_____KU_:FSG7k__d8o_9_0XVxaJW_h__M_O_rD_AIw_rbfNxBH__j__CEYL_0;
    *(arg1 + 0x20) = 0x14001a630;
    *arg1 = 0x60;
    *(arg1 + 0x18) = 0xe00;
    iVar2 = fcn.14000a590(iVar6,0,0);
    uVar4 = iVar6;
    if (iVar2 == 0) {
        uVar3 = fcn.1401c0d1a();
        uVar4 = uVar4 | 0x80070000;
        if (uVar3 < 1) {
            uVar4 = uVar3;
        }
        if (uVar4 < 0) {
            fcn.140278a8f();
            iVar5 = 0x4001a640;
            iVar2 = fcn.1400321d5();
            piVar1 = (iVar2 + 0xac31) - 0x75;
            *piVar1 = *piVar1 + iVar5;
        }
    }
    return arg1;
}
