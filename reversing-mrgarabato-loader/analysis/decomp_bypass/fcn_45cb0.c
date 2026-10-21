/* RVA 0x45cb0  tam 94 B  addr 0x140045cb0 */

void fcn.140045cb0(int64_t arg1)

{
    int64_t iVar1;
    int64_t iVar2;
    
    iVar1 = fcn.14003e9d8();
    if (arg1 != *(iVar1 + 0x120)) {
        fcn.14003f234();
    }
    iVar1 = fcn.14003e9d8();
    iVar1 = *(iVar1 + 0x120);
    while( true ) {
        if (iVar1 == 0) {
            fcn.14003f234();
            return;
        }
        if (arg1 == iVar1) break;
        iVar1 = *(iVar1 + 8);
    }
    iVar2 = fcn.14003e9d8();
    *(iVar2 + 0x120) = *(iVar1 + 8);
    return;
}
