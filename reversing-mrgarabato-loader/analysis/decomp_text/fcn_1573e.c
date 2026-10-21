/* RVA 0x1573e  tam 182 B  addr 0x14001573e */

void fcn.14001573c(void)

{
    code *pcVar1;
    uint *puVar2;
    char cVar3;
    uint uVar4;
    int iVar5;
    
    func_0x000140015f2a(1);
    uVar4 = func_0x000140015cd0();
    func_0x000140015f4e(uVar4);
    uVar4 = func_0x000140015b60();
    puVar2 = func_0x000140015f78();
    *puVar2 = uVar4;
    cVar3 = fcn.140015088(1);
    if (cVar3 != '\0') {
        func_0x000140015d24();
        fcn.140015238(0x140015d60);
        uVar4 = func_0x0001400159f4();
        iVar5 = func_0x000140015f00(uVar4);
        if (iVar5 == 0) {
            func_0x000140015cd8();
            iVar5 = func_0x000140015d08();
            if (iVar5 != 0) {
                func_0x000140015f30(0x140015b60);
            }
            func_0x0001400159b0();
            func_0x0001400159b0();
            uVar4 = func_0x000140015b60();
            func_0x000140015f6c(uVar4);
            cVar3 = func_0x000140015ce8();
            if (cVar3 != '\0') {
                func_0x000140015f06();
            }
            func_0x000140015b60();
            iVar5 = func_0x000140015b58();
            if (iVar5 == 0) {
                return;
            }
        }
    }
    func_0x000140015a10(7);
    pcVar1 = swi(3);
    (*pcVar1)();
    return;
}
