/* RVA 0x1f40  tam 3 B  addr 0x140001f40 */

void fcn.140001f40(ulong param_1,ulong param_2,int64_t *param_3)

{
    char cVar1;
    int64_t *piVar2;
    
    cVar1 = *(param_3 + 0x19);
    while (cVar1 == '\0') {
        fcn.140001f40(param_1,param_2,param_3[2]);
        piVar2 = *param_3;
        fcn.1400094b0(param_3 + 8);
        fcn.1400094b0(param_3 + 4);
        fcn.14001a940(param_3,0x60);
        param_3 = piVar2;
        cVar1 = *(piVar2 + 0x19);
    }
    return;
}
