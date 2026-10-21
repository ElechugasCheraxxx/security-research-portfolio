/* RVA 0x3cb10  tam 214 B  addr 0x14003cb10 */

uint64_t fcn.14003cb00(int64_t arg1,int64_t arg2,int64_t arg3)

{
    int iVar1;
    int iVar2;
    uint *puVar3;
    uint64_t uVar4;
    int64_t var_20h;
    int64_t var_bp_10h;
    int8_t var_bp_8h;
    
    fcn.14003c53c(&var_20h,arg3);
    if ((arg1 == 0) || (arg2 == 0)) {
        puVar3 = fcn.14003ef2c();
        *puVar3 = 0x16;
        fcn.14003eec4();
        if (var_bp_8h != 0) {
            *(var_bp_10h + 200) = *(var_bp_10h + 200) & 0xfffffffd;
        }
        uVar4 = 0x7fffffff;
    }
    else if (*(var_20h + 0x14) == 0) {
        uVar4 = func_0x00014003cac4(arg1,arg2);
        if (var_bp_8h != 0) {
            *(var_bp_10h + 200) = *(var_bp_10h + 200) & 0xfffffffd;
        }
    }
    else {
        arg1 = arg1 - arg2;
        do {
            iVar1 = func_0x00014003cfb8(*(arg2 + arg1),&var_20h);
            iVar2 = func_0x00014003cfb8(*arg2,&var_20h);
            arg2 = arg2 + 1;
            if (iVar1 == 0) break;
        } while (iVar1 == iVar2);
        if (var_bp_8h != 0) {
            *(var_bp_10h + 200) = *(var_bp_10h + 200) & 0xfffffffd;
        }
        uVar4 = iVar1 - iVar2;
    }
    return uVar4;
}
