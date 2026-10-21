/* RVA 0x414d8  tam 304 B  addr 0x1400414d8 */

ulong fcn.1400414c8(void)

{
    char cVar1;
    code *pcVar2;
    int iVar3;
    int iVar4;
    int64_t iVar5;
    ulong uVar6;
    char *pcVar7;
    int64_t *piVar8;
    
    if (*0x140058af8 == 0) {
        fcn.14003e4c0();
    }
    iVar3 = 0;
    pcVar7 = *0x1400567e8;
    if (*0x1400567e8 != NULL) {
        for (; *pcVar7 != '\0'; pcVar7 = pcVar7 + iVar5 + 1) {
            if (*pcVar7 != '=') {
                iVar3 = iVar3 + 1;
            }
            iVar5 = fcn.140040870(pcVar7);
        }
        *0x140056870 = func_0x000140040cd0(iVar3 + 1,8);
        if (*0x140056870 != NULL) {
            cVar1 = **0x1400567e8;
            piVar8 = *0x140056870;
            pcVar7 = *0x1400567e8;
            do {
                if (cVar1 == '\0') {
                    fcn.14003dc60(*0x1400567e8);
                    *0x1400567e8 = NULL;
                    *piVar8 = 0;
                    *0x140058ae0 = 1;
                    return 0;
                }
                iVar3 = fcn.140040870(pcVar7);
                iVar3 = iVar3 + 1;
                if (*pcVar7 != '=') {
                    iVar5 = func_0x000140040cd0(iVar3,1);
                    *piVar8 = iVar5;
                    if (iVar5 == 0) {
                        fcn.14003dc60(*0x140056870);
                        *0x140056870 = NULL;
                        return 0xffffffff;
                    }
                    iVar4 = fcn.14003d128(iVar5,iVar3,pcVar7);
                    if (iVar4 != 0) {
                        fcn.14003ee20(0,0,0,0,0);
                        pcVar2 = swi(3);
                        uVar6 = (*pcVar2)();
                        return uVar6;
                    }
                    piVar8 = piVar8 + 1;
                }
                pcVar7 = pcVar7 + iVar3;
                cVar1 = *pcVar7;
            } while( true );
        }
    }
    return 0xffffffff;
}
