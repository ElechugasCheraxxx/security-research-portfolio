/* RVA 0x3a30  tam 60 B  addr 0x140003a30 */

int64_t fcn.140003a30(int64_t arg1,int64_t arg2)

{
    *arg1 = 0x1400188a8;
    *(arg1 + 8) = 0;
    *(arg1 + 0x10) = 0;
    fcn.140015e9a(arg2 + 8);
    *arg1 = 0x1400188f0;
    return arg1;
}
