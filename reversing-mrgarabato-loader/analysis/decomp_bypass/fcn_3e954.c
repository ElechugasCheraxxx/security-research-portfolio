/* RVA 0x3e954  tam 132 B  addr 0x14003e954 */

uint64_t fcn.14003e954(void)

{
    uint32_t uVar1;
    int iVar2;
    uint *arg1;
    int64_t iVar3;
    uchar *puVar4;
    uint64_t uVar5;
    uint64_t uStack_40;
    uint64_t auStack_38 [6];
    
    auStack_38[0] = 0x14003e964;
    uVar1 = func_0x000140203931();
    uVar5 = uVar1;
    uStack_40 = 0x14003e972;
    auStack_38[0] = uVar5;
    arg1 = func_0x0001401333d9(*0x1400539e8);
    puVar4 = &stack0xffffffffffffffc8;
    if (arg1 == NULL) {
        uStack_40 = 0x14003e987;
        arg1 = func_0x000140040cd0(1,0x2c8);
        puVar4 = &stack0xffffffffffffffc8;
        if (arg1 != NULL) {
            puVar4 = &stack0xffffffffffffffc0;
            uStack_40 = uVar5;
            iVar2 = func_0x00014015ac84(*0x1400539e8);
            if (iVar2 == 0) {
                fcn.14003dc60(arg1);
                arg1 = NULL;
            }
            else {
                fcn.14003e89c(arg1,0);
                iVar3 = func_0x0001402a5198();
                *(iVar3 + -0x7d) = *(iVar3 + -0x7d) + -1;
                *arg1 = iVar3;
                puVar4 = &stack0xffffffffffffffc0;
            }
        }
    }
    *(puVar4 + -8) = 0x14003e9c9;
    func_0x00014020dfed(uVar5);
    in(0x48);
    return arg1 & 0xffffffff;
}
