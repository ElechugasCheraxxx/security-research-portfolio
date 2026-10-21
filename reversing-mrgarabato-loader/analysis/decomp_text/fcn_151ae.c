/* RVA 0x151ae  tam 36 B  addr 0x1400151ae */

void fcn.1400151ac(int64_t arg1)

{
    int iVar1;
    
    iVar1 = fcn.1400159fc();
    if ((iVar1 != 0) && (arg1 == '\0')) {
        LOCK();
        *0x140020b20 = 0;
        UNLOCK();
    }
    return;
}
