/* RVA 0x40efc  tam 175 B  addr 0x140040efc */

ulong fcn.140040efc(int64_t arg1)

{
    int iVar1;
    ulong uVar2;
    ulong *puVar3;
    
    if (*0x140058b00 != NULL) {
        iVar1 = func_0x000140043140(0x140058b00);
        if (iVar1 != 0) {
            (**0x140058b00)(arg1 & 0xffffffff);
        }
    }
    func_0x000140044030();
    uVar2 = fcn.140040ec0(0x140049380,0x1400493a0);
    if (uVar2 == 0) {
        fcn.14003f104(0x1400419ec);
        for (puVar3 = 0x140049370; puVar3 < 0x140049378; puVar3 = puVar3 + 1) {
            if (*puVar3 != NULL) {
                (**puVar3)();
            }
        }
        if (*0x140058b08 != NULL) {
            iVar1 = func_0x000140043140(0x140058b08);
            if (iVar1 != 0) {
                (**0x140058b08)(0,2);
            }
        }
        uVar2 = 0;
    }
    return uVar2;
}
