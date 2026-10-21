/* RVA 0x47a10  tam 47 B  addr 0x140047a10 */

void fcn.140047a10(ulong noname_0,int64_t arg1)

{
    if ((*(arg1 + 0xb0) & 1) != 0) {
        *(arg1 + 0xb0) = *(arg1 + 0xb0) & 0xfffffffe;
        fcn.140023140(*(arg1 + 0xb8));
    }
    return;
}
