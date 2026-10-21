/* RVA 0x3eb72  tam 129 B  addr 0x14003eb72 */

ulong fcn.14003eb70(void)

{
    int iVar1;
    uint uVar2;
    uint *arg1;
    uint *puVar3;
    uchar *puVar4;
    uchar auStack_28 [32];
    
    func_0x000140040e48();
    iVar1 = func_0x000140042320();
    puVar4 = &stack0xffffffffffffffd8;
    if (iVar1 != 0) {
        *0x1400539e8 = func_0x000140164c48(0x14003e9fc);
        puVar4 = &stack0xffffffffffffffd0;
        if (((*0x1400539e8 != -1) &&
            (arg1 = func_0x000140040cd0(1,0x2c8), puVar4 = &stack0xffffffffffffffd0, arg1 != NULL)) &&
           (puVar3 = arg1, func_0x0001401825de(*0x1400539e8), puVar4 = &stack0xffffffffffffffd0, puVar3 != 0)) {
            fcn.14003e89c(arg1,0);
            uVar2 = func_0x000140037631();
            *(arg1 + 2) = 0xffffffffffffffff;
            *arg1 = uVar2;
            return 1;
        }
    }
    *(puVar4 + -8) = 0x14003ebe9;
    fcn.14003e874();
    return 0;
}
