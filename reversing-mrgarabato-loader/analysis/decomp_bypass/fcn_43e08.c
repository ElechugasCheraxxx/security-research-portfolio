/* RVA 0x43e08  tam 38 B  addr 0x140043e08 */

uint fcn.140043e08(int64_t arg1)

{
    uint uVar1;
    uint *puVar2;
    
    if (arg1 == 0) {
        puVar2 = fcn.14003ef2c();
        *puVar2 = 0x16;
        fcn.14003eec4();
        uVar1 = 0xffffffff;
    }
    else {
        uVar1 = *(arg1 + 0x1c);
    }
    return uVar1;
}
