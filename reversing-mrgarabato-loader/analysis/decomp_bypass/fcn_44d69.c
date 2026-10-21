/* RVA 0x44d69  tam 84 B  addr 0x140044d69 */

ushort fcn.140044d69(void)

{
    int iVar1;
    ushort unaff_retaddr;
    uchar auStackX_8 [8];
    uchar auStackX_10 [24];
    
    if (*0x140054320 == -2) {
        func_0x0001400453a0();
    }
    if ((*0x140054320 != -1) && (iVar1 = func_0x0001401af7c2(*0x140054320,auStackX_8,1,auStackX_10), iVar1 != 0)) {
        return unaff_retaddr;
    }
    return 0xffff;
}
