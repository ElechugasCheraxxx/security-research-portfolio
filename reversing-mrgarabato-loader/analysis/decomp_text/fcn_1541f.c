/* RVA 0x1541f  tam 417 B  addr 0x14001541f */

//WARNING: Removing unreachable block (ram,0x0001400154de)
//WARNING: Removing unreachable block (ram,0x00014001544e)
//WARNING: Removing unreachable block (ram,0x000140015427)

ulong fcn.14001541f(ulong noname_0,int64_t arg1)

{
    int *piVar1;
    uint32_t *puVar2;
    int64_t iVar3;
    uint32_t uVar4;
    ulong uVar5;
    uint8_t uVar6;
    uint32_t uVar7;
    uint32_t uVar8;
    uint8_t in_XCR0;
    
    piVar1 = cpuid_basic_info(0);
    uVar8 = 0;
    puVar2 = cpuid_Version_info(1);
    uVar4 = puVar2[3];
    if ((piVar1[2] == 0x49656e69 && piVar1[3] == 0x6c65746e) && piVar1[1] == 0x756e6547) {
        *0x140020660 = 0xffffffffffffffff;
        uVar7 = *puVar2 & 0xfff3ff0;
        *0x140020658 = 0x8000;
        if ((((uVar7 == 0x106c0) || (uVar7 == 0x20660)) || (uVar7 == 0x20670)) ||
           ((uVar7 - 0x30650 < 0x21 && ((0x100010001U >> (uVar7 - 0x30650 & 0x3f) & 1) != 0)))) {
            *0x140020b74 = *0x140020b74 | 1;
        }
    }
    if (6 < *piVar1) {
        iVar3 = cpuid_Extended_Feature_Enumeration_info(7);
        uVar8 = *(iVar3 + 4);
        if ((uVar8 >> 9 & 1) != 0) {
            *0x140020b74 = *0x140020b74 | 2;
        }
    }
    *0x140020650 = 1;
    *0x140020654 = 2;
    if ((uVar4 >> 0x14 & 1) != 0) {
        *0x140020650 = 2;
        *0x140020654 = 6;
        if (((uVar4 >> 0x1b & 1) != 0) && ((uVar4 >> 0x1c & 1) != 0)) {
            uVar5 = xinuse(0);
            uVar6 = in_XCR0 & uVar5;
            if ((uVar6 & 6) == 6) {
                *0x140020654 = 0xe;
                *0x140020650 = 3;
                if ((uVar8 & 0x20) != 0) {
                    *0x140020650 = 5;
                    *0x140020654 = 0x2e;
                    if (((uVar8 & 0xd0030000) == 0xd0030000) && ((uVar6 & 0xe0) == 0xe0)) {
                        *0x140020654 = 0x6e;
                        *0x140020650 = 6;
                    }
                }
            }
        }
    }
    return 0;
}
