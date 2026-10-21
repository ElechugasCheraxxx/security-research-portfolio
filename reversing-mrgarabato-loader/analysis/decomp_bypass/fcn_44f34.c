/* RVA 0x44f34  tam 47 B  addr 0x140044f34 */

int fcn.140044f34(int64_t arg1)

{
    int64_t iVar1;
    int iVar2;
    uint32_t uVar3;
    int iVar4;
    int iVar5;
    ulong in_R8;
    ulong in_R9;
    int64_t iVar6;
    uint32_t uVar7;
    
    iVar4 = 0;
    iVar5 = 0;
    fcn.14004252c(1);
    for (uVar3 = 0; iVar2 = arg1, uVar3 < *0x1400588c0; uVar3 = uVar3 + 1) {
        iVar6 = uVar3;
        if ((*(*0x1400578a8 + iVar6 * 8) != 0) && (iVar1 = *(*0x1400578a8 + iVar6 * 8), (*(iVar1 + 0x18) & 0x83) != 0))
        {
            uVar7 = uVar3;
            fcn.140043d68(uVar3,iVar1);
            iVar1 = *(*0x1400578a8 + iVar6 * 8);
            if ((*(iVar1 + 0x18) & 0x83) != 0) {
                if (iVar2 == 1) {
                    iVar2 = fcn.140044ee8(iVar1);
                    if (iVar2 != -1) {
                        iVar4 = iVar4 + 1;
                    }
                }
                else if (((iVar2 == 0) && ((*(iVar1 + 0x18) & 2) != 0)) && (iVar2 = fcn.140044ee8(iVar1), iVar2 == -1))
                {
                    iVar5 = -1;
                }
            }
            func_0x000140043de8(uVar3,*(*0x1400578a8 + iVar6 * 8),in_R8,in_R9,uVar7);
        }
    }
    fcn.14004242c(1);
    if (iVar2 == 1) {
        iVar5 = iVar4;
    }
    return iVar5;
}
