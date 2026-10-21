/* RVA 0x165a0  tam 38 B  addr 0x1400165a0 */

void fcn.1400165a0(ulong noname_0,int64_t arg1)

{
    if ((*(arg1 + 0x68) & 1) != 0) {
        *(arg1 + 0x68) = *(arg1 + 0x68) & 0xfffffffe;
        fcn.140003c00(arg1 + 0x48);
    }
    return;
}
