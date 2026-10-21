/* RVA 0x44c20  tam 116 B  addr 0x140044c20 */

ulong fcn.140044c20(int64_t arg1)

{
    int64_t iVar1;
    uint *puVar2;
    uint32_t uVar3;
    int64_t iVar4;
    
    uVar3 = arg1;
    if (uVar3 == 0xfffffffe) {
        puVar2 = fcn.14003ef4c();
        *puVar2 = 0;
        puVar2 = fcn.14003ef2c();
        *puVar2 = 9;
    }
    else {
        if ((-1 < uVar3) && (uVar3 < *0x1400588c8)) {
            iVar4 = (uVar3 & 0x1f) * 0x58;
            iVar1 = *((uVar3 >> 5) * 8 + 0x1400588e0);
            if ((*(iVar1 + 8 + iVar4) & 1) != 0) {
                return *(iVar1 + iVar4);
            }
        }
        puVar2 = fcn.14003ef4c();
        *puVar2 = 0;
        puVar2 = fcn.14003ef2c();
        *puVar2 = 9;
        fcn.14003eec4();
    }
    return 0xffffffffffffffff;
}
