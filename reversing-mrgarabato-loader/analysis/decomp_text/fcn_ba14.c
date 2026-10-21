/* RVA 0xba14  tam 489 B  addr 0x14000ba14 */

void fcn.14000ba14(int64_t arg1)

{
    uint64_t uVar1;
    code *pcVar2;
    int iVar3;
    int64_t iVar4;
    uint64_t uVar5;
    char *pcVar6;
    uchar *puVar7;
    int64_t iVar8;
    uint64_t uVar9;
    uchar *puVar10;
    uint64_t uVar11;
    uint64_t auStack_80 [2];
    uchar auStack_70 [40];
    int64_t aiStack_48 [9];
    
    aiStack_48[8] = *0x140020600 ^ &stack0xffffffffffffff90;
    uVar9 = 0;
    aiStack_48[5] = 0;
    aiStack_48[6] = 0;
    aiStack_48[7] = 0xf;
    aiStack_48[4] = 0;
    puVar10 = &stack0xffffffffffffff90;
    do {
        uVar5 = *(arg1 + 0x10);
        uVar1 = *(arg1 + 0x18);
        iVar8 = arg1;
        if (0xf < uVar1) {
            iVar8 = *arg1;
        }
        if (uVar9 < uVar5) {
            *(puVar10 + -8) = 0x14000ba7d;
            iVar4 = func_0x000140015eb2(iVar8 + uVar9,0x5c,uVar5 - uVar9);
            if (iVar4 == 0) goto code_r0x00014000ba8a;
            uVar9 = iVar4 - iVar8;
        }
        else {
code_r0x00014000ba8a:
            uVar9 = 0xffffffffffffffff;
        }
        if (uVar9 == 0xffffffffffffffff) {
            if (0xf < uVar1) {
                arg1 = *arg1;
            }
            *(puVar10 + -8) = 0x14000bb7b;
            func_0x0001402dad85(arg1,0);
            in(0x85);
            *(uVar1 + 0x11) = 0;
            *(puVar10 + -8) = 0x14000bb86;
            func_0x000140192d46();
code_r0x00014000bb93:
            uVar9 = *(puVar10 + 0x60);
            if (0xf < uVar9) {
                uVar5 = uVar9 + 1;
                iVar8 = *(puVar10 + 0x48);
                iVar4 = iVar8;
                if (0xfff < uVar5) {
                    uVar5 = uVar9 + 0x28;
                    iVar4 = *(iVar8 + -8);
                    if (0x1f < (iVar8 - iVar4) - 8U) {
                        *(puVar10 + -8) = 0x14000bbcc;
                        func_0x00014015dafa();
                        pcVar2 = swi(3);
                        (*pcVar2)();
                        return;
                    }
                }
                *(puVar10 + -8) = 0x14000bbd3;
                fcn.140015008(iVar4,uVar5);
            }
            *(puVar10 + -8) = 0x14000bbe3;
            fcn.1400153c0(*(puVar10 + 0x68) ^ puVar10);
            return;
        }
        *(puVar10 + 0x28) = 0;
        *(puVar10 + 0x30) = 0;
        *(puVar10 + 0x38) = 0;
        *(puVar10 + 0x40) = 0;
        uVar11 = uVar9;
        if (uVar5 < uVar9) {
            uVar11 = uVar5;
        }
        iVar8 = arg1;
        if (0xf < uVar1) {
            iVar8 = *arg1;
        }
        *(puVar10 + -8) = 0x14000bacd;
        fcn.140001b90(puVar10 + 0x28,iVar8,uVar11);
        if (0xf < *(puVar10 + 0x60)) {
            if ((0xfff < *(puVar10 + 0x60) + 1) &&
               (uVar5 = (*(puVar10 + 0x48) - *(*(puVar10 + 0x48) + -8)) - 8, 0x1f < uVar5)) {
                *(puVar10 + -8) = uVar5;
                *(puVar10 + -0x10) = 0x14000bb67;
                func_0x0001402d41f4();
                pcVar2 = swi(3);
                (*pcVar2)();
                return;
            }
            *(puVar10 + -8) = 0x14000bb06;
            fcn.140015008();
        }
        *(puVar10 + 0x48) = *(puVar10 + 0x28);
        *(puVar10 + 0x50) = *(puVar10 + 0x30);
        *(puVar10 + 0x58) = *(puVar10 + 0x38);
        *(puVar10 + 0x60) = *(puVar10 + 0x40);
        puVar7 = puVar10;
        if (*(puVar10 + 0x38) != 0) {
            puVar7 = puVar10 + 0x48;
            if (0xf < *(puVar10 + 0x40)) {
                puVar7 = *(puVar10 + 0x28);
            }
            *(puVar10 + -8) = puVar7;
            *(puVar10 + -0x10) = 0x14000bb48;
            iVar3 = func_0x000140207a4a();
            puVar7 = puVar10 + -8;
            if (iVar3 == 0) {
                *(puVar10 + -0x10) = 0x14000bb51;
                pcVar6 = func_0x000140290733();
                uVar9 = CONCAT62(uVar9 >> 0x10,uVar9);
                *pcVar6 = *pcVar6 + pcVar6;
                puVar7 = puVar10 + -8;
                puVar10 = puVar10 + -8;
                if (*pcVar6 != '\0') goto code_r0x00014000bb93;
            }
        }
        uVar9 = uVar9 + 1;
        puVar10 = puVar7;
    } while( true );
}
