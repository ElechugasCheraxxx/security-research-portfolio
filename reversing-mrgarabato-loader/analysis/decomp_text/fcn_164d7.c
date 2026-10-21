/* RVA 0x164d7  tam 55 B  addr 0x1400164d7 */

void fcn.1400164d7(ulong noname_0,int64_t arg1)

{
    code *pcVar1;
    
    fcn.14000aad0(*(arg1 + 0x78),*(arg1 + 0x28),*(arg1 + 0x70));
    fcn.14000ee20(*(arg1 + 0x70),*(arg1 + 0x20),*(arg1 + 0x88));
    fcn.140015ea6(0,0);
    pcVar1 = swi(3);
    (*pcVar1)();
    return;
}
