/* RVA 0x3e796  tam 87 B  addr 0x14003e796 */

int64_t fcn.14003e794(int64_t arg1,int64_t arg2)

{
    int *arg1_00;
    int *piVar1;
    
    if ((arg2 == 0) || (arg1 == 0)) {
        arg2 = 0;
    }
    else {
        arg1_00 = *arg1;
        if (arg1_00 != arg2) {
            *arg1 = arg2;
            func_0x00014003e4e8(arg2);
            if (arg1_00 != NULL) {
                piVar1 = arg1_00;
                func_0x00014003e574();
                if ((*piVar1 == 0) && (piVar1 != 0x140053870)) {
                    fcn.14003e618(arg1_00);
                }
            }
        }
    }
    return arg2;
}
