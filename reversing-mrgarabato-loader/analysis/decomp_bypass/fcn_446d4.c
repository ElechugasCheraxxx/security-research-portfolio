/* RVA 0x446d4  tam 68 B  addr 0x1400446d4 */

void fcn.1400446d4(int64_t arg1)

{
    int64_t iVar1;
    ulong ***pppuVar2;
    uint32_t uVar3;
    int16_t *piVar4;
    ulong ***pppuVar5;
    int16_t iVar6;
    uint64_t uVar7;
    ulong unaff_retaddr;
    int64_t aiStackX_8 [4];
    uchar auStack_48 [8];
    uchar auStack_40 [8];
    int64_t iStack_38;
    uint64_t uStack_30;
    ulong ***pppuStack_28;
    ulong uStack_20;
    ulong uStack_18;
    
    uVar3 = 0x40057380;
    aiStackX_8[0] = arg1;
    iVar1 = fcn.14025e3a2();
    *(iVar1 + -0x75) = *(iVar1 + -0x75) ^ uVar3;
    uStack_30 = iVar1 + 0x12d84;
    uVar7 = 0;
    pppuVar5 = &pppuStack_28;
    iStack_38 = fcn.140045780(uStack_30);
    if (iStack_38 == 0) {
        *0x140057418 = aiStackX_8;
        *0x140057478 = unaff_retaddr;
    }
    else {
        uVar7 = uStack_30;
        fcn.14004577a(0,pppuStack_28,uStack_30,iStack_38,0x140057380,auStack_48,auStack_40,0);
        pppuVar5 = pppuStack_28;
    }
    *0x1400572f0 = *0x140057478;
    *0x140057400 = aiStackX_8[0];
    *0x1400572e0 = 0xc0000409;
    *0x1400572e4 = 1;
    uStack_20 = *0x140053bd0;
    uStack_18 = *0x140053bd8;
    fcn.14014e4f9();
    *0x140057378 = uVar7;
    fcn.140042b38();
    iVar6 = uVar7;
    piVar4 = NULL;
    pppuVar2 = fcn.1402bc6c7();
    do {
        if (*piVar4 == iVar6) {
            return;
        }
        pppuVar2 = pppuVar2 + 1;
        piVar4 = piVar4 + 1;
    } while (pppuVar2 < pppuVar5);
    return;
}
