/* RVA 0x171a0  tam 101 B  addr 0x1400171a0 */

//WARNING: Instruction at (ram,0x0001400171d0) overlaps instruction at (ram,0x0001400171cf)
//

void fcn.1400171a0(void)

{
    uint64_t uVar1;
    code *pcVar2;
    int64_t iVar3;
    int64_t iVar4;
    uint64_t uVar5;
    bool bVar6;
    char cVar7;
    char cVar8;
    
    if (0xf < *0x140020248) {
        iVar3 = CONCAT71(*0x140020231,*0x140020230);
        uVar5 = *0x140020248 + 1;
        iVar4 = iVar3;
        if (0xfff < uVar5) {
            while( true ) {
                iVar4 = *(iVar3 + -8);
                uVar5 = uVar5 + 0x27;
                iVar3 = iVar3 - iVar4;
                uVar1 = iVar3 - 8;
                cVar8 = SBORROW8(uVar1,0x1f);
                cVar7 = iVar3 + -0x27 < 0;
                bVar6 = uVar1 == 0x1f;
                if (uVar1 < 0x20) break;
                func_0x0001401e0523(iVar3,uVar5);
                if (bVar6 || cVar8 != cVar7) {
                    pcVar2 = swi(3);
                    (*pcVar2)();
                    return;
                }
            }
        }
        fcn.140015008(iVar4);
    }
    *0x140020240 = *0x140018f70;
    *0x140020248 = *0x140018f78;
    *0x140020230 = 0;
    return;
}
