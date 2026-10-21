/* RVA 0x16c50  tam 99 B  addr 0x140016c50 */

//WARNING: Control flow encountered bad instruction data

void fcn.140016c50(void)

{
    int64_t iVar1;
    int64_t iVar2;
    
    if (0xf < *0x140020018) {
        iVar1 = CONCAT71(*0x140020001,*0x140020000);
        iVar2 = iVar1;
        if (0xfff < *0x140020018 + 1) {
            iVar2 = *(iVar1 + -8);
            if (0x1f < (iVar1 - iVar2) - 8U) {
                fcn.140219e56(iVar1 - iVar2,*0x140020018 + 0x28);
    //WARNING: Bad instruction - Truncating control flow here
                halt_baddata();
            }
        }
        fcn.140015008(iVar2);
    }
    *0x140020010 = *0x140018f70;
    *0x140020018 = *0x140018f78;
    *0x140020000 = 0;
    return;
}
