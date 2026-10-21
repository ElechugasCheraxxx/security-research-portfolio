/* RVA 0xa886  tam 109 B  addr 0x14000a886 */

int64_t fcn.14000a880(int64_t arg1,int64_t arg2,int64_t arg3)

{
    ulong uVar1;
    ulong *puVar2;
    int64_t arg3_00;
    
    arg3_00 = -1;
    do {
        arg3_00 = arg3_00 + 1;
    } while (*(arg3 + arg3_00) != '\0');
    puVar2 = fcn.140009420(arg2,arg3,arg3_00);
    *arg1 = 0;
    *(arg1 + 8) = 0;
    *(arg1 + 0x10) = 0;
    *(arg1 + 0x18) = 0;
    uVar1 = puVar2[1];
    *arg1 = *puVar2;
    *(arg1 + 8) = uVar1;
    uVar1 = puVar2[3];
    *(arg1 + 0x10) = puVar2[2];
    *(arg1 + 0x18) = uVar1;
    puVar2[2] = 0;
    puVar2[3] = 0xf;
    *puVar2 = 0;
    return arg1;
}
