/* RVA 0x31126  tam 203 B  addr 0x140031126 */

uchar fcn.140031126(int64_t arg1,int64_t arg2,int64_t arg3)

{
    uint64_t uVar1;
    ulong uVar2;
    code *pcVar3;
    uchar uVar4;
    uint64_t uVar5;
    
    if (0x7ffffffffffffffe < arg2) {
        fcn.14003c470(0x14004be20);
        pcVar3 = swi(3);
        uVar4 = (*pcVar3)();
        return uVar4;
    }
    uVar1 = *(arg1 + 0x18);
    if (uVar1 < arg2) {
        fcn.140030fd0(arg1,arg2,*(arg1 + 0x10));
    }
    else if ((arg3 == '\0') || (7 < arg2)) {
        if (arg2 == 0) {
            *(arg1 + 0x10) = 0;
            if (7 < uVar1) {
                arg1 = *arg1;
            }
            *arg1 = 0;
        }
    }
    else {
        uVar5 = *(arg1 + 0x10);
        if (arg2 < *(arg1 + 0x10)) {
            uVar5 = arg2;
        }
        if (7 < uVar1) {
            uVar2 = *arg1;
            if (uVar5 != 0) {
                fcn.140041d50(arg1,uVar2,uVar5 * 2);
            }
            fcn.14003c534(uVar2);
        }
        *(arg1 + 0x10) = uVar5;
        *(arg1 + 0x18) = 7;
        *(arg1 + uVar5 * 2) = 0;
    }
    return arg2 != 0;
}
