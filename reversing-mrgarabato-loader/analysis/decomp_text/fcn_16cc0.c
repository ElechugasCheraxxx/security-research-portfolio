/* RVA 0x16cc0  tam 101 B  addr 0x140016cc0 */

void fcn.140016cc0(void)

{
    code *pcVar1;
    int64_t iVar2;
    int64_t iVar3;
    
    if (0xf < *0x140020098) {
        iVar2 = CONCAT71(*0x140020081,*0x140020080);
        iVar3 = iVar2;
        if (0xfff < *0x140020098 + 1) {
            iVar3 = *(iVar2 + -8);
            if (0x1f < (iVar2 - iVar3) - 8U) {
                fcn.14025ce9f(iVar2 - iVar3,*0x140020098 + 0x28);
                pcVar1 = swi(3);
                (*pcVar1)();
                return;
            }
        }
        fcn.140015008(iVar3);
    }
    *0x140020090 = *0x140018f70;
    *0x140020098 = *0x140018f78;
    *0x140020080 = 0;
    return;
}
