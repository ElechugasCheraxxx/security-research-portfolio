/* RVA 0x1a904  tam 60 B  addr 0x14001a904 */

void fcn.14001a904(int64_t param_1)

{
    code *pcVar1;
    int64_t iVar2;
    int iVar3;
    
    do {
        iVar2 = func_0x00014001b828(param_1);
        if (iVar2 != 0) {
            return;
        }
        iVar3 = func_0x00014001b834(param_1);
    } while (iVar3 != 0);
    if (param_1 == -1) {
        fcn.140009490();
        pcVar1 = swi(3);
        (*pcVar1)();
        return;
    }
    func_0x00014001b314();
    pcVar1 = swi(3);
    (*pcVar1)();
    return;
}
