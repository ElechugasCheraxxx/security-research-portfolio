/* RVA 0x16f00  tam 101 B  addr 0x140016f00 */

void fcn.140016f00(void)

{
    code *pcVar1;
    int64_t iVar2;
    int64_t iVar3;
    
    if (0xf < *0x140020af8) {
        iVar2 = CONCAT71(*0x140020ae1,*0x140020ae0);
        iVar3 = iVar2;
        if (0xfff < *0x140020af8 + 1) {
            iVar3 = *(iVar2 + -8);
            if (0x1f < (iVar2 - iVar3) - 8U) {
                fcn.1402b6656(iVar2 - iVar3,*0x140020af8 + 0x28);
                pcVar1 = swi(3);
                (*pcVar1)();
                return;
            }
        }
        fcn.140015008(iVar3);
    }
    *0x140020af0 = *0x140018f70;
    *0x140020af8 = *0x140018f78;
    *0x140020ae0 = 0;
    return;
}
