/* RVA 0x1bc0  tam 253 B  addr 0x140001bc0 */

void fcn.140001bc0(uint64_t *param_1,ulong param_2,uint64_t param_3)

{
    code *pcVar1;
    uint64_t uVar2;
    uint64_t uVar3;
    int64_t iVar4;
    
    if (0x7fffffffffffffff < param_3) {
        fcn.140009520();
        pcVar1 = swi(3);
        (*pcVar1)();
        return;
    }
    if (param_3 < 0x10) {
        param_1[2] = param_3;
        param_1[3] = 0xf;
        fcn.14001b7f8();
        *(param_3 + param_1) = 0;
        return;
    }
    uVar2 = param_3 | 0xf;
    if (uVar2 < 0x8000000000000000) {
        if (uVar2 < 0x16) {
            uVar2 = 0x16;
        }
        if (uVar2 + 1 < 0x1000) {
            if (uVar2 == 0xffffffffffffffff) {
                uVar3 = 0;
            }
            else {
                uVar3 = fcn.14001a904();
            }
            goto code_r0x000140001c85;
        }
        uVar3 = uVar2 + 0x28;
        if (uVar3 <= uVar2 + 1) {
            fcn.140009490();
            pcVar1 = swi(3);
            (*pcVar1)();
            return;
        }
    }
    else {
        uVar3 = 0x8000000000000027;
        uVar2 = 0x7fffffffffffffff;
    }
    iVar4 = fcn.14001a904(uVar3);
    if (iVar4 == 0) {
        fcn.14061d902();
        pcVar1 = swi(3);
        (*pcVar1)();
        return;
    }
    uVar3 = iVar4 + 0x27U & 0xffffffffffffffe0;
    *(uVar3 - 8) = iVar4;
code_r0x000140001c85:
    *param_1 = uVar3;
    param_1[2] = param_3;
    param_1[3] = uVar2;
    fcn.14001b7f8(uVar3,param_2,param_3);
    *(param_3 + uVar3) = 0;
    return;
}
