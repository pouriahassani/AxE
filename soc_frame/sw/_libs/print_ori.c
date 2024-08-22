
// ---------------------------------------------------------------------
// 
// P R I N T
// 
// ---------------------------------------------------------------------
#include "util.h"
#include "print.h"
// #define OUTPORT ( 0x00000000 )

// #define NL ( *((volatile int*)OUTPORT) = '\n' )

void NL(){
    // char* p = ".NL\n ";
    // while (*p != 0)
    // {
    //     *((volatile int*)OUTPORT) = *(p++);
    // }
    // *((volatile int*)OUTPORT) = '\0';
}

// char
// -------------------------------------

void print_char(char ch);
inline void print_char(char ch)
{
    // *((volatile int*)OUTPORT) = ch;
}

// str
// -------------------------------------

void print_str(const char *p)
{
    while (*p != 0)
    {
        *((volatile int*)OUTPORT) = *(p++);
    }
    *((volatile int*)OUTPORT) = 0;
}

// dec
// -------------------------------------

void print_dec(unsigned int val)
{
    // char buffer[10];
    // char *p = buffer;
    
    // // val % 10 returns the last digit
    // // val / 10 discards the last digit and allows the extraction of the
    // // next one
    
    // while (val || p == buffer)
    // {
    //     *(p++) = val % 10;
    //     val = val / 10;
    // }
    
    // // as the digits have been collected beginning with the least
    // // significant one the output is running in reverse order
    
    // while (p != buffer)
    // {
    //     *((volatile int*)OUTPORT) = '0' + *(--p);
    // }
    //     *((volatile int*)OUTPORT) = '\0';
}

void print_signed(int val)
{
    unsigned int u_val = 0;
    
    if ( 0 > val )
    {
        u_val = ~val;
        u_val += 1;
        
        print_char( '-' );
    }
    else
    {
        u_val = val;
    }
    
    print_dec( u_val );
}

// hex
// -------------------------------------

void print_hex(unsigned int val, int digits)
{
    // for (int i = (4*digits)-4; i >= 0; i -= 4)
    // {
    //     *((volatile int*)OUTPORT) = "0123456789ABCDEF"[(val >> i) % 16];
    // }
}

// binary
// -------------------------------------

void print_bin(unsigned int val, int bits)
{
    for (int i = (bits-1); i >= 0; i-- )
    {
        // *((volatile int*)OUTPORT) = '0' + ((char)( 1 & (val >> i) ));
    }
}

// fixed_point
// -------------------------------------

void print_fix( unsigned int val, int d, int f )
{
    int dec = 0;
    int frc = 0;
    
    dec = (val >> f);
    
    unsigned int mask = 0;
    
    mask = ( 1 << f );
    mask -= 1;
    
    val &= mask;
    
    unsigned int table[8] = {
         390625
        ,781250
        ,1562500
        ,3125000
        ,6250000
        ,12500000
        ,25000000
        ,50000000
    };
    
    for( int j = 0; j < f; j++ )
    {
        if( 1 == ( 1 & (val>>j) ) )
        {
            frc += table[ j ];
        }
    }
    
    print_dec( dec );
    print_char( ',' );
    print_dec( frc );
}

void print_fixed( unsigned int val, int d, int f )
{
    int dec = 0;
    int frc = 0;
    
    dec = (val >> f);
    
    // prepare the 5
    
    int five = 5;
    int div_five_by = 0;
    
    // we prepare a number that starts with 5 and has a number of 0 after it.
    // the number of 0 is based on f and is used to calculate the fraction
    // part like an integer.
    
    // if we have a Xq3 number we multiply 5 with 10 for 3-1 = 2 times.
    // this gives us 500.
    
    // this number is than devided by a multiple of 2 to get the values for
    // each fraction bit.
    
    // recall that the msb bit of the fraction is 0.5. with our multiplication
    // we got 500, a number that we can print like a decimal.
    
    // 500
    // 500 / 2 = 250
    // 500 / 4 = 125
    
    // so instead of seeing the 3rd bit (counting from the msb) as 0.125 we see
    // it as 125.
    
    // assuming the number .101 we can add 500 and 125 together to get 625 and
    // print this number as every other decimal number.
    
    for( int i = 0; i < (f-1); i++ )
    {
        five *= 10;
    }
    
    // we mask out the decimal part of the fixed point number by putting a 1
    // over the radix point. by subtracting 0 we get a mask that has all the
    // fraction bits set to 1
    
    unsigned int mask = 0;
    
    mask = ( 1 << f );
    mask -= 1;
    
    val &= mask;
    
    // we walk through the fraction part of the number and check the bits
    // starting with the lsb. if the bit is set to 1 we calculate by what
    // multiple of 2 we have to devide our 5000.... number by.
    
    // continuing from from our example before for the first loop iteration we
    // divide 500 by 2*(f-1-j) = 2*(3-1-0) = 4 => 500/4 = 125.
    
    for( int j = 0; j < f; j++ )
    {
        if( 1 == ( 1 & (val>>j) ) )
        {
            div_five_by = ( 2 * (f-1-j) );
            
            if ( 0 == div_five_by )
            {
                frc += five;
            }
            else
            {
                frc += five / div_five_by;
            }
        }
    }
    
    print_dec( dec );
    print_char( '.' );
    print_dec( frc );
}



// node
// -------------------------------------

void print_node( int node_i )
{
    print_char( 'n' );
	print_dec( node_i );
	print_str( ": " );
}
 
// prg
// -------------------------------------

void print_prg( int prg_i )
{
    print_char( 'p' );
	print_dec( prg_i );
	print_str( ": " );
}

// string dec newline
// -------------------------------------

void print_str_dec_nl( char* str, unsigned int dec )
{
	print_str( str );
	print_dec( dec );
	 print_str( "\n  \n" );
}



// newline
// -------------------------------------

void nl()
{
    print_str("\n");
}

// add
// -------------------------------------

void print_add( unsigned int a, unsigned int b, unsigned int c )
{
    print_calculation( a, b, c, '+' );
}

// sub
// -------------------------------------

void print_sub( unsigned int a, unsigned int b, unsigned int c )
{
    print_calculation( a, b, c, '-' );
}

// mul
// -------------------------------------

void print_mul( unsigned int a, unsigned int b, unsigned int c )
{
    print_calculation( a, b, c, '*' );
}

// div
// -------------------------------------

void print_div( unsigned int a, unsigned int b, unsigned int c )
{
    print_calculation( a, b, c, '/' );
}

// general calculation
// -------------------------------------

void print_calculation( unsigned int a, unsigned int b, unsigned int c, char op )
{
    print_dec( a );
    print_char( ' ' );
    print_char( op );
    print_char( ' ' );
    print_dec( b );
    print_str( " = " );
    print_dec( c ); NL;
}

// fixed_add
// -------------------------------------

void print_fixed_add( unsigned int a, unsigned int b, unsigned int c )
{
    print_fixed_calculation( a, b, c, '+' );
}

// fixed_sub
// -------------------------------------

void print_fixed_sub( unsigned int a, unsigned int b, unsigned int c )
{
    print_fixed_calculation( a, b, c, '-' );
}

// fixed_mul
// -------------------------------------

void print_fixed_mul( unsigned int a, unsigned int b, unsigned int c )
{
    print_fixed_calculation( a, b, c, '*' );
}

// fixed_div
// -------------------------------------

void print_fixed_div( unsigned int a, unsigned int b, unsigned int c )
{
    print_fixed_calculation( a, b, c, '/' );
}

// general fixed calculation
// -------------------------------------

void print_fixed_calculation( unsigned int a, unsigned int b, unsigned int c, char op )
{
    print_fix( a, 8, 8 );
    print_char( ' ' );
    print_char( op );
    print_char( ' ' );
    print_fix( b, 8, 8 );
    print_str( " = " );
    print_fix( c, 8, 8 );  print_str( ";\n" );
}
