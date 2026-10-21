/* RVA 0x16910  tam 47 B  addr 0x140016910 */

void fcn.140016910(ulong noname_0,int64_t arg1)

{
    if ((*(arg1 + 0xb8) & 0x10) != 0) {
        *(arg1 + 0xb8) = *(arg1 + 0xb8) & 0xffffffef;
        fcn.140003c00(arg1 + 0x90);
    }
    return;
}
