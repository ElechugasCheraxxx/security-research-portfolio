/* RVA 0x41c86  tam 173 B  addr 0x140041c86 */

void fcn.140041c86(ulong param_1,ushort param_2)

{
    ulong uVar1;
    uchar *unaff_RSI;
    uint64_t uVar2;
    ulong uStackX_10;
    uchar auStackX_18 [16];
    
    uStackX_10 = 0;
    if (*0x140053bd0 == 0x2b992ddfa232) {
        func_0x000140225084(&uStackX_10);
        func_0x0001402380b2();
        out(*unaff_RSI,param_2);
        func_0x0001401b8683();
        uVar1 = func_0x0001402787ed();
        uVar2 = CONCAT71(uVar1 >> 8,uVar1 + -0x48) & 0xffffffff;
        func_0x0001401de55b(auStackX_18 & 0xffffffff);
        *0x140053bd0 = uVar2 & 0xffffffffffff;
        if (*0x140053bd0 == 0x2b992ddfa232) {
            *0x140053bd0 = 0x2b992ddfa233;
        }
    }
    *0x140053bd8 = ~*0x140053bd0;
    return;
}
