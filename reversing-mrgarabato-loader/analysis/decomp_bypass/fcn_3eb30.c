/* RVA 0x3eb30  tam 62 B  addr 0x14003eb30 */

//WARNING: Control flow encountered bad instruction data

void fcn.14003eb30(int64_t arg1)

{
    uint64_t uVar1;
    uchar *puVar2;
    uint64_t uStack_30;
    uchar auStack_28 [32];
    
    puVar2 = &stack0xffffffffffffffd8;
    uVar1 = *0x1400539e8;
    if (*0x1400539e8 != 0xffffffff) {
        if (arg1 == 0) {
            puVar2 = &stack0xffffffffffffffd0;
            uStack_30 = uVar1;
            fcn.14013dbdd();
            uVar1 = *0x1400539e8;
        }
        *(puVar2 + -8) = 0x14003eb5f;
        fcn.140216423(uVar1,0);
    //WARNING: Bad instruction - Truncating control flow here
        halt_baddata();
    }
    return;
}
