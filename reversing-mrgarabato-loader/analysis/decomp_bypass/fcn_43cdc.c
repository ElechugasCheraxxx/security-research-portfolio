/* RVA 0x43cdc  tam 39 B  addr 0x140043cdc */

void fcn.140043cdc(void)

{
    uint *puVar1;
    int iVar2;
    uint uVar3;
    
    fcn.140045020();
    if (*0x1400568a0 != '\0') {
        fcn.140044dc0();
    }
    if ((*0x1400578a8 != 0) && (iVar2 = fcn.14002e131(*0x1400569b8,0,*0x1400578a8), iVar2 == 0)) {
        puVar1 = fcn.14003ef2c();
        uVar3 = fcn.1406b54b7();
        uVar3 = fcn.14003eee4(uVar3);
        *puVar1 = uVar3;
    }
    return;
}
