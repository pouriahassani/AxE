
// This is free and unencumbered software released into the public domain.

#include "util.h"

// The main function has to be called my_main. An explanation will follow.

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
    
    //~ print_str( "mul s\n" );
    int n = 0;
    int a = 333;
    int b = 444;
    
    int pro;
    for (n = 0; n < 100; n++)
    {
        /* code */
        pro = a * b;
    }
    
    // pro = a * b;
    
    // Printing a decimal number. Note the function nl() to print just a newline
    // right after it.
    
    //~ print_dec(pro);
    //~ nl();
    
    //~ print_str( "mul d\n" );
}
