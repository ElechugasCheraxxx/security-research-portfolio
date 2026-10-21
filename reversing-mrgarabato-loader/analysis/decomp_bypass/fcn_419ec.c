/* RVA 0x419ec  tam 56 B  addr 0x1400419ec */

void fcn.1400419ec(void)

{
    ulong *puVar1;
    
    for (puVar1 = 0x14004d118; puVar1 < 0x14004d118; puVar1 = puVar1 + 1) {
        if (*puVar1 != NULL) {
            (**puVar1)();
        }
    }
    return;
}
