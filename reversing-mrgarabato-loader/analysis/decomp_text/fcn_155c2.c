/* RVA 0x155c2  tam 20 B  addr 0x1400155c2 */

void fcn.1400155c0(int64_t arg1)

{
    code *pcVar1;
    char cVar2;
    ulong uVar3;
    char *pcVar4;
    ulong unaff_RBX;
    ulong uStack_10;
    
    fcn.14021e807();
    func_0x0001401bc826(arg1);
    uVar3 = func_0x00014016593b();
    func_0x00014025cf58(uVar3,0xc0000409);
    pcVar4 = func_0x000140129858(0x17);
    cVar2 = pcVar4 + *pcVar4;
    pcVar4 = CONCAT71(pcVar4 >> 8,cVar2);
    *pcVar4 = *pcVar4 + cVar2;
    pcVar1 = swi(0x29);
    (*pcVar1)();
    func_0x0001400156c8(0x140020c20);
    *0x140020d18 = uStack_10;
    *0x140020cb8 = &stack0xfffffffffffffff8;
    *0x140020b90 = uStack_10;
    *0x140020b80 = 0xc0000409;
    *0x140020b84 = 1;
    *0x140020b98 = 1;
    *0x140020ba0 = 2;
    *0x140020ca0 = unaff_RBX;
    fcn.1400155c0(0x14001a610);
    return;
}
