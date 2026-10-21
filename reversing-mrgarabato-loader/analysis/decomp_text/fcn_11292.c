/* RVA 0x11292  tam 68 B  addr 0x140011292 */

void fcn.140011290(ulong noname_0,int64_t arg1)

{
    int64_t iVar1;
    uint32_t uVar2;
    ushort uVar3;
    int64_t unaff_RBP;
    int unaff_ESI;
    int32_t var_15h;
    
    uVar3 = arg1;
    iVar1 = -1;
    do {
        iVar1 = iVar1 + 1;
    } while (*(arg1 + iVar1) != '\0');
    if (iVar1 != 0) {
        uVar2 = *arg1;
        iVar1 = fcn.1401d881f();
        *(iVar1 + 0x5b8d4803) = *(iVar1 + 0x5b8d4803) | uVar2;
        *(iVar1 + -0x7d) = *(iVar1 + -0x7d) + uVar2;
        out(uVar3,iVar1);
        *(unaff_RBP + -0x15) = *(unaff_RBP + -0x15) + unaff_ESI;
    }
    return;
}
