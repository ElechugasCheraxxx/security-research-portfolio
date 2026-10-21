/* RVA 0xb800  tam 43 B  addr 0x14000b800 */

void fcn.14000b800(int64_t arg1)

{
    int64_t *piVar1;
    
    piVar1 = fcn.14012e2a0(*(**arg1 + 4) + *arg1);
    if (piVar1 != NULL) {
        (**(*piVar1 + 0x10))(piVar1);
    }
    return;
}
