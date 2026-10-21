/* RVA 0x155f9  tam 205 B  addr 0x1400155f9 */

void fcn.1400155f9(void)

{
    code *pcVar1;
    char cVar2;
    char *pcVar3;
    ulong uStackX_8;
    ulong auStackX_10 [3];
    
    pcVar3 = fcn.140129858(0x17);
    cVar2 = pcVar3 + *pcVar3;
    pcVar3 = CONCAT71(pcVar3 >> 8,cVar2);
    *pcVar3 = *pcVar3 + cVar2;
    pcVar1 = swi(0x29);
    (*pcVar1)();
    fcn.1400156c8(0x140020c20);
    *0x140020d18 = uStackX_8;
    *0x140020cb8 = auStackX_10;
    *0x140020b90 = uStackX_8;
    *0x140020ca0 = auStackX_10[0];
    *0x140020b80 = 0xc0000409;
    *0x140020b84 = 1;
    *0x140020b98 = 1;
    *0x140020ba0 = 2;
    fcn.1400155c0(0x14001a610);
    return;
}
