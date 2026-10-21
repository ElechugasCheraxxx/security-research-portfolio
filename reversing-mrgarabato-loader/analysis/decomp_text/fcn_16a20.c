/* RVA 0x16a20  tam 101 B  addr 0x140016a20 */

void fcn.140016a20(void)

{
    code *pcVar1;
    int64_t iVar2;
    int64_t iVar3;
    
    if (0xf < *0x1400200d8) {
        iVar2 = CONCAT71(*0x1400200c1,*0x1400200c0);
        iVar3 = iVar2;
        if (0xfff < *0x1400200d8 + 1) {
            iVar3 = *(iVar2 + -8);
            if (0x1f < (iVar2 - iVar3) - 8U) {
                fcn.140236ee4(iVar2 - iVar3,*0x1400200d8 + 0x28);
                pcVar1 = swi(3);
                (*pcVar1)();
                return;
            }
        }
        fcn.140015008(iVar3);
    }
    *0x1400200d0 = *0x140018f70;
    *0x1400200d8 = *0x140018f78;
    *0x1400200c0 = 0;
    return;
}
