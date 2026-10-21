/* RVA 0x9490  tam 32 B  addr 0x140009490 */

void fcn.140009490(void)

{
    code *pcVar1;
    uchar auStack_28 [40];
    
    fcn.140003bb0(auStack_28);
    fcn.14001b7e0(auStack_28,0x14002c210);
    pcVar1 = swi(3);
    (*pcVar1)();
    return;
}
