/* RVA 0x3d922  tam 332 B  addr 0x14003d922 */

//WARNING: Control flow encountered bad instruction data

ulong fcn.14003d922(ulong noname_0,int64_t arg1,int64_t arg2)

{
    code *pcVar1;
    int iVar2;
    int64_t iVar3;
    ulong uVar4;
    
    iVar2 = arg1;
    if (iVar2 == 1) {
        iVar2 = func_0x000140041a24();
        if (iVar2 != 0) {
            iVar2 = func_0x00014003eb70();
            if (iVar2 != 0) {
                func_0x0001400419b4();
                func_0x00014025c9b2();
    //WARNING: Bad instruction - Truncating control flow here
                halt_baddata();
            }
            func_0x000140041a7c();
        }
    }
    else if (iVar2 == 0) {
        if (0 < *0x1400567e0) {
            *0x1400567e0 = *0x1400567e0 + -1;
            if (*0x1400568a4 == 0) {
                func_0x000140041148();
            }
            if (arg2 == 0) {
                func_0x000140041454();
                func_0x00014003e874();
                func_0x000140041a7c();
                if (*0x1400539e8 != -1) {
                    func_0x00014003e874();
                }
            }
            return 1;
        }
    }
    else {
        if (iVar2 != 2) {
            if (iVar2 != 3) {
                return 1;
            }
            func_0x00014003eb30(0);
            return 1;
        }
        func_0x00014003e870();
        iVar3 = func_0x000140040cd0(1,0x2c8);
        if (iVar3 != 0) {
            func_0x00014021a666(*0x1400539e8,iVar3);
            pcVar1 = swi(3);
            uVar4 = (*pcVar1)();
            return uVar4;
        }
    }
    return 0;
}
