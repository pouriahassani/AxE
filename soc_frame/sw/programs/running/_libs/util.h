
#define MAX ( 0xFFFFFFFF )
#define MAX_HALF ( 0x7FFFFFFF )

#define OUTPORT 0x00000000

#define FINISHED ( 0x00FFFFFC )

#define ASSERT(expr) \
    if (expr) \
        {} \
    else \
        { emb_assert(__LINE__,__FILE__,#expr); }

//~ { print_dec(__LINE__);print_str(#expr);nl(); }
//~ { print_dec(__LINE__);print_str(#expr); }

// is now done in the asm file.

void signal_fin();
inline void signal_fin()
{
    *((volatile int*)FINISHED) = FINISHED;
}

void signal_kill_sim()
{
    print_char( 0x04 );
}

// -----------------------------------------------------------------------------
// 
// P R I N T
// 
// -----------------------------------------------------------------------------

// TODO - add some define to supress debug output. do it here so you don't
// have to worry about it when adding new output.

// char
// -------------------------------------

void print_char(char ch);
inline void print_char(char ch)
{
    *((volatile int*)OUTPORT) = ch;
}

// str
// -------------------------------------

void print_str(const char *p)
{
    while (*p != 0)
    {
        *((volatile int*)OUTPORT) = *(p++);
    }
}

// dec
// -------------------------------------

void print_dec(unsigned int val)
{
    char buffer[10];
    char *p = buffer;
    
    // val % 10 returns the last digit
    // val / 10 discards the last digit and allows the extraction of the next
    // one
    
    while (val || p == buffer)
    {
        *(p++) = val % 10;
        val = val / 10;
    }
    
    // as the digits have been collected beginning with the least significant
    // one the output is running in reverse order
    
    while (p != buffer)
    {
        *((volatile int*)OUTPORT) = '0' + *(--p);
    }
}

// hex
// -------------------------------------

void print_hex(unsigned int val, int digits)
{
    for (int i = (4*digits)-4; i >= 0; i -= 4)
    {
        *((volatile int*)OUTPORT) = "0123456789ABCDEF"[(val >> i) % 16];
    }
}

// binary
// -------------------------------------

void print_bin(unsigned int val, int bits)
{
    for (int i = (bits-1); i >= 0; i-- )
    {
        *((volatile int*)OUTPORT) = '0' + ((char)( 1 & (val >> i) ));
    }
}

// newline
// -------------------------------------

void nl()
{
    print_str("\n");
}

// print_assert
// -------------------------------------
void emb_assert( unsigned int line, const char *file, const char *exp )
{
    print_dec( line );
    print_str( file );
    print_str( exp );
    
    //~ nl();
    
    asm volatile( "ebreak" );
}
