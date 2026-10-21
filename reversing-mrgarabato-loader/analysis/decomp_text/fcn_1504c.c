/* RVA 0x1504c  tam 58 B  addr 0x14001504c */

uchar fcn.14001504c(int64_t arg1)

{
    char cVar1;
    
    if (arg1 == 0) {
        *0x140020b28 = 1;
    }
    func_0x000140015414();
    cVar1 = func_0x000140015ce8();
    if (cVar1 != '\0') {
        cVar1 = func_0x000140015ce8();
        if (cVar1 != '\0') {
            return 1;
        }
        func_0x000140015ce8(0);
    }
    return 0;
}
