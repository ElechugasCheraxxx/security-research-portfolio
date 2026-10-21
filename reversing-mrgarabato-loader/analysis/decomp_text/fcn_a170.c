/* RVA 0xa170  tam 328 B  addr 0x14000a170 */

int64_t fcn.14000a170(int64_t arg1,int64_t arg2,int64_t arg3,int64_t arg4)

{
    bool bVar1;
    ulong in_RAX;
    unkuint7 Var6;
    int64_t iVar2;
    uint64_t uVar3;
    int64_t iVar4;
    ulong uVar5;
    uchar *puVar7;
    uint64_t uVar8;
    uint64_t uVar9;
    int64_t iStack_60;
    int64_t iStack_58;
    int64_t iStack_50;
    
    if (((arg4 & 1U) == 0) || ((*(arg1 + 0x70) & 4) == 0)) {
        bVar1 = false;
    }
    else {
        bVar1 = true;
    }
    Var6 = in_RAX >> 8;
    if (((arg4 & 2U) == 0) || ((*(arg1 + 0x70) & 2) == 0)) {
        iStack_50 = Var6 << 8;
    }
    else {
        iStack_50 = CONCAT71(Var6,1);
    }
    if ((!bVar1) && (iStack_50 == '\0')) {
        uVar8 = *(arg3 + 8) + *arg3;
        iStack_58 = 0x14000a1d6;
        iVar4 = arg2;
        iVar2 = func_0x00014021e77f(arg1);
        if ((*(arg1 + 0x70) & 2) == 0) {
            iStack_58 = 0x14000a1eb;
            uVar5 = func_0x00014011f103(arg1);
            uVar3 = CONCAT62(uVar5 >> 0x10,CONCAT11(0x48,uVar5));
            uVar9 = uVar3 & 0xffffffff;
            if ((uVar3 != 0) && (*(arg1 + 0x68) < uVar3)) {
                *(arg1 + 0x68) = uVar3;
            }
        }
        else {
            uVar9 = 0;
        }
        iStack_60 = 0x14000a207;
        iStack_58 = iVar4;
        iVar4 = func_0x0001402338bb(arg1);
        if ((uVar8 <= *(arg1 + 0x68) - iVar4) &&
           ((uVar8 == 0 || ((((arg4 & 1U) == 0 || (iVar2 != 0)) && (((arg4 & 2U) == 0 || (uVar9 != 0)))))))) {
            puVar7 = &stack0xffffffffffffffa8;
            if (((arg4 & 1U) != 0) && (puVar7 = &stack0xffffffffffffffa8, iVar2 != 0)) {
                puVar7 = &stack0xffffffffffffffa0;
                iStack_60 = iVar4;
                func_0x0001406abbce(arg1,iVar4,iVar4 + uVar8);
            }
            if (((arg4 & 2U) != 0) && (uVar9 != 0)) {
                *(puVar7 + -8) = arg1;
                *(puVar7 + -0x10) = 0x14000a26b;
                uVar5 = func_0x00014018e82d();
                *(puVar7 + -0x10) = uVar5;
                *(puVar7 + -0x18) = 0x14000a27d;
                func_0x000140202e00(arg1,iVar4,iVar4 + uVar8,uVar5);
            }
            *arg2 = uVar8;
            goto code_r0x00014000a28e;
        }
    }
    *arg2 = 0xffffffffffffffff;
code_r0x00014000a28e:
    *(arg2 + 8) = 0;
    *(arg2 + 0x10) = 0;
    return arg2;
}
