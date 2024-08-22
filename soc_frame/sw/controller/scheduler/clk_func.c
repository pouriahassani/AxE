#include "clk_func.h"
unsigned int clk_cnt_to_ms( int clk_cnt )
{
    int milli_sec = 0;
    
    // calc ms
    // ( clk_cnt * 4 ) / 100000 = ms
    
    milli_sec = clk_cnt * 4;
    milli_sec /= 100000;
    
#ifdef DBG_ESTIMATE_EXECUTION_TIME
    print_str( "\nresult: " );
    print_dec( milli_sec );
    nl();
#endif
    
    return milli_sec;
}

unsigned int ms_to_clk_cnt( unsigned int ms )
{
    // calc clk_cnt
    // clk_cnt = ms * 100000 / 4
    // clk_cnt = ms * 25000
    
    // 25000 is considered as a 16q0 fixed point number.
    // ms as a 8q8 fixed point number.
    
    // the result of the multiplication is a 24q8 fixed point number
    // that is shifted to the right by 8 to get a regular integer.
    
    //~ b = ;
    
    //~ print_str( "b als dec" ); NL;
    //~ print_dec( b ); NL;
    
    //~ print_str( "b als fixed 16q0" ); NL;
    //~ print_fixed( b, 16, 0 ); NL;
    //~ print_fix( b, 16, 0 ); NL;
    
    //~ print_str( "einfach mal ein mul" ); NL;
    
    unsigned int clk_cnt = 0;
    
    clk_cnt = ms * 25000;
    clk_cnt >>= 8;
    
    //~ print_str( "result mal als bits" ); NL;
    //~ print_bin( c, 32 ); NL;
    //~ print_dec( c ); NL;
    //~ print_fix( c, 24, 8 ); NL;
    
    return clk_cnt;
}
