/* RVA 0x1b7e0  tam 24 B  addr 0x14001b7e0 */

//WARNING: Control flow encountered bad instruction data

void fcn.14001b7e0(ulong param_1,ushort param_2)

{
    uint *unaff_RSI;
    
    fcn.1400c2083();
    out(*unaff_RSI,param_2);
    fcn.14058124e();
    fcn.1405f4cdb();
    fcn.1405dda15();
    int.140580469();
    fcn.1405363bf();
    fcn.1405d3f78();
    fcn.1404b5727();
    //WARNING: Bad instruction - Truncating control flow here
    halt_baddata();
}
