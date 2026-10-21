/* RVA 0x4670  tam 146 B  addr 0x140004670 */

int64_t fcn.140004670(int64_t arg1,int64_t arg2)

{
    int iVar1;
    code *pcVar2;
    
    *(*(*(arg1 + -0x88) + 4) + -0x88 + arg1) = 0x140018ab0;
    iVar1 = *(*(arg1 + -0x88) + 4);
    *(iVar1 + -0x8c + arg1) = iVar1 + -0x88;
    fcn.140003c70(arg1 + -0x80);
    fcn.1402e9daa(arg1 + -0x78);
    fcn.140219d20(arg1);
    pcVar2 = swi(0x40);
    (*pcVar2)();
    if ((arg1 & 0x100U) != 0) {
        fcn.140015008(arg1 + -0x88,0xe8);
    }
    return arg1 + -0x88;
}
