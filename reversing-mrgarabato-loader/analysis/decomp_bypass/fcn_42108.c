/* RVA 0x42108  tam 350 B  addr 0x140042108 */

//WARNING: Instruction at (ram,0x0001400421b5) overlaps instruction at (ram,0x0001400421b4)
//
//WARNING: Variable defined which should be unmapped: var_10h

void fcn.140042108(int64_t arg1,int64_t arg2,int64_t arg3,int64_t arg4,int64_t arg_60h,int32_t arg_68h,
                  int32_t arg_70h)

{
    uint32_t uVar1;
    int iVar2;
    int64_t iVar3;
    uint *puVar4;
    uint64_t uVar5;
    uint *puVar6;
    uchar *puVar7;
    uchar *puVar8;
    uchar *puVar9;
    uint64_t unaff_R12;
    bool bVar10;
    bool bVar11;
    int64_t var_10h;
    ulong in_stack_00000028;
    int in_stack_00000030;
    int64_t var_40h;
    int64_t var_48h;
    int64_t var_50h;
    uchar auStack_68 [32];
    ulong uStack_48;
    uint uStack_40;
    uint64_t auStack_38 [2];
    
    auStack_38[0] = *0x140053bd0 ^ &stack0xffffffffffffffc8;
    puVar6 = NULL;
    if (in_stack_00000030 == 0) {
        in_stack_00000030 = *(*arg1 + 4);
    }
    uStack_40 = 0;
    uStack_48 = 0;
    bVar10 = false;
    bVar11 = (-(var_40h != 0) & 8U) == 0xff;
    uVar1 = func_0x00014029fa4e(in_stack_00000030);
    puVar9 = &stack0xffffffffffffff98;
    if (bVar10 || bVar11) {
        puVar7 = uVar1;
        puVar9 = puVar7;
        if (uVar1 == 0) goto code_r0x000140042240;
        if ((0 < uVar1) && (unaff_R12 < 0x7ffffffffffffff1)) {
            uVar5 = unaff_R12 * 2 + 0x10;
            if (uVar5 < 0x401) goto code_r0x0001400421a8;
            *(puVar7 + -8) = 0x1400421cb;
            puVar4 = fcn.14003f11c(uVar5);
            puVar6 = NULL;
            if (puVar4 != NULL) {
                *puVar4 = 0xdddd;
                goto code_r0x0001400421d9;
            }
        }
    }
    else {
code_r0x0001400421a8:
        *(puVar9 + -8) = 0x1400421b1;
        iVar3 = func_0x000140044210();
        iVar3 = -iVar3;
        puVar7 = puVar9 + iVar3;
        puVar4 = puVar9 + iVar3 + 0x30;
        puVar9 = puVar9 + iVar3;
        if (puVar4 == NULL) goto code_r0x000140042240;
        *puVar4 = 0xcccc;
code_r0x0001400421d9:
        puVar6 = puVar4 + 4;
    }
    puVar9 = puVar7;
    if (puVar6 != NULL) {
        *(puVar7 + -8) = 0x1400421f7;
        fcn.14003f620(puVar6,0,unaff_R12 * 2);
        *(puVar7 + 0x28) = unaff_R12;
        *(puVar7 + 0x20) = puVar6;
        puVar8 = puVar7 + -8;
        *(puVar7 + -8) = puVar6;
        *(puVar7 + -0x10) = 0x140042214;
        iVar2 = func_0x00014021f045(in_stack_00000030,1,arg3,arg4 & 0xffffffff);
        if (iVar2 != 0) {
            puVar8 = puVar7 + -0x10;
            *(puVar7 + -0x10) = arg2 & 0xffffffffU;
            *(puVar7 + -0x18) = 0x14004222b;
            func_0x0001406a110a(arg2 & 0xffffffffU,puVar6,iVar2,in_stack_00000028);
        }
        puVar9 = puVar8;
        if (puVar6[-4] == 0xdddd) {
            *(puVar8 + -8) = 0x14004223e;
            fcn.14003dc60(puVar6 + -4);
        }
    }
code_r0x000140042240:
    uVar5 = auStack_38[0] ^ &stack0xffffffffffffffc8;
    *(puVar9 + -8) = 0x14004224c;
    fcn.140042300(uVar5);
    return;
}
