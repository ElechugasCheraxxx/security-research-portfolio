/* RVA 0x45c7c  tam 50 B  addr 0x140045c7c */

uint fcn.140045c7c(int64_t arg1)

{
    int64_t iVar1;
    int64_t *piVar2;
    
    iVar1 = fcn.14003e9d8();
    piVar2 = *(iVar1 + 0x120);
    while( true ) {
        if (piVar2 == NULL) {
            return 1;
        }
        if (*piVar2 == arg1) break;
        piVar2 = piVar2[1];
    }
    return 0;
}
