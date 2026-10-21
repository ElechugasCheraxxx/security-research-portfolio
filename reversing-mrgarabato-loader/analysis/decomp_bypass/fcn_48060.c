/* RVA 0x48060  tam 44 B  addr 0x140048060 */

void fcn.140048060(ulong noname_0,int64_t arg1)

{
    if ((*(arg1 + 0xb8) & 2) != 0) {
        *(arg1 + 0xb8) = *(arg1 + 0xb8) & 0xfffffffd;
        fcn.140023140(arg1 + 0x48);
    }
    return;
}
