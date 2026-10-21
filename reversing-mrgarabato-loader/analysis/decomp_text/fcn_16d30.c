/* RVA 0x16d30  tam 100 B  addr 0x140016d30 */

void fcn.140016d30(void)

{
    code *pcVar1;
    int64_t iVar2;
    int64_t iVar3;
    
    if (0xf < *0x140020118) {
        iVar2 = CONCAT71(*0x140020101,*0x140020100);
        iVar3 = iVar2;
        if (0xfff < *0x140020118 + 1) {
            iVar3 = *(iVar2 + -8);
            if (0x1f < (iVar2 - iVar3) - 8U) {
                fcn.140244593(iVar2 - iVar3,*0x140020118 + 0x28);
                pcVar1 = swi(3);
                (*pcVar1)();
                return;
            }
        }
        fcn.140015008(iVar3);
    }
    *0x140020110 = *0x140018f70;
    *0x140020118 = *0x140018f78;
    *0x140020100 = 0;
    return;
}
