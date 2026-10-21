/* RVA 0x4d10  tam 847 B  addr 0x140004d10 */

int64_t fcn.140004d10(int64_t arg1)

{
    int64_t iVar1;
    ulong *puVar2;
    ulong *puVar3;
    ulong *puVar4;
    ulong *puVar5;
    ulong *puVar6;
    ulong *puVar7;
    
    *arg1 = 0;
    *(arg1 + 8) = 0;
    *(arg1 + 0x10) = 0;
    *(arg1 + 0x18) = 7;
    *arg1 = 0;
    puVar2 = arg1 + 0x20;
    *puVar2 = 0;
    *(arg1 + 0x28) = 0;
    *(arg1 + 0x30) = 0;
    *(arg1 + 0x38) = 0xf;
    *puVar2 = 0;
    puVar5 = arg1 + 0x40;
    *puVar5 = 0;
    *(arg1 + 0x48) = 0;
    *(arg1 + 0x50) = 0;
    *(arg1 + 0x58) = 0xf;
    *puVar5 = 0;
    puVar7 = arg1 + 0x60;
    *puVar7 = 0;
    *(arg1 + 0x68) = 0;
    *(arg1 + 0x70) = 0;
    *(arg1 + 0x78) = 0xf;
    *puVar7 = 0;
    puVar6 = arg1 + 0x80;
    *puVar6 = 0;
    *(arg1 + 0x88) = 0;
    *(arg1 + 0x90) = 0;
    *(arg1 + 0x98) = 0xf;
    *puVar6 = 0;
    puVar3 = arg1 + 0xa0;
    *puVar3 = 0;
    *(arg1 + 0xa8) = 0;
    *(arg1 + 0xb0) = 0;
    *(arg1 + 0xb8) = 0xf;
    *puVar3 = 0;
    puVar4 = arg1 + 0xc0;
    *puVar4 = 0;
    *(arg1 + 200) = 0;
    *(arg1 + 0xd0) = 0;
    *(arg1 + 0xd8) = 0xf;
    *puVar4 = 0;
    *(arg1 + 0xe0) = 12000;
    if (*(arg1 + 0x18) < 0x1c) {
        func_0x000140002320(arg1,0x1c,0,L"https://panel.mrgarabato.com",1);
    }
    else {
        iVar1 = *arg1;
        *(arg1 + 0x10) = 0x1c;
        fcn.140015ec4(iVar1,L"https://panel.mrgarabato.com",0x38);
        *(iVar1 + 0x38) = 0;
    }
    if (*(arg1 + 0x38) < 10) {
        func_0x0001400021e0(puVar2,10,0,"MrGarabato");
    }
    else {
        if (0xf < *(arg1 + 0x38)) {
            puVar2 = *puVar2;
        }
        *(arg1 + 0x30) = 10;
        fcn.140015ec4(puVar2,"MrGarabato",10);
        *(puVar2 + 10) = 0;
    }
    if (*(arg1 + 0x58) < 0xb) {
        func_0x0001400021e0(puVar5,0xb,0,"urus_bypass");
    }
    else {
        if (0xf < *(arg1 + 0x58)) {
            puVar5 = *puVar5;
        }
        *(arg1 + 0x50) = 0xb;
        fcn.140015ec4(puVar5,"urus_bypass",0xb);
        *(puVar5 + 0xb) = 0;
    }
    if (*(arg1 + 0x78) < 0xf) {
        func_0x0001400021e0(puVar7,0xf,0,"YourApplication");
    }
    else {
        if (0xf < *(arg1 + 0x78)) {
            puVar7 = *puVar7;
        }
        *(arg1 + 0x70) = 0xf;
        fcn.140015ec4(puVar7,"YourApplication",0xf);
        *(puVar7 + 0xf) = 0;
    }
    if (*(arg1 + 0x98) < 8) {
        func_0x0001400021e0(puVar6,8,0,"OWNER_ID");
    }
    else {
        if (0xf < *(arg1 + 0x98)) {
            puVar6 = *puVar6;
        }
        *(arg1 + 0x90) = 8;
        *puVar6 = 0x44495f52454e574f;
        *(puVar6 + 1) = 0;
    }
    if (*(arg1 + 0xb8) < 10) {
        func_0x0001400021e0(puVar3,10,0,"APP_SECRET");
    }
    else {
        if (0xf < *(arg1 + 0xb8)) {
            puVar3 = *puVar3;
        }
        *(arg1 + 0xb0) = 10;
        fcn.140015ec4(puVar3,"APP_SECRET",10);
        *(puVar3 + 10) = 0;
    }
    if (*(arg1 + 0xd8) < 3) {
        func_0x0001400021e0(puVar4,3,0,0x140018ebc);
    }
    else {
        if (0xf < *(arg1 + 0xd8)) {
            puVar4 = *puVar4;
        }
        *(arg1 + 0xd0) = 3;
        fcn.140015ec4(puVar4,0x140018ebc,3);
        *(puVar4 + 3) = 0;
    }
    return arg1;
}
