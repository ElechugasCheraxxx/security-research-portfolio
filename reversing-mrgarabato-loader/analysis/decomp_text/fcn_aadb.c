/* RVA 0xaadb  tam 122 B  addr 0x14000aadb */

void fcn.14000aadb(int64_t arg1,int64_t arg2)

{
    uint64_t uVar1;
    int64_t iVar2;
    code *pcVar3;
    int64_t iVar4;
    
    do {
        uVar1 = *(arg1 + 0x18);
        if (0xf < uVar1) {
            iVar2 = *arg1;
            iVar4 = iVar2;
            if (0xfff < uVar1 + 1) {
                iVar4 = *(iVar2 + -8);
                if (0x1f < (iVar2 - iVar4) - 8U) {
                    func_0x000140280796(iVar2 - iVar4,uVar1 + 0x28);
                    pcVar3 = swi(3);
                    (*pcVar3)();
                    return;
                }
            }
            fcn.140015008(iVar4);
        }
        *(arg1 + 0x10) = 0;
        *(arg1 + 0x18) = 0xf;
        *arg1 = 0;
        arg1 = arg1 + 0x20;
    } while (arg1 != arg2);
    return;
}
