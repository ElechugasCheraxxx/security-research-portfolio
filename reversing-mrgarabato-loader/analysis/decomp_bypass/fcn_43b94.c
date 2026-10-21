/* RVA 0x43b94  tam 95 B  addr 0x140043b94 */

uint8_t fcn.140043b94(int64_t arg1)

{
    uint *puVar1;
    uint32_t uVar2;
    
    uVar2 = arg1;
    if (uVar2 == 0xfffffffe) {
        puVar1 = fcn.14003ef2c();
        *puVar1 = 9;
    }
    else {
        if ((-1 < uVar2) && (uVar2 < *0x1400588c8)) {
            return *(*((uVar2 >> 5) * 8 + 0x1400588e0) + 8 + (uVar2 & 0x1f) * 0x58) & 0x40;
        }
        puVar1 = fcn.14003ef2c();
        *puVar1 = 9;
        fcn.14003eec4();
    }
    return 0;
}
