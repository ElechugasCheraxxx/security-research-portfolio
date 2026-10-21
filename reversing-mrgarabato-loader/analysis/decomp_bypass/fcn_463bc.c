/* RVA 0x463bc  tam 530 B  addr 0x1400463bc */

ulong fcn.1400463bc(int64_t arg1)

{
    ulong uVar1;
    ulong uVar2;
    int *piVar3;
    ulong uVar4;
    int64_t *piVar5;
    int iVar6;
    int64_t iVar7;
    int64_t iVar8;
    ulong uVar9;
    uchar auStack_48 [16];
    
    iVar7 = fcn.14003e9d8();
    uVar1 = *(iVar7 + 0xf8);
    iVar7 = fcn.14003e9d8();
    uVar2 = *(iVar7 + 0xf0);
    piVar3 = *(arg1 + 0x50);
    iVar7 = *(arg1 + 0x48);
    uVar9 = *(arg1 + 0x40);
    uVar4 = *(arg1 + 0x30);
    piVar5 = *(arg1 + 0x28);
    iVar8 = fcn.14003e9d8();
    *(iVar8 + 0xf0) = piVar3;
    iVar8 = fcn.14003e9d8();
    *(iVar8 + 0xf8) = uVar9;
    iVar8 = fcn.14003e9d8();
    iVar8 = fcn.140045c38(auStack_48,*(*(iVar8 + 0xf0) + 0x28));
    if (*(arg1 + 0x58) != 0) {
        fcn.14003e9d8();
    }
    uVar9 = func_0x0001400472b0(uVar4,piVar5,0x100);
    fcn.140045cb0(iVar8);
    if ((((*piVar3 == -0x1f928c9d) && (piVar3[6] == 4)) &&
        ((piVar3[8] == 0x19930520 || ((piVar3[8] == 0x19930521 || (piVar3[8] == 0x19930522)))))) &&
       (iVar6 = fcn.140045c7c(*(piVar3 + 10)), iVar6 != 0)) {
        func_0x000140046280(piVar3,1);
    }
    iVar8 = fcn.14003e9d8();
    *(iVar8 + 0xf0) = uVar2;
    iVar8 = fcn.14003e9d8();
    *(iVar8 + 0xf8) = uVar1;
    *(*(iVar7 + 0x1c) + *piVar5) = 0xfffffffffffffffe;
    return uVar9;
}
