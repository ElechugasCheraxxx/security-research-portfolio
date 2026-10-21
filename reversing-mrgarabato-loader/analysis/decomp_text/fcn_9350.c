/* RVA 0x9350  tam 32 B  addr 0x140009350 */

void fcn.140009350(void)

{
    code *pcVar1;
    uchar auStack_28 [40];
    
    fcn.140003a70(auStack_28);
    fcn.140015ea6(auStack_28,0x14001d3c8);
    pcVar1 = swi(3);
    (*pcVar1)();
    return;
}
