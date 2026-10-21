/* RVA 0x15010  tam 57 B  addr 0x140015010 */

ulong fcn.140015010(void)

{
    int64_t iVar1;
    int iVar2;
    int64_t iVar3;
    ulong uVar4;
    int64_t unaff_GS_OFFSET;
    bool bVar5;
    
    iVar2 = func_0x0001400159fc();
    if (iVar2 == 0) {
code_r0x00014001503e:
        uVar4 = 0;
    }
    else {
        iVar1 = *(*(unaff_GS_OFFSET + 0x30) + 8);
        do {
            iVar3 = 0;
            LOCK();
            bVar5 = *0x140020b20 == 0;
            if (bVar5) {
                *0x140020b20 = iVar1;
            }
            else {
                iVar3 = *0x140020b20;
            }
            UNLOCK();
            if (bVar5) goto code_r0x00014001503e;
        } while (iVar1 != iVar3);
        uVar4 = 1;
    }
    return uVar4;
}
