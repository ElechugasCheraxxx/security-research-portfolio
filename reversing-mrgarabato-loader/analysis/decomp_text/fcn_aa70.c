/* RVA 0xaa70  tam 89 B  addr 0x14000aa70 */

//WARNING: Instruction at (ram,0x00014000aa7a) overlaps instruction at (ram,0x00014000aa74)
//

uint64_t fcn.14000aa70(int64_t arg1)

{
    char *pcVar1;
    code *pcVar2;
    int iVar3;
    uint64_t uVar4;
    uchar in_DL;
    char in_DH;
    unkbyte6 in_register_00000012;
    
    if (0xfff < arg1) {
        while( true ) {
            if (arg1 + 0x27U <= arg1) {
                fcn.140009350();
                pcVar2 = swi(3);
                uVar4 = (*pcVar2)();
                return uVar4;
            }
            arg1 = fcn.140014fcc(arg1 + 0x27U);
            if (arg1 != 0) break;
            fcn.1400252fc();
            pcVar1 = CONCAT62(in_register_00000012,CONCAT11(in_DH,in_DL)) + 0x31;
            *pcVar1 = *pcVar1 + in_DH;
        }
        uVar4 = arg1 + 0x27U & 0xffffffffffffffe0;
        *(uVar4 - 8) = arg1;
        return uVar4;
    }
    if (arg1 == 0) {
        return 0;
    }
    do {
        uVar4 = func_0x000140015eee(arg1);
        if (uVar4 != 0) {
            return uVar4;
        }
        iVar3 = func_0x000140015efa(arg1);
    } while (iVar3 != 0);
    if (arg1 == -1) {
        fcn.140009350();
        pcVar2 = swi(3);
        uVar4 = (*pcVar2)();
        return uVar4;
    }
    func_0x0001400159d4();
    pcVar2 = swi(3);
    uVar4 = (*pcVar2)();
    return uVar4;
}
