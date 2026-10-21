/* RVA 0x3dbd7  tam 147 B  addr 0x14003dbd7 */

uint64_t fcn.14003dbcc(int64_t arg1,int64_t arg2)

{
    uint64_t uVar1;
    int64_t var_bp_10h;
    int64_t var_40h;
    int32_t var_28h;
    int64_t var_20h;
    int64_t var_bp_18h;
    int64_t iStack_18;
    int64_t var_8h;
    
    fcn.140041d50(&var_40h,0x140049480,0x40);
    var_bp_18h = arg1;
    iStack_18 = arg2;
    var_bp_10h = func_0x000140045774(arg2,&var_bp_10h);
    if (arg2 != 0) {
        if ((*arg2 & 8) == 0) {
            if (var_bp_10h == 0) {
                var_20h._0_4_ = 0x1994000;
            }
        }
        else {
            var_20h._0_4_ = 0x1994000;
        }
    }
    var_8h = var_bp_10h;
    uVar1 = func_0x000140202fb9(var_40h,var_40h._4_4_,var_28h,&var_20h);
    return uVar1 & 0xffffffffffffff60;
}
