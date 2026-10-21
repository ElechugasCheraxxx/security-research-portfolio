/* RVA 0x44ee8  tam 76 B  addr 0x140044ee8 */

//WARNING: Removing unreachable block (ram,0x000140045001)
//WARNING: Removing unreachable block (ram,0x000140044fad)
//WARNING: Removing unreachable block (ram,0x000140044fb7)

int fcn.140044ee8(int64_t arg1)

{
    int64_t iVar1;
    int iVar2;
    uint uVar3;
    int iVar4;
    uint32_t uVar5;
    ulong in_R8;
    ulong in_R9;
    int64_t iVar6;
    uint32_t uVar7;
    
    if (arg1 != 0) {
        iVar2 = fcn.140044e6c(arg1);
        if (iVar2 == 0) {
            if ((*(arg1 + 0x18) & 0x4000) == 0) {
                iVar2 = 0;
            }
            else {
                uVar3 = fcn.140043e08(arg1);
                iVar2 = func_0x0001400454e4(uVar3);
                iVar2 = -(iVar2 != 0);
            }
        }
        else {
            iVar2 = -1;
        }
        return iVar2;
    }
    iVar2 = 0;
    fcn.14004252c(1);
    for (uVar5 = 0; uVar5 < *0x1400588c0; uVar5 = uVar5 + 1) {
        iVar6 = uVar5;
        if ((*(*0x1400578a8 + iVar6 * 8) != 0) && (iVar1 = *(*0x1400578a8 + iVar6 * 8), (*(iVar1 + 0x18) & 0x83) != 0))
        {
            uVar7 = uVar5;
            fcn.140043d68(uVar5,iVar1);
            iVar1 = *(*0x1400578a8 + iVar6 * 8);
            if (((*(iVar1 + 0x18) & 0x83) != 0) &&
               (((*(iVar1 + 0x18) & 2) != 0 && (iVar4 = fcn.140044ee8(iVar1), iVar4 == -1)))) {
                iVar2 = -1;
            }
            func_0x000140043de8(uVar5,*(*0x1400578a8 + iVar6 * 8),in_R8,in_R9,uVar7);
        }
    }
    fcn.14004242c(1);
    return iVar2;
}
