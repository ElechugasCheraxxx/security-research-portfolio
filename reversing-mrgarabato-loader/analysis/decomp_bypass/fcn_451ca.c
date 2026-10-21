/* RVA 0x451ca  tam 371 B  addr 0x1400451ca */

//WARNING: Variable defined which should be unmapped: var_bp_8h
//WARNING: Variable defined which should be unmapped: var_10h

uint64_t fcn.1400451bc(int64_t arg1,int64_t arg2,int64_t arg3,int64_t arg4,int64_t noname_4,ulong noname_5,
                      int64_t arg_40h)

{
    uint *puVar1;
    uint64_t uVar2;
    uint32_t *puVar3;
    char *pcVar4;
    int64_t iVar5;
    bool bVar6;
    uint auStackX_10 [4];
    int32_t var_28h;
    int64_t aiStack_38 [2];
    int64_t var_bp_20h;
    char cStack_20;
    int64_t var_10h;
    int8_t var_bp_8h;
    
    var_28h._0_2_ = arg4;
    if ((arg2 == 0) && (arg3 != 0)) {
        if (arg1 == 0) {
            return 0;
        }
        *arg1 = 0;
        return 0;
    }
    if (arg1 != 0) {
        *arg1 = 0xffffffff;
    }
    if (arg3 < 0x80000000) {
        fcn.14003c53c(aiStack_38,noname_4);
        if (*(aiStack_38[0] + 0x14) == 0) {
            if (var_28h < 0x100) {
                if (arg2 != 0) {
                    if (arg3 == 0) {
                        pcVar4 = fcn.14003ef2c();
                        arg1 = 0x22;
                        goto code_r0x00014004529e;
                    }
                    *arg2 = var_28h;
                }
                if (arg1 != 0) {
                    *arg1 = 1;
                }
code_r0x0001400452cc:
                if (cStack_20 != '\0') {
                    *(var_bp_20h + 200) = *(var_bp_20h + 200) & 0xfffffffd;
                }
                return 0;
            }
            if ((arg2 != 0) && (arg3 != 0)) {
                fcn.14003f620(arg2,0,arg3);
            }
        }
        else {
            auStackX_10[0] = 0;
            iVar5 = 0;
            bVar6 = true;
            pcVar4 = func_0x0001401cfc16(*(aiStack_38[0] + 4),0,&var_28h,1,arg2,arg3,0,auStackX_10);
            if (!bVar6) {
code_r0x00014004529e:
                *pcVar4 = arg1;
                fcn.14003eec4();
                if (cStack_20 != arg3) {
                    *(var_bp_20h + 200) = *(var_bp_20h + 200) & 0xfffffffd;
                }
                goto code_r0x000140045214;
            }
            *(arg1 + -0x7d + iVar5) = 0;
            *pcVar4 = *pcVar4 - pcVar4;
            if (*pcVar4 == '\0') {
                if (arg1 != 0) {
                    *arg1 = pcVar4;
                }
                goto code_r0x0001400452cc;
            }
        }
        puVar1 = fcn.14003ef2c();
        *puVar1 = 0x2a;
        puVar3 = fcn.14003ef2c();
        uVar2 = *puVar3;
        if (cStack_20 != '\0') {
            *(var_bp_20h + 200) = *(var_bp_20h + 200) & 0xfffffffd;
        }
    }
    else {
        puVar1 = fcn.14003ef2c();
        arg1 = 0x16;
        *puVar1 = 0x16;
        fcn.14003eec4();
code_r0x000140045214:
        uVar2 = arg1 & 0xffffffff;
    }
    return uVar2;
}
