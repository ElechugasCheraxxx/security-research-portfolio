/* RVA 0x16da0  tam 100 B  addr 0x140016da0 */

void fcn.140016da0(void)

{
    code *pcVar1;
    int64_t iVar2;
    int64_t iVar3;
    
    if (7 < *0x1400201c8) {
        iVar2 = CONCAT62(*0x1400201b2,*0x1400201b0);
        iVar3 = iVar2;
        if (0xfff < *0x1400201c8 * 2 + 2) {
            iVar3 = *(iVar2 + -8);
            if (0x1f < (iVar2 - iVar3) - 8U) {
                func_0x0001406a9cdc(iVar2 - iVar3,*0x1400201c8 * 2 + 0x29);
                pcVar1 = swi(3);
                (*pcVar1)();
                return;
            }
        }
        fcn.140015008(iVar3);
    }
    *0x1400201c0 = *0x140018f60;
    *0x1400201c8 = *0x140018f68;
    *0x1400201b0 = 0;
    return;
}
