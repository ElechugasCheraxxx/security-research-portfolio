/* RVA 0x159d4  tam 32 B  addr 0x1400159d4 */

void fcn.1400159d4(void)

{
    code *pcVar1;
    uchar auStack_28 [40];
    
    fcn.1400159b4(auStack_28);
    fcn.140015ea6(auStack_28,0x14001d548);
    pcVar1 = swi(3);
    (*pcVar1)();
    return;
}
