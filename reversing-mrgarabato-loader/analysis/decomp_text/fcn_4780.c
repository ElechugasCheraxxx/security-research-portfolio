/* RVA 0x4780  tam 66 B  addr 0x140004780 */

int64_t fcn.140004780(int64_t arg1,int64_t arg2)

{
    *arg1 = 0x1400188a8;
    fcn.140015ea0(arg1 + 8);
    if ((arg2 & 1U) != 0) {
        fcn.140015008(arg1,0x28);
    }
    return arg1;
}
