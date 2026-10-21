/* RVA 0x2f9f9  tam 258 B  addr 0x14002f9f9 */

uint64_t fcn.14002f9f9(int64_t arg1,int64_t arg2)

{
    char cVar1;
    uchar uVar2;
    uint64_t uVar3;
    uint64_t uVar4;
    uint64_t uVar5;
    int64_t iVar6;
    uchar uStack0000000000000028;
    
    uVar4 = 0xffffffff;
    if (0x1f < *(arg2 + 0x10) - 4U) {
        cVar1 = func_0x00014002b230(arg2,0x20,&stack0x00000028);
        uVar3 = _uStack0000000000000028;
        if (cVar1 != '\0') goto code_r0x00014002fa37;
    }
    uVar3 = 0xffffffff;
code_r0x00014002fa37:
    if (uVar3 == 0) {
        return uVar3;
    }
    if ((0x1b < *(arg2 + 0x10) - 4U) && (cVar1 = func_0x00014002b230(arg2,0x1c,&stack0x00000028), cVar1 != '\0')) {
        uVar4 = _uStack0000000000000028;
    }
    if (uVar3 != 0) {
        iVar6 = arg1 - uVar4;
        uVar5 = uVar3;
        do {
            if (*(arg2 + 0x10) - 1U < uVar4) {
code_r0x00014002fabb:
                uVar2 = 0xff;
            }
            else {
                cVar1 = func_0x00014002b230(arg2,uVar4,&stack0x00000028,1);
                uVar2 = uStack0000000000000028;
                if (cVar1 == '\0') goto code_r0x00014002fabb;
            }
            *(iVar6 + 8 + uVar4) = uVar2;
            uVar4 = uVar4 + 1;
            uVar5 = uVar5 - 1;
        } while (uVar5 != 0);
    }
    if (*(uVar3 + 8 + arg1) != '/') {
        *(uVar3 + 8 + arg1) = 0x2f;
        uVar3 = uVar3 + 1;
    }
    *(uVar3 + 8 + arg1) = 0;
    return 1;
}
