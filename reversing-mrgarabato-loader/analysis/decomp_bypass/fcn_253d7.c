/* RVA 0x253d7  tam 92 B  addr 0x1400253d7 */

void fcn.140025399(int64_t arg1,int64_t arg2)

{
    code *pcVar1;
    int *piVar2;
    int in_R10D;
    uint in_R10;
    ulong uStack0000000000000060;
    ulong in_stack_00000070;
    
    LOCK();
    UNLOCK();
    uStack0000000000000060 = CONCAT44(in_R10,in_R10D * 2);
    fcn.1402dd4df(arg1,in_stack_00000070);
    fcn.140242033();
    fcn.1401fb747();
    piVar2 = fcn.140145d2d();
    *piVar2 = *piVar2 + piVar2;
    *piVar2 = *piVar2 + piVar2;
    pcVar1 = swi(3);
    (*pcVar1)();
    return;
}
