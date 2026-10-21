/* RVA 0x43bfc  tam 224 B  addr 0x140043bfc */

ulong fcn.140043bfc(void)

{
    int64_t iVar1;
    int64_t iVar2;
    uint *puVar3;
    int64_t iVar4;
    
    iVar4 = 0x14;
    if (*0x1400588c0 == 0) {
        *0x1400588c0 = 0x200;
    }
    else if (*0x1400588c0 < 0x14) {
        *0x1400588c0 = 0x14;
    }
    *0x1400578a8 = func_0x000140040cd0(*0x1400588c0,8);
    if (*0x1400578a8 == 0) {
        *0x1400588c0 = 0x14;
        *0x1400578a8 = func_0x000140040cd0(0x14,8);
        if (*0x1400578a8 == 0) {
            return 0x1a;
        }
    }
    iVar1 = 0;
    iVar2 = 0x140053f00;
    do {
        *(iVar1 + *0x1400578a8) = iVar2;
        iVar2 = iVar2 + 0x30;
        iVar1 = iVar1 + 8;
        iVar4 = iVar4 + -1;
    } while (iVar4 != 0);
    iVar4 = 0;
    puVar3 = 0x140053f1c;
    iVar1 = 3;
    do {
        iVar2 = *((iVar4 & 0x1f) * 0x58 + *((iVar4 >> 5) * 8 + 0x1400588e0));
        if (((iVar2 == -1) || (iVar2 == -2)) || (iVar2 == 0)) {
            *puVar3 = 0xfffffffe;
        }
        iVar4 = iVar4 + 1;
        puVar3 = puVar3 + 0xc;
        iVar1 = iVar1 + -1;
    } while (iVar1 != 0);
    return 0;
}
