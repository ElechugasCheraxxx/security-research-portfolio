/* RVA 0x6580  tam 1132 B  addr 0x140006580 */

//WARNING: Control flow encountered bad instruction data
//WARNING: Variable defined which should be unmapped: var_30h_2

void fcn.140006580(int64_t arg1,int64_t arg2,int64_t arg3,int64_t arg4)

{
    int64_t var_30h;
    int32_t var_38h_2;
    int64_t var_48h;
    int64_t var_b0h;
    uchar auStack_1f8 [72];
    uint uStack_1b0;
    uint uStack_1a8;
    int64_t iStack_1a0;
    uchar auStack_180 [32];
    uchar auStack_160 [36];
    int iStack_13c;
    int64_t iStack_138;
    uchar auStack_130 [128];
    uchar auStack_b0 [48];
    int64_t var_bp_78h;
    int64_t var_68h;
    int32_t var_44h;
    int64_t var_40h;
    int64_t var_38h;
    int64_t var_30h_2;
    
    var_40h = *0x140020600 ^ auStack_1f8;
    uStack_1a8 = 0;
    iStack_1a0 = arg1;
    func_0x000140004820(auStack_160);
    func_0x0001400097f0(auStack_180);
    func_0x000140015eca(&iStack_138,0,0xe8);
    iStack_138 = 0x140018ab8;
    func_0x00014015d975(auStack_b0);
    uStack_1b0 = 2;
    func_0x0001401e128e(&iStack_138,auStack_130,0,0);
    *(auStack_130 + *(iStack_138 + 4) + -8) = 0x140018ab0;
    *(&iStack_13c + *(iStack_138 + 4)) = *(iStack_138 + 4) + -0x88;
    func_0x00014029ccbd(auStack_130);
    //WARNING: Bad instruction - Truncating control flow here
    halt_baddata();
}
