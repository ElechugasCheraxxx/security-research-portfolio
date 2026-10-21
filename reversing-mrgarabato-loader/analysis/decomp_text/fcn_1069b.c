/* RVA 0x1069b  tam 168 B  addr 0x14001069b */

int64_t fcn.14001069b(int64_t arg1)

{
    uint64_t uVar1;
    int64_t iVar2;
    uint64_t uVar3;
    ulong in_R8;
    uint8_t uVar4;
    ulong in_R9;
    
    uVar3 = 0;
    *arg1 = 0;
    *(arg1 + 8) = 0;
    *(arg1 + 0x10) = 0;
    *(arg1 + 0x18) = 0xf;
    *arg1 = 0;
    func_0x000140009f10(0,0x83,in_R8,in_R9,1,arg1);
    do {
        uVar4 = *(uVar3 + 0x1400203e0) ^ 0x55;
        uVar1 = *(arg1 + 0x10);
        if (uVar1 < *(arg1 + 0x18)) {
            *(arg1 + 0x10) = uVar1 + 1;
            iVar2 = arg1;
            if (0xf < *(arg1 + 0x18)) {
                iVar2 = *arg1;
            }
            *(iVar2 + uVar1) = uVar4;
            *(iVar2 + 1 + uVar1) = 0;
        }
        else {
            fcn.140002bc0(arg1,1,0,uVar4);
        }
        uVar3 = uVar3 + 1;
    } while (uVar3 < 0x83);
    return arg1;
}
