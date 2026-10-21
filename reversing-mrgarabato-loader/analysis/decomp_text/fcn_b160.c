/* RVA 0xb160  tam 489 B  addr 0x14000b160 */

int64_t fcn.14000b150(int64_t arg1,ulong noname_1,int64_t arg2,int64_t arg3)

{
    uint64_t uVar1;
    uint64_t uVar2;
    uint64_t uVar3;
    code *pcVar4;
    uint uVar5;
    uint uVar6;
    uint uVar7;
    uint8_t extraout_AH;
    uint64_t uVar8;
    uint64_t uVar9;
    int64_t iVar10;
    uint64_t uVar11;
    uint64_t uVar12;
    
    uVar12 = 0;
    *arg1 = 0;
    *(arg1 + 8) = 0;
    *(arg1 + 0x10) = 0;
    *(arg1 + 0x18) = 0;
    uVar2 = *(arg2 + 0x10);
    uVar3 = *(arg3 + 0x10);
    uVar1 = uVar3 + uVar2;
    if ((uVar3 <= *(arg2 + 0x18) - uVar2) && (*(arg3 + 0x18) <= *(arg2 + 0x18))) {
        uVar5 = *(arg2 + 4);
        uVar6 = *(arg2 + 8);
        uVar7 = *(arg2 + 0xc);
        *arg1 = *arg2;
        *(arg1 + 4) = uVar5;
        *(arg1 + 8) = uVar6;
        *(arg1 + 0xc) = uVar7;
        uVar5 = *(arg2 + 0x14);
        uVar6 = *(arg2 + 0x18);
        uVar7 = *(arg2 + 0x1c);
        *(arg1 + 0x10) = *(arg2 + 0x10);
        *(arg1 + 0x14) = uVar5;
        *(arg1 + 0x18) = uVar6;
        *(arg1 + 0x1c) = uVar7;
        *(arg2 + 0x10) = 0;
        *(arg2 + 0x18) = 0xf;
        *arg2 = 0;
        iVar10 = arg1;
        if (0xf < *(arg1 + 0x18)) {
            iVar10 = *arg1;
        }
        if (0xf < *(arg3 + 0x18)) {
            arg3 = *arg3;
        }
        fcn.140015ebe(iVar10 + uVar2,arg3,uVar3 + 1);
        *(arg1 + 0x10) = uVar1;
        return arg1;
    }
    if (uVar2 <= *(arg3 + 0x18) - uVar3) {
        uVar5 = *(arg3 + 4);
        uVar6 = *(arg3 + 8);
        uVar7 = *(arg3 + 0xc);
        *arg1 = *arg3;
        *(arg1 + 4) = uVar5;
        *(arg1 + 8) = uVar6;
        *(arg1 + 0xc) = uVar7;
        uVar5 = *(arg3 + 0x14);
        uVar6 = *(arg3 + 0x18);
        uVar7 = *(arg3 + 0x1c);
        *(arg1 + 0x10) = *(arg3 + 0x10);
        *(arg1 + 0x14) = uVar5;
        *(arg1 + 0x18) = uVar6;
        *(arg1 + 0x1c) = uVar7;
        *(arg3 + 0x10) = 0;
        *(arg3 + 0x18) = 0xf;
        *arg3 = 0;
        iVar10 = *arg1;
        fcn.140015ec4(iVar10 + uVar2,iVar10,uVar3 + 1);
        if (0xf < *(arg2 + 0x18)) {
            arg2 = *arg2;
        }
        fcn.140015ebe(iVar10,arg2,uVar2);
        *(arg1 + 0x10) = uVar1;
        return arg1;
    }
    if (0x7fffffffffffffff - uVar2 < uVar3) {
        fcn.1400093e0();
        pcVar4 = swi(3);
        iVar10 = (*pcVar4)();
        return iVar10;
    }
    uVar8 = uVar1 | 0xf;
    if (uVar8 < 0x8000000000000000) {
        if (uVar8 < 0x16) {
            uVar8 = 0x16;
        }
        uVar11 = uVar8 + 1;
        if (0xfff < uVar11) {
            uVar9 = uVar8 + 0x28;
            if (uVar9 <= uVar11) {
                fcn.140009350();
                pcVar4 = swi(3);
                iVar10 = (*pcVar4)();
                return iVar10;
            }
            goto code_r0x00014000b281;
        }
    }
    else {
        uVar9 = 0x8000000000000027;
        uVar8 = 0x7fffffffffffffff;
code_r0x00014000b281:
        iVar10 = fcn.140014fcc();
        if (iVar10 != 0) {
            uVar12 = iVar10 + 0x27U & 0xffffffffffffffe0;
            *(uVar12 - 8) = iVar10;
            goto code_r0x00014000b2d7;
        }
        func_0x0001402dbea5();
        uVar11 = CONCAT71(uVar9 >> 8,uVar9 | extraout_AH);
    }
    if (uVar11 != 0) {
        uVar12 = fcn.140014fcc();
    }
code_r0x00014000b2d7:
    *arg1 = uVar12;
    *(arg1 + 0x10) = uVar1;
    *(arg1 + 0x18) = uVar8;
    if (0xf < *(arg2 + 0x18)) {
        arg2 = *arg2;
    }
    fcn.140015ebe(uVar12,arg2,uVar2);
    if (0xf < *(arg3 + 0x18)) {
        arg3 = *arg3;
    }
    fcn.140015ebe(uVar12 + uVar2,arg3,uVar3 + 1);
    return arg1;
}
