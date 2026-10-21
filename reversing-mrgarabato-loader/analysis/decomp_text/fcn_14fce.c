/* RVA 0x14fce  tam 58 B  addr 0x140014fce */

void fcn.140014fce(int64_t arg1)

{
    code *pcVar1;
    int64_t iVar2;
    int iVar3;
    
    do {
        iVar2 = func_0x000140015eee(arg1);
        if (iVar2 != 0) {
            return;
        }
        iVar3 = func_0x000140015efa(arg1);
    } while (iVar3 != 0);
    if (arg1 == -1) {
        fcn.140009350();
        pcVar1 = swi(3);
        (*pcVar1)();
        return;
    }
    func_0x0001400159d4();
    pcVar1 = swi(3);
    (*pcVar1)();
    return;
}
