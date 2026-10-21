/* RVA 0x3dca0  tam 140 B  addr 0x14003dca0 */

void fcn.14003dca0(int64_t arg1)

{
    int64_t iVar1;
    uchar *puVar2;
    int64_t iVar3;
    ushort *puVar4;
    
    puVar2 = arg1 + 0x1c;
    iVar3 = 0x101;
    fcn.14003f620(puVar2,0,0x101);
    *(arg1 + 0xc) = 0;
    *(arg1 + 4) = 0;
    puVar4 = arg1 + 0x10;
    for (iVar1 = 6; iVar1 != 0; iVar1 = iVar1 + -1) {
        *puVar4 = 0;
        puVar4 = puVar4 + 1;
    }
    do {
        *puVar2 = puVar2[0x140053070 - arg1];
        puVar2 = puVar2 + 1;
        iVar3 = iVar3 + -1;
    } while (iVar3 != 0);
    puVar2 = arg1 + 0x11d;
    iVar1 = 0x100;
    do {
        *puVar2 = puVar2[0x140053070 - arg1];
        puVar2 = puVar2 + 1;
        iVar1 = iVar1 + -1;
    } while (iVar1 != 0);
    return;
}
