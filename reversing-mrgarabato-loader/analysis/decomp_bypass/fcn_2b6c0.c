/* RVA 0x2b6c0  tam 252 B  addr 0x14002b6c0 */

ulong fcn.14002b6c0(int64_t arg1,int64_t arg2,int64_t arg3,int64_t arg4)

{
    char cVar1;
    int iVar2;
    uint8_t uVar3;
    uint64_t uVar4;
    uint64_t uVar5;
    uint64_t uVar6;
    uint64_t uVar7;
    uint64_t uVar8;
    
    if (arg3 == 0) {
        return 0;
    }
    uVar4 = 0;
    uVar5 = uVar4;
    uVar7 = uVar4;
    uVar8 = uVar4;
    if (arg2 != 0) {
        do {
            cVar1 = *(uVar4 + arg1);
            uVar6 = uVar5;
            if (cVar1 + 0xbfU < 0x1a) {
                iVar2 = cVar1 + -0x41;
code_r0x00014002b73f:
                if (iVar2 != -1) {
code_r0x00014002b75c:
                    uVar7 = uVar7 << 6 | iVar2;
                    uVar6 = uVar5 + 6;
                    if (7 < uVar5 + 6) {
                        if (uVar8 == *arg4) {
                            return 0;
                        }
                        uVar3 = uVar5 - 2;
                        *(uVar8 + arg3) = uVar7 >> (uVar3 & 0x3f);
                        uVar7 = uVar7 & (1 << (uVar3 & 0x1f)) + -1;
                        uVar6 = uVar5 - 2;
                        uVar8 = uVar8 + 1;
                    }
                }
            }
            else {
                if (cVar1 + 0x9fU < 0x1a) {
                    iVar2 = cVar1 + -0x47;
                    goto code_r0x00014002b73f;
                }
                if (cVar1 - 0x30U < 10) {
                    iVar2 = cVar1 + 4;
                    goto code_r0x00014002b73f;
                }
                if (cVar1 == '+') {
                    iVar2 = 0x3e;
                    goto code_r0x00014002b75c;
                }
                if (cVar1 == '/') {
                    iVar2 = 0x3f;
                    goto code_r0x00014002b75c;
                }
            }
            uVar4 = uVar4 + 1;
            uVar5 = uVar6;
        } while (uVar4 < arg2);
    }
    *arg4 = uVar8;
    return 1;
}
