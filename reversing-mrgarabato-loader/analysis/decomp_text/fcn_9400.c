/* RVA 0x9400  tam 17 B  addr 0x140009400 */

void fcn.140009400(void)

{
    code *pcVar1;
    
    fcn.140014ecd("invalid string position");
    pcVar1 = swi(3);
    (*pcVar1)();
    return;
}
