/* RVA 0x15a10  tam 119 B  addr 0x140015a10 */

//WARNING: Control flow encountered bad instruction data

void fcn.140015a10(int64_t arg1)

{
    char *pcVar1;
    code *pcVar2;
    uint64_t uVar3;
    int64_t unaff_RDI;
    uchar auStackX_10 [24];
    int64_t var_e8h;
    int64_t var_4d8h;
    char acStack_580 [168];
    uchar auStack_4d8 [248];
    ulong uStack_3e0;
    int64_t var_10h;
    
    fcn.140037c00(0x17);
    pcVar2 = swi(0x29);
    (*pcVar2)(arg1 & 0xffffffff);
    fcn.140015a08(3);
    fcn.140015eca(auStack_4d8,0,0x4d0);
    fcn.1402badab(auStack_4d8);
    uVar3 = fcn.140254a50(uStack_3e0,auStackX_10,0);
    acStack_580[unaff_RDI] = acStack_580[unaff_RDI] << 3;
    pcVar1 = (uVar3 & 0xffffffffffffff38) - 0x73;
    *pcVar1 = *pcVar1 + uVar3 + -0x7b;
    //WARNING: Bad instruction - Truncating control flow here
    halt_baddata();
}
