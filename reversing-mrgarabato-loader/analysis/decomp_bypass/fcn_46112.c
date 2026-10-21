/* RVA 0x46112  tam 363 B  addr 0x140046112 */

void fcn.140046112(int64_t arg1,int64_t arg2,int64_t arg3,int64_t arg4)

{
    int iVar1;
    int iVar2;
    int64_t iVar3;
    int64_t iVar4;
    int64_t iVar5;
    int iVar6;
    
    iVar2 = fcn.140045e94(arg1,arg2,arg3);
    iVar3 = fcn.140045878();
    iVar4 = fcn.14003e9d8();
    *(iVar4 + 0x100) = *(iVar4 + 0x100) + 1;
    while ((iVar2 != -1 && (arg4 < iVar2))) {
        if ((iVar2 < 0) || (*(arg3 + 4) <= iVar2)) {
            fcn.14003f234();
        }
        iVar5 = iVar2;
        iVar4 = fcn.140045878();
        iVar2 = *(*(arg3 + 8) + iVar4 + iVar5 * 8);
        iVar6 = iVar2;
        iVar4 = fcn.140045878();
        if (*(*(arg3 + 8) + 4 + iVar4 + iVar5 * 8) == 0) {
            iVar4 = 0;
        }
        else {
            iVar4 = fcn.140045878();
            iVar1 = *(*(arg3 + 8) + 4 + iVar4 + iVar5 * 8);
            iVar4 = fcn.140045878();
            iVar4 = iVar4 + iVar1;
        }
        if (iVar4 != 0) {
            func_0x000140045ebc(arg1,arg2,arg3,iVar2,iVar6);
            iVar4 = fcn.140045878();
            if (*(*(arg3 + 8) + 4 + iVar4 + iVar5 * 8) == 0) {
                iVar4 = 0;
            }
            else {
                iVar4 = fcn.140045878();
                iVar6 = *(*(arg3 + 8) + 4 + iVar4 + iVar5 * 8);
                iVar4 = fcn.140045878();
                iVar4 = iVar4 + iVar6;
            }
            func_0x0001400472b0(iVar4,arg1,0x103);
            fcn.1400458a8(iVar3);
        }
    }
    iVar3 = fcn.14003e9d8();
    if (0 < *(iVar3 + 0x100)) {
        iVar3 = fcn.14003e9d8();
        *(iVar3 + 0x100) = *(iVar3 + 0x100) + -1;
    }
    if ((iVar2 != -1) && (arg4 < iVar2)) {
        fcn.14003f234();
    }
    func_0x000140045ebc(arg1,arg2,arg3,iVar2);
    return;
}
