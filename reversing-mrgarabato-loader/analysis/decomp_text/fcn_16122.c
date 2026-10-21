/* RVA 0x16122  tam 41 B  addr 0x140016122 */

void fcn.140016120(ulong noname_0,int64_t arg1)

{
    if ((*(arg1 + 0x20) & 1) != 0) {
        *(arg1 + 0x20) = *(arg1 + 0x20) & 0xfffffffe;
        fcn.140003dd0(*(arg1 + 0x90));
    }
    return;
}
