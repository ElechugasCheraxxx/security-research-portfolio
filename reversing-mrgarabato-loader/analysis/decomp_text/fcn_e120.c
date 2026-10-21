/* RVA 0xe120  tam 3321 B  addr 0x14000e120 */

//WARNING: Control flow encountered bad instruction data
//WARNING: Variable defined which should be unmapped: var_1fh

void fcn.14000e120(void)

{
    code *pcVar1;
    ulong uVar2;
    int iVar3;
    uint uVar4;
    uchar *puVar5;
    uint64_t uVar6;
    uchar *puVar7;
    int64_t var_1fh;
    int64_t var_27h;
    int64_t var_37h;
    int64_t var_47h;
    uchar *puStack_e8;
    uchar auStack_d8 [8];
    uchar *puStack_d0;
    uchar *puStack_c8;
    uchar *puStack_c0;
    ulong uStack_b8;
    uchar *puStack_a8;
    ulong uStack_a0;
    ulong uStack_98;
    uint64_t uStack_90;
    uchar *puStack_88;
    ulong uStack_80;
    ulong uStack_78;
    uint64_t uStack_70;
    uchar auStack_68 [9];
    uchar auStack_5f [14];
    int64_t var_49h;
    int64_t var_39h;
    int64_t var_31h;
    int64_t var_29h;
    uchar auStack_28 [7];
    int64_t var_19h;
    int64_t var_11h;
    int64_t var_9h;
    
    *NULL = *0x140020600 ^ &stack0xffffffffffffff28;
    uStack_b8 = 0x140020a90;
    puStack_e8 = 0x14000e16e;
    iVar3 = fcn.1406b3fcc(0xffffffff80000001,0x140019218,0,0x20119);
    if (iVar3 == 0) {
        puStack_e8 = 0x14000ecc9;
        fcn.1400153c0(stack0xffffffffffffffe8 ^ &stack0xffffffffffffff20);
        return;
    }
    stack0xffffffffffffffc8 = 0;
    stack0xffffffffffffffd0 = 0;
    _auStack_28 = 0;
    stack0xffffffffffffffe0 = 0;
    puStack_e8 = 0x14000e19b;
    fcn.140001c90(&fcn.14000e120::var_31h + 1,L"SOFTWARE\\Microsoft\\PhoneHx\\Ignyx",0x20);
    stack0xffffffffffffffc0 = 0;
    puStack_e8 = 0x14000e1b6;
    fcn.14000b5f0(&fcn.14000e120::var_39h + 1,-0x7fffffff,&fcn.14000e120::var_31h + 1);
    puStack_88 = NULL;
    uStack_80 = 0;
    uStack_78 = 0;
    uStack_70 = 0;
    puStack_e8 = 0x14000e1da;
    fcn.140001c90(&stack0xffffffffffffff78,str.0123456789,1);
    puStack_a8 = NULL;
    uStack_a0 = 0;
    uStack_98 = 0;
    uStack_90 = 0;
    puStack_e8 = 0x14000e1fe;
    fcn.140001c90(&stack0xffffffffffffff58,str.0123456789 + 1,1);
    uVar2 = stack0xffffffffffffffc0;
    puStack_c0 = &stack0xffffffffffffff78;
    if (7 < uStack_70) {
        puStack_c0 = puStack_88;
    }
    puVar5 = &stack0xffffffffffffff58;
    if (7 < uStack_90) {
        puVar5 = puStack_a8;
    }
    uStack_b8 = CONCAT44(uStack_b8._4_4_,uStack_78 * 2 + 2);
    puVar7 = &stack0xffffffffffffff18;
    puStack_e8 = &stack0xffffffffffffffa1;
    iVar3 = fcn.14017acc4(stack0xffffffffffffffc0,puVar5,0,1);
    if (iVar3 == 0) {
        if (7 < uStack_90) {
            uVar6 = uStack_90 * 2 + 2;
            puVar5 = puStack_a8;
            if (0xfff < uVar6) {
                uVar6 = uStack_90 * 2 + 0x29;
                puVar5 = *(puStack_a8 + -8);
                if (0x1f < puStack_a8 + (-8 - puVar5)) {
                    fcn.14011f1dc();
                    pcVar1 = swi(3);
                    (*pcVar1)();
                    return;
                }
            }
            fcn.140015008(puVar5,uVar6);
        }
        uStack_98 = *0x140018f60;
        uStack_90 = *0x140018f68;
        puStack_a8 = puStack_a8 & 0xffffffffffff0000;
        if (7 < uStack_70) {
            uVar6 = uStack_70 * 2 + 2;
            if (0xfff < uVar6) {
                uVar6 = uStack_70 * 2 + 0x29;
                if (0x1f < puStack_88 + (-8 - *(puStack_88 + -8))) {
                    fcn.140278b34();
                    pcVar1 = swi(3);
                    (*pcVar1)();
                    return;
                }
            }
            fcn.140015008(*0x140018f60,uVar6);
        }
        puStack_88 = NULL;
        uStack_80 = 0;
        uStack_78 = 0;
        uStack_70 = 0;
        fcn.140001c90(&stack0xffffffffffffff78,str.0123456789,1);
        puStack_a8 = NULL;
        uStack_a0 = 0;
        uStack_98 = 0;
        uStack_90 = 0;
        fcn.140001c90(&stack0xffffffffffffff58,str.0123456789 + 2,1);
        puStack_c8 = &stack0xffffffffffffff78;
        if (7 < uStack_70) {
            puStack_c8 = puStack_88;
        }
        puVar5 = &stack0xffffffffffffff58;
        if (7 < uStack_90) {
            puVar5 = puStack_a8;
        }
        puStack_c0 = CONCAT44(puStack_c0._4_4_,uStack_78 * 2 + 2);
        puVar7 = &stack0xffffffffffffff10;
        iVar3 = fcn.14023777c(uVar2,puVar5,0,1);
        if (iVar3 == 0) {
            if (7 < uStack_90) {
                uVar6 = uStack_90 * 2 + 2;
                puVar5 = puStack_a8;
                if (0xfff < uVar6) {
                    uVar6 = uStack_90 * 2 + 0x29;
                    puVar5 = *(puStack_a8 + -8);
                    if (0x1f < puStack_a8 + (-8 - puVar5)) {
                        fcn.14026498d();
                        pcVar1 = swi(3);
                        (*pcVar1)();
                        return;
                    }
                }
                fcn.140015008(puVar5,uVar6);
            }
            uStack_98 = *0x140018f60;
            uStack_90 = *0x140018f68;
            puStack_a8 = puStack_a8 & 0xffffffffffff0000;
            if (7 < uStack_70) {
                uVar6 = uStack_70 * 2 + 2;
                if (0xfff < uVar6) {
                    uVar6 = uStack_70 * 2 + 0x29;
                    if (0x1f < puStack_88 + (-8 - *(puStack_88 + -8))) {
                        fcn.14011feee();
                        pcVar1 = swi(3);
                        (*pcVar1)();
                        return;
                    }
                }
                fcn.140015008(*0x140018f60,uVar6);
            }
            puStack_88 = NULL;
            uStack_80 = 0;
            uStack_78 = 0;
            uStack_70 = 0;
            fcn.140001c90(&stack0xffffffffffffff78,str.0123456789,1);
            puStack_a8 = NULL;
            uStack_a0 = 0;
            uStack_98 = 0;
            uStack_90 = 0;
            fcn.140001c90(&stack0xffffffffffffff58,str.0123456789 + 3,1);
            puStack_d0 = &stack0xffffffffffffff78;
            if (7 < uStack_70) {
                puStack_d0 = puStack_88;
            }
            puVar5 = &stack0xffffffffffffff58;
            if (7 < uStack_90) {
                puVar5 = puStack_a8;
            }
            puStack_c8 = CONCAT44(puStack_c8._4_4_,uStack_78 * 2 + 2);
            fcn.14014a1cf(uVar2,puVar5,0,1);
    //WARNING: Bad instruction - Truncating control flow here
            halt_baddata();
        }
    }
    else {
        fcn.14000b520(&stack0xffffffffffffff98,iVar3,"Cannot write string value: RegSetValueExW failed.");
        iVar3 = fcn.140015ea6(&stack0xffffffffffffff98,0x14001d4d0);
    }
    *(puVar7 + -8) = 0x14000ed36;
    fcn.14000b520(&stack0xffffffffffffff98,iVar3,"Cannot write string value: RegSetValueExW failed.");
    *(puVar7 + -8) = 0x14000ed46;
    uVar4 = fcn.140015ea6(&stack0xffffffffffffff98,0x14001d4d0);
    *(puVar7 + -8) = 0x14000ed59;
    fcn.14000b520(&stack0xffffffffffffff98,uVar4,"Cannot write string value: RegSetValueExW failed.");
    *(puVar7 + -8) = 0x14000ed69;
    uVar4 = fcn.140015ea6(&stack0xffffffffffffff98,0x14001d4d0);
    *(puVar7 + -8) = 0x14000ed7c;
    fcn.14000b520(&stack0xffffffffffffff98,uVar4,"Cannot write string value: RegSetValueExW failed.");
    *(puVar7 + -8) = 0x14000ed8c;
    uVar4 = fcn.140015ea6(&stack0xffffffffffffff98,0x14001d4d0);
    *(puVar7 + -8) = 0x14000ed9f;
    fcn.14000b520(&stack0xffffffffffffff98,uVar4,"Cannot write string value: RegSetValueExW failed.");
    *(puVar7 + -8) = 0x14000edaf;
    uVar4 = fcn.140015ea6(&stack0xffffffffffffff98,0x14001d4d0);
    *(puVar7 + -8) = 0x14000edc2;
    fcn.14000b520(&stack0xffffffffffffff98,uVar4,"Cannot write string value: RegSetValueExW failed.");
    *(puVar7 + -8) = 0x14000edd2;
    uVar4 = fcn.140015ea6(&stack0xffffffffffffff98,0x14001d4d0);
    *(puVar7 + -8) = 0x14000ede5;
    fcn.14000b520(&stack0xffffffffffffff98,uVar4,"Cannot write string value: RegSetValueExW failed.");
    *(puVar7 + -8) = 0x14000edf5;
    uVar4 = fcn.140015ea6(&stack0xffffffffffffff98,0x14001d4d0);
    *(puVar7 + -8) = 0x14000ee08;
    fcn.14000b520(&stack0xffffffffffffff98,uVar4,"Cannot write string value: RegSetValueExW failed.");
    *(puVar7 + -8) = 0x14000ee18;
    fcn.140015ea6(&stack0xffffffffffffff98,0x14001d4d0);
    pcVar1 = swi(3);
    (*pcVar1)();
    return;
}
