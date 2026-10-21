/* RVA 0x43a71  tam 206 B  addr 0x140043a71 */

uint fcn.140043a71(int64_t arg1,int64_t arg2,int64_t arg3)

{
    uint uVar1;
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
            if ((*(*((uVar3 >> 5) * 8 + 0x1400588e0) + 8 + iVar4) & 1) != 0) {
                func_0x000140044c94(arg1 & 0xffffffff);
                if ((*(*((uVar3 >> 5) * 8 + 0x1400588e0) + 8 + iVar4) & 1) == 0) {
                    puVar2 = fcn.14003ef2c();
                    *puVar2 = 9;
                    puVar2 = fcn.14003ef4c();
                    *puVar2 = 0;
                    uVar1 = 0xffffffff;
                }
                else {
                    uVar1 = func_0x000140043300(arg1 & 0xffffffff,arg2,arg3 & 0xffffffff);
                }
                func_0x000140044d3c(arg1 & 0xffffffff);
                return uVar1;
            }
        }
        puVar2 = fcn.14003ef4c();
        *puVar2 = 0;
        puVar2 = fcn.14003ef2c();
        *puVar2 = 9;
        fcn.14003eec4();
    }
    return 0xffffffff;
}
