/* RVA 0x40e18  tam 23 B  addr 0x140040e18 */

void fcn.140040e18(int64_t arg1)

{
    code *pcVar1;
    
    fcn.140040ddc(arg1);
    fcn.14025ad24(arg1 & 0xffffffff);
    pcVar1 = swi(3);
    (*pcVar1)();
    return;
}
