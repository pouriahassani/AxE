
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
    uint32_t PI = 0x40490fdb;

    fp_Sin(fpsub(0,fpmul(0x40000000,PI)));//-2*pi
    fp_Sin(fpmul(0xbfc00000,PI));//-3/2*pi
    fp_Sin(fpmul(0xbf800000,PI));//-*pi
    fp_Sin(fpmul(0xbf000000,PI));//-1/2*pi
    fp_Sin(0x00000000);//0
    fp_Sin(fpmul(0x3f000000,PI));//1/2*pi
    fp_Sin(PI);//pi
    fp_Sin(fpmul(0x3fc00000,PI));//3/2*pi
    fp_Sin(fpmul(0x40000000,PI));//2*pi

    fp_Sin(fpsub(0,fpadd(fpmul(0x3fc00000,PI),fpmul(0x40000000,PI))));//-2*pi-3/2pi
    fp_Sin(fpadd(fpmul(0x3fc00000,PI),fpmul(0x40000000,PI)));//-2*pi-3/2pi

    fp_Cos(fpsub(0,fpmul(0x40000000,PI)));//-2*pi
    fp_Cos(fpmul(0xbfc00000,PI));//-3/2*pi
    fp_Cos(fpmul(0xbf800000,PI));//-*pi
    fp_Cos(fpmul(0xbf000000,PI));//-1/2*pi
    fp_Cos(0x00000000);//0
    fp_Cos(fpmul(0x3f000000,PI));//1/2*pi
    fp_Cos(PI);//pi
    fp_Cos(fpmul(0x3fc00000,PI));//3/2*pi
    fp_Cos(fpmul(0x40000000,PI));//2*pi

    fp_Cos(fpsub(0,fpadd(fpmul(0x40000000,PI),fpmul(0x40000000,PI))));//-2*pi-3/2pi
    fp_Cos(fpadd(fpmul(0x40000000,PI),fpmul(0x40000000,PI)));//-2*pi-3/2pi


}