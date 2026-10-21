/* RVA 0x43d04  tam 100 B  addr 0x140043d04 */

void fcn.140043d04(int64_t arg1)

{
    code *pcVar1;
    
    if ((0x140053eff < arg1) && (arg1 < 0x140054291)) {
        fcn.14004252c((arg1 + -0x140053f00) / 0x30 + 0x10);
        *(arg1 + 0x18) = *(arg1 + 0x18) | 0x8000;
        return;
    }
    fcn.1401dcc43();
    pcVar1 = swi(3);
    (*pcVar1)();
    return;
}
