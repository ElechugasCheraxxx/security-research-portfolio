/* RVA 0x16a90  tam 100 B  addr 0x140016a90 */

void fcn.140016a90(void)

{
    code *pcVar1;
    int64_t iVar2;
    int64_t iVar3;
    
    if (0xf < *0x140020038) {
        iVar2 = CONCAT71(*0x140020021,*0x140020020);
        iVar3 = iVar2;
        if (0xfff < *0x140020038 + 1) {
            iVar3 = *(iVar2 + -8);
            if (0x1f < (iVar2 - iVar3) - 8U) {
                fcn.140287a3e(iVar2 - iVar3,*0x140020038 + 0x28);
                pcVar1 = swi(3);
                (*pcVar1)();
                return;
            }
        }
        fcn.140015008(iVar3);
    }
    *0x140020030 = *0x140018f70;
    *0x140020038 = *0x140018f78;
    *0x140020020 = 0;
    return;
}
