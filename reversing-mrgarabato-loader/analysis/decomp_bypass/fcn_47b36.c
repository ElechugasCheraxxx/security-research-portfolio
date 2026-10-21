/* RVA 0x47b36  tam 93164 B  addr 0x140047b36 */

void fcn.140030fd0(int64_t arg1,int64_t arg2,int64_t arg3)

{
    uint64_t uVar1;
    int64_t iVar2;
    uint64_t uVar3;
    int64_t iVar4;
    uint64_t uVar5;
    ulong uStackX_20;
    ulong auStack_40 [3];
    
    uVar5 = arg2 | 7;
    if (uVar5 < 0x7fffffffffffffff) {
        uVar1 = *(arg1 + 0x18);
        uVar3 = uVar1 >> 1;
        if ((uVar5 / 3 < uVar3) && (uVar5 = uVar3 + uVar1, 0x7ffffffffffffffe - uVar3 < uVar1)) {
            uVar5 = 0x7ffffffffffffffe;
        }
    }
    else {
        uVar5 = arg2;
    }
    uVar1 = uVar5 + 1;
    iVar2 = 0;
    if (uVar1 != 0) {
        if (uVar1 < 0x8000000000000000) {
            iVar2 = fcn.14003c76c(uVar1 * 2);
            if (iVar2 != 0) goto code_r0x0001400310ab;
        }
        uStackX_20 = 0;
        fcn.14003d240(auStack_40,&uStackX_20);
        auStack_40[0] = 0x140049418;
        fcn.14003dbcc(auStack_40,0x1400517f0);
    }
code_r0x0001400310ab:
    if (arg3 != 0) {
        if (*(arg1 + 0x18) < 8) {
            iVar4 = arg1;
        }
        else {
            iVar4 = *arg1;
        }
        fcn.140041d50(iVar2,iVar4,arg3 * 2);
    }
    if (7 < *(arg1 + 0x18)) {
        fcn.14003c534(*arg1);
    }
    *arg1 = iVar2;
    *(arg1 + 0x18) = uVar5;
    *(arg1 + 0x10) = arg3;
    if (7 < uVar5) {
        arg1 = iVar2;
    }
    *(arg1 + arg3 * 2) = 0;
    return;
}
