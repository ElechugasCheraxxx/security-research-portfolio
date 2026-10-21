/* RVA 0x45acc  tam 61 B  addr 0x140045acc */

uint fcn.140045acc(int64_t arg1,ulong noname_1,int64_t arg2)

{
    int64_t in_RAX;
    int64_t iVar1;
    uchar auStack_18 [24];
    
    *(in_RAX + -0x28) = 0;
    *(in_RAX + -0x20) = arg1;
    *(in_RAX + -0x18) = arg2;
    iVar1 = fcn.14003e9d8();
    (**(iVar1 + 0xe0))(*arg1,auStack_18);
    return 0;
}
