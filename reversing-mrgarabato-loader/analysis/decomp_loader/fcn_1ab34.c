/* RVA 0x1ab34  tam 58 B  addr 0x14001ab34 */

ulong fcn.14001ab34(ulong param_1)

{
    int iVar1;
    ulong uVar2;
    
    if (*0x14002fa90 == -1) {
        iVar1 = func_0x00014001b852();
    }
    else {
        iVar1 = func_0x00014001b84c(0x14002fa90,param_1);
    }
    uVar2 = 0;
    if (iVar1 == 0) {
        uVar2 = param_1;
    }
    return uVar2;
}
