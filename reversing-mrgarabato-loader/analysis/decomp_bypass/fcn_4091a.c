/* RVA 0x4091a  tam 108 B  addr 0x14004091a */

void fcn.140040918(int64_t arg1)

{
    int64_t *arg1_00;
    int64_t *piVar1;
    
    fcn.14004252c(0xe);
    arg1_00 = *0x140056848;
    if (*(arg1 + 8) != 0) {
        piVar1 = 0x140056840;
        while (*0x140056848 != NULL) {
            if (**0x140056848 == *(arg1 + 8)) {
                piVar1[1] = (*0x140056848)[1];
                fcn.14003dc60(arg1_00);
                break;
            }
            piVar1 = *0x140056848;
        }
        fcn.14003dc60(*(arg1 + 8));
        *(arg1 + 8) = 0;
    }
    fcn.14004242c(0xe);
    return;
}
