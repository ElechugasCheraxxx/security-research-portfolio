/* RVA 0xb740  tam 108 B  addr 0x14000b740 */

//WARNING: Instruction at (ram,0x00014000b777) overlaps instruction at (ram,0x00014000b774)
//

void fcn.14000b740(int64_t arg1)

{
    code *pcVar1;
    int64_t iVar2;
    int64_t iVar3;
    uint64_t uVar4;
    bool bVar5;
    
    if (*arg1 != 0) {
        func_0x00014000aad0(*arg1,*(arg1 + 8),arg1);
        iVar2 = *arg1;
        uVar4 = *(arg1 + 0x10) - iVar2 & 0xffffffffffffffe0;
        iVar3 = iVar2;
        if (0xfff < uVar4) {
            while( true ) {
                iVar3 = *(iVar2 + -8);
                uVar4 = uVar4 + 0x27;
                iVar2 = iVar2 - iVar3;
                bVar5 = SBORROW8(iVar2 - 8U,0x1f);
                if (iVar2 - 8U < 0x20) break;
                func_0x0001401346df(iVar2,uVar4);
                if (!bVar5) {
                    pcVar1 = swi(3);
                    (*pcVar1)();
                    return;
                }
            }
        }
        fcn.140015008(iVar3);
        *arg1 = 0;
        *(arg1 + 8) = 0;
        *(arg1 + 0x10) = 0;
    }
    return;
}
