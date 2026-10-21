/* RVA 0x4900d  tam 31 B  addr 0x14004900d */

void fcn.14004900d(int64_t arg1)

{
    code *pcVar1;
    
    *(arg1 + 0x4e43bfe8) = *(arg1 + 0x4e43bfe8) >> 1;
    pcVar1 = swi(1);
    (*pcVar1)();
    return;
}
