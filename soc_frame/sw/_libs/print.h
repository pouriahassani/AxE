
// ---------------------------------------------------------------------
// 
// P R I N T
// 
// ---------------------------------------------------------------------
#ifndef PRINT_H
#define PRINT_H
#include "util.h"
#define OUTPORT ( 0x00000000 )

void NL();

void print_char(char);
void print_str(const char*);
void print_dec(unsigned int);
void print_str_m(const char*);
void print_dec_m(unsigned int);
void print_hex(unsigned int, int);
void print_bin(unsigned int, int);
void print_fix( unsigned int, int, int);
void print_fixed( unsigned int, int, int);
void print_node( int);
void print_prg( int);
void print_str_dec_nl( char*, unsigned int);
void nl();
void print_add( unsigned int, unsigned int, unsigned int);
void print_sub( unsigned int, unsigned int, unsigned int);
void print_mul( unsigned int, unsigned int, unsigned int);
void print_div( unsigned int, unsigned int, unsigned int);
void print_calculation( unsigned int, unsigned int, unsigned int, char);
void print_fixed_add( unsigned int, unsigned int, unsigned int);
void print_fixed_sub( unsigned int, unsigned int, unsigned int);
void print_fixed_mul( unsigned int, unsigned int, unsigned int);
void print_fixed_div( unsigned int, unsigned int, unsigned int);
void print_fixed_calculation( unsigned int, unsigned int, unsigned int, char);

#endif