/* RVA 0x465e5  tam 514 B  addr 0x1400465e5 */

char fcn.1400465d0(int64_t arg1,int64_t arg2,int64_t arg3,int64_t arg4)

{
    int iVar1;
    int64_t iVar2;
    int64_t iVar3;
    ulong uVar4;
    
    iVar3 = 0;
    iVar1 = *(arg3 + 4);
    if (iVar1 == 0) {
        iVar2 = iVar3;
    }
    else {
        iVar2 = fcn.140045878();
        iVar2 = iVar1 + iVar2;
    }
    if (iVar2 == 0) {
        return '\0';
    }
    if (iVar1 == 0) {
        iVar2 = iVar3;
    }
    else {
        iVar2 = fcn.140045878();
        iVar2 = iVar2 + *(arg3 + 4);
    }
    if (*(iVar2 + 0x10) == '\0') {
        return '\0';
    }
    if ((*(arg3 + 8) == 0) && ((*arg3 & 0x80000000) == 0)) {
        return '\0';
    }
    if (-1 < *arg3) {
        arg2 = *(arg3 + 8) + *arg2;
    }
    if ((*arg3 & 8) == 0) {
        if ((*arg4 & 1) == 0) {
            if (*(arg4 + 0x18) != 0) {
                iVar3 = fcn.140045890();
                iVar3 = iVar3 + *(arg4 + 0x18);
            }
            if (iVar3 == 0) {
                iVar1 = func_0x0001400472f8(*(arg1 + 0x28),1);
                if ((iVar1 != 0) && (iVar1 = func_0x000140047304(arg2,1), iVar1 != 0)) {
                    iVar3 = *(arg4 + 0x14);
                    uVar4 = func_0x0001400462c4(*(arg1 + 0x28),arg4 + 8);
                    fcn.140041d50(arg2,uVar4,iVar3);
                    return '\0';
                }
            }
            else {
                iVar1 = func_0x0001400472f8(*(arg1 + 0x28),1);
                if ((iVar1 != 0) && (iVar1 = func_0x000140047304(arg2,1), iVar1 != 0)) {
                    if (*(arg4 + 0x18) != 0) {
                        fcn.140045890();
                    }
                    iVar1 = func_0x000140047310();
                    if (iVar1 != 0) {
                        return ((*arg4 & 4) != 0) + '\x01';
                    }
                }
            }
        }
        else {
            iVar1 = func_0x0001400472f8(*(arg1 + 0x28),1);
            if ((iVar1 != 0) && (iVar1 = func_0x000140047304(arg2,1), iVar1 != 0)) {
                fcn.140041d50(arg2,*(arg1 + 0x28),*(arg4 + 0x14));
                if (*(arg4 + 0x14) != 8) {
                    return '\0';
                }
                if (*arg2 == 0) {
                    return '\0';
                }
                iVar3 = *arg2;
                goto code_r0x000140046697;
            }
        }
    }
    else {
        iVar1 = func_0x0001400472f8(*(arg1 + 0x28),1);
        if ((iVar1 != 0) && (iVar1 = func_0x000140047304(arg2,1), iVar1 != 0)) {
            iVar3 = *(arg1 + 0x28);
            *arg2 = iVar3;
code_r0x000140046697:
            iVar3 = func_0x0001400462c4(iVar3,arg4 + 8);
            *arg2 = iVar3;
            return '\0';
        }
    }
    fcn.14003f234();
    return '\0';
}
