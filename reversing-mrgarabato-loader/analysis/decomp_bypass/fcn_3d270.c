/* RVA 0x3d270  tam 68 B  addr 0x14003d270 */

int64_t fcn.14003d270(int64_t arg1,int64_t arg2)

{
    if (arg1 != arg2) {
        fcn.14003d218(arg1);
        if (*(arg2 + 0x10) == '\0') {
            *(arg1 + 8) = *(arg2 + 8);
        }
        else {
            fcn.14003d1bc(arg1,*(arg2 + 8));
        }
    }
    return arg1;
}
