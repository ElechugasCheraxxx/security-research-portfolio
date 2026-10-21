/* RVA 0x455bc  tam 209 B  addr 0x1400455bc */

//WARNING: Control flow encountered bad instruction data

ulong fcn.1400455bc(int64_t arg1)

{
    uint32_t uVar1;
    int64_t iVar2;
    int64_t iVar3;
    ulong uVar4;
    uint32_t uVar5;
    int64_t unaff_RBP;
    uchar uVar6;
    
    uVar5 = arg1;
    iVar2 = fcn.140044c20(arg1 & 0xffffffff);
    if (iVar2 == -1) {
code_r0x00014004562f:
        uVar1 = 0;
    }
    else {
        if (((uVar5 == 1) && ((*(*0x1400588e0 + 0xb8) & arg1) != 0)) ||
           ((uVar6 = SBORROW4(uVar5,2), uVar5 == 2 && (uVar6 = false, (*(*0x1400588e0 + 0x60) & 1) != 0)))) {
            iVar2 = fcn.140044c20(2);
            iVar3 = fcn.140044c20(1);
            uVar6 = SBORROW8(iVar3,iVar2);
            if (iVar3 == iVar2) goto code_r0x00014004562f;
        }
        uVar4 = fcn.140044c20(arg1 & 0xffffffff);
        func_0x0001402dbe19(uVar4);
        if (!uVar6) {
    //WARNING: Bad instruction - Truncating control flow here
            halt_baddata();
        }
        *(unaff_RBP + 10) = 0;
        uVar1 = func_0x0001406aa9aa();
    }
    fcn.140044b74(arg1 & 0xffffffff);
    *(*((uVar5 >> 5) * 8 + 0x1400588e0) + 8 + (uVar5 & 0x1f) * 0x58) = 0;
    if (uVar1 == 0) {
        uVar4 = 0;
    }
    else {
        fcn.14003ef6c(uVar1);
        uVar4 = 0xffffffff;
    }
    return uVar4;
}
