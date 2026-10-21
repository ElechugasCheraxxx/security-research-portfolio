/* RVA 0x41454  tam 115 B  addr 0x140041454 */

void fcn.140041454(ulong noname_0,int64_t arg1)

{
    uint64_t uVar1;
    uint64_t *puVar2;
    uchar *puVar3;
    uchar *puVar4;
    int64_t iVar5;
    uint64_t uVar6;
    int64_t aiStack_38 [2];
    uchar auStack_28 [32];
    
    puVar4 = &stack0xffffffffffffffd8;
    puVar2 = 0x1400588e0;
    iVar5 = 0x40;
    do {
        uVar6 = *puVar2;
        uVar1 = uVar6;
        if (uVar6 != 0) {
            for (; uVar6 < uVar1 + 0xb00; uVar6 = uVar6 + 0x58) {
                puVar3 = puVar4;
                if (*(uVar6 + 0xc) != 0) {
                    puVar3 = puVar4 + -8;
                    *(puVar4 + -8) = arg1;
                    *(puVar4 + -0x10) = 0x140041490;
                    func_0x0001401429b7(uVar6 + 0x10);
                }
                puVar4 = puVar3;
                uVar1 = *puVar2;
            }
            uVar6 = *puVar2;
            *(puVar4 + -8) = 0x1400414aa;
            fcn.14003dc60(uVar6);
            *puVar2 = 0;
        }
        puVar2 = puVar2 + 1;
        iVar5 = iVar5 + -1;
    } while (iVar5 != 0);
    return;
}
