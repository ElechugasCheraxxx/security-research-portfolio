/* RVA 0x15270  tam 91 B  addr 0x140015270 */

void fcn.140015270(int64_t arg1,int64_t arg2,int64_t arg3)

{
    code *pcVar1;
    char cVar2;
    char *pcVar3;
    uint64_t uVar4;
    uint64_t uVar5;
    ulong auStackX_10 [3];
    
    uVar5 = arg1;
    if ((*arg3 & 4) != 0) {
        uVar5 = *(arg3 + 4) + arg1 & -*(arg3 + 8);
    }
    uVar4 = *(*(arg2 + 0x10) + 8);
    if ((*(uVar4 + 3 + *(arg2 + 8)) & 0xf) != 0) {
        arg1 = arg1 + (*(uVar4 + 3 + *(arg2 + 8)) & 0xfffffff0);
    }
    uVar5 = arg1 ^ *((*arg3 & 0xfffffff8) + uVar5);
    if ((uVar5 == *0x140020600) && (uVar5 >> 0x30 == 0)) {
        return;
    }
    pcVar3 = func_0x000140129858(0x17);
    cVar2 = pcVar3 + *pcVar3;
    pcVar3 = CONCAT71(pcVar3 >> 8,cVar2);
    *pcVar3 = *pcVar3 + cVar2;
    pcVar1 = swi(0x29);
    (*pcVar1)();
    func_0x0001400156c8(0x140020c20);
    *0x140020cb8 = auStackX_10;
    *0x140020ca0 = auStackX_10[0];
    *0x140020b80 = 0xc0000409;
    *0x140020b84 = 1;
    *0x140020b98 = 1;
    *0x140020ba0 = 2;
    *0x140020b90 = uVar5;
    *0x140020d18 = uVar5;
    func_0x0001400155c0(0x14001a610);
    return;
}
