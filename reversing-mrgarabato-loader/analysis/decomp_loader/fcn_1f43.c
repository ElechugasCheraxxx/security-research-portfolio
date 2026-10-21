/* RVA 0x1f43  tam 122 B  addr 0x140001f43 */

void fcn.140001f43(int64_t arg1,int64_t arg2,int64_t arg3)

{
    char cVar1;
    int64_t *piVar2;
    
    cVar1 = *(arg3 + 0x19);
    while (cVar1 == '\0') {
        fcn.140001f40(arg1,arg2,*(arg3 + 0x10));
        piVar2 = *arg3;
        fcn.1400094b0(arg3 + 0x40);
        fcn.1400094b0(arg3 + 0x20);
        fcn.14001a940(arg3,0x60);
        arg3 = piVar2;
        cVar1 = *(piVar2 + 0x19);
    }
    return;
}
