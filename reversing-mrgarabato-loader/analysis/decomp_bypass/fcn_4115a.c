/* RVA 0x4115a  tam 38 B  addr 0x14004115a */

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
