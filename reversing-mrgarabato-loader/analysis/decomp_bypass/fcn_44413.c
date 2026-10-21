/* RVA 0x44413  tam 543 B  addr 0x140044413 */

ulong fcn.140044413(int64_t arg1)

{
    uint uVar1;
    uint64_t uVar2;
    bool bVar3;
    uint *puVar4;
    int64_t iVar5;
    code *pcVar6;
    ulong uVar7;
    ulong uVar8;
    int iVar9;
    uint64_t uVar10;
    int iVar11;
    uchar *puVar12;
    ulong *puVar13;
    uint uVar14;
    uint uStack0000000000000030;
    uint64_t uStack_38;
    uchar auStack_30 [48];
    
    puVar12 = &stack0xffffffffffffffd0;
    iVar9 = arg1;
    uStack_38 = arg1 & 0xffffffff;
    bVar3 = false;
    uStack0000000000000030 = 0;
    iVar5 = 0;
    if (iVar9 == 2) {
        puVar13 = 0x1400572a8;
        goto code_r0x0001400444ff;
    }
    if (iVar9 == 4) {
code_r0x000140044493:
        uStack_38 = 0x140044498;
        iVar5 = fcn.14003e954();
        if (iVar5 == 0) {
            return 0xffffffff;
        }
        uVar2 = *(iVar5 + 0xa0);
        uVar10 = uVar2;
        do {
            if (*(uVar10 + 4) == iVar9) break;
            uVar10 = uVar10 + 0x10;
        } while (uVar10 < *0x1400499ec * 0x10 + uVar2);
        if ((*0x1400499ec * 0x10 + uVar2 <= uVar10) || (*(uVar10 + 4) != iVar9)) {
            uVar10 = 0;
        }
        puVar13 = uVar10 + 8;
        pcVar6 = *puVar13;
    }
    else {
        if (iVar9 == 6) {
code_r0x000140044483:
            puVar13 = 0x1400572b8;
        }
        else {
            if ((iVar9 == 8) || (iVar9 == 0xb)) goto code_r0x000140044493;
            if (iVar9 == 0xf) {
                puVar13 = 0x1400572c0;
            }
            else {
                if (iVar9 != 0x15) {
                    if (iVar9 != 0x16) {
                        uStack_38 = 0x140044453;
                        puVar4 = fcn.14003ef2c();
                        *puVar4 = 0x16;
                        uStack_38 = 0x14004445e;
                        fcn.14003eec4();
                        return 0xffffffff;
                    }
                    goto code_r0x000140044483;
                }
                puVar13 = 0x1400572b0;
            }
        }
code_r0x0001400444ff:
        bVar3 = true;
        uStack0000000000000030 = 1;
        puVar12 = &stack0xffffffffffffffc8;
        pcVar6 = func_0x000140151b28();
    }
    if (pcVar6 == 0x1) {
        return 0;
    }
    if (pcVar6 == NULL) {
        *(puVar12 + -8) = 0x14004452c;
        func_0x00014004113c(3);
        pcVar6 = swi(3);
        uVar7 = (*pcVar6)();
        return uVar7;
    }
    if (bVar3) {
        *(puVar12 + -8) = 0x140044538;
        fcn.14004252c(0);
    }
    if (((iVar9 == 8) || (iVar9 == 0xb)) || (iVar9 == 4)) {
        uVar7 = *(iVar5 + 0xa8);
        *(puVar12 + 0x28) = uVar7;
        *(iVar5 + 0xa8) = 0;
        if (iVar9 == 8) {
            uVar14 = *(iVar5 + 0xb0);
            *(iVar5 + 0xb0) = 0x8c;
            goto code_r0x000140044580;
        }
    }
    else {
        uVar7 = *(puVar12 + 0x28);
    }
    uVar14 = *(puVar12 + 0x60);
code_r0x000140044580:
    if (iVar9 == 8) {
        *(puVar12 + 0x20) = *0x1400499e0;
        iVar11 = *0x1400499e0;
        while (iVar11 < *0x1400499e0 + *0x1400499e4) {
            *(*(iVar5 + 0xa0) + 8 + iVar11 * 0x10) = 0;
            iVar11 = iVar11 + 1;
            *(puVar12 + 0x20) = iVar11;
        }
    }
    else {
        *(puVar12 + -8) = 0x1400445c3;
        uVar8 = fcn.14003e864();
        *puVar13 = uVar8;
    }
    if (bVar3) {
        *(puVar12 + -8) = 0x1400445d2;
        fcn.14004242c(0);
    }
    if (iVar9 == 8) {
        uVar1 = *(iVar5 + 0xb0);
        *(puVar12 + -8) = 0x1400445e6;
        (*pcVar6)(8,uVar1);
    }
    else {
        *(puVar12 + -8) = 0x1400445ed;
        (*pcVar6)(arg1 & 0xffffffff);
        if ((iVar9 != 0xb) && (iVar9 != 4)) {
            return 0;
        }
    }
    *(iVar5 + 0xa8) = uVar7;
    if (iVar9 == 8) {
        *(iVar5 + 0xb0) = uVar14;
    }
    return 0;
}
