/* RVA 0x43d68  tam 50 B  addr 0x140043d68 */

void fcn.140043d68(int64_t arg1,int64_t arg2)

{
    code *pcVar1;
    uchar uVar2;
    uchar *unaff_RDI;
    
    if (arg1 < 0x14) {
        fcn.14004252c(arg1 + 0x10);
        *(arg2 + 0x18) = *(arg2 + 0x18) | 0x8000;
        return;
    }
    uVar2 = fcn.140154f87(arg2 + 0x30);
    *unaff_RDI = uVar2;
    pcVar1 = swi(3);
    (*pcVar1)();
    return;
}
