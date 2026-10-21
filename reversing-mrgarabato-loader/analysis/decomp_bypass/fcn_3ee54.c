/* RVA 0x3ee54  tam 111 B  addr 0x14003ee54 */

void fcn.14003ee54(int64_t arg1,int64_t arg2,int64_t arg3,int64_t arg4)

{
    ulong uVar1;
    code *pcVar2;
    int64_t iVar3;
    
    iVar3 = *0x140056820;
    uVar1 = fcn.140138957();
    pcVar2 = CONCAT71(uVar1 >> 8,uVar1 + *(((arg4 & 0xffffffffU) - 0x35) + iVar3 * 4));
    if (pcVar2 != NULL) {
        (*pcVar2)();
        return;
    }
    fcn.14003ee20(arg1,arg2,arg3);
    pcVar2 = swi(3);
    (*pcVar2)();
    return;
}
