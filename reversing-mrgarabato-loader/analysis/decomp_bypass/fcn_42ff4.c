/* RVA 0x42ff4  tam 64 B  addr 0x140042ff4 */

void fcn.140042ff4(void)

{
    code *pcVar1;
    int64_t iVar2;
    
    iVar2 = func_0x0001400443f0();
    if (iVar2 != 0) {
        func_0x000140044400(0x16);
    }
    if ((*0x140053ef0 & 2) != 0) {
        fcn.14003ecd4(3,0x40000015);
    }
    func_0x00014004113c(3);
    pcVar1 = swi(3);
    (*pcVar1)();
    return;
}
