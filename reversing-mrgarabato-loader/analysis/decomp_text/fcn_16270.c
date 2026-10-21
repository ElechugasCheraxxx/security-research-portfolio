/* RVA 0x16270  tam 38 B  addr 0x140016270 */

void fcn.140016270(ulong noname_0,int64_t arg1)

{
    if ((*(arg1 + 0x48) & 1) != 0) {
        *(arg1 + 0x48) = *(arg1 + 0x48) & 0xfffffffe;
        fcn.140003fe0(*(arg1 + 0x50));
    }
    return;
}
