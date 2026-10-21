/* RVA 0x44840  tam 318 B  addr 0x140044840 */

//WARNING: Control flow encountered bad instruction data

void fcn.140044840(int64_t arg1,int64_t arg2,int64_t arg3)

{
    int iVar1;
    uint64_t uVar2;
    int64_t iVar3;
    int64_t iVar4;
    ulong uVar5;
    code *pcVar6;
    code *pcVar7;
    uint64_t uVar8;
    uchar *puVar9;
    uchar *puVar10;
    uint64_t uVar11;
    char cVar12;
    int64_t iStack_98;
    uint64_t uStack_90;
    uchar auStack_88 [24];
    uchar *puStack_70;
    uchar auStack_60 [8];
    uchar auStack_58 [8];
    uint8_t uStack_50;
    uint64_t uStack_40;
    
    uStack_40 = *0x140053bd0 ^ &stack0xffffffffffffff78;
    uVar11 = arg3 & 0xffffffff;
    uStack_90 = 0x14004486c;
    uVar2 = fcn.14003e864();
    iVar3 = 0;
    if (*0x140057850 == 0) {
        puVar10 = &stack0xffffffffffffff70;
        iStack_98 = 0x14004488b;
        uStack_90 = uVar2;
        iVar3 = func_0x0001401ad399(0x14004b778);
        if (iVar3 != 0) {
            puVar10 = &stack0xffffffffffffff68;
            iStack_98 = iVar3;
            iVar4 = func_0x00014003b7cc(iVar3,0x14004b768);
            if (iVar4 != 0) {
                *0x140057850 = func_0x00014019153f(iVar4);
                uVar2 = func_0x0001401b5214(iVar3,0x14004b758);
                *0x140057858 = func_0x00014021b4d7(*(uVar2 & 0xff));
                uVar5 = func_0x000140284a83(iVar3);
                *0x140057860 = func_0x0001406b6c1b(uVar5);
                uVar5 = func_0x0001401a9338(iVar3,0x14004b720);
                func_0x00014015d69b(uVar5);
    //WARNING: Bad instruction - Truncating control flow here
                halt_baddata();
            }
        }
        goto code_r0x000140044a2c;
    }
    puVar9 = &stack0xffffffffffffff78;
    if ((*0x140057868 == uVar2) ||
       (cVar12 = *0x140057870 < uVar2, puVar9 = &stack0xffffffffffffff78, *0x140057870 == uVar2)) {
code_r0x0001400449c8:
        if (*0x140057858 != uVar2) {
            *(puVar9 + -8) = 0x1400449d9;
            uVar8 = *0x140057858;
            iVar3 = fcn.140039e3d();
            *(iVar3 + -0x7b) = *(iVar3 + -0x7b) + uVar8;
            *((uVar8 - 1) + uVar11) = 0;
            if ((iVar3 != 0) && (*0x140057860 != uVar2)) {
                *(puVar9 + -8) = 0x1400449fa;
                fcn.140299f11();
    //WARNING: Bad instruction - Truncating control flow here
                halt_baddata();
            }
        }
    }
    else {
        uStack_90 = 0x140044973;
        uVar8 = *0x140057868;
        iVar4 = func_0x0001401c36b4();
        *(iVar4 + -0x75) = (*(iVar4 + -0x75) - uVar8) - cVar12;
        pcVar7 = iVar4 | 0x12ef5;
        iStack_98 = 0x140044984;
        uStack_90 = uVar2;
        pcVar6 = fcn.140131ed2();
        puVar9 = &stack0xffffffffffffff70;
        if ((pcVar7 == NULL) || (puVar9 = &stack0xffffffffffffff70, pcVar6 == NULL)) goto code_r0x0001400449c8;
        iStack_98 = 0x140044993;
        iVar4 = (*pcVar7)();
        if (iVar4 != 0) {
            puStack_70 = &stack0xffffffffffffffa0;
            iStack_98 = 0x1400449b7;
            iVar1 = (*pcVar6)(iVar4,1,&stack0xffffffffffffffa8);
            if ((iVar1 != 0) && (puVar9 = &stack0xffffffffffffff70, (uStack_50 & 1) != 0)) goto code_r0x0001400449c8;
        }
        uVar11 = arg3 | 0x200000;
        puVar9 = &stack0xffffffffffffff70;
    }
    puVar10 = puVar9 + -8;
    *(puVar9 + -8) = uVar2;
    *(puVar9 + -0x10) = 0x140044a15;
    pcVar7 = fcn.1402dae0e(*0x140057850);
    if (pcVar7 != NULL) {
        *(puVar9 + -0x10) = 0x140044a28;
        (*pcVar7)(iVar3,arg1,arg2,uVar11);
        puVar10 = puVar9 + -8;
    }
code_r0x000140044a2c:
    *(puVar10 + -8) = 0x140044a39;
    fcn.140042300(*(puVar10 + 0x48) ^ puVar10);
    return;
}
