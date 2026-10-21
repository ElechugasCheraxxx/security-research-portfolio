/* RVA 0x16e10  tam 93 B  addr 0x140016e10 */

void fcn.140016e10(void)

{
    code *pcVar1;
    int64_t iVar2;
    int64_t iVar3;
    
    if (0xf < *0x140020ab8) {
        iVar2 = CONCAT71(*0x140020aa1,*0x140020aa0);
        iVar3 = iVar2;
        if (0xfff < *0x140020ab8 + 1) {
            iVar3 = *(iVar2 + -8);
            if (0x1f < (iVar2 - iVar3) - 8U) {
                fcn.140037791(iVar2 - iVar3,*0x140020ab8 + 0x28);
                pcVar1 = swi(3);
                (*pcVar1)();
                return;
            }
        }
        fcn.140015008(iVar3);
    }
    *0x140020ab0 = *0x140018f70;
    *0x140020ab8 = *0x140018f78;
    *0x140020aa0 = 0;
    return;
}
