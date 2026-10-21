/* RVA 0x419ba  tam 56 B  addr 0x1400419ba */

void fcn.1400419b4(void)

{
    ulong *puVar1;
    
    for (puVar1 = 0x14004d108; puVar1 < 0x14004d108; puVar1 = puVar1 + 1) {
        if (*puVar1 != NULL) {
            (**puVar1)();
        }
    }
    return;
}
