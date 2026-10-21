/* RVA 0x44b34  tam 64 B  addr 0x140044b34 */

uint fcn.140044b34(int64_t arg1)

{
    uint uVar1;
    uint *puVar2;
    int iVar3;
    
    iVar3 = arg1;
    if (-1 < iVar3) {
        if (iVar3 < 3) {
            uVar1 = *0x1400567e4;
            *0x1400567e4 = iVar3;
            return uVar1;
        }
        if (iVar3 == 3) {
            return *0x1400567e4;
        }
    }
    puVar2 = fcn.14003ef2c();
    *puVar2 = 0x16;
    fcn.14003eec4();
    return 0xffffffff;
}
