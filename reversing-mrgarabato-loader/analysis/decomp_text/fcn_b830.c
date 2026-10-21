/* RVA 0xb830  tam 68 B  addr 0x14000b830 */

void fcn.14000b830(int64_t arg1)

{
    int iVar1;
    int64_t iVar2;
    code *pcVar3;
    char cVar4;
    int64_t *piVar5;
    uchar *puVar6;
    uchar auStack_28 [32];
    
    puVar6 = &stack0xffffffffffffffd8;
    cVar4 = func_0x000140014ec1();
    if (cVar4 == '\0') {
        puVar6 = &stack0xffffffffffffffd0;
        func_0x00014016620d(*arg1);
    }
    piVar5 = *arg1;
    iVar2 = *piVar5;
    iVar1 = *(iVar2 + 4);
    *(puVar6 + -8) = iVar2;
    *(puVar6 + -0x10) = 0x14000b85f;
    piVar5 = func_0x0001406ac2c4(iVar1 + piVar5);
    if (piVar5 != NULL) {
        pcVar3 = *(*piVar5 + 0x10);
        *(puVar6 + -0x10) = 0x14000b86d;
        (*pcVar3)(piVar5);
    }
    return;
}
