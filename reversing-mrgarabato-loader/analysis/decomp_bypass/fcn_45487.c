/* RVA 0x45487  tam 97 B  addr 0x140045487 */

uint fcn.140045481(int64_t arg1)

{
    uint uVar1;
    uint *puVar2;
    
    uVar1 = 0xffffffff;
    if (arg1 == 0) {
        puVar2 = fcn.14003ef2c();
        *puVar2 = 0x16;
        fcn.14003eec4();
        uVar1 = 0xffffffff;
    }
    else if ((*(arg1 + 0x18) & 0x40) == 0) {
        fcn.140043d04(arg1);
        uVar1 = fcn.140045400(arg1);
        func_0x000140043d9c(arg1);
    }
    else {
        *(arg1 + 0x18) = 0;
    }
    return uVar1;
}
