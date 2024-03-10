// DESCRIPTION: Verilator: Verilog example module
//
// This file ONLY is placed into the Public Domain, for any use,
// without warranty, 2017 by Wilson Snyder.
//======================================================================

#include <time.h>

#include <stdio.h>

// Include common routines
#include <verilated.h>

// Include model header, generated from Verilating "top.v"
#include "Vtop.h"

# include <verilated_vcd_c.h>

// Current simulation time (64-bit unsigned)
vluint64_t main_time = 0;
// Called by $time in Verilog
double sc_time_stamp() {
    return main_time;  // Note does conversion to real, to match SystemC
}

#define DEBUG_LEGTH ( 100 )
#define NODES_NUM ( 1 )

struct ascii_debug_t
{
    uint8_t sig;
    char c;
    
    uint8_t id;
    uint8_t cnt;
    
    char str[ DEBUG_LEGTH ];
};

uint8_t debug;

int main(int argc, char** argv, char** env) {
    // See a similar example walkthrough in the verilator manpage.
    
    // This is intended to be a minimal example.  Before copying this to start a
    // real project, it is better to start with a more complete example,
    // e.g. examples/c_tracing.

    // Prevent unused variable warnings
    if (0 && argc && argv && env) {}
    // Pass arguments so Verilated code can see them, e.g. $value$plusargs
    Verilated::commandArgs(argc, argv);
    
    //~ debug = argv[1];
    
    if ( *argv[1] == '1' )
    {
        debug = 1;
    }
    else
    {
        debug = 0;
    }
    
    if ( debug == 1 )
    {
        VL_PRINTF( "%u\n", argc );
        VL_PRINTF( "%s\n", argv[1] );
        //~ return 0;
        
    }
    //~ return 0;
    
    // Construct the Verilated model, from Vtop.h generated from Verilating "top.v"
    Vtop* top = new Vtop;
    
    // If verilator was invoked with --trace argument,
    // and if at run time passed the +trace argument, turn on tracing
    VerilatedVcdC* tfp = NULL;
    const char* flag = Verilated::commandArgsPlusMatch("trace");
    if (flag && 0==strcmp(flag, "+trace")) {
        Verilated::traceEverOn(true);  // Verilator must compute traced signals
        VL_PRINTF("Enabling waves into logs/vlt_dump.vcd...\n");
        tfp = new VerilatedVcdC;
        top->trace(tfp, 99);  // Trace 99 levels of hierarchy
        Verilated::mkdir("logs");
        tfp->open("logs/vlt_dump.vcd");  // Open the dump file
    }
    
    ascii_debug_t ascii_debug[ NODES_NUM-1 ];
    
    uint8_t i = 0;
    
    for ( i = 0; i < NODES_NUM; i++ )
    {
        ascii_debug[ i ].sig = 0;
        ascii_debug[ i ].c = '\0';
        ascii_debug[ i ].id = i;
        ascii_debug[ i ].cnt = 0;
        ascii_debug[ i ].str[0] = '\0';
    }
    
    ascii_debug[ NODES_NUM-1 ].id = 255;
    
    uint8_t done = 0;
    
    uint32_t data_read = 0;
    
    double t = 0;
    
    top->res_n = 0;
    
    char debug_char     = '0';
    char debug_char_old = '0';
    
    if ( debug == 1 )
    {
        VL_PRINTF( "\n" );
        VL_PRINTF( "--------------------\n" );
        VL_PRINTF( "starting\n" );
        VL_PRINTF( "--------------------\n" );
        VL_PRINTF( "\n" );
    }
    
    //~ FILE *fp;
    
    //~ fp = fopen(argv[1], "w+");
    
    while ( ! Verilated::gotFinish() )
    {
        // inc time
        
        main_time++;
        
        // clock
        
        top->clk = !top->clk;
        
        // dereset reset
        
        if ( main_time > 10 )
        {
            top->res_n = 1;
        }
        
        // written index
        
        if ( 1 == top->clk )
        {
            if ( 1 == top->w )
            {
                if ( debug == 0 )
                {
                    //~ fprintf(fp, "%lu\n", top->w_index);
                    VL_PRINTF( "%u\n", top->w_index );
                }
                
                //~ VL_PRINTF( "%x\n", top->w_index );
            }
        }
        
        // print stuff
        
        if ( debug == 1 )
        {
            if ( 1 == top->clk )
            {
                // assign debug signals
                
                ascii_debug[0].sig = top->debugger_sig;
                ascii_debug[0].c = (char)top->debugger_ascii;
                
                for ( i = 0; i < NODES_NUM; i++ )
                {
                    if ( 1 == ascii_debug[ i ].sig )
                    {
                        ascii_debug[ i ].str[ ascii_debug[ i ].cnt ] = ascii_debug[ i ].c;
                        
                        ascii_debug[ i ].cnt += 1;
                        
                        if ( ascii_debug[ i ].c == '\n' )
                        {
                            t = (double)clock() / CLOCKS_PER_SEC;
                            
                            ascii_debug[ i ].str[ ascii_debug[ i ].cnt ] = '\0';
                            ascii_debug[ i ].cnt = 0;
                            
                            VL_PRINTF( "%lf ", t );
                            
                            if ( ascii_debug[ i ].id == 255 )
                            {
                                VL_PRINTF( "C " );
                            }
                            else
                            {
                                VL_PRINTF( "-> Pico %d", ascii_debug[ i ].id );
                            }
                            
                            VL_PRINTF( ": %s", ascii_debug[ i ].str );
                        }
                    }
                }
            }
        }
        
        // fin
        if ( top->fin == 1 )
        {
            if ( debug == 1 )
            {
                VL_PRINTF( "FIN\n" );
                VL_PRINTF( "FIN\n" );
                VL_PRINTF( "FIN\n" );
                VL_PRINTF( "FIN\n" );
                VL_PRINTF( "FIN\n" );
                VL_PRINTF( "FIN\n" );
            }
            break;
        }
        
        // trap
        
        if ( top->trap == 1 )
        {
            VL_PRINTF( "TRAP\n" );
            return 0;
        }
        
        // shit
        
        //~ if ( main_time == 3000000 )
        //~ if ( main_time == 50000000 ) // blowfish
        //~ if ( main_time == 10000000 ) // blowfish
        if ( main_time == 100000000000 ) // norx full data width
        {
            if ( debug == 1 )
            {
                VL_PRINTF( "\n" );
                VL_PRINTF( "\n" );
                VL_PRINTF( "--------------------\n" );
                VL_PRINTF( "time max reached\n" );
                VL_PRINTF( "--------------------\n" );
                VL_PRINTF( "\n" );
                
                VL_PRINTF( "ill_awaddr: %x\n", top->ill_awaddr_out_of_range );
                VL_PRINTF( "ill_araddr: %x\n", top->ill_araddr_out_of_range );
            }
            
            break;
        }
        
        // Evaluate model
        top->eval();
        
        // Dump trace data for this cycle
        if (tfp) tfp->dump (main_time);
    }
    
    //~ fclose(fp);
    
    // Final model cleanup
    top->final();
    
    if (tfp) { tfp->close(); tfp = NULL; }
    
    // Destroy model
    delete top;
    
    // Fin
    exit(0);
}
