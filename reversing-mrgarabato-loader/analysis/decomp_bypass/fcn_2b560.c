/* RVA 0x2b560  tam 345 B  addr 0x14002b560 */

uint64_t fcn.14002b560(int64_t arg1,int64_t arg2,int64_t arg3,int64_t arg4)

{
    uint8_t *puVar1;
    uint64_t in_RAX;
    uint64_t uVar2;
    uint64_t uVar3;
    uchar *puVar4;
    uint64_t uVar5;
    uint64_t uVar6;
    uint64_t uVar7;
    uint32_t uVar8;
    uint64_t uVar9;
    ulong uStack_40;
    ulong uStack_38;
    ulong uStack_30;
    ulong uStack_28;
    ulong uStack_20;
    ulong uStack_18;
    ulong uStack_10;
    ulong uStack_8;
    
    if (arg3 == 0) {
        uVar2 = in_RAX & 0xffffffffffffff00;
    }
    else {
        uVar3 = *arg4;
        uVar5 = 0;
        uStack_40 = *0x14004bae0;
        uStack_38 = *0x14004bae8;
        uStack_30 = *0x14004baf0;
        uStack_28 = *0x14004baf8;
        uVar2 = arg3 + uVar3;
        uStack_20 = *0x14004bb00;
        uStack_18 = *0x14004bb08;
        uStack_10 = *0x14004bb10;
        uStack_8 = *0x14004bb18;
        puVar4 = arg3;
        uVar9 = uVar5;
        uVar7 = arg3;
        if (arg2 != 0) {
            do {
                uVar6 = uVar5 + 1;
                uVar8 = *(uVar5 + arg1) << 0x10;
                if (uVar6 == arg2) {
                    uVar9 = 2;
                }
                else {
                    puVar1 = uVar6 + arg1;
                    uVar6 = uVar5 + 2;
                    uVar3 = *puVar1 << 8;
                    uVar8 = uVar8 | uVar3;
                    if (uVar6 == arg2) {
                        uVar9 = 1;
                    }
                    else {
                        uVar3 = 0;
                        uVar8 = uVar8 | *(uVar6 + arg1);
                        uVar6 = uVar5 + 3;
                    }
                }
                if (uVar2 < uVar7 + 4) {
                    return uVar3 & 0xffffffffffffff00;
                }
                *puVar4 = *(&uStack_40 + (uVar8 >> 0x12));
                puVar4[1] = *(&uStack_40 + (uVar8 >> 0xc & 0x3f));
                if (uVar9 < 2) {
                    puVar4[2] = *(&uStack_40 + (uVar8 >> 6 & 0x3f));
                }
                else {
                    puVar4[2] = 0x3d;
                }
                if (uVar9 == 0) {
                    puVar4[3] = *(&uStack_40 + (uVar8 & 0x3f));
                }
                else {
                    puVar4[3] = 0x3d;
                }
                uVar3 = 0;
                puVar4 = puVar4 + 4;
                uVar5 = uVar6;
                uVar7 = uVar7 + 4;
            } while (uVar6 < arg2);
        }
        uVar2 = CONCAT71(uVar3 >> 8,1);
        *arg4 = puVar4 - arg3;
    }
    return uVar2;
}
