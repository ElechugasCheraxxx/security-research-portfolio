/* RVA 0x30de6  tam 236 B  addr 0x140030de6 */

int64_t fcn.140030de6(int64_t arg1,int64_t arg2)

{
    uint64_t uVar1;
    code *pcVar2;
    int64_t iVar3;
    
    if (-*(arg1 + 0x10) - 1U < 2) {
        fcn.14003c470(0x14004be20);
        pcVar2 = swi(3);
        iVar3 = (*pcVar2)();
        return iVar3;
    }
    uVar1 = *(arg1 + 0x10) + 1;
    if (uVar1 < 0x7fffffffffffffff) {
        if (*(arg1 + 0x18) < uVar1) {
            fcn.140030fd0(arg1,uVar1);
            if (uVar1 == 0) {
                return arg1;
            }
        }
        else if (uVar1 == 0) {
            *(arg1 + 0x10) = 0;
            if (*(arg1 + 0x18) < 8) {
                *arg1 = 0;
                return arg1;
            }
            **arg1 = 0;
            return arg1;
        }
        if (*(arg1 + 0x18) < 8) {
            iVar3 = arg1;
        }
        else {
            iVar3 = *arg1;
        }
        *(iVar3 + *(arg1 + 0x10) * 2) = arg2;
        *(arg1 + 0x10) = uVar1;
        if (*(arg1 + 0x18) < 8) {
            iVar3 = arg1;
        }
        else {
            iVar3 = *arg1;
        }
        *(iVar3 + uVar1 * 2) = 0;
        return arg1;
    }
    fcn.14003c470(0x14004be20);
    pcVar2 = swi(3);
    iVar3 = (*pcVar2)();
    return iVar3;
}
