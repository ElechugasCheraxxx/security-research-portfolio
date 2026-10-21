/* RVA 0x16b00  tam 101 B  addr 0x140016b00 */

void fcn.140016b00(void)

{
    int64_t iVar1;
    int64_t iVar2;
    
    if (0xf < *0x140020078) {
        iVar1 = CONCAT71(*0x140020061,*0x140020060);
        iVar2 = iVar1;
        if (0xfff < *0x140020078 + 1) {
            iVar2 = *(iVar1 + -8);
            if (0x1f < (iVar1 - iVar2) - 8U) {
                fcn.1401347b7(iVar1 - iVar2,*0x140020078 + 0x28);
                return;
            }
        }
        fcn.140015008(iVar2);
    }
    *0x140020070 = *0x140018f70;
    *0x140020078 = *0x140018f78;
    *0x140020060 = 0;
    return;
}
