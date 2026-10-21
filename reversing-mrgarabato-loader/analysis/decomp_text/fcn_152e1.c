/* RVA 0x152e1  tam 106 B  addr 0x1400152e1 */

void fcn.1400152e1(int64_t arg1,int64_t arg2,int64_t arg3,int64_t arg4)

{
    int64_t iVar1;
    
    iVar1 = *(arg4 + 0x38);
    fcn.140015270(arg2,arg4,iVar1 + 4);
    if ((*(iVar1 + 4) & ((*(arg1 + 4) & 0x66) != 0) + 1) != 0) {
        fcn.140015eac(arg1,arg2,arg3,arg4);
    }
    return;
}
