/* RVA 0x17130  tam 100 B  addr 0x140017130 */

void fcn.140017130(void)

{
    code *pcVar1;
    int64_t iVar2;
    int64_t iVar3;
    
    if (0xf < *0x1400201e8) {
        iVar2 = CONCAT71(*0x1400201d1,*0x1400201d0);
        iVar3 = iVar2;
        if (0xfff < *0x1400201e8 + 1) {
            iVar3 = *(iVar2 + -8);
            if (0x1f < (iVar2 - iVar3) - 8U) {
                fcn.14029e833(iVar2 - iVar3,*0x1400201e8 + 0x28);
                pcVar1 = swi(3);
                (*pcVar1)();
                return;
            }
        }
        fcn.140015008(iVar3);
    }
    *0x1400201e0 = *0x140018f70;
    *0x1400201e8 = *0x140018f78;
    *0x1400201d0 = 0;
    return;
}
