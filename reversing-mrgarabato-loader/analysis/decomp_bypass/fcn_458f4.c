/* RVA 0x458f4  tam 151 B  addr 0x1400458f4 */

void fcn.1400458f4(ulong noname_0,int64_t arg1,int64_t arg2)

{
    ulong uVar1;
    int iVar2;
    int64_t iVar3;
    int64_t iVar4;
    uint32_t uVar5;
    uint64_t uVar6;
    uint uVar7;
    
    uVar1 = func_0x00014004578c();
    iVar2 = func_0x000140045e8c(arg2);
    uVar6 = *(arg2 + 0xc);
    if (*(arg2 + 0xc) != 0) {
        iVar4 = uVar6 * 0x14;
        do {
            iVar4 = iVar4 + -0x14;
            iVar3 = fcn.14003e9d8();
            iVar3 = *(iVar3 + 0x128) + *(arg2 + 0x10) + iVar4;
            if ((*(iVar3 + 4) < iVar2) && (iVar2 <= *(iVar3 + 8))) goto code_r0x000140045955;
            uVar5 = uVar6 - 1;
            uVar6 = uVar5;
        } while (uVar5 != 0);
    }
    iVar3 = 0;
code_r0x000140045955:
    if (iVar3 == 0) {
        uVar7 = 0xffffffff;
    }
    else {
        uVar7 = *(iVar3 + 4);
    }
    func_0x0001400460f4(uVar1,arg1,arg2,uVar7);
    return;
}
