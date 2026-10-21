/* RVA 0x16442  tam 38 B  addr 0x140016442 */

void fcn.140016440(ulong noname_0,int64_t arg1)

{
    if ((*(arg1 + 0x20) & 1) != 0) {
        *(arg1 + 0x20) = *(arg1 + 0x20) & 0xfffffffe;
        fcn.140003c00(*(arg1 + 0x58));
    }
    return;
}
