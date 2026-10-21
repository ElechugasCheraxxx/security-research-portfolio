/* RVA 0x170c0  tam 100 B  addr 0x1400170c0 */

void fcn.1400170c0(void)

{
    code *pcVar1;
    int64_t iVar2;
    int64_t iVar3;
    int64_t iVar4;
    uint *unaff_RSI;
    
    if (0xf < *0x140020208) {
        iVar2 = CONCAT71(*0x1400201f1,*0x1400201f0);
        iVar3 = iVar2;
        if (0xfff < *0x140020208 + 1) {
            iVar3 = *(iVar2 + -8);
            iVar4 = *0x140020208 + 0x28;
            if (0x1f < (iVar2 - iVar3) - 8U) {
                fcn.140287aa2(iVar2 - iVar3,iVar4);
                out(*unaff_RSI,iVar4);
                pcVar1 = swi(3);
                (*pcVar1)();
                return;
            }
        }
        fcn.140015008(iVar3);
    }
    *0x140020200 = *0x140018f70;
    *0x140020208 = *0x140018f78;
    *0x1400201f0 = 0;
    return;
}
