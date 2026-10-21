/* RVA 0x454f1  tam 202 B  addr 0x1400454f1 */

//WARNING: Control flow encountered bad instruction data
//WARNING: Instruction at (ram,0x000140045574) overlaps instruction at (ram,0x00014004556f)
//
//WARNING: Removing unreachable block (ram,0x00014004557a)

ulong fcn.1400454f1(int64_t arg1)

{
    int iVar1;
    uint *puVar2;
    uint32_t uVar3;
    int64_t iVar4;
    ulong uVar5;
    uchar *puVar6;
    ulong uStack_28;
    uchar auStack_20 [32];
    
    puVar6 = &stack0xffffffffffffffe0;
    uVar3 = arg1;
    if (uVar3 == 0xfffffffe) {
        uStack_28 = 0x140045502;
        puVar2 = fcn.14003ef2c();
        *puVar2 = 9;
    }
    else {
        if ((-1 < uVar3) && (uVar3 < *0x1400588c8)) {
            iVar4 = (uVar3 & 0x1f) * 0x58;
            if ((*(*((uVar3 >> 5) * 8 + 0x1400588e0) + 8 + iVar4) & 1) != 0) {
                uStack_28 = 0x14004554a;
                func_0x000140044c94(arg1 & 0xffffffff);
                if ((*(*((uVar3 >> 5) * 8 + 0x1400588e0) + 8 + iVar4) & 1) == 0) {
                    uStack_28 = 0x140045586;
                    puVar2 = fcn.14003ef2c();
                    *puVar2 = 9;
                    uVar5 = 0xffffffff;
                }
                else {
                    uStack_28 = 0x14004555d;
                    uStack_28 = fcn.140044c20(arg1 & 0xffffffff);
                    puVar6 = &stack0xffffffffffffffd8;
                    iVar1 = func_0x00014020391a(uStack_28);
                    if (iVar1 == 0) {
                        func_0x000140186a06();
    //WARNING: Bad instruction - Truncating control flow here
                        halt_baddata();
                    }
                    uVar5 = 0;
                }
                *(puVar6 + -8) = 0x140045596;
                func_0x000140044d3c(arg1 & 0xffffffff);
                return uVar5;
            }
        }
        uStack_28 = 0x14004559f;
        puVar2 = fcn.14003ef2c();
        *puVar2 = 9;
        uStack_28 = 0x1400455aa;
        fcn.14003eec4();
    }
    return 0xffffffff;
}
