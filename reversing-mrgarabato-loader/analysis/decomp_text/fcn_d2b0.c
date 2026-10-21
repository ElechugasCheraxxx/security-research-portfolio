/* RVA 0xd2b0  tam 17 B  addr 0x14000d2b0 */

void fcn.14000d2b0(void)

{
    code *pcVar1;
    
    fcn.140014ec7("vector too long");
    pcVar1 = swi(3);
    (*pcVar1)();
    return;
}
