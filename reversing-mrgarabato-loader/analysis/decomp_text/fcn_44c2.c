/* RVA 0x44c2  tam 68 B  addr 0x1400044c2 */

void fcn.1400044c0(int64_t arg1)

{
    int iVar1;
    code *pcVar2;
    char cVar3;
    int64_t *piVar4;
    ulong in_RDX;
    uchar *puVar5;
    ulong uStack_30;
    uchar auStack_28 [32];
    
    puVar5 = &stack0xffffffffffffffd8;
    uStack_30 = 0x1400044ce;
    cVar3 = func_0x000140014ec1();
    if (cVar3 == '\0') {
        puVar5 = &stack0xffffffffffffffd0;
        uStack_30 = in_RDX;
        func_0x00014020b62a(*arg1);
    }
    piVar4 = *arg1;
    iVar1 = *(*piVar4 + 4);
    *(puVar5 + -8) = arg1;
    *(puVar5 + -0x10) = 0x1400044ef;
    piVar4 = func_0x00014015868a(iVar1 + piVar4);
    if (piVar4 != NULL) {
        pcVar2 = *(*piVar4 + 0x10);
        *(puVar5 + -0x10) = 0x1400044fd;
        (*pcVar2)(piVar4);
    }
    return;
}
