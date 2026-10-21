/* RVA 0x3b22  tam 114 B  addr 0x140003b22 */

void fcn.140003b20(int64_t arg1,int64_t arg2)

{
    uchar auStack_48 [32];
    int64_t iStack_28;
    uchar uStack_20;
    uint64_t uStack_18;
    
    uStack_18 = *0x140020600 ^ auStack_48;
    if (0xf < *(arg2 + 0x18)) {
        arg2 = *arg2;
    }
    uStack_20 = 1;
    *arg1 = 0x1400188a8;
    *(arg1 + 8) = 0;
    *(arg1 + 0x10) = 0;
    iStack_28 = arg2;
    fcn.140015e9a(&iStack_28);
    *arg1 = 0x140018930;
    fcn.1400153c0(uStack_18 ^ auStack_48);
    return;
}
