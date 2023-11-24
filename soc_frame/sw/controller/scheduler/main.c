
// This is free and unencumbered software released into the public domain.

// A simple test program to run on the controller.

#define MAX_HALF ( 0x7FFFFFFF )

#include "debug.h"

#include "mpsoc.h"

#include "typedefs.h"

#include "defines.h"

#include "controller.h"

#include "nodes.h"
#include "prgs.h"
#include "arch.h"

#include "energy_harvester.h"

#include "util.h"

#include "globals.h"

#include "nodes_func.h"
#include "prgs_func.h"
#include "arch_func.h"
#include "queue_func.h"



// period_in_s = 1 / ( MHz * 1.000.000 )
// 60 / period_in_s = clk_cnt_for_1_min

// everytime the cnt reaches clk_cnt_for_1_min * n the next power value is read

// watt is the rate at which energy is created
// W * t = E
// Power output = energy / time

// charge = energy / voltage


/// events at time t
// 
// 1. charging events
// 2. scheduling events
// 
// all events are in a single queue so only a single if has to be checked during
// each iteration.

/// 1. charging events
// 
// go through every node and apply the energy.
// the calculation of the energy is done in some init process.

/// 2. scheduling events
// 
// assign some tasks to a node.



/// measurements of a big and a small node:
// 
// datab.ods, sheet "bit"
// 
// 334; 5,00045; 0,225107; 1,1256362982
// 363; 5,00044; 0,224977; 1,1249839899
// 
// -> big:   1.1256362982 W ~ 1125636 microwatts ~ 1126 milliwatts
// -> small: 1.1249839899 W ~ 1124983 microwatts ~ 1125 milliwatts
// 
// diff
// 1125636 - 1124983 = 653 microwatts

/// clk_cnt
// 
// mul_500_nop_500
// 3,685,821
// 
// mul_500_nop_501
// 3,686,947
// 
// mul_500_nop_502
// 3,687,889

/// period t
// 
// period_in_microseconds = ( 1s / ( 25MHz * 1,000,000 ) ) * 1,000,000
// -> one period takes 0.04 microseconds

/// exec duration
// 
// mul_500_nop_500
// 3,685,821 * 0.04 = 147432.84 microseconds
// 
// mul_500_nop_501
// 3,686,947 * 0.04 = 147477.88 microseconds
// 
// mul_500_nop_502
// 3,687,889 * 0.04 = 147515.56 microseconds
// 
// calc without float:
// 3687889 * 0.04 = x | * 100
// 3687889 * 4 = 100x
// -> 100x / 100 = x
// 
// as milliseconds
// 3687889 * 0.00004 = x | * 100000
// 3687889 * 4 = 100000x
// -> 100000x / 100000 = x

/// energy
// 
// mul_500_nop_502
// 
// 147,432 microseconds * 1,125,636 microwatts = 165,954,766,752 microjouls
// 147 milliseconds * 1,126 milliwatts = 165,522 millijouls

/// clk cnts for 1 millisecond
// 
// one period takes 0.04 microseconds
// -> 0.00004 milliseconds
// -> 25,000 clk cycles in 1 milliseconds

/// multiple cnt reads
// 
// 117,960
// 162,064
// 207,722
// 254,934
// 303,552
// 
// -> considering, that subsecquent cnt reads and writes of the number take so
// long it is not going to be possible to update the batteries of multiple nodes
// between 25,000 clk cylces long reads. writes cannot be avoided for debugging
// purposes.
// 
// -> update the battery every second.

/// clk cnts for 1 s
// 
// one period takes 0.04 microseconds
// -> 0.00000004 s
// -> 25,000,000 clk cycles in 1 s

/// how the battery is charged
// 
// every second some millijouls are added to the battery.




//------------------------------------------------------------------------------
// notes
//------------------------------------------------------------------------------

// prints
// although prints are throught the loop and one might think it is better to
// do them between iterations of the loop. however, printing is not so hard
// and just saving the chars into a buffer might cause even more delay.

//------------------------------------------------------------------------------
// prg should be executed again
//------------------------------------------------------------------------------

// if the battery is charging this means, that save_mode is off

// enough battery
// - run on im arch
// - run on i if all im busy

// drained battery
// - skip if possible
// - run on i arch
// - run on im if all i busy

__attribute__((noinline))
int amul(int rd, int rs1, int rs2)
{
    asm __volatile__ (".word 0xFEC5857F\n");
    asm __volatile__ ("addi %0, x10, 0" : "=r" (rd));
    
    return rd;
}

void my_main()
{
    int i = 0;
    int j = 0;
    
    print_str( "start\n" );
    
    int a = 123;
    int b = 456;
    
    int pro = 0;
    int pro_appr = 0;
    
    pro = a * b;
    pro_appr = amul( pro_appr, a, b );
    
    print_str("exact\n");
    print_dec(pro);
    nl();
    
    print_str("approx\n");
    print_dec(pro_appr);
    nl();
    
    cnt = GET_COUNTER_GLOBAL;
    
    print_str( "t0: " );
    print_dec( cnt );
    nl();
    nl();
    
    // -------------------------------------------------------------------------
    // init
    // -------------------------------------------------------------------------
    
    init_nodes( nodes );
    init_prgs( prgs );
    init_archs( archs );
    
    init_charges( charges );
    
    // -------------------------------------------------------------------------
    // running timing estimations
    // -------------------------------------------------------------------------
    
    print_str( "timing estimations\n" );
    nl();
    
    prgs_estimate_execution_times();
    
    nl();
    print_str( "timing estimations -> done\n" );
    
    SET_LEDS_STATUS = 0x2;
    SET_TRIGGERS = 0x2;
    
    ///-------------------------------------------------------------------------
    /// 1. build event queue
    ///-------------------------------------------------------------------------
    
    queue_build_event_queue();
    
    ///-------------------------------------------------------------------------
    /// 2. estimate energy requirement
    ///-------------------------------------------------------------------------
    
    prgs_estimate_energy_requirements();
    
    SET_LEDS_STATUS = 0x4;
    SET_TRIGGERS = 0x4;
    
    cnt_prev = 0;
    
    // -------------
    // run scheduler
    // -------------
    
    queue_index = 0;
    
    cnt = GET_COUNTER_GLOBAL_RESET;
    
    int node_index = 0;
    
    while ( 1 == 1 )
    {
        // get the next event and wait for it
        
        j = queue[ queue_index ].cnt;
        i = queue[ queue_index ].event;
        
        print_dec( j );
        print_str( ": " );
        print_dec( i );
        nl();
        
        cnt = GET_COUNTER_GLOBAL;
        
        while ( cnt < j )
        {
            cnt = GET_COUNTER_GLOBAL;
        }
        
        queue_index += 1;
        
        print_dec( cnt );
        nl();
        
        ///---------------------------------------------------------------------
        /// 
        /// event
        /// 
        ///---------------------------------------------------------------------
        
        // now is the time to execute the event
        
        if ( QUEUE_CHARGING_EVENT == i )
        {
            print_str( "charging event\n" );
            
            nodes_charge( charges[ charges_i ] );
            
            charges_i += 1;
        }
        else
        {
            print_str( ",p" );
            print_dec( i );
            print_str( "," );
            
            //--------------------------------------------------------------
            // check which prgs are finished
            //--------------------------------------------------------------
            
            prgs_check_if_finished();
            
            //--------------------------------------------------------------
            // check if prg is still running
            //--------------------------------------------------------------
            
            // i holds the prg we want to execute
            
            // we mask the prgs_active variable with 1 at the index of the
            // prg we want to execute. if this is 1 -> prg still running.
            
            int prg_running = prg_is_running( i );
            
            if ( 1 == prg_running )
            {
                print_str( "pr\n" );
                continue;
            }
            
            // the program is idle, it can be executed now.
            
            print_str( "pi" );
            
            //--------------------------------------------------------------
            // skip
            //--------------------------------------------------------------
            
            
            
#ifdef EN_SKIPPING
            if (
                ( 0 == prgs[i].skip_cnt_down ) &&
                ( 1 == save_mode )
            )
            {
                prgs[i].skip_cnt_down = prgs[i].skip_after;
                
                print_str( "sk\n" );
                continue;
            }
#endif
            
            
            
            //----------------------------------------------------------
            // find node
            //----------------------------------------------------------
            
            archs_get_preferred( preferred_archs );
            
            node_index = node_get( preferred_archs, i );
            
            // make sure that any node is available
            
            if ( -1 == node_index )
            {
                print_str( "nn\n" );
                continue;
            }
            
            print_str( ",n" );
            print_dec( node_index );
            nl();
            
            //----------------------------------------------------------
            // node_discharge
            //----------------------------------------------------------
            
            node_discharge( node_index, i );
            
            //----------------------------------------------------------
            // node_assign_prg
            //----------------------------------------------------------
            
            node_assign_prg( node_index, i );
            prg_set_active( i );
            node_set_busy( node_index );
            
            
            
#ifdef EN_SKIPPING
            // update skip cnt
            // watch out that the cnt does not go neg
            
            if ( 0 != prgs[i].skip_cnt_down )
            {
                prgs[i].skip_cnt_down -= 1;
            }
#endif
            
            
            
        }
    }
    
    print_str( "done\n" );
    
    signal_fin();
    
    while ( 1 == 1 ) {}
}
