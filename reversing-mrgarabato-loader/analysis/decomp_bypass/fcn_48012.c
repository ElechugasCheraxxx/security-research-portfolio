/* RVA 0x48012  tam 44 B  addr 0x140048012 */

void fcn.140048010(ulong noname_0,int64_t arg1)

{
    if ((*(arg1 + 0xb8) & 1) != 0) {
        *(arg1 + 0xb8) = *(arg1 + 0xb8) & 0xfffffffe;
        fcn.140023140(arg1 + 0x48);
    }
    return;
}
