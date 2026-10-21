/* RVA 0x4573e  tam 55 B  addr 0x14004573e */

void fcn.14004573c(int64_t arg1)

{
    if (((*(arg1 + 0x18) & 0x83) != 0) && ((*(arg1 + 0x18) & 8) != 0)) {
        fcn.14003dc60(*(arg1 + 0x10));
        *(arg1 + 0x18) = *(arg1 + 0x18) & 0xfffffbf7;
        *arg1 = 0;
        *(arg1 + 0x10) = 0;
        *(arg1 + 8) = 0;
    }
    return;
}
