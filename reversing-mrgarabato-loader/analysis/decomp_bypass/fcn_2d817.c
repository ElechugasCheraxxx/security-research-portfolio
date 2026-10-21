/* RVA 0x2d817  tam 2399522 B  addr 0x14002d817 */

//WARNING: Control flow encountered bad instruction data

void fcn.14027749d(ulong param_1,ulong param_2,ulong param_3,ulong param_4)

{
    uint8_t uVar1;
    char cVar2;
    uint16_t unaff_BX;
    ulong *puVar3;
    uint32_t uVar4;
    ulong in_R10;
    ulong unaff_R14;
    uint8_t uVar5;
    uchar in_SF;
    uint8_t uVar6;
    uint8_t uVar7;
    uchar uVar8;
    uint8_t uVar9;
    uint8_t uVar10;
    uint8_t uVar11;
    uint8_t uVar12;
    uint8_t uVar13;
    uint64_t uVar14;
    ulong uStackX_8;
    int64_t iStackX_10;
    int64_t iStackX_18;
    ulong uStackX_20;
    
    func_0x00014020f841();
    if (!in_SF) {
        func_0x00014003bcfd();
        func_0x00014013c936();
        func_0x0001402055e2();
        uStackX_20 = 0xffffffff874e0fee;
        puVar3 = &uStackX_8;
        if (unaff_BX < 0xaf85) {
            puVar3 = *0x20;
        }
        *(puVar3 + -8) = *(puVar3 + 0x18);
        uVar14 = *(puVar3 + -8);
        uVar9 = (uVar14 & 0x4000) != 0;
        uVar7 = (uVar14 & 0x200) != 0;
        uVar6 = (uVar14 & 0x100) != 0;
        uVar5 = (uVar14 & 0x10) != 0;
        uVar13 = (uVar14 & 0x200000) != 0;
        uVar10 = (uVar14 & 0x40000) != 0;
        uVar12 = 0;
        uVar11 = 0;
        *(puVar3 + 0x18) = 0x140241217;
        fcn.140740f6a();
        *(puVar3 + 0x18) = in_R10;
        *(puVar3 + 0x48) = param_1;
        *(puVar3 + 0x38) = *(puVar3 + 0x38) ^ 0x2418;
        *(puVar3 + 0x38) = *(puVar3 + 0x38) + 'W';
        *(puVar3 + 0x10) = 0x14024122f;
        uVar1 = func_0x0001402dd365();
        cVar2 = uVar1 + 0x10;
        *(puVar3 + 0x10) =
             (uVar9 & 1) * 0x4000 | SBORROW1(uVar1,-0x10) * 0x800 | ((uVar14 & 0x400) != 0) * 0x400 |
             (uVar7 & 1) * 0x200 | (uVar6 & 1) * 0x100 | (cVar2 < '\0') * 0x80 | (cVar2 == '\0') * 0x40 |
             (uVar5 & 1) * 0x10 | ((POPCOUNT(cVar2) & 1U) == 0) * 4 | uVar1 < 0xf0 | (uVar13 & 1) * 0x200000 |
             (uVar12 & 1) * 0x100000 | (uVar11 & 1) * 0x80000 | (uVar10 & 1) * 0x40000;
    //WARNING: Bad instruction - Truncating control flow here
        halt_baddata();
    }
    func_0x0001402ba8f7();
    uVar8 = 0;
    func_0x00014019d7ff();
    LOCK();
    UNLOCK();
    func_0x00014014e568();
    uStackX_8 = CONCAT71(param_1 >> 8,0x7d173aec < CONCAT62(unaff_R14 >> 0x10,~CONCAT71(unaff_R14 >> 8,!uVar8)));
    iStackX_18 = iStackX_18 + -0x402a41f0;
    uVar4 = CONCAT71(param_4 >> 8,-param_4) ^ 0x5e577193;
    if (uVar4 < '\0') {
    //WARNING: Bad instruction - Truncating control flow here
        halt_baddata();
    }
    LOCK();
    UNLOCK();
    func_0x00014003a45c(uVar4 * 8 + 0x6e2d33da);
    iStackX_10 = iStackX_10 + 0x40202;
    func_0x00014023ebfd();
    return;
}
