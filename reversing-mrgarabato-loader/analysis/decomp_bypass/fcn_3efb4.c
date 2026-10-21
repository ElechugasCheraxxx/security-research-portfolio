/* RVA 0x3efb4  tam 67 B  addr 0x14003efb4 */

uint fcn.14003efb4(void)

{
    uint uVar1;
    ulong *puVar2;
    
    puVar2 = func_0x000140040cd0(0x20);
    *0x140058ae8 = func_0x00014029bf9d(puVar2);
    *0x140058af0 = *0x140058ae8;
    if (puVar2 == NULL) {
        uVar1 = 0x18;
    }
    else {
        *puVar2 = 0;
        uVar1 = 0;
    }
    return uVar1;
}
