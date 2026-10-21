/* RVA 0x3dfda  tam 144 B  addr 0x14003dfda */

uint64_t fcn.14003dfd8(int64_t arg1)

{
    uint64_t uVar1;
    int iVar2;
    uchar *puVar3;
    uchar auStack_48 [32];
    int64_t aiStack_28 [2];
    int64_t iStack_18;
    char cStack_10;
    
    puVar3 = auStack_48;
    fcn.14003c53c(aiStack_28,0);
    *0x140056800 = 0;
    iVar2 = arg1;
    if (iVar2 == -2) {
        *0x140056800 = 1;
        puVar3 = &stack0xffffffffffffffb0;
        uVar1 = func_0x000140241fc0();
    }
    else if (iVar2 == -3) {
        *0x140056800 = 1;
        puVar3 = &stack0xffffffffffffffb0;
        uVar1 = func_0x0001401c4bbf();
    }
    else {
        if (iVar2 != -4) {
            if (cStack_10 != '\0') {
                *(iStack_18 + 200) = *(iStack_18 + 200) & 0xfffffffd;
            }
            return arg1 & 0xffffffff;
        }
        *0x140056800 = 1;
        uVar1 = *(aiStack_28[0] + 4);
    }
    if (puVar3[0x38] != '\0') {
        *(*(puVar3 + 0x30) + 200) = *(*(puVar3 + 0x30) + 200) & 0xfffffffd;
    }
    return uVar1;
}
