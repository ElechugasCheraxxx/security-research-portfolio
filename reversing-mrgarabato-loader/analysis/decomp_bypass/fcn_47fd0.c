/* RVA 0x47fd0  tam 44 B  addr 0x140047fd0 */

void fcn.140047fd0(ulong noname_0,int64_t arg1)

{
    if ((*(arg1 + 0xb8) & 2) != 0) {
        *(arg1 + 0xb8) = *(arg1 + 0xb8) & 0xfffffffd;
        fcn.140023140(arg1 + 0x48);
    }
    return;
}
