/* RVA 0xd140  tam 20 B  addr 0x14000d140 */

void fcn.14000d140(void)

{
    code *pcVar1;
    
    fcn.14000c5d0();
    fcn.14000f140();
    fcn.14000f5c0();
    pcVar1 = swi(3);
    (*pcVar1)();
    return;
}
