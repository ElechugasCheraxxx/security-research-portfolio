/* RVA 0x15b64  tam 81 B  addr 0x140015b64 */

uint64_t fcn.140015b64(void)

{
    ulong uVar1;
    int16_t *piVar2;
    uint64_t uVar3;
    int *piVar4;
    char cVar5;
    
    cVar5 = '\0';
    uVar1 = func_0x000140123092(0);
    piVar2 = CONCAT71(uVar1 >> 8,(uVar1 + -0x48) - cVar5);
    if ((((piVar2 == 0) || (*piVar2 != 0x5a4d)) || (piVar4 = *(piVar2 + 0x1e) + piVar2, *piVar4 != 0x4550)) ||
       ((piVar2 = 0x20b, piVar4[6] != 0x20b || (piVar4[0x21] < 0xf)))) {
        uVar3 = piVar2 & 0xffffffffffffff00;
    }
    else {
        uVar3 = CONCAT71(2,piVar4[0x3e] != 0);
    }
    return uVar3;
}
