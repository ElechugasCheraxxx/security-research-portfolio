/* RVA 0x3d38d  tam 499 B  addr 0x14003d38d */

//WARNING: Removing unreachable block (ram,0x00014003d50e)
//WARNING: Removing unreachable block (ram,0x00014003d515)
//WARNING: Removing unreachable block (ram,0x00014003d51d)
//WARNING: Removing unreachable block (ram,0x00014003d521)
//WARNING: Removing unreachable block (ram,0x00014003d53b)

uint32_t fcn.14003d570(int64_t arg1,int64_t arg2,int64_t arg3)

{
    uint16_t *puVar1;
    bool bVar2;
    bool bVar3;
    bool bVar4;
    int iVar5;
    int iVar6;
    uint32_t uVar7;
    uint *puVar8;
    uint16_t *puVar9;
    uint16_t uVar10;
    uint32_t uVar11;
    uint64_t uVar12;
    uint32_t uVar13;
    
    iVar6 = arg3;
    bVar4 = false;
    uVar12 = arg3 & 0xffffffff;
    if (arg2 != 0) {
        *arg2 = arg1;
    }
    if ((arg1 == 0) || ((iVar6 != 0 && ((iVar6 < 2 || (0x24 < iVar6)))))) {
        puVar8 = fcn.14003ef2c();
        *puVar8 = 0x16;
        fcn.14003eec4();
        return 0;
    }
    uVar10 = *arg1;
    uVar11 = 0;
    puVar1 = arg1;
    while( true ) {
        puVar9 = puVar1 + 1;
        iVar5 = func_0x000140040be8(uVar10);
        if (iVar5 == 0) break;
        uVar10 = *puVar9;
        puVar1 = puVar9;
    }
    if (uVar10 == 0x2d) {
        bVar2 = true;
code_r0x00014003d415:
        bVar4 = bVar2;
        uVar10 = *puVar9;
        puVar9 = puVar1 + 2;
    }
    else {
        bVar2 = false;
        if (uVar10 == 0x2b) goto code_r0x00014003d415;
    }
    bVar3 = false;
    bVar2 = false;
    if (iVar6 == 0) {
        iVar6 = func_0x000140040a50(uVar10);
        if (iVar6 != 0) {
            uVar12 = 10;
            goto code_r0x00014003d472;
        }
        if ((*puVar9 != 0x78) && (*puVar9 != 0x58)) {
            uVar12 = 8;
            goto code_r0x00014003d472;
        }
        uVar12 = 0x10;
    }
    if (((uVar12 == 0x10) && (iVar6 = func_0x000140040a50(uVar10), iVar6 == 0)) &&
       ((*puVar9 == 0x78 || (*puVar9 == 0x58)))) {
        uVar10 = puVar9[1];
        puVar9 = puVar9 + 2;
    }
code_r0x00014003d472:
    do {
        uVar7 = func_0x000140040a50(uVar10);
        if (uVar7 == 0xffffffff) {
            if (((uVar10 < 0x41) || (0x5a < uVar10)) && (0x19 < uVar10 - 0x61)) {
code_r0x00014003d4d4:
                puVar9 = puVar9 + -1;
                if (bVar2) {
                    if (bVar3) {
                        puVar8 = fcn.14003ef2c();
                        *puVar8 = 0x22;
                        uVar11 = 0xffffffff;
                    }
                }
                else {
                    if (arg2 != 0) {
                        puVar9 = arg1;
                    }
                    uVar11 = 0;
                }
                if (arg2 != 0) {
                    *arg2 = puVar9;
                }
                if (bVar4) {
                    uVar11 = -uVar11;
                }
                return uVar11;
            }
            uVar7 = uVar10;
            if (uVar10 - 0x61 < 0x1a) {
                uVar7 = uVar10 - 0x20;
            }
            uVar7 = uVar7 - 0x37;
        }
        if (uVar12 <= uVar7) goto code_r0x00014003d4d4;
        uVar13 = 0xffffffff / uVar12;
        if ((uVar11 < uVar13) || ((uVar11 == uVar13 && (uVar7 <= 0xffffffff % uVar12)))) {
            uVar11 = uVar11 * uVar12 + uVar7;
        }
        else {
            bVar3 = true;
            bVar2 = true;
            if (arg2 == 0) goto code_r0x00014003d4d4;
        }
        bVar2 = true;
        uVar10 = *puVar9;
        puVar9 = puVar9 + 1;
    } while( true );
}
