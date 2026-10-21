/* RVA 0x3ee20  tam 50 B  addr 0x14003ee20 */

void fcn.14003ee20(void)

{
    code *pcVar1;
    ulong uVar2;
    
    fcn.14003ecd4(2,0xc0000417);
    uVar2 = fcn.140036ca6();
    fcn.14013f79f(uVar2,0xc0000417);
    pcVar1 = swi(3);
    (*pcVar1)();
    return;
}
