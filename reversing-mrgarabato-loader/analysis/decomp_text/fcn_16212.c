/* RVA 0x16212  tam 49 B  addr 0x140016212 */

int fcn.140016210(ulong noname_0,int64_t arg1)

{
    int16_t iVar1;
    int iVar2;
    
    iVar2 = 0;
    if ((*(arg1 + 0x50) & 2) != 0) {
        *(arg1 + 0x50) = *(arg1 + 0x50) & 0xfffffffd;
        iVar1 = fcn.140037d50(arg1 + 0x148);
        iVar2 = iVar1;
    }
    return iVar2;
}
