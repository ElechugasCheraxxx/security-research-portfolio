/* RVA 0x41158  tam 38 B  addr 0x140041158 */

void fcn.140041158(int64_t arg1)

{
    code *pcVar1;
    
    fcn.140042fb0();
    fcn.140042d50(arg1 & 0xffffffff);
    fcn.140040fac(0xff,1,0);
    pcVar1 = swi(3);
    (*pcVar1)();
    return;
}
