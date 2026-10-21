/* RVA 0x43b40  tam 83 B  addr 0x140043b40 */

void fcn.140043b40(int64_t arg1)

{
    int64_t iVar1;
    
    *0x14005722c = *0x14005722c + 1;
    iVar1 = func_0x000140040c50(0x1000);
    *(arg1 + 0x10) = iVar1;
    if (iVar1 == 0) {
        *(arg1 + 0x18) = *(arg1 + 0x18) | 4;
        *(arg1 + 0x24) = 2;
        *(arg1 + 0x10) = arg1 + 0x20;
    }
    else {
        *(arg1 + 0x18) = *(arg1 + 0x18) | 8;
        *(arg1 + 0x24) = 0x1000;
    }
    *(arg1 + 8) = 0;
    *arg1 = *(arg1 + 0x10);
    return;
}
