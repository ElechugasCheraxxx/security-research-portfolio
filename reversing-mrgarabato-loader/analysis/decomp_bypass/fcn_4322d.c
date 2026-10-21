/* RVA 0x4322d  tam 210 B  addr 0x14004322d */

ulong fcn.14004322d(int64_t arg1,int64_t arg2,int64_t arg3)

{
    uint *puVar1;
    ulong uVar2;
    uint32_t uVar3;
    int64_t iVar4;
    
    uVar3 = arg1;
    if (uVar3 == 0xfffffffe) {
        puVar1 = fcn.14003ef4c();
        *puVar1 = 0;
        puVar1 = fcn.14003ef2c();
        *puVar1 = 9;
    }
    else {
        if ((-1 < uVar3) && (uVar3 < *0x1400588c8)) {
            iVar4 = (uVar3 & 0x1f) * 0x58;
            if ((*(*((uVar3 >> 5) * 8 + 0x1400588e0) + 8 + iVar4) & 1) != 0) {
                func_0x000140044c94(arg1 & 0xffffffff);
                if ((*(*((uVar3 >> 5) * 8 + 0x1400588e0) + 8 + iVar4) & 1) == 0) {
                    puVar1 = fcn.14003ef2c();
                    *puVar1 = 9;
                    puVar1 = fcn.14003ef4c();
                    *puVar1 = 0;
                    uVar2 = 0xffffffffffffffff;
                }
                else {
                    uVar2 = fcn.140043184(arg1 & 0xffffffff,arg2,arg3 & 0xffffffff);
                }
                func_0x000140044d3c(arg1 & 0xffffffff);
                return uVar2;
            }
        }
        puVar1 = fcn.14003ef4c();
        *puVar1 = 0;
        puVar1 = fcn.14003ef2c();
        *puVar1 = 9;
        fcn.14003eec4();
    }
    return 0xffffffffffffffff;
}
