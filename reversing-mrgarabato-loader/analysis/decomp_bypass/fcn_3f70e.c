/* RVA 0x3f70e  tam 55 B  addr 0x14003f70e */

void fcn.14003f70c(ulong noname_0,int64_t arg1,int64_t arg2)

{
    int16_t iVar1;
    
    if (((*(arg1 + 0x18) & 0x40) == 0) || (*(arg1 + 0x10) != 0)) {
        iVar1 = func_0x000140043e30();
        if (iVar1 == -1) {
            *arg2 = 0xffffffff;
        }
        else {
            *arg2 = *arg2 + 1;
        }
    }
    else {
        *arg2 = *arg2 + 1;
    }
    return;
}
