/* RVA 0x14ed4  tam 157 B  addr 0x140014ed4 */

uint64_t fcn.140014ecd(uint64_t param_1,int64_t *param_2)

{
    uint32_t uVar1;
    uint64_t uVar2;
    uint64_t uVar3;
    uint8_t *puVar4;
    uint auStackX_18 [4];
    
    func_0x0001401d79d7();
    auStackX_18[0] = 2;
    func_0x000140222971(L"!x-sys-default-locale",0x20000001,auStackX_18);
    uVar1 = func_0x000140031f59(0x1300,0,param_1 & 0xffffffff);
    uVar2 = uVar1;
    if (uVar1 != 0) {
        puVar4 = *param_2 + -1 + uVar2;
        uVar3 = uVar2;
        do {
            if (*(*puVar4 + 0x14001a4c0) == '\0') {
                return uVar3;
            }
            puVar4 = puVar4 + -1;
            uVar3 = uVar3 - 1;
            uVar2 = 0;
        } while (uVar3 != 0);
    }
    return uVar2;
}
