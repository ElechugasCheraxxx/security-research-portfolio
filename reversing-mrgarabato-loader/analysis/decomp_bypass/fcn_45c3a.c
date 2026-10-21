/* RVA 0x45c3a  tam 67 B  addr 0x140045c3a */

int64_t fcn.140045c38(int64_t arg1,int64_t arg2)

{
    int64_t iVar1;
    ulong uVar2;
    
    *arg1 = arg2;
    iVar1 = fcn.14003e9d8();
    if (arg1 < *(iVar1 + 0x120)) {
        iVar1 = fcn.14003e9d8();
        uVar2 = *(iVar1 + 0x120);
    }
    else {
        uVar2 = 0;
    }
    *(arg1 + 8) = uVar2;
    iVar1 = fcn.14003e9d8();
    *(iVar1 + 0x120) = arg1;
    return arg1;
}
