/* RVA 0x30d47  tam 94492 B  addr 0x140030d47 */

void fcn.140030d40(int64_t arg1,int64_t arg2,int64_t arg3)

{
    uint64_t uVar1;
    char cVar2;
    int64_t iVar3;
    uint64_t uVar4;
    ulong in_R9;
    
    uVar4 = arg3 - arg2;
    uVar1 = *(arg1 + 0x10);
    if ((uVar1 <= uVar4) && (*(arg1 + 0x18) != uVar4)) {
        cVar2 = func_0x000140031120(arg1,uVar4,1,in_R9,0xfffffffffffffffe);
        if (cVar2 != '\0') {
            *(arg1 + 0x10) = uVar1;
            if (*(arg1 + 0x18) < 8) {
                iVar3 = arg1;
            }
            else {
                iVar3 = *arg1;
            }
            *(iVar3 + uVar1 * 2) = 0;
        }
    }
    for (; arg2 != arg3; arg2 = arg2 + 1) {
        func_0x000140030de0(arg1,*arg2);
    }
    return;
}
