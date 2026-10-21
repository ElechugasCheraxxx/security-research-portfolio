/* RVA 0x3d1cc  tam 50 B  addr 0x14003d1cc */

void fcn.14003d1c1(int64_t arg1,int64_t arg2)

{
    int64_t iVar1;
    int64_t arg1_00;
    
    iVar1 = fcn.140040870(arg2);
    arg1_00 = fcn.14003f11c(iVar1 + 1);
    *(arg1 + 8) = arg1_00;
    if (arg1_00 != 0) {
        fcn.14003d128(arg1_00,iVar1 + 1,arg2);
        *(arg1 + 0x10) = 1;
    }
    return;
}
