/* RVA 0x42086  tam 99 B  addr 0x140042086 */

void fcn.140042084(int64_t arg1,int64_t arg2,int64_t arg3)

{
    ulong *****pppppuVar1;
    uint32_t uVar2;
    int64_t iVar3;
    int16_t *piVar4;
    ulong *****pppppuVar5;
    int16_t iVar6;
    uint64_t uVar7;
    ulong unaff_retaddr;
    uint64_t auStackX_8 [4];
    uchar auStack_48 [8];
    uchar auStack_40 [8];
    int64_t iStack_38;
    uint64_t uStack_30;
    ulong *****pppppuStack_28;
    uint64_t uStack_20;
    ulong uStack_18;
    
    uVar7 = arg1;
    if ((*arg3 & 4) != 0) {
        uVar7 = *(arg3 + 4) + arg1 & -*(arg3 + 8);
    }
    iVar3 = *(*(arg2 + 0x10) + 8) + *(arg2 + 8);
    if ((*(iVar3 + 3) & 0xf) != 0) {
        arg1 = arg1 + (*(iVar3 + 3) & 0xfffffff0);
    }
    auStackX_8[0] = arg1 ^ *((*arg3 & 0xfffffff8) + uVar7);
    if ((auStackX_8[0] == *0x140053bd0) && (auStackX_8[0] >> 0x30 == 0)) {
        return;
    }
    uVar2 = 0x40057380;
    iVar3 = fcn.14025e3a2();
    *(iVar3 + -0x75) = *(iVar3 + -0x75) ^ uVar2;
    uStack_30 = iVar3 + 0x12d84;
    uVar7 = 0;
    pppppuVar5 = &pppppuStack_28;
    iStack_38 = fcn.140045780(uStack_30);
    if (iStack_38 == 0) {
        *0x140057418 = auStackX_8;
        *0x140057478 = unaff_retaddr;
    }
    else {
        uVar7 = uStack_30;
        fcn.14004577a(0,pppppuStack_28,uStack_30,iStack_38,0x140057380,auStack_48,auStack_40,0);
        pppppuVar5 = pppppuStack_28;
    }
    *0x1400572f0 = *0x140057478;
    *0x140057400 = auStackX_8[0];
    *0x1400572e0 = 0xc0000409;
    *0x1400572e4 = 1;
    uStack_20 = *0x140053bd0;
    uStack_18 = *0x140053bd8;
    fcn.14014e4f9();
    *0x140057378 = uVar7;
    fcn.140042b38();
    iVar6 = uVar7;
    piVar4 = NULL;
    pppppuVar1 = fcn.1402bc6c7();
    do {
        if (*piVar4 == iVar6) {
            return;
        }
        pppppuVar1 = pppppuVar1 + 1;
        piVar4 = piVar4 + 1;
    } while (pppppuVar1 < pppppuVar5);
    return;
}
