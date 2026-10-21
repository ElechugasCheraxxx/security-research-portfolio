/* RVA 0x4742  tam 90 B  addr 0x140004742 */

void fcn.140004742(int64_t arg1)

{
    code *pcVar1;
    uchar auStack_20 [32];
    
    *(*(*arg1 + 4) + -0x88 + arg1 + 0x88) = 0x1400229e0;
    *(*(*arg1 + 4) + -0x8c + arg1 + 0x88) = *(*arg1 + 4) + -0x88;
    fcn.140003db0(arg1 + 8);
    fcn.1404d9f0b(arg1 + 0x10);
    *(&stack0xffffffffffffffe0 + 0x20) = 0x14000479a;
    fcn.140034029();
    pcVar1 = swi(3);
    (*pcVar1)();
    return;
}
