/* RVA 0x48356  tam 142 B  addr 0x140048356 */

void fcn.140048353(ulong noname_0,int64_t arg1)

{
    int *piVar1;
    int64_t iVar2;
    int iVar3;
    
    fcn.140045cb0(*(arg1 + 0x50));
    if ((((*(arg1 + 0x20) == 0) && (piVar1 = *(arg1 + 200), *piVar1 == -0x1f928c9d)) && (piVar1[6] == 4)) &&
       (((piVar1[8] == 0x19930520 || (piVar1[8] == 0x19930521)) || (piVar1[8] == 0x19930522)))) {
        iVar3 = fcn.140045c7c(*(piVar1 + 10));
        if (iVar3 != 0) {
            func_0x000140046280(piVar1,1);
        }
    }
    iVar2 = fcn.14003e9d8();
    *(iVar2 + 0xf0) = *(arg1 + 0xd0);
    iVar2 = fcn.14003e9d8();
    *(iVar2 + 0xf8) = *(arg1 + 0xd8);
    return;
}
