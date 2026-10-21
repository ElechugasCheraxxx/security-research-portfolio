/* RVA 0x16f70  tam 108 B  addr 0x140016f70 */

void fcn.140016f70(void)

{
    code *pcVar1;
    uint8_t extraout_AH;
    int64_t iVar2;
    int64_t iVar3;
    
    if (7 < *0x140020168) {
        iVar2 = CONCAT62(*0x140020152,*0x140020150);
        iVar3 = iVar2;
        if (0xfff < *0x140020168 * 2 + 2) {
            iVar3 = *(iVar2 + -8);
            iVar2 = iVar2 - iVar3;
            if (0x1f < iVar2 - 8U) {
                fcn.14028fc94(iVar2,*0x140020168 * 2 + 0x29);
                pcVar1 = swi(3);
                (*pcVar1)(iVar2 | extraout_AH);
                return;
            }
        }
        fcn.140015008(iVar3);
    }
    *0x140020160 = *0x140018f60;
    *0x140020168 = *0x140018f68;
    *0x140020150 = 0;
    return;
}
