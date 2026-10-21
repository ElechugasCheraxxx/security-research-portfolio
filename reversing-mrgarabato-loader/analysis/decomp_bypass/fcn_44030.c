/* RVA 0x44030  tam 54 B  addr 0x140044030 */

void fcn.140044030(void)

{
    ulong uVar1;
    ulong in_RAX;
    ulong *puVar2;
    uchar *puVar3;
    int64_t iVar4;
    ulong auStack_38 [2];
    uchar auStack_28 [32];
    
    puVar2 = 0x1400542c0;
    iVar4 = 10;
    puVar3 = &stack0xffffffffffffffd8;
    do {
        uVar1 = *puVar2;
        *(puVar3 + -8) = in_RAX;
        *(puVar3 + -0x10) = 0x14004404f;
        in_RAX = fcn.140244444(uVar1);
        *puVar2 = in_RAX;
        puVar2 = puVar2 + 1;
        iVar4 = iVar4 + -1;
        puVar3 = puVar3 + -8;
    } while (iVar4 != 0);
    return;
}
