/* RVA 0x3ef6c  tam 70 B  addr 0x14003ef6c */

void fcn.14003ef6c(int64_t arg1)

{
    uint uVar1;
    int64_t iVar2;
    uint *puVar3;
    
    iVar2 = fcn.14003e954();
    if (iVar2 == 0) {
        puVar3 = 0x140053b5c;
    }
    else {
        puVar3 = iVar2 + 0x14;
    }
    *puVar3 = arg1;
    iVar2 = fcn.14003e954();
    puVar3 = 0x140053b58;
    if (iVar2 != 0) {
        puVar3 = iVar2 + 0x10;
    }
    uVar1 = fcn.14003eee4(arg1 & 0xffffffff);
    *puVar3 = uVar1;
    return;
}
