// DESCRIPTION: Verilator: Verilog example module
//
// This file ONLY is placed into the Public Domain, for any use,
// without warranty, 2017 by Wilson Snyder.
//======================================================================

#include <time.h>
#include <signal.h>


// Include common routines
#include <verilated.h>

// Include model header, generated from Verilating "top.v"
#include "Vtop.h"

# include <verilated_vcd_c.h>

//~ #include <iostream>
//~ #include <string>

//~ using namespace std;

// Current simulation time (64-bit unsigned)
vluint64_t main_time = 0;
// Called by $time in Verilog
double sc_time_stamp() {
    return main_time;  // Note does conversion to real, to match SystemC
}

//~ char* buffer = (char *)malloc(sizeof(char) * 1000);

//~ string buffer = "test";

char buffer[10000];
int buffer_index = 0;

int leds_status = 0;
int triggers = 0;

void ctrl_c_handler(int dummy)
{
    VL_PRINTF( "main time: %d\n", main_time );
    
    //~ buffer[sizeof(buffer)] = '\0';
    //~ VL_PRINTF( "buffer\n" );
    
    int i = 0;
    
    for ( i = 0; i < buffer_index; i++ )
    {
        VL_PRINTF( "%c", buffer[ i ] );
    }
    
    
    //~ VL_PRINTF( "buffer_end\n" ); 
    
    
    
    //~ cout << buffer << endl;
    
    exit(0);
}

int main(int argc, char** argv, char** env) {
    
    signal(SIGINT, ctrl_c_handler);
    
    
    // See a similar example walkthrough in the verilator manpage.
    
    // This is intended to be a minimal example.  Before copying this to start a
    // real project, it is better to start with a more complete example,
    // e.g. examples/c_tracing.

    // Prevent unused variable warnings
    if (0 && argc && argv && env) {}
    // Pass arguments so Verilated code can see them, e.g. $value$plusargs
    Verilated::commandArgs(argc, argv);

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
    
    top->res_n = 0;
    
    
    //~ char* buffer;
    
    
    VL_PRINTF( "\n" );
    VL_PRINTF( "--------------------\n" );
    VL_PRINTF( "starting 4x5_16\n" );
    VL_PRINTF( "--------------------\n" );
    VL_PRINTF( "\n" );
    
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
        
        // ---------------------------------------------------------------------
        // print debug stuff
        // ---------------------------------------------------------------------
        
        // as the execution of the loop is not dependend on the clk state
        // the output is only triggered if clk is 1. if this would not be done
        // the output would be printed twice.
        
        if ( 1 == top->clk )
        {
            // -----------------------------------------------------------------
            // uart
            // -----------------------------------------------------------------
            
            if ( 1 == top->buffer_out_valid )
            {
                // the controller software signals termination by sending some
                // ascii control char
                
                if ( 0x04 == top->buffer_out_data )
                {
                    int i = 0;
                    for ( i = 0; i < buffer_index; i++ )
                    {
                        VL_PRINTF( "%c", buffer[ i ] );
                    }
                    
                    VL_PRINTF( "kill me\n" );
                    break;
                }
                
                // *( buffer++ ) = (char)top->buffer_out_data;
                // buffer += (char)top->buffer_out_data;
                
                //~ buffer[ buffer_index ] = (char)top->buffer_out_data;
                
                // VL_PRINTF( "buffer at index: %c\n", buffer[ buffer_index ] );
                
                //~ buffer_index += 1;
                
                VL_PRINTF( "%c", top->buffer_out_data );
            }

            // -----------------------------------------------------------------
            // leds
            // -----------------------------------------------------------------
            
            if ( leds_status != top->leds_status )
            {
                leds_status = top->leds_status;
                
                VL_PRINTF( "+---+---+---+---+---+---+---+---+\n" );
                
                VL_PRINTF( "|" );
                
                for ( int j = 7; j >= 0; j-- )
                {
                    VL_PRINTF( " %i |", ( (leds_status>>j)&1 ) );
                }
                
                VL_PRINTF( "\n" );
                
                VL_PRINTF( "+---+---+---+---+---+---+---+---+\n" );
            }
            
            // -----------------------------------------------------------------
            // triggers
            // -----------------------------------------------------------------
            
            if ( triggers != top->triggers )
            {
                triggers = top->triggers;
                
                VL_PRINTF( "/---/---/---/---/---/---/---/---/\n" );
                
                VL_PRINTF( "|" );
                
                for ( int j = 7; j >= 0; j-- )
                {
                    VL_PRINTF( " %i |", ( (triggers>>j)&1 ) );
                }
                
                VL_PRINTF( "\n" );
                
                VL_PRINTF( "/---/---/---/---/---/---/---/---/\n" );
            }
        }
        
        // ---------------------------------------------------------------------
        // end of the simulation
        // ---------------------------------------------------------------------
        
        if ( main_time == 10000000000 )
        {
            VL_PRINTF( "\n" );
            VL_PRINTF( "--------------------\n" );
            VL_PRINTF( "done\n" );
            VL_PRINTF( "--------------------\n" );
            VL_PRINTF( "\n" );
            
            VL_PRINTF( "time max reached\n" );
            
            break;
        }
        
        // Evaluate model
        top->eval();
        
        //~ if ( main_time > 4611193 )
        //~ {
            // Dump trace data for this cycle
            if (tfp) tfp->dump (main_time);
        //~ }
    }
    
    // Final model cleanup
    top->final();
    
    if ( main_time > 350000 )
    {
        if (tfp) { tfp->close(); tfp = NULL; }
    }
    
    // Destroy model
    delete top;
    
    // Fin
    exit(0);
}
