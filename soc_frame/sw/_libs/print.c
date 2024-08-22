
// ---------------------------------------------------------------------
// 
// P R I N T
// 
// ---------------------------------------------------------------------
#include "print.h"
// #include "util.h"
// #define OUTPORT ( 0x00000000 )

void NL(){}

void print_char(char x){}
void print_str(const char *p){
    while (*p != 0)
    {
        *((volatile int*)OUTPORT) = (int)(*(p++));
    }
    *((volatile int*)OUTPORT) = 0;
}

void print_dec(unsigned int val){
    char buffer[10];
    char *p = buffer;
    
    // val % 10 returns the last digit
    // val / 10 discards the last digit and allows the extraction of the
    // next one
    
    while (val || p == buffer)
    {
        *(p++) = val % 10;
        val = val / 10;
    }
    
    // as the digits have been collected beginning with the least
    // significant one the output is running in reverse order
    
    while (p != buffer)
    {
        *((volatile int*)OUTPORT) = '0' + *(--p);
    }
    *((volatile int*)OUTPORT) = 0;
}
void print_str_m(const char* p){

}
void print_dec_m(unsigned int p){}
void print_hex(unsigned int x, int y){}
void print_bin(unsigned int y, int x){}
void print_fix( unsigned int x, int y, int z){}
void print_fixed( unsigned int z, int y , int x){}
void print_node( intx){}
void print_prg( int x){}
void print_str_dec_nl( char* x, unsigned int y){}
void nl(){}
void print_add( unsigned int y, unsigned int z, unsigned int x){}
void print_sub( unsigned int x, unsigned int y, unsigned int z){}
void print_mul( unsigned int g, unsigned int c, unsigned int z){}
void print_div( unsigned int g, unsigned int d, unsigned int m){}
void print_calculation( unsigned int q, unsigned int f, unsigned int b, char t){}
void print_fixed_add( unsigned int a, unsigned int t, unsigned int g){}
void print_fixed_sub( unsigned int a, unsigned int d,  unsigned int g){}
void print_fixed_mul( unsigned int f, unsigned int h, unsigned int g){}
void print_fixed_div( unsigned int rt, unsigned int r, unsigned int g){}
void print_fixed_calculation( unsigned int rf, unsigned int r, unsigned int e, char q){}

