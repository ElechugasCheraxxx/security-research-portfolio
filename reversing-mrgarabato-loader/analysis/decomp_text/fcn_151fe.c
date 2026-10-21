/* RVA 0x151fe  tam 58 B  addr 0x1400151fe */

int64_t fcn.1400151fc(int64_t arg1)

{
    int iVar1;
    int64_t iVar2;
    
    if (*0x140020b30 == -1) {
        iVar1 = func_0x000140015f18();
    }
    else {
        iVar1 = func_0x000140015f12(0x140020b30,arg1);
    }
    iVar2 = 0;
    if (iVar1 == 0) {
        iVar2 = arg1;
    }
    return iVar2;
}
