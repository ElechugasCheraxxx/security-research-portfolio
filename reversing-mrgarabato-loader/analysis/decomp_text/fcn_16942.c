/* RVA 0x16942  tam 52 B  addr 0x140016942 */

void fcn.140016940(ulong noname_0,int64_t arg1)

{
    if ((*(arg1 + 0xb8) & 0x40000000) != 0) {
        *(arg1 + 0xb8) = *(arg1 + 0xb8) & 0xbfffffff;
        fcn.140003c00(arg1 + 0x90);
    }
    return;
}
