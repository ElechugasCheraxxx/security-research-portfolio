/* RVA 0x162f0  tam 38 B  addr 0x1400162f0 */

void fcn.1400162f0(ulong noname_0,int64_t arg1)

{
    if ((*(arg1 + 0x30) & 1) != 0) {
        *(arg1 + 0x30) = *(arg1 + 0x30) & 0xfffffffe;
        fcn.140003c00(arg1 + 0x38);
    }
    return;
}
