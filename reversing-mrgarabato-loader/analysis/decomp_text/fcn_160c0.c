/* RVA 0x160c0  tam 49 B  addr 0x1400160c0 */

//WARNING: Instruction at (ram,0x0001400160eb) overlaps instruction at (ram,0x0001400160ea)
//

void fcn.1400160c0(ulong noname_0,int64_t arg1)

{
    if ((*(arg1 + 0x20) & 2) != 0) {
        *(arg1 + 0x20) = *(arg1 + 0x20) & 0xfffffffd;
        fcn.1402e8a99(arg1 + 0x178);
    }
    return;
}
