/* RVA 0x15088  tam 139 B  addr 0x140015088 */

ulong fcn.140015088(int64_t arg1)

{
    code *pcVar1;
    int iVar2;
    ulong uVar3;
    
    if (*0x140020b29 == '\0') {
        if (1 < arg1) {
            func_0x000140015a10(5);
            pcVar1 = swi(3);
            uVar3 = (*pcVar1)();
            return uVar3;
        }
        iVar2 = func_0x0001400159fc();
        if ((iVar2 == 0) || (arg1 != 0)) {
            *0x140020b30 = *0x14001a5f0;
            *0x140020b38 = *0x14001a5f8;
            *0x140020b40 = 0xffffffffffffffff;
            *0x140020b48 = *0x14001a5f0;
            *0x140020b50 = *0x14001a5f8;
            *0x140020b58 = 0xffffffffffffffff;
        }
        else {
            iVar2 = func_0x000140015f0c(0x140020b30);
            if ((iVar2 != 0) || (iVar2 = func_0x000140015f0c(0x140020b48), iVar2 != 0)) {
                return 0;
            }
        }
        *0x140020b29 = '\x01';
    }
    return 1;
}
