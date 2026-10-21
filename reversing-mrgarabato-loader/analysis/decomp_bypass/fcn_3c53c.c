/* RVA 0x3c53c  tam 161 B  addr 0x14003c53c */

int64_t fcn.14003c53c(int64_t arg1,int64_t arg2)

{
    uint32_t *puVar1;
    int64_t iVar2;
    int64_t iVar3;
    ulong uVar4;
    
    *(arg1 + 0x18) = 0;
    if (arg2 == 0) {
        iVar3 = func_0x00014003e9d8();
        *(arg1 + 0x10) = iVar3;
        iVar2 = *(iVar3 + 0xc0);
        *arg1 = iVar2;
        *(arg1 + 8) = *(iVar3 + 0xb8);
        if ((iVar2 != *0x1400539d0) && ((*0x1400535a0 & *(iVar3 + 200)) == 0)) {
            uVar4 = func_0x00014003e7ec();
            *arg1 = uVar4;
        }
        if ((*(arg1 + 8) != *0x1400534a0) && ((*0x1400535a0 & *(*(arg1 + 0x10) + 200)) == 0)) {
            uVar4 = func_0x00014003df1c();
            *(arg1 + 8) = uVar4;
        }
        if ((*(*(arg1 + 0x10) + 200) & 2) == 0) {
            puVar1 = *(arg1 + 0x10) + 200;
            *puVar1 = *puVar1 | 2;
            *(arg1 + 0x18) = 1;
        }
    }
    else {
        uVar4 = *(arg2 + 8);
        *arg1 = *arg2;
        *(arg1 + 8) = uVar4;
    }
    return arg1;
}
