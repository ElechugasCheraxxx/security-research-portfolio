/* RVA 0x40ec0  tam 57 B  addr 0x140040ec0 */

void fcn.140040ec0(int64_t arg1,int64_t arg2)

{
    int iVar1;
    
    iVar1 = 0;
    while ((arg1 < arg2 && (iVar1 == 0))) {
        if (*arg1 != NULL) {
            iVar1 = (**arg1)();
        }
        arg1 = arg1 + 8;
    }
    return;
}
