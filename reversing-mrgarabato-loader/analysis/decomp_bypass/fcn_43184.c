/* RVA 0x43184  tam 149 B  addr 0x140043184 */

uint64_t fcn.140043184(int64_t arg1,int64_t arg2,int64_t arg3)

{
    uint8_t *puVar1;
    int iVar2;
    uint32_t uVar3;
    int64_t iVar4;
    uint *puVar5;
    ulong uStackX_10;
    
    uStackX_10 = arg2;
    iVar4 = func_0x000140044c20(arg1 & 0xffffffff);
    if (iVar4 == -1) {
        puVar5 = fcn.14003ef2c();
        *puVar5 = 9;
code_r0x0001400431b1:
        uStackX_10 = 0xffffffffffffffff;
    }
    else {
        iVar2 = func_0x0001400258f1(iVar4,uStackX_10 & 0xffffffff,&uStackX_10 + 4,arg3 & 0xffffffff);
        uStackX_10 = CONCAT44(uStackX_10._4_4_,iVar2);
        if (iVar2 == -1) {
            uVar3 = func_0x0001402a775e();
            if (uVar3 != 0) {
                fcn.14003ef6c(uVar3);
                goto code_r0x0001400431b1;
            }
        }
        puVar1 = *((arg1 >> 5) * 8 + 0x1400588e0) + 8 + (arg1 & 0x1f) * 0x58;
        *puVar1 = *puVar1 & 0xfd;
    }
    return uStackX_10;
}
