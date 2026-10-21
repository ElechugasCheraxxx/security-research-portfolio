/* RVA 0x3758e  tam 54 B  addr 0x14003758e */

void fcn.14003758a(int64_t arg1,ulong noname_1,ulong noname_2,int64_t arg2)

{
    int64_t in_RAX;
    uint64_t uVar1;
    uint8_t uStack0000000000000040;
    int64_t iStack0000000000000060;
    
    uStack0000000000000040 = arg1;
    uVar1 = CONCAT71(arg2 >> 8,arg2 & uStack0000000000000040);
    iStack0000000000000060 = in_RAX + 0x425d7c5e + uVar1 * 2;
    _uStack0000000000000040 = arg1 & 0xffffffff00000000;
    LOCK();
    UNLOCK();
    fcn.140024140(-arg1,noname_1,noname_2,~uVar1);
    fcn.1402c9763();
    return;
}
