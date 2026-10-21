/* RVA 0x3ea0b  tam 292 B  addr 0x14003ea0b */

void fcn.14003ea0b(int64_t arg1)

{
    int *piVar1;
    
    if (*(arg1 + 0x38) != 0) {
        fcn.14003dc60(*(arg1 + 0x38));
    }
    if (*(arg1 + 0x48) != 0) {
        fcn.14003dc60(*(arg1 + 0x48));
    }
    if (*(arg1 + 0x58) != 0) {
        fcn.14003dc60(*(arg1 + 0x58));
    }
    if (*(arg1 + 0x68) != 0) {
        fcn.14003dc60(*(arg1 + 0x68));
    }
    if (*(arg1 + 0x70) != 0) {
        fcn.14003dc60(*(arg1 + 0x70));
    }
    if (*(arg1 + 0x78) != 0) {
        fcn.14003dc60(*(arg1 + 0x78));
    }
    if (*(arg1 + 0x80) != 0) {
        fcn.14003dc60(*(arg1 + 0x80));
    }
    if (*(arg1 + 0xa0) != 0x140049920) {
        fcn.14003dc60(*(arg1 + 0xa0));
    }
    fcn.14004252c(0xd);
    piVar1 = *(arg1 + 0xb8);
    if (piVar1 != NULL) {
        LOCK();
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if ((*piVar1 == 0) && (piVar1 != 0x140053070)) {
            fcn.14003dc60(piVar1);
        }
    }
    fcn.14004242c(0xd);
    fcn.14004252c(0xc);
    piVar1 = *(arg1 + 0xc0);
    if (piVar1 != NULL) {
        func_0x00014003e574(piVar1);
        if (((piVar1 != *0x1400539d0) && (piVar1 != 0x140053870)) && (*piVar1 == 0)) {
            fcn.14003e618(piVar1);
        }
    }
    fcn.14004242c(0xc);
    fcn.14003dc60(arg1);
    return;
}
