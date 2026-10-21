/* RVA 0x17050  tam 104 B  addr 0x140017050 */

void fcn.140017050(void)

{
    code *pcVar1;
    int64_t iVar2;
    int64_t iVar3;
    
    if (0xf < *0x1400201a8) {
        iVar2 = CONCAT71(*0x140020191,*0x140020190);
        iVar3 = iVar2;
        if (0xfff < *0x1400201a8 + 1) {
            iVar3 = *(iVar2 + -8);
            if (0x1f < (iVar2 - iVar3) - 8U) {
                fcn.14025c8bb(iVar2 - iVar3,*0x1400201a8 + 0x28);
                pcVar1 = swi(3);
                (*pcVar1)();
                return;
            }
        }
        fcn.140015008(iVar3);
    }
    *0x1400201a0 = *0x140018f70;
    *0x1400201a8 = *0x140018f78;
    *0x140020190 = 0;
    return;
}
