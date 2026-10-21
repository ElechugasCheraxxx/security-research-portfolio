/* RVA 0x15820  tam 398 B  addr 0x140015820 */

uint64_t fcn.140015820(void)

{
    int64_t iVar1;
    char cVar2;
    uchar uVar3;
    int iVar4;
    uint32_t uVar5;
    int64_t *piVar6;
    uint32_t *puVar7;
    uint64_t uVar8;
    uint64_t uVar9;
    uint64_t unaff_RBX;
    uint64_t unaff_RSI;
    ulong unaff_RDI;
    
    do {
        *(*0x20 + 8) = unaff_RBX;
        *(*0x20 + 0x10) = unaff_RSI;
        *(*0x20 + -8) = unaff_RDI;
        *(*0x20 + -0x40) = 0x140015839;
        cVar2 = fcn.14001504c(1);
        if (cVar2 == '\0') {
            *(*0x20 + -0x40) = 0x140015981;
            func_0x000140015a10(7);
code_r0x000140015982:
            *(*0x20 + -0x40) = 0x14001598c;
            func_0x000140015a10(7);
        }
        else {
            uVar9 = unaff_RSI >> 8;
            unaff_RSI = unaff_RSI & 0xffffffffffffff00;
            *(*0x20 + -0x18) = 0;
            *(*0x20 + -0x40) = 0x14001584e;
            uVar3 = fcn.140015010();
            unaff_RBX = CONCAT71(unaff_RBX >> 8,uVar3);
            uVar8 = *0x140020b18;
            if (*0x140020b18 == 1) goto code_r0x000140015982;
            if (*0x140020b18 == 0) {
                *0x140020b18 = 1;
                *(*0x20 + -0x40) = 0x140015880;
                iVar4 = func_0x000140015f42(0x140018850,0x140018868);
                if (iVar4 != 0) {
                    return 0xff;
                }
                uVar8 = 0x140018780;
                *(*0x20 + -0x40) = 0x1400158a1;
                func_0x000140015f3c(0x140018780,0x140018848);
                *0x140020b18 = 2;
            }
            else {
                unaff_RSI = CONCAT71(uVar9,1);
                *(*0x20 + -0x18) = 1;
            }
            *(*0x20 + -0x40) = 0x1400158bc;
            fcn.1400151ac(CONCAT71(uVar8 >> 8,uVar3));
            *(*0x20 + -0x40) = 0x1400158c1;
            piVar6 = func_0x000140015d14();
            if (*piVar6 != 0) {
                *(*0x20 + -0x40) = 0x1400158d2;
                cVar2 = fcn.140015114(piVar6);
                if (cVar2 != '\0') {
                    *(*0x20 + -0x40) = 0x1400158e8;
                    (**0x140018758)(0,2);
                }
            }
            *(*0x20 + -0x40) = 0x1400158ed;
            piVar6 = func_0x000140015d1c();
            if (*piVar6 != 0) {
                *(*0x20 + -0x40) = 0x1400158fe;
                cVar2 = fcn.140015114(piVar6);
                if (cVar2 != '\0') {
                    iVar1 = *piVar6;
                    *(*0x20 + -0x40) = 0x14001590a;
                    func_0x000140015f66(iVar1);
                }
            }
            *(*0x20 + -0x40) = 0x14001590f;
            unaff_RDI = func_0x000140015f36();
            *(*0x20 + -0x40) = 0x140015917;
            func_0x000140015f5a();
            *(*0x20 + -0x40) = 0x14001591f;
            puVar7 = func_0x000140015f54();
            uVar9 = *puVar7;
            *(*0x20 + -0x40) = 0x14001592c;
            uVar5 = fcn.140012410(uVar9);
            unaff_RBX = uVar5;
            *(*0x20 + -0x40) = 0x140015933;
            cVar2 = func_0x000140015b64();
            if (cVar2 != '\0') {
                if (unaff_RSI == '\0') {
                    *(*0x20 + -0x40) = 0x140015941;
                    func_0x000140015f1e();
                }
                *(*0x20 + -0x40) = 0x14001594a;
                fcn.1400151d0(CONCAT71(uVar9 >> 8,1),0);
                return unaff_RBX;
            }
        }
        *(*0x20 + -0x40) = 0x140015993;
        func_0x000140015ef4(unaff_RBX & 0xffffffff);
        *(*0x20 + -0x40) = 0x14001599b;
        func_0x000140015f48(unaff_RBX & 0xffffffff);
        *(*0x20 + -0x68) = 0x1400159a5;
        func_0x000140015c24();
        *0x20 = *0x20 + -0x38;
    } while( true );
}
