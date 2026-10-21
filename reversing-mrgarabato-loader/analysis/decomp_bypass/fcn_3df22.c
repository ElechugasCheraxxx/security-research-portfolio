/* RVA 0x3df22  tam 180 B  addr 0x14003df22 */

int * fcn.14003df22(void)

{
    int64_t iVar1;
    int *arg1;
    
    iVar1 = func_0x00014003e9d8();
    if (((*0x1400535a0 & *(iVar1 + 200)) == 0) || (*(iVar1 + 0xc0) == 0)) {
        func_0x00014004252c(0xd);
        arg1 = *(iVar1 + 0xb8);
        if (arg1 != *0x1400534a0) {
            if (arg1 != NULL) {
                LOCK();
                *arg1 = *arg1 + -1;
                UNLOCK();
                if ((*arg1 == 0) && (arg1 != 0x140053070)) {
                    fcn.14003dc60(arg1);
                }
            }
            *(iVar1 + 0xb8) = *0x1400534a0;
            arg1 = *0x1400534a0;
            LOCK();
            **0x1400534a0 = **0x1400534a0 + 1;
            UNLOCK();
        }
        fcn.14004242c(0xd);
    }
    else {
        arg1 = *(iVar1 + 0xb8);
    }
    if (arg1 == NULL) {
        func_0x000140041158(0x20);
    }
    return arg1;
}
