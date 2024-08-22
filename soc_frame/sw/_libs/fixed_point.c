#include "fixed_point.h"

unsigned int fixed_mul_8q8( unsigned int a, unsigned int b )
{
    unsigned int mul = (a*b)>>8;
    
    return mul;
}

unsigned int fixed_div_8q8( unsigned int a, unsigned int b )
{
    unsigned int div = (a<<8)/b;
    
    return div;
}