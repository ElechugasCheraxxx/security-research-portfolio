/* RVA 0x1a984  tam 58 B  addr 0x14001a984 */

uchar fcn.14001a984(int64_t arg1)

{
    char cVar1;
    
    if (arg1 == 0) {
        *0x14002fa88 = 1;
    }
    func_0x00014001ad54();
    cVar1 = func_0x00014001b628();
    if (cVar1 != '\0') {
        cVar1 = func_0x00014001b628();
        if (cVar1 != '\0') {
            return 1;
        }
        func_0x00014001b628(0);
    }
    return 0;
}
