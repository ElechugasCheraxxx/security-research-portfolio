/* RVA 0x47dd2  tam 44 B  addr 0x140047dd2 */

void fcn.140047dd0(ulong noname_0,int64_t arg1)

{
    if ((*(arg1 + 0x4d8) & 1) != 0) {
        *(arg1 + 0x4d8) = *(arg1 + 0x4d8) & 0xfffffffe;
        fcn.140023140(arg1 + 0x60);
    }
    return;
}
