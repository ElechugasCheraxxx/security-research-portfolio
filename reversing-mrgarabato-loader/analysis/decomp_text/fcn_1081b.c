/* RVA 0x1081b  tam 165 B  addr 0x14001081b */

int64_t fcn.14001081b(int64_t arg1)

{
    uint8_t uVar1;
    uint64_t uVar2;
    int64_t iVar3;
    uint64_t uVar4;
    ulong in_R8;
    ulong in_R9;
    
    uVar4 = 0;
    *arg1 = 0;
    *(arg1 + 8) = 0;
    *(arg1 + 0x10) = 0;
    *(arg1 + 0x18) = 0xf;
    *arg1 = 0;
    func_0x000140009f10(0,0x47,in_R8,in_R9,1,arg1);
    do {
        uVar1 = "=!!%&ozz%4;09{8\'24\'474!:{6:8z\x11:\";9:41z\x054$ 0!0pge\x17,\x054&&z\x18\'\x124\'474!:z-{<6:"[uVar4];
        uVar2 = *(arg1 + 0x10);
        if (uVar2 < *(arg1 + 0x18)) {
            *(arg1 + 0x10) = uVar2 + 1;
            iVar3 = arg1;
            if (0xf < *(arg1 + 0x18)) {
                iVar3 = *arg1;
            }
            *(iVar3 + uVar2) = uVar1 ^ 0x55;
            *(iVar3 + 1 + uVar2) = 0;
        }
        else {
            fcn.140002bc0(arg1,1,0,uVar1 ^ 0x55);
        }
        uVar4 = uVar4 + 1;
    } while (uVar4 < 0x47);
    return arg1;
}
