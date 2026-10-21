/* RVA 0x3065  tam 265 B  addr 0x140003065 */

int64_t fcn.140003065(int64_t arg1,int64_t arg2,int64_t arg3)

{
    code *pcVar1;
    uint64_t uVar2;
    uint64_t uVar3;
    int64_t iVar4;
    int64_t iVar5;
    ushort uVar6;
    
    uVar3 = 0;
    *arg1 = 0;
    *(arg1 + 8) = 0;
    *(arg1 + 0x10) = 0;
    *(arg1 + 0x18) = 0;
    if (0x7fffffffffffffff < arg2) {
        fcn.140009520();
        pcVar1 = swi(3);
        iVar5 = (*pcVar1)();
        return iVar5;
    }
    if (arg2 < 0x10) {
        *(arg1 + 0x10) = arg2;
        *(arg1 + 0x18) = 0xf;
        fcn.14001b804(0,arg3,arg2);
        *(arg2 + arg1) = 0;
        return arg1;
    }
    uVar2 = arg2 | 0xf;
    if (uVar2 < 0x8000000000000000) {
        if (uVar2 < 0x16) {
            uVar2 = 0x16;
        }
        if (uVar2 + 1 < 0x1000) {
            if (uVar2 != 0xffffffffffffffff) {
                uVar3 = fcn.14001a904();
            }
            goto code_r0x000140003137;
        }
        uVar3 = uVar2 + 0x28;
        if (uVar3 <= uVar2 + 1) {
            fcn.140009490();
            pcVar1 = swi(3);
            iVar5 = (*pcVar1)();
            return iVar5;
        }
    }
    else {
        uVar3 = 0x8000000000000027;
        uVar2 = 0x7fffffffffffffff;
    }
    iVar5 = arg2;
    iVar4 = fcn.14001a904(uVar3);
    uVar6 = iVar5;
    if (iVar4 == 0) {
        fcn.1404e5ce6();
        in(uVar6);
        pcVar1 = swi(3);
        iVar5 = (*pcVar1)();
        return iVar5;
    }
    uVar3 = iVar4 + 0x27U & 0xffffffffffffffe0;
    *(uVar3 - 8) = iVar4;
code_r0x000140003137:
    *arg1 = uVar3;
    *(arg1 + 0x10) = arg2;
    *(arg1 + 0x18) = uVar2;
    fcn.14001b804(uVar3,arg3,arg2);
    *(uVar3 + arg2) = 0;
    return arg1;
}
