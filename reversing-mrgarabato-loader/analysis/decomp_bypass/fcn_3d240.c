/* RVA 0x3d240  tam 45 B  addr 0x14003d240 */

int64_t fcn.14003d240(int64_t arg1,int64_t arg2)

{
    *(arg1 + 8) = 0;
    *(arg1 + 0x10) = 0;
    *arg1 = 0x140049440;
    fcn.14003d1bc(arg1,*arg2);
    return arg1;
}
