/* RVA 0x17210  tam 191 B  addr 0x140017210 */

//WARNING: Instruction at (ram,0x000140017240) overlaps instruction at (ram,0x00014001723f)
//

void fcn.140017210(void)

{
    ulong *puVar1;
    int64_t iVar2;
    int64_t iVar3;
    uint64_t uVar4;
    bool bVar5;
    
    if (0xf < *0x140020228) {
        iVar3 = CONCAT71(*0x140020211,*0x140020210);
        uVar4 = *0x140020228 + 1;
        iVar2 = iVar3;
        if (0xfff < uVar4) {
            while( true ) {
                iVar2 = *(iVar3 + -8);
                uVar4 = uVar4 + 0x27;
                iVar3 = iVar3 - iVar2;
                bVar5 = iVar3 + -0x27 < 0;
                if (iVar3 - 8U < 0x20) break;
                func_0x00014026e43b(iVar3,uVar4);
                if (!bVar5) {
                    while (puVar1 = *0x140020b08, *0x140020b08 != NULL) {
                        *0x140020b08 = **0x140020b08;
                        iVar2 = (**0x140018758)();
                        if (iVar2 != 0) {
                            (**0x140018758)(iVar2,1);
                        }
                        fcn.140015008(puVar1,0x10);
                    }
                    return;
                }
            }
        }
        fcn.140015008(iVar2);
    }
    *0x140020220 = *0x140018f70;
    *0x140020228 = *0x140018f78;
    *0x140020210 = 0;
    return;
}
