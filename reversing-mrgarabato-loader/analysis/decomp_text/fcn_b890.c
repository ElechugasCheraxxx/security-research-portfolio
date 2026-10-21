/* RVA 0xb890  tam 126 B  addr 0x14000b890 */

int64_t fcn.14000b890(int64_t arg1,int64_t arg2)

{
    uchar uVar1;
    uchar *puVar2;
    ulong uVar3;
    uchar *puVar4;
    uchar *puVar5;
    int64_t aiStackX_8 [4];
    ulong auStack_30 [2];
    uchar auStack_20 [32];
    
    puVar5 = arg2;
    if (0xf < *(arg2 + 0x18)) {
        puVar5 = *arg2;
    }
    puVar4 = puVar5 + *(arg2 + 0x10);
    puVar2 = &stack0xffffffffffffffe0;
    for (; puVar5 != puVar4; puVar5 = puVar5 + 1) {
        uVar1 = *puVar5;
        *(puVar2 + -8) = 0x14000b8cb;
        uVar3 = func_0x000140001310(arg1,uVar1);
        *(puVar2 + -8) = uVar3;
        *(puVar2 + -0x10) = 0x14000b8db;
        func_0x00014012bc3d(uVar3,fcn.14000afa0);
        *(puVar2 + 0x28) = *(arg2 + 0x20);
        *(puVar2 + -0x10) = 0x14000b8ee;
        func_0x00014000afc0(puVar2 + 0x28);
        puVar2 = puVar2 + -8;
    }
    return arg1;
}
