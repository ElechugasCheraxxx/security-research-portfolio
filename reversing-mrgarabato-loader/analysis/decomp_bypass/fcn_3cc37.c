/* RVA 0x3cc37  tam 282 B  addr 0x14003cc37 */

uint64_t fcn.14003cc20(int64_t arg1,int64_t arg2,int64_t arg3,int64_t arg4,ulong noname_4,ulong noname_5,
                      int64_t arg_40h,int64_t arg_48h)

{
    int iVar1;
    uint *puVar2;
    uint64_t uVar3;
    uint64_t uVar4;
    uchar *puStack_48;
    int aiStack_40 [2];
    int64_t var_30h;
    int64_t var_28h;
    int64_t var_20h;
    int32_t var_bp_18h;
    
    puStack_48 = NULL;
    fcn.14003f620(aiStack_40,0,0x28);
    if ((arg4 == 0) || ((arg3 != 0 && (arg2 == 0)))) {
        puVar2 = fcn.14003ef2c();
        *puVar2 = 0x16;
        fcn.14003eec4();
        return 0xffffffff;
    }
    var_28h._0_4_ = 0x42;
    if (arg3 < 0x40000000) {
        aiStack_40[0] = arg3 * 2;
    }
    else {
        aiStack_40[0] = 0x7fffffff;
    }
    puStack_48 = arg2;
    var_30h = arg2;
    uVar3 = (*arg1)(&puStack_48,arg4,noname_4,noname_5);
    uVar4 = uVar3 & 0xffffffff;
    if (arg2 == 0) {
        return uVar3;
    }
    if (-1 < uVar3) {
        aiStack_40[0] = aiStack_40[0] + -1;
        if (aiStack_40[0] < 0) {
            iVar1 = func_0x00014003f47c(0,&puStack_48);
            if (iVar1 == -1) goto code_r0x00014003cd11;
        }
        else {
            *puStack_48 = 0;
            puStack_48 = puStack_48 + 1;
        }
        aiStack_40[0] = aiStack_40[0] + -1;
        if (-1 < aiStack_40[0]) {
            *puStack_48 = 0;
            goto code_r0x00014003cd20;
        }
        iVar1 = func_0x00014003f47c(0,&puStack_48);
        if (iVar1 != -1) goto code_r0x00014003cd20;
    }
code_r0x00014003cd11:
    *(arg2 + -2 + arg3 * 2) = 0;
    uVar4 = (-1 < aiStack_40[0]) - 2;
code_r0x00014003cd20:
    return uVar4;
}
