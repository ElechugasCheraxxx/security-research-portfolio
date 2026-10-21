/* RVA 0x3010b  tam 291 B  addr 0x14003010b */

void fcn.14003010b(int64_t arg1,int64_t arg2,int64_t arg3)

{
    char cVar1;
    int iVar2;
    uint64_t uVar3;
    uint8_t uVar4;
    
    uVar3 = 0;
    cVar1 = *(arg1 + 8);
    while (cVar1 != '\0') {
        uVar3 = uVar3 + 1;
        cVar1 = *(arg1 + 8 + uVar3);
    }
    if (arg3 == '\0') {
        cVar1 = *arg2;
        if (cVar1 != '\0') {
            arg2 = arg2 - uVar3;
            do {
                if (0x7ff < uVar3) break;
                *(arg1 + 8 + uVar3) = cVar1;
                cVar1 = *(uVar3 + 1 + arg2);
                uVar3 = uVar3 + 1;
            } while (cVar1 != '\0');
        }
        *(uVar3 + 8 + arg1) = 0;
        return;
    }
    uVar4 = *arg2;
    if (uVar4 == 0) {
        *(uVar3 + 8 + arg1) = 0;
    }
    else {
        do {
            if (0x7fb < uVar3) break;
            iVar2 = func_0x00014003cf18(uVar4);
            if ((((iVar2 == 0) && (uVar4 != 0x2d)) && (uVar4 != 0x5f)) && ((uVar4 != 0x2e && (uVar4 != 0x7e)))) {
                if (uVar4 == 0x20) {
                    *(arg1 + 8 + uVar3) = 0x2b;
                    goto code_r0x0001400301ba;
                }
                *(arg1 + 8 + uVar3) = 0x25;
                uVar3 = uVar3 + 3;
                *(arg1 + 6 + uVar3) = *((uVar4 >> 4) + 0x14004bdf0);
                *(arg1 + 7 + uVar3) = *((uVar4 & 0xf) + 0x14004bdf0);
            }
            else {
                *(arg1 + 8 + uVar3) = uVar4;
code_r0x0001400301ba:
                uVar3 = uVar3 + 1;
            }
            uVar4 = *(arg2 + 1);
            arg2 = arg2 + 1;
        } while (uVar4 != 0);
        *(uVar3 + 8 + arg1) = 0;
    }
    return;
}
