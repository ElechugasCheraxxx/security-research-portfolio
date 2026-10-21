/* RVA 0x16170  tam 38 B  addr 0x140016170 */

void fcn.140016170(ulong noname_0,int64_t arg1)

{
    if ((*(arg1 + 0x30) & 1) != 0) {
        *(arg1 + 0x30) = *(arg1 + 0x30) & 0xfffffffe;
        fcn.140003c00(*(arg1 + 0x38));
    }
    return;
}
