
// This is free and unencumbered software released into the public domain.

#include "util.h"

// The main function has to be called my_main. An explanation will follow.

int cnt_to = 0x0000004F;

void my_main()
{
    int a = 333;
    int b = 444;
    
    int pro;
    
    int i = 0;
    
    for ( i = 0; i < cnt_to; i++ )
    {
        pro = a * b;
    }
}
