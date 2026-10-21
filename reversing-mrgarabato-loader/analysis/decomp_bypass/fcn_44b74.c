/* RVA 0x44b74  tam 170 B  addr 0x140044b74 */

ulong fcn.140044b74(int64_t arg1)

{
    int64_t iVar1;
    uint *puVar2;
    uint32_t uVar3;
    ulong uVar4;
    int64_t iVar5;
    
    uVar3 = arg1;
    if ((-1 < uVar3) && (uVar3 < *0x1400588c8)) {
        iVar5 = (uVar3 & 0x1f) * 0x58;
        iVar1 = *((uVar3 >> 5) * 8 + 0x1400588e0);
        if (((*(iVar1 + 8 + iVar5) & 1) != 0) && (*(iVar1 + iVar5) != -1)) {
            if (*0x1400567f8 == 1) {
                if (uVar3 == 0) {
                    uVar4 = 0xfffffff6;
                }
                else if (uVar3 == 1) {
                    uVar4 = 0xfffffff5;
                }
                else {
                    if (uVar3 != 2) goto code_r0x000140044bea;
                    uVar4 = 0xfffffff4;
                }
                func_0x0001402e3e31(uVar4,0);
            }
code_r0x000140044bea:
            *(iVar5 + *((uVar3 >> 5) * 8 + 0x1400588e0)) = 0xffffffffffffffff;
            return 0;
        }
    }
    puVar2 = fcn.14003ef2c();
    *puVar2 = 9;
    puVar2 = fcn.14003ef4c();
    *puVar2 = 0;
    return 0xffffffff;
}
