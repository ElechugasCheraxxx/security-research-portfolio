/* RVA 0xb5f0  tam 238 B  addr 0x14000b5f0 */

//WARNING: Instruction at (ram,0x00014000b695) overlaps instruction at (ram,0x00014000b694)
//

void fcn.14000b5f0(int64_t arg1,int64_t arg2,int64_t arg3)

{
    code *pcVar1;
    int iVar2;
    int64_t iVar3;
    int64_t iVar4;
    int64_t iStack_a0;
    uchar auStack_98 [32];
    uint uStack_78;
    uint uStack_70;
    ulong uStack_68;
    uint64_t *puStack_60;
    ulong uStack_58;
    uchar auStack_50 [40];
    int64_t iStack_28;
    uint64_t uStack_20;
    uint64_t uStack_18;
    
    uStack_18 = *0x140020600 ^ auStack_98;
    *arg1 = 0;
    uStack_20 = 0;
    if (7 < *(arg3 + 0x18)) {
        arg3 = *arg3;
    }
    uStack_58 = 0;
    puStack_60 = &uStack_20;
    uStack_68 = 0;
    uStack_70 = 0x2011f;
    uStack_78 = 0;
    iStack_a0 = arg2;
    iVar2 = func_0x000140031f26(arg2,arg3,0,0);
    if (iVar2 != 0) {
        func_0x00014000b520(auStack_50,iVar2,"RegCreateKeyExW failed.");
        fcn.140015ea6(auStack_50,0x14001d4d0);
        pcVar1 = swi(3);
        (*pcVar1)();
        return;
    }
    iVar4 = *arg1;
    if ((((iVar4 != 0) && (5 < iVar4 + 0x80000000U)) && (iVar4 != -0x7ffffff9)) &&
       ((iVar4 != -0x7fffffa0 && (iVar4 != -0x7fffffb0)))) {
        iVar3 = func_0x000140227537();
        *(iVar3 + -0x75) = *(iVar3 + -0x75) + -1;
        iStack_28 = iVar4;
    }
    *arg1 = iStack_28;
    fcn.1400153c0(uStack_20 ^ &iStack_a0);
    return;
}
