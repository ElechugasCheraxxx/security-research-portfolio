/* RVA 0x45400  tam 122 B  addr 0x140045400 */

uint fcn.140045400(int64_t arg1)

{
    uint uVar1;
    uint uVar2;
    int iVar3;
    uint *puVar4;
    
    uVar1 = 0xffffffff;
    if (arg1 == 0) {
        puVar4 = fcn.14003ef2c();
        *puVar4 = 0x16;
        fcn.14003eec4();
        uVar1 = 0xffffffff;
    }
    else {
        if ((*(arg1 + 0x18) & 0x83) != 0) {
            uVar1 = fcn.140044e6c(arg1);
            func_0x00014004573c(arg1);
            uVar2 = fcn.140043e08(arg1);
            iVar3 = func_0x000140045678(uVar2);
            if (iVar3 < 0) {
                uVar1 = 0xffffffff;
            }
            else if (*(arg1 + 0x28) != 0) {
                fcn.14003dc60(*(arg1 + 0x28));
                *(arg1 + 0x28) = 0;
            }
        }
        *(arg1 + 0x18) = 0;
    }
    return uVar1;
}
