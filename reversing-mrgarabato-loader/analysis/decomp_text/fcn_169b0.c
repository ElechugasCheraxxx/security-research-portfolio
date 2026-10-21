/* RVA 0x169b0  tam 100 B  addr 0x1400169b0 */

void fcn.1400169b0(void)

{
    code *pcVar1;
    int64_t iVar2;
    int64_t iVar3;
    
    if (0xf < *0x1400200b8) {
        iVar2 = CONCAT71(*0x1400200a1,*0x1400200a0);
        iVar3 = iVar2;
        if (0xfff < *0x1400200b8 + 1) {
            iVar3 = *(iVar2 + -8);
            if (0x1f < (iVar2 - iVar3) - 8U) {
                fcn.14028247b(iVar2 - iVar3,*0x1400200b8 + 0x28);
                pcVar1 = swi(3);
                (*pcVar1)();
                return;
            }
        }
        fcn.140015008(iVar3);
    }
    *0x1400200b0 = *0x140018f70;
    *0x1400200b8 = *0x140018f78;
    *0x1400200a0 = 0;
    return;
}
