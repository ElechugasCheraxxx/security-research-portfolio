/* RVA 0xd160  tam 71 B  addr 0x14000d160 */

char fcn.14000d160(int64_t arg1,int64_t arg2,int64_t arg3)

{
    int *piVar1;
    char cVar2;
    int64_t unaff_RBP;
    char cVar3;
    
    piVar1 = arg3 + 0x10;
    if (7 < *(arg3 + 0x18)) {
        arg3 = *arg3;
    }
    if (7 < *(arg2 + 0x18)) {
        arg2 = *arg2;
    }
    cVar3 = '\0';
    cVar2 = func_0x0001401844aa(*arg1,arg2,0,1,arg3,*piVar1 * 2 + 2);
    *(unaff_RBP + 5) = 0;
    return cVar2 + -0x7b + cVar3;
}
