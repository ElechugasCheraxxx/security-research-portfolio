/* RVA 0x3e89c  tam 181 B  addr 0x14003e89c */

void fcn.14003e89c(int64_t arg1,int64_t arg2)

{
    *(arg1 + 0xa0) = 0x140049920;
    *(arg1 + 0x10) = 0;
    *(arg1 + 0x1c) = 1;
    *(arg1 + 200) = 1;
    *(arg1 + 0x174) = 0x43;
    *(arg1 + 0x1f7) = 0x43;
    *(arg1 + 0xb8) = 0x140053070;
    fcn.14004252c(0xd);
    LOCK();
    **(arg1 + 0xb8) = **(arg1 + 0xb8) + 1;
    UNLOCK();
    fcn.14004242c(0xd);
    fcn.14004252c(0xc);
    *(arg1 + 0xc0) = arg2;
    if (arg2 == 0) {
        *(arg1 + 0xc0) = *0x1400539d0;
    }
    fcn.14003e4e8(*(arg1 + 0xc0));
    fcn.14004242c(0xc);
    return;
}
