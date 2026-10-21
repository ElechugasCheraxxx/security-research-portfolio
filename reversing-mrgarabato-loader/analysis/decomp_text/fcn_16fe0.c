/* RVA 0x16fe0  tam 108 B  addr 0x140016fe0 */

//WARNING: Instruction at (ram,0x000140017017) overlaps instruction at (ram,0x000140017014)
//

void fcn.140016fe0(void)

{
    code *pcVar1;
    int64_t iVar2;
    int64_t iVar3;
    uint64_t uVar4;
    char cVar5;
    char cVar6;
    
    if (7 < *0x140020188) {
        iVar2 = CONCAT62(*0x140020172,*0x140020170);
        uVar4 = *0x140020188 * 2 + 2;
        iVar3 = iVar2;
        if (0xfff < uVar4) {
            while( true ) {
                iVar3 = *(iVar2 + -8);
                uVar4 = uVar4 + 0x27;
                iVar2 = iVar2 - iVar3;
                cVar6 = SBORROW8(iVar2 - 8U,0x1f);
                cVar5 = iVar2 + -0x27 < 0;
                if (iVar2 - 8U < 0x20) break;
                func_0x0001401a862e(iVar2,uVar4);
                if (cVar6 != cVar5) {
                    pcVar1 = swi(3);
                    (*pcVar1)();
                    return;
                }
            }
        }
        fcn.140015008(iVar3);
    }
    *0x140020180 = *0x140018f60;
    *0x140020188 = *0x140018f68;
    *0x140020170 = 0;
    return;
}
