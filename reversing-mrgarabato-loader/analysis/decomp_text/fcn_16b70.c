/* RVA 0x16b70  tam 101 B  addr 0x140016b70 */

//WARNING: Instruction at (ram,0x000140016ba0) overlaps instruction at (ram,0x000140016b9f)
//

void fcn.140016b70(void)

{
    code *pcVar1;
    int64_t iVar2;
    int64_t iVar3;
    uint64_t uVar4;
    bool bVar5;
    
    if (0xf < *0x140020058) {
        iVar2 = CONCAT71(*0x140020041,*0x140020040);
        uVar4 = *0x140020058 + 1;
        iVar3 = iVar2;
        if (0xfff < uVar4) {
            while( true ) {
                iVar3 = *(iVar2 + -8);
                uVar4 = uVar4 + 0x27;
                iVar2 = iVar2 - iVar3;
                bVar5 = (POPCOUNT(iVar2 - 0x27U & 0xff) & 1U) == 0;
                if (iVar2 - 8U < 0x1f || iVar2 - 0x27U == 0) break;
                func_0x000140214b09(iVar2,uVar4);
                if (!bVar5) {
                    pcVar1 = swi(3);
                    (*pcVar1)();
                    return;
                }
            }
        }
        fcn.140015008(iVar3);
    }
    *0x140020050 = *0x140018f70;
    *0x140020058 = *0x140018f78;
    *0x140020040 = 0;
    return;
}
