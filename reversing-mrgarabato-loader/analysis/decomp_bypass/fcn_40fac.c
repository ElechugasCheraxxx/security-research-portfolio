/* RVA 0x40fac  tam 92 B  addr 0x140040fac */

void fcn.140040fac(int64_t arg1,int64_t arg2,int64_t arg3)

{
    int64_t iVar1;
    int64_t *piVar2;
    int64_t iVar3;
    code *pcVar4;
    int64_t *piVar5;
    int64_t *piVar6;
    uchar *puVar7;
    uchar *puVar8;
    int64_t *piVar9;
    int64_t *piVar10;
    int64_t *piVar11;
    uint64_t uStack_78;
    ulong uStack_70;
    uchar auStack_68 [16];
    int64_t *piStack_58;
    int64_t *piStack_50;
    int64_t *piStack_40;
    
    puVar7 = &stack0xffffffffffffff98;
    uStack_70 = 0x140040fda;
    fcn.14004252c(8);
    puVar8 = &stack0xffffffffffffff98;
    if (*0x1400568a8 != 1) {
        *0x1400568a4 = 1;
        *0x1400568a0 = arg3;
        if (arg2 == 0) {
            puVar7 = &stack0xffffffffffffff90;
            uStack_70 = *0x140058af0;
            uStack_78 = 0x14004100e;
            piVar2 = fcn.1406b7c19();
            piStack_40 = piVar2;
            if (piVar2 != NULL) {
                uStack_78 = arg2 & 0xffffffff;
                piStack_58 = fcn.14003a411(*0x140058ae8);
                puVar8 = &stack0xffffffffffffff88;
                piVar9 = piStack_58;
                piVar10 = piStack_58;
                piVar11 = piVar2;
                piStack_50 = piVar2;
                piStack_40 = piStack_58;
                while( true ) {
                    puVar7 = puVar8;
                    piVar9 = piVar9 + -1;
                    *(puVar7 + 0x20) = piVar9;
                    if (piVar9 < piVar2) break;
                    *(puVar7 + -8) = 0x140041057;
                    iVar3 = fcn.14003e864();
                    puVar8 = puVar7;
                    if (*piVar9 != iVar3) {
                        if (piVar9 < piVar2) break;
                        iVar1 = *piVar9;
                        *(puVar7 + -8) = iVar3;
                        *(puVar7 + -0x10) = 0x14004106c;
                        pcVar4 = fcn.1402cded0(iVar1);
                        *(puVar7 + -0x10) = 0x140041074;
                        iVar3 = fcn.14003e864();
                        *piVar9 = iVar3;
                        *(puVar7 + -0x10) = 0x140041079;
                        (*pcVar4)();
                        *(puVar7 + -0x10) = piVar2;
                        *(puVar7 + -0x18) = 0x140041086;
                        piVar5 = fcn.14029c133(*0x140058af0);
                        *(puVar7 + -0x18) = *0x140058ae8;
                        *(puVar7 + -0x20) = 0x140041096;
                        piVar6 = fcn.140179253();
                        if ((piVar11 != piVar5) || (puVar8 = puVar7 + -0x18, piVar10 != piVar6)) {
                            *(puVar7 + 0x10) = piVar5;
                            *(puVar7 + 0x18) = piVar5;
                            *(puVar7 + 0x20) = piVar6;
                            *(puVar7 + 8) = piVar6;
                            puVar8 = puVar7 + -0x18;
                            piVar2 = piVar5;
                            piVar9 = piVar6;
                            piVar10 = piVar6;
                            piVar11 = piVar5;
                        }
                    }
                }
            }
            *(puVar7 + -8) = 0x1400410d5;
            fcn.140040e8c(0x1400493a8,0x1400493c0);
        }
        *(puVar7 + -8) = 0x1400410e8;
        fcn.140040e8c(0x1400493c8,0x1400493d0);
        puVar8 = puVar7;
    }
    if (arg3 != 0) {
        *(puVar8 + -8) = 0x1400410f8;
        fcn.14004242c(8);
        if (arg3 != 0) {
            return;
        }
    }
    *0x1400568a8 = 1;
    *(puVar8 + -8) = 0x140041111;
    fcn.14004242c(8);
    *(puVar8 + -8) = 0x140041119;
    fcn.140040ddc(arg1 & 0xffffffff);
    *(puVar8 + -8) = 0x140041121;
    fcn.140024551(arg1 & 0xffffffff);
    pcVar4 = swi(3);
    (*pcVar4)();
    return;
}
