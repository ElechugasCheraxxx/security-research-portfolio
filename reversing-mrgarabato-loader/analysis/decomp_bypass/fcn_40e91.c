/* RVA 0x40e91  tam 16 B  addr 0x140040e91 */

void fcn.140040e91(int64_t arg1,int64_t arg2)

{
    do {
        if (*arg1 != NULL) {
            (**arg1)();
        }
        arg1 = arg1 + 8;
    } while (arg1 < arg2);
    return;
}
