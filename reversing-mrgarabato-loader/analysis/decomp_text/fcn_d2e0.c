/* RVA 0xd2e0  tam 92 B  addr 0x14000d2e0 */

void fcn.14000d2e0(void)

{
    uchar auStack_48 [32];
    uint uStack_28;
    uchar *puStack_20;
    uchar auStack_18 [4];
    uchar auStack_14 [4];
    uint64_t uStack_10;
    
    uStack_10 = *0x140020600 ^ auStack_48;
    fcn.140015e7c(0x13,1,0,auStack_18);
    puStack_20 = auStack_14;
    uStack_28 = 6;
    fcn.140015e82(0xc0000420,0,0,0);
    fcn.1400153c0(uStack_10 ^ auStack_48);
    return;
}
