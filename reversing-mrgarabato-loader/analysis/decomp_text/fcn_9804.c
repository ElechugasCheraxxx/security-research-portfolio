/* RVA 0x9804  tam 681 B  addr 0x140009804 */

//WARNING: Control flow encountered bad instruction data
//WARNING: Instruction at (ram,0x000140009953) overlaps instruction at (ram,0x000140009951)
//
//WARNING: This function may have set the stack pointer

void fcn.140009804(int64_t arg1,int64_t arg2)

{
    uint32_t *puVar1;
    int iVar2;
    int64_t iVar3;
    int64_t iVar4;
    uint64_t uVar5;
    int64_t unaff_RBX;
    uchar *puVar6;
    int64_t iStack_88;
    ulong uStack_80;
    int64_t iStack_78;
    uchar auStack_70 [16];
    int64_t iStack_60;
    int32_t var_3ch;
    int64_t var_38h;
    int64_t var_30h;
    int64_t var_28h;
    int64_t iStack_28;
    int64_t var_18h;
    int64_t var_10h;
    int64_t var_8h;
    uint64_t uStack_8;
    
    uStack_8 = *0x140020600 ^ &stack0xffffffffffffff90;
    var_30h = 0;
    uStack_80 = 0x14000982d;
    iStack_78 = arg2;
    var_28h = arg1;
    uStack_80 = func_0x0001402cbfc6();
    iStack_88 = 0x14000983e;
    iVar2 = func_0x0001402d8199(uStack_80,8,&fcn.140009804::var_30h);
    if (iVar2 == 0) {
        *arg1 = 0;
        *(arg1 + 8) = 0;
        *(arg1 + 0x10) = 0;
        *(arg1 + 0x18) = 0;
        iStack_88 = 0x140009862;
        fcn.140001b90(arg1,0x140018a15);
        puVar6 = &stack0xffffffffffffff80;
    }
    else {
        var_38h._4_4_ = 0;
        iStack_60 = &fcn.140009804::var_38h + 4;
        iStack_88 = 0x140009884;
        iVar4 = var_30h;
        iVar3 = func_0x0001401335ed(var_30h,1,0);
        puVar1 = unaff_RBX + -0x3f7a3bbb;
        *puVar1 = *puVar1 ^ iVar4;
        if (*puVar1 == 0) {
            iStack_88 = iVar3;
            func_0x00014027dff6(var_30h);
            *arg1 = 0;
            *(arg1 + 8) = 0;
            *(arg1 + 0x10) = 0;
            *(arg1 + 0x18) = 0;
            fcn.140001b90(arg1,0x140018a15,0);
            puVar6 = &stack0xffffffffffffff78;
        }
        else {
            var_18h = 0;
            var_10h = 0;
            var_8h = 0xf;
            iStack_28 = 0;
            iStack_88 = 0x1400098da;
            iVar4 = func_0x000140037bc0(iVar3);
            if (iVar4 != 0) {
                iStack_60 = &fcn.140009804::var_38h + 4;
                iStack_88 = 0x14000996d;
                *0x7b75c07d = func_0x000140201486(var_30h,1);
                *0x7b75c075 = 0x14000997b;
                func_0x0001401ca0f3();
                *0x7b75c075 = 0x140009984;
                func_0x0001401a3b79(var_30h);
    //WARNING: Bad instruction - Truncating control flow here
                halt_baddata();
            }
            iStack_88 = arg1;
            func_0x00014015859b();
            *arg1 = 0;
            *(arg1 + 8) = 0;
            *(arg1 + 0x10) = 0;
            *(arg1 + 0x18) = 0;
            fcn.140001b90(arg1,0x140018a15,0);
            puVar6 = &stack0xffffffffffffff78;
            if (0xf < var_8h) {
                uVar5 = var_8h + 1;
                iVar4 = iStack_28;
                if (0xfff < uVar5) {
                    uVar5 = var_8h + 0x28;
                    iVar4 = *(iStack_28 + -8);
                    if (0x1f < (iStack_28 - iVar4) - 8U) {
                        func_0x0001401bf576();
    //WARNING: Bad instruction - Truncating control flow here
                        halt_baddata();
                    }
                }
                fcn.140015008(iVar4,uVar5);
                puVar6 = &stack0xffffffffffffff78;
            }
        }
    }
    *(puVar6 + -8) = 0x140009a93;
    fcn.1400153c0(uStack_8 ^ puVar6);
    return;
}
