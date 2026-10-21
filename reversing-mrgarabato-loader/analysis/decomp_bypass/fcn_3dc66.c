/* RVA 0x3dc66  tam 61 B  addr 0x14003dc66 */

void fcn.14003dc60(int64_t arg1)

{
    uint *puVar1;
    int iVar2;
    uint uVar3;
    
    if ((arg1 != 0) && (iVar2 = fcn.14002e131(*0x1400569b8,0,arg1), iVar2 == 0)) {
        puVar1 = fcn.14003ef2c();
        uVar3 = fcn.1406b54b7();
        uVar3 = fcn.14003eee4(uVar3);
        *puVar1 = uVar3;
    }
    return;
}
