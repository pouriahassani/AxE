
// This is free and unencumbered software released into the public domain.

#include "util.h"

// idea from:
// http://quasilyte.dev/blog/post/riscv32-custom-instruction-and-its-simulation/

//~ 0000001 01100 01011 000 01010 1101011
//~ 1111111 01100 01011 000 01010 1111111
//~ 11111110110001011000010101111111

// Should not be inlined, because we expect arguments
// in particular registers.

// the instruction itself does work with optimization O1, but not with O0.
// this is problam because mul only works with O0.
// to keep everything working with O0 an additional instruction is needed to
// read the result from the register. this is done by adding 0 to x10.

__attribute__((noinline))
int fpmul_approx(int rd, int rs1, int rs2)
{
    asm __volatile__ (".word 0x82C5850B\n");
    asm __volatile__ ("addi %0, x10, 0" : "=r" (rd)); //TODO: what is addi? Assembly? May have to be edited to also designate the custom instruction used (PCPI_FPMUL_APPROX)
    
    return rd;
}

// The main function has to be called my_main.

void my_main()
{
    // There are a few print functions located in util.h (found in dir _libs).
    // Contrary to printf there is a function for each type and should always
    // end with a newline as this tells the system the message is complete.
    
    // Please note that these prints can increase the program size dramatically
    // and it is best to use as few characters as possible e.g. using "s"
    // instead of "start" and "d" instead of "done".
    
    // The messeges are detected by the debugger module and further processed
    // by the simulation environment (sim_main.cpp under configurations)




    /*************************************************************************************************************************
    Sanity test for custom pcpi_fpmul_approx instruction running on PCPI coprocessor called picorv32_pcpi_fpmul_approx
    **************************************************************************************************************************/
   //TODO: THIS DIRECTORY IS A STRAIGHT COPY OF THE FPMUL BENCHMARK PROGRAM. FILES IN THIS DIRECTORY HERE HAVE NOT BEEN VERIFIED AND WE DO NOT KNOW WHAT THEY DO OR IF THEY MATTER.
    int fpa = 0x40133333; // 2.3
    int fpb = 0x3DCCCCCD; // 0.1
    
    int fppro = 0;
    fppro = fpmul_approx( fppro, fpa, fpb);



    // print_str("exact\n");
    // print_dec(pro);
    nl();
    
    // print_str("approx\n");
    print_dec(fppro);
    nl();
    
    print_str( "mul d\n" );
    
    while (1==1){}
}
