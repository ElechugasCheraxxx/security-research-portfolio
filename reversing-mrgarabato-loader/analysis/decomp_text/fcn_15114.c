/* RVA 0x15114  tam 152 B  addr 0x140015114 */

uint64_t fcn.140015114(int64_t arg1)

{
    code *pcVar1;
    uint64_t uVar2;
    unkuint7 Var3;
    int64_t iVar4;
    code *pcVar5;
    
    uVar2 = 0x5a4d;
    if (_sym.MZ__wlaXGQ1DzJg_TsuQK_b_3i_____KU_:FSG7k__d8o_9_0XVxaJW_h__M_O_rD_AIw_rbfNxBH__j__CEYL_0 == 0x5a4d) {
        iVar4 = *0x14000003c;
        if ((*(sym.MZ__wlaXGQ1DzJg_TsuQK_b_3i_____KU_:FSG7k__d8o_9_0XVxaJW_h__M_O_rD_AIw_rbfNxBH__j__CEYL_0 + iVar4) ==
             0x4550) && (uVar2 = 0x20b, *(iVar4 + 0x140000018) == 0x20b)) {
            pcVar5 = sym.MZ__wlaXGQ1DzJg_TsuQK_b_3i_____KU_:FSG7k__d8o_9_0XVxaJW_h__M_O_rD_AIw_rbfNxBH__j__CEYL_0 +
                     iVar4 + *(iVar4 + 0x140000014) + 0x18;
            uVar2 = *(iVar4 + 0x140000006);
            pcVar1 = pcVar5 + uVar2 * 0x28;
            for (; pcVar5 != pcVar1; pcVar5 = pcVar5 + 0x28) {
                if ((*(pcVar5 + 0xc) <= arg1 - 0x140000000U) &&
                   (uVar2 = *(pcVar5 + 8) + *(pcVar5 + 0xc), arg1 - 0x140000000U < uVar2)) goto code_r0x00014001518a;
            }
            pcVar5 = NULL;
code_r0x00014001518a:
            if (pcVar5 == NULL) {
                return uVar2 & 0xffffffffffffff00;
            }
            Var3 = uVar2 >> 8;
            if (*(pcVar5 + 0x24) < 0) {
                return Var3 << 8;
            }
            return CONCAT71(Var3,1);
        }
    }
    return uVar2 & 0xffffffffffffff00;
}
