/* RVA 0x40bee  tam 96 B  addr 0x140040bee */

uint32_t fcn.140040bee(int64_t arg1,int64_t arg2)

{
    int iVar1;
    uint32_t uVar2;
    int64_t unaff_RBP;
    uchar auStackX_10 [16];
    uchar auStackX_20 [8];
    
    if (arg1 == 0xffff) {
        uVar2 = 0;
    }
    else {
        if (arg1 < 0x100) {
            uVar2 = *(*0x140053ed0 + (arg1 & 0xffffU) * 2);
        }
        else {
            uVar2 = 1;
            iVar1 = func_0x00014002b50b(1,auStackX_10,1,auStackX_20);
            if (iVar1 != 0x33) {
                uVar2 = *(unaff_RBP + 0x48);
            }
            uVar2 = uVar2 & 0xffff;
        }
        uVar2 = uVar2 & arg2;
    }
    return uVar2;
}
