/* RVA 0x1229e  tam 371 B  addr 0x14001229e */

uchar fcn.140012290(int64_t arg1)

{
    uchar uVar1;
    uint64_t uVar2;
    uint64_t uVar3;
    int32_t var_20h;
    int32_t var_1ch;
    int32_t var_18h;
    int16_t var_14h;
    ushort uStack_1a;
    int8_t var_11h;
    int16_t var_bp_10h;
    int8_t var_eh;
    
    uVar3 = 0;
    _var_20h = 0x3e2a343839213925;
    _var_18h = CONCAT26(uStack_1a,0x1003b253975);
    uVar2 = uVar3;
    do {
        *(&var_20h + uVar2) = *(&var_20h + uVar2) ^ uVar2 + 0x53U;
        uVar2 = uVar2 + 1;
    } while (uVar2 < 0xc);
    _var_18h = _var_18h;
    fcn.14000f1e0(arg1,&var_20h);
    _var_20h = 0x282d3d2537223925;
    _var_18h = 0x10005273b73253a;
    uVar2 = uVar3;
    do {
        *(&var_20h + uVar2) = *(&var_20h + uVar2) ^ uVar2 + 0x53U;
        uVar2 = uVar2 + 1;
    } while (uVar2 < 0xe);
    _var_18h = _var_18h & 0xffffffffffffff;
    fcn.14000f1e0(arg1,&var_20h);
    _var_20h = 0x292c3d2537223925;
    _var_18h = 0x10005273b732e3e;
    uVar2 = uVar3;
    do {
        *(&var_20h + uVar2) = *(&var_20h + uVar2) ^ uVar2 + 0x53U;
        uVar2 = uVar2 + 1;
    } while (uVar2 < 0xe);
    _var_18h = _var_18h & 0xffffffffffffff;
    fcn.14000f1e0(arg1,&var_20h);
    _var_20h = *0x14001a440;
    _var_18h = *0x14001a448;
    var_bp_10h = 6;
    uVar2 = uVar3;
    do {
        *(&var_20h + uVar2) = *(&var_20h + uVar2) ^ uVar2 + 0x53U;
        uVar2 = uVar2 + 1;
    } while (uVar2 < 0x11);
    var_eh = 0;
    fcn.14000f1e0(arg1,&var_20h);
    _var_20h = 0x2a35302335343925;
    _var_18h = CONCAT26(uStack_1a,0x1003b253975);
    do {
        *(&var_20h + uVar3) = *(&var_20h + uVar3) ^ uVar3 + 0x53U;
        uVar3 = uVar3 + 1;
    } while (uVar3 < 0xc);
    _var_18h = _var_18h;
    uVar1 = fcn.14000f1e0(arg1,&var_20h);
    return uVar1;
}
