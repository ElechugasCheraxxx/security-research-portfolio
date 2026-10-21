/* RVA 0x467d4  tam 176 B  addr 0x1400467d4 */

void fcn.1400467d4(int64_t arg1,int64_t arg2,int64_t arg3,int64_t arg4)

{
    int iVar1;
    int64_t iVar2;
    ulong uVar3;
    int64_t iVar4;
    code *pcVar5;
    
    if ((*arg3 & 0x80000000) == 0) {
        iVar4 = *(arg3 + 8) + *arg2;
    }
    else {
        iVar4 = arg2;
    }
    iVar1 = fcn.1400465d0(arg1,arg2,arg3,arg4);
    if (iVar1 == 1) {
        pcVar5 = NULL;
        if (*(arg4 + 0x18) != 0) {
            iVar2 = fcn.140045890();
            pcVar5 = *(arg4 + 0x18) + iVar2;
        }
        uVar3 = func_0x0001400462c4(*(arg1 + 0x28),arg4 + 8);
        (*pcVar5)(iVar4,uVar3);
    }
    else if (iVar1 == 2) {
        pcVar5 = NULL;
        if (*(arg4 + 0x18) != 0) {
            iVar2 = fcn.140045890();
            pcVar5 = iVar2 + *(arg4 + 0x18);
        }
        uVar3 = func_0x0001400462c4(*(arg1 + 0x28),arg4 + 8);
        (*pcVar5)(iVar4,uVar3,1);
    }
    return;
}
