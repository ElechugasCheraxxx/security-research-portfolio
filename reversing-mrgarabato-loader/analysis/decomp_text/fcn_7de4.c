/* RVA 0x7de4  tam 297 B  addr 0x140007de4 */

void fcn.140007de0(int64_t arg1,int64_t arg2)

{
    uint *puVar1;
    int iVar2;
    uchar *puVar3;
    int64_t iVar4;
    uint64_t uStack_90;
    uchar auStack_88 [24];
    uchar *puStack_70;
    ulong uStack_68;
    uint uStack_60;
    ulong uStack_50;
    ulong uStack_48;
    ulong uStack_40;
    uint64_t uStack_38;
    uint64_t uStack_28;
    
    puVar3 = &stack0xffffffffffffff78;
    uStack_28 = *0x140020600 ^ &stack0xffffffffffffff78;
    uStack_50 = arg1;
    if (*(arg2 + 0x10) == 0) {
        *arg1 = 0;
        *(arg1 + 8) = 0;
        *(arg1 + 0x10) = 0;
        *(arg1 + 0x18) = 0;
        uStack_90 = 0x140007e2a;
        func_0x000140001c90(0,0x140018b78,0);
    }
    else {
        iVar4 = arg2;
        if (0xf < *(arg2 + 0x18)) {
            iVar4 = *arg2;
        }
        uStack_60 = 0;
        uStack_68 = 0;
        puVar3 = &stack0xffffffffffffff70;
        uStack_90 = uStack_28;
        iVar2 = func_0x00014025cf2d(0xfde9,0,iVar4);
        if (iVar2 < 1) {
            *arg1 = 0;
            *(arg1 + 8) = 0;
            *(arg1 + 0x10) = 0;
            *(arg1 + 0x18) = 0;
            func_0x000140001c90(arg1,0x140018b78,0);
        }
        else {
            uStack_40 = 0;
            uStack_38 = 0;
            uStack_50 = NULL;
            uStack_48 = 0;
            func_0x000140001dd0(&stack0xffffffffffffffb0,0,iVar2);
            puVar1 = arg2 + 0x10;
            puStack_70 = &stack0xffffffffffffffb0;
            if (7 < uStack_38) {
                puStack_70 = uStack_50;
            }
            if (0xf < *(arg2 + 0x18)) {
                arg2 = *arg2;
            }
            uStack_68 = CONCAT44(uStack_68._4_4_,iVar2);
            func_0x000140280763(0xfde9,0,arg2,*puVar1);
            *arg1 = uStack_50;
            *(arg1 + 4) = uStack_50._4_4_;
            *(arg1 + 8) = uStack_48;
            *(arg1 + 0xc) = uStack_48._4_4_;
            *(arg1 + 0x10) = uStack_40;
            *(arg1 + 0x18) = uStack_38;
        }
    }
    *(puVar3 + -8) = 0x140007f01;
    fcn.1400153c0(*(puVar3 + 0x60) ^ puVar3);
    return;
}
