/* RVA 0x16602  tam 38 B  addr 0x140016602 */

void fcn.140016600(ulong noname_0,int64_t arg1)

{
    if ((*(arg1 + 0x20) & 1) != 0) {
        *(arg1 + 0x20) = *(arg1 + 0x20) & 0xfffffffe;
        fcn.140003c00(*(arg1 + 0x28));
    }
    return;
}
