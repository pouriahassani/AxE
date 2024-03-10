
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
int amul(int rd, int rs1, int rs2)
{
    asm __volatile__ (".word 0xFEC5857F\n");
    asm __volatile__ ("addi %0, x10, 0" : "=r" (rd));
    
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
    
    print_str( "mul s\n" );
    
    int a = 333;
    int b = 444;
    
    int pro = 0;
    int pro_appr = 0;
    
    pro = a * b;
    pro_appr = amul( pro_appr, a, b );
    
    print_str("exact\n");
    print_dec(pro);
    nl();
    
    print_str("approx\n");
    print_dec(pro_appr);
    nl();
    
    print_str( "mul d\n" );
    
    while (1==1){}
}
