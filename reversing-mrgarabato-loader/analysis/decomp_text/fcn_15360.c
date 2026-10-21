/* RVA 0x15360  tam 78 B  addr 0x140015360 */

void fcn.140015360(void)

{
    uchar *in_RAX;
    uchar *puVar1;
    uchar *puVar2;
    int64_t unaff_GS_OFFSET;
    uchar auStackX_8 [32];
    
    puVar1 = auStackX_8 + -in_RAX;
    if (auStackX_8 < in_RAX) {
        puVar1 = NULL;
    }
    puVar2 = *(unaff_GS_OFFSET + 0x10);
    if (puVar1 < puVar2) {
        do {
            puVar2 = puVar2 + -0x1000;
            *puVar2 = 0;
        } while ((puVar1 & 0xfffffffffffff000) != puVar2);
    }
    return;
}
