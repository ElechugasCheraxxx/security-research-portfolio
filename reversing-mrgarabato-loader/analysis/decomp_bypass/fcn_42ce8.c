/* RVA 0x42ce8  tam 58 B  addr 0x140042ce8 */

ulong fcn.140042ce8(int64_t arg1)

{
    code *pcVar1;
    uint *puVar2;
    ulong uVar3;
    
    if (arg1 == 0) {
        puVar2 = fcn.14003ef2c();
        *puVar2 = 0x16;
        fcn.14003eec4();
        return 0xffffffffffffffff;
    }
    fcn.14016c78e(*0x1400569b8,0,arg1);
    pcVar1 = swi(3);
    uVar3 = (*pcVar1)();
    return uVar3;
}
