/* RVA 0x15c2d  tam 166 B  addr 0x140015c2d */

//WARNING: Control flow encountered bad instruction data

void fcn.140015c2a(void)

{
    int64_t var_10h;
    int64_t var_18h;
    uchar auStackX_18 [16];
    int64_t var_10h_2;
    
    if (*0x140020600 == 0x2b992ddfa232) {
        var_18h = 0;
        fcn.14016ef51(&var_18h);
        fcn.1402cfccf();
        fcn.14002838f();
        fcn.1402dac9d(auStackX_18);
    //WARNING: Bad instruction - Truncating control flow here
        halt_baddata();
    }
    *0x140020640 = ~*0x140020600;
    return;
}
