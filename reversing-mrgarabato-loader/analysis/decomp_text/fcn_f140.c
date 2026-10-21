/* RVA 0xf140  tam 147 B  addr 0x14000f140 */

void fcn.14000f140(void)

{
    ulong uVar1;
    code *pcVar2;
    char *pcVar3;
    int64_t iVar4;
    ulong *puVar5;
    uchar *puVar6;
    ulong *unaff_RBP;
    ulong auStack_80 [3];
    uchar auStack_68 [32];
    uint auStack_48 [4];
    char *apcStack_38 [4];
    char *pcStack_18;
    
    puVar5 = NULL;
    apcStack_38[2] = "\\\\.\\kdstinker";
    apcStack_38[3] = "\\\\.\\NiGgEr";
    pcVar3 = "\\\\.\\KsDumper";
    pcStack_18 = "\\\\.\\KsDumper";
    puVar6 = &stack0xffffffffffffff98;
    do {
        uVar1 = *(puVar6 + puVar5 * 8 + 0x40);
        *(puVar6 + 0x30) = 0;
        *(puVar6 + 0x28) = 0x80;
        *(puVar6 + 0x20) = 3;
        *(puVar6 + -8) = pcVar3;
        *(puVar6 + -0x10) = 0x14000f19e;
        iVar4 = fcn.1401a39e9(uVar1,0x80000000,1);
        if (iVar4 != -1) {
            *(puVar6 + -0x10) = 0x14000f1c4;
            fcn.14020b38f(
                         "start cmd /c START CMD /C \"COLOR C && TITLE Protection && ECHO KsDumper Detected. && TIMEOUT 10 >nul"
                         );
            *(puVar6 + -0x10) = 0xffffffffffe116e8;
            *(puVar6 + -0x18) = *puVar5;
            *unaff_RBP = 0x14000f1d1;
            fcn.140151c75();
            pcVar2 = swi(3);
            (*pcVar2)();
            return;
        }
        puVar5 = puVar5 + 1;
        pcVar3 = 0xffffffffffffffff;
        puVar6 = puVar6 + -8;
    } while (puVar5 < 3);
    return;
}
