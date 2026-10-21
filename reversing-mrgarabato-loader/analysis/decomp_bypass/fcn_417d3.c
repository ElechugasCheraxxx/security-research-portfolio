/* RVA 0x417d3  tam 235 B  addr 0x1400417d3 */

ulong fcn.1400417d3(void)

{
    uint64_t uVar1;
    int64_t iVar2;
    uint64_t uVar3;
    char *pcVar4;
    uint64_t uVar5;
    int aiStackX_8 [2];
    int aiStackX_10 [6];
    
    if (*0x140058af8 == 0) {
        fcn.14003e4c0();
    }
    *0x1400569b4 = 0;
    func_0x00014015c452(0,0x1400568b0,0x104);
    *0x140056890 = 0x1400568b0;
    if ((*0x140058b10 == NULL) || (pcVar4 = *0x140058b10, **0x140058b10 == '\0')) {
        pcVar4 = 0x1400568b0;
    }
    func_0x0001400415f8(pcVar4,0,0,aiStackX_8,aiStackX_10);
    uVar5 = aiStackX_8[0];
    if ((((uVar5 < 0x1fffffffffffffff) && (uVar3 = aiStackX_10[0], uVar3 != 0xffffffffffffffff)) &&
        (uVar1 = uVar3 + uVar5 * 8, uVar3 <= uVar1)) && (iVar2 = func_0x000140040c50(uVar1), iVar2 != 0)) {
        func_0x0001400415f8(pcVar4,iVar2,iVar2 + uVar5 * 8,aiStackX_8,aiStackX_10);
        *0x14005685c = aiStackX_8[0] + -1;
        *0x140056860 = iVar2;
        return 0;
    }
    return 0xffffffff;
}
