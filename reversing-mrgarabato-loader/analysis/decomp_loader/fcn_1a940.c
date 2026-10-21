/* RVA 0x1a940  tam 3816 B  addr 0x14001a940 */

//WARNING: Control flow encountered bad instruction data

void fcn.14001a940(ulong param_1,ulong param_2)

{
    char *pcVar1;
    uint8_t uVar2;
    uint32_t *puVar3;
    char cVar4;
    uchar uVar5;
    unkbyte6 Var6;
    int64_t unaff_R13;
    char in_SF;
    char in_OF;
    
    Var6 = param_2 >> 0x10;
    uVar5 = param_2 >> 8;
    cVar4 = param_2;
    func_0x0001404b407c();
    fcn.1405627c2();
    fcn.140512c74();
    fcn.14055f9ef();
    fcn.140591128();
    fcn.140048599();
    if (in_OF != in_SF) {
        fcn.14059d104();
        fcn.1405cacf6();
        uVar2 = fcn.140526098();
        pcVar1 = CONCAT62(Var6,CONCAT11(uVar5,cVar4)) + -0x596017aa;
        *pcVar1 = *pcVar1 + (uVar2 ^ 0xe8);
        *(unaff_R13 + -0x18) = *(unaff_R13 + -0x18) + cVar4;
        in(CONCAT11(uVar5,cVar4));
        fcn.140564555();
        puVar3 = fcn.140045ac7();
        *puVar3 = *puVar3 | puVar3;
        fcn.14056c96d();
    //WARNING: Bad instruction - Truncating control flow here
        halt_baddata();
    }
    //WARNING: Bad instruction - Truncating control flow here
    halt_baddata();
}
