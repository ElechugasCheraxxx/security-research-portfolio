/* RVA 0x3da70  tam 283 B  addr 0x14003da70 */

uint32_t fcn.14003da70(int64_t arg1,int64_t arg2,int64_t arg3)

{
    int iVar1;
    uint32_t uVar2;
    int iVar3;
    uint64_t uVar4;
    
    iVar3 = arg2;
    uVar4 = arg2 & 0xffffffff;
    iVar1 = 1;
    if ((iVar3 == 0) && (*0x1400567e0 == 0)) {
        uVar2 = 0;
    }
    else {
        if ((iVar3 == 1) || (iVar3 == 2)) {
            if (*0x140049478 != NULL) {
                iVar1 = (**0x140049478)();
            }
            if ((iVar1 == 0) || (iVar1 = func_0x00014003d91c(arg1,uVar4,arg3), iVar1 == 0)) {
                return 0;
            }
        }
        uVar2 = func_0x000140026d90(arg1,uVar4,arg3);
        if ((iVar3 == 1) && (uVar2 == 0)) {
            func_0x000140026d90(arg1,0,arg3);
            func_0x00014003d91c(arg1,0,arg3);
            if (*0x140049478 != NULL) {
                (**0x140049478)(arg1,0,arg3);
            }
        }
        if ((iVar3 == 0) || (iVar3 == 3)) {
            iVar1 = func_0x00014003d91c(arg1,uVar4,arg3);
            uVar2 = -(iVar1 != 0) & uVar2;
            if ((uVar2 != 0) && (*0x140049478 != NULL)) {
                uVar2 = (**0x140049478)(arg1,uVar4,arg3);
            }
        }
    }
    return uVar2;
}
