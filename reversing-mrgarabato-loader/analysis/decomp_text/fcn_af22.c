/* RVA 0xaf22  tam 48 B  addr 0x14000af22 */

void fcn.14000af20(int64_t arg1)

{
    code *pcVar1;
    uchar unaff_DIL;
    
    fcn.1402c6e51(*(*arg1 + 4) + arg1,10);
    fcn.14016aba8(arg1,unaff_DIL);
    fcn.1402106bc(arg1);
    pcVar1 = swi(3);
    (*pcVar1)();
    return;
}
