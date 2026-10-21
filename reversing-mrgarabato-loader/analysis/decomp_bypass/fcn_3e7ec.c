/* RVA 0x3e7ec  tam 117 B  addr 0x14003e7ec */

int64_t fcn.14003e7ec(void)

{
    int64_t iVar1;
    
    iVar1 = func_0x00014003e9d8();
    if (((*0x1400535a0 & *(iVar1 + 200)) == 0) || (*(iVar1 + 0xc0) == 0)) {
        func_0x00014004252c(0xc);
        iVar1 = fcn.14003e794(iVar1 + 0xc0,*0x1400539d0);
        fcn.14004242c(0xc);
    }
    else {
        iVar1 = func_0x00014003e9d8();
        iVar1 = *(iVar1 + 0xc0);
    }
    if (iVar1 == 0) {
        func_0x000140041158(0x20);
    }
    return iVar1;
}
