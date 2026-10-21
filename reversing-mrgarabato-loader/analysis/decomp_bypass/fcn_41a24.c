/* RVA 0x41a24  tam 86 B  addr 0x140041a24 */

//WARNING: Control flow encountered bad instruction data

ulong fcn.140041a24(void)

{
    int64_t iVar1;
    ulong uVar2;
    int64_t unaff_RSI;
    uint32_t unaff_EDI;
    
    *0x1400569b8 = fcn.14025ea0d(0,0x1000,0);
    uVar2 = 0;
    if (*0x1400569b8 != 0) {
        iVar1 = fcn.140154273();
        if (CARRY4(unaff_EDI,*(unaff_RSI + iVar1))) {
            fcn.14002cd7d(*0x1400569b8,0,&stack0x00000000,4);
    //WARNING: Bad instruction - Truncating control flow here
            halt_baddata();
        }
        uVar2 = 1;
    }
    return uVar2;
}
