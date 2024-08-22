
//------------------------------------------------------------------------------
// 
// estimate execution time
// 
//------------------------------------------------------------------------------

// for every arch, every prg is executed. the selected node has to have the arch
// for which the execution time is estimated.
#include "prgs_func.h"

void prgs_estimate_execution_times() // CHECKED
{
    int i = 0;
    int j = 0;
    
    int node_to_use = 0;
    
    for ( i = 0; i < NUM_ARCHS; i++ )
    {
        if ( i == 1 )
        {
            #ifdef DBG_ESTIMATE_EXECUTION_TIME
                
                print_str( "\nskipping execution time estimation for\n" );
                print_str( "arch: " );
                print_dec( i );
                
            #endif
            break;
        }
        
        // a node is selected that fits the arch
        
        #ifdef DBG_ESTIMATE_EXECUTION_TIME
            print_str( "\narch: " );
            print_dec( i );
            print_str( ";\n");
        #endif
        
        //~ preferred_archs[ 0 ] = i;
        //~ node_to_use = node_get( preferred_archs, i );
        //node_to_use = get_node_for_arch( i );
		node_to_use = 1;
        
        for ( j = 0; j < NUM_PRGS; j++ )
        {
            #ifdef DBG_ESTIMATE_EXECUTION_TIME
                print_prg( j );
			#endif
            
            prg_estimate_execution_time( node_to_use, j );
        }
    }
    
    
    
#ifdef DBG_ESTIMATE_EXECUTION_TIME
    prgs_execution_time_debug();
#endif
    
    
    
}

void prg_estimate_execution_time( int node_i, int prg_i ) // CHECKED
{
    
#ifdef DBG_ESTIMATE_EXECUTION_TIME
    print_str( "\nexec time of: " );
    print_str( prgs[ prg_i ].name );
   
#endif
    
    int cnt_start = 0;
    int cnt_end = 0;
    
    int cnt_diff = 0;
    
    // we reset the timer just in case all these inits overflow the timer
    
    cnt = GET_COUNTER_GLOBAL_RESET;
    
    // assign a prg and wait for it to finish
    print_str("\nnode id: ");print_dec(prgs[prg_i].addr[nodes[node_i].arch]);
    ASSIGN( nodes[node_i], prgs[ prg_i ] );
    print_str( "\nexec time of: " );
    cnt_start = GET_COUNTER_GLOBAL;
    
    while ( IS_BUSY( nodes[node_i].id_flag ) ) {}
    
    cnt_end = GET_COUNTER_GLOBAL;
    
    // calculate the diff
    
    cnt_diff = cnt_end - cnt_start;
    
    //~ if ( prg_i == 0 )
    //~ {
        //~ cnt_diff = 3686042;
    //~ }
    //~ else if ( prg_i == 1 )
    //~ {
        //~ cnt_diff = 3687094;
    //~ }
    //~ else
    //~ {
        //~ cnt_diff = 3687094;
    //~ }
    
    print_str( "\nset cnt_diff to: " ); print_dec( cnt_diff );
    
    // use the node index to get the node and it's arch.
    // this is used to save the cnt_diff in the correct array index of c.
    
    prgs[ prg_i ].c_clk_cnt[ nodes[node_i].arch ] = cnt_diff;
    
    prgs[ prg_i ].c[ nodes[node_i].arch ] = prgs_get_execution_time_in_ms( cnt_diff );
    
    // set c to 8q8 format
    
    prgs[ prg_i ].c[ nodes[node_i].arch ] <<= 8;
}
void prgs_execution_time_debug() // CHECKED
{
    
    print_str( "\nexecution time estimations:\n" );
    
    int i = 0;
    int j = 0;
    
    for ( i = 0; i < NUM_ARCHS; i++ )
    {
       
        
        print_str( "\narch " );
        print_dec( i );
        print_str( ";\n" );
        
        for ( j = 0; j < NUM_PRGS; j++ )
        {
            print_str( ";\n" );
            print_prg( j );
            print_str( prgs[ j ].name );

            print_str( ": " );
            print_dec( prgs[ j ].c[ i ] );
            
        }
    }
}

// generally speaking ms are considered fixed point numbers

int prgs_get_execution_time_in_ms( int clk_cnt ) // DEPRECATED
{
    return clk_cnt_to_ms( clk_cnt );
}

//------------------------------------------------------------------------------
// 
// prgs_set_relative_deadline
// 
//------------------------------------------------------------------------------

void prgs_set_relative_deadline() // CHECKED
{
    int i = 0;
    int j = 0;
    
    for ( i = 0; i < NUM_ARCHS; i++ )
    {
        for ( j = 0; j < NUM_PRGS; j++ )
        {
            prgs[ j ].d[ i ] = fixed_mul_8q8( prgs[ j ].c[ i ], prgs[ j ].d_multiplyer );
        }
    }
    
    #ifdef DBG_GET_RELATIVE_DEADLINE
        prgs_get_relative_deadline_debug();
    #endif
}
#ifdef DBG_GET_RELATIVE_DEADLINE
    void prgs_get_relative_deadline_debug()
    {
        
        print_str( "\nget relative deadlines:\n" );
        
        int i = 0;
        int j = 0;
        
        for ( i = 0; i < NUM_ARCHS; i++ )
        {
            
            
            print_str( "\narch " );
            print_dec( i );
            
            for ( j = 0; j < NUM_PRGS; j++ )
            {
                print_str( "\np" );
                print_dec( j );
                print_str( " - " );
                print_str( prgs[ j ].name );
                print_str( ": " );
                
                
                print_str( "\nc " );
                print_fix( prgs[ j ].c[ i ], 8, 8 );
                print_str( " mod " );
                print_fix( prgs[ j ].d_multiplyer, 8, 8 );
                print_str( " d " );
                print_fix( prgs[ j ].d[ i ], 8, 8 );
                
            }
        }
    }
#endif

//------------------------------------------------------------------------------
// 
// prgs_set_period
// 
//------------------------------------------------------------------------------

void prgs_set_period() // CHECKED
{
    int i = 0;
    int j = 0;
    
    for ( i = 0; i < NUM_ARCHS; i++ )
    {
        for ( j = 0; j < NUM_PRGS; j++ )
        {
            // the period or execution interval is the same as the
            // deadline.
            
            prgs[ j ].t[ i ] = prgs[ j ].d[ i ];
        }
    }
}
void prgs_set_period_clk_cnt()
{
    int i = 0;
    int j = 0;
    
    for ( i = 0; i < NUM_ARCHS; i++ )
    {
        for ( j = 0; j < NUM_PRGS; j++ )
        {
            prgs[ j ].t_clk_cnt[ i ] = ms_to_clk_cnt( prgs[ j ].t[ i ] );
            // print_str("t_clk_cnt arch: ");print_dec(i);print_str("prg: ");print_dec(j);print_str("t_clk_cnt: ");print_dec(prgs[ j ].t_clk_cnt[ i ]);NL;
        }
    }
}















//------------------------------------------------------------------------------
// 
// estimate energy requirements
// 
//------------------------------------------------------------------------------

void prgs_estimate_energy_requirements() // CHECKED
{
    int i = 0;
    int j = 0;
    
    for ( i = 0; i < NUM_ARCHS; i++ )
    {
        print_str( "n" );
        print_dec( i );
        nl();
        
        for ( j = 0; j < NUM_PRGS; j++ )
        {
            estimate_energy_requirement( i, j );
        }
    }
}
void estimate_energy_requirement( int arch_i, int prg_i ) // CHECKED
{
    // big:   1126 milliwatts
    // small: 1125 milliwatts
    
    // 147 milliseconds * 1,126 milliwatts = 165,522 millijouls
    
    // calc energy
    // milli_sec * power = millijouls
    
    //~ prgs[ prg_i ].e[ arch_i ] = prgs[ prg_i ].c[ arch_i ] * archs[ arch_i ].power;
    prgs[ prg_i ].e[ arch_i ] = fixed_mul_8q8( prgs[ prg_i ].c[ arch_i ], archs[ arch_i ].power );
    
    print_str( " - e: " );
    print_dec( prgs[ prg_i ].e[ arch_i ] );
    
    nl();
}






void prgs_set_initial_deadlines()
{
    // as the prgs have already been assigned to a node at the time the
    // next deadlines are set, we do not have to consider different
    // architectures at this point. as the architecture of a node is
    // fixed an a task cannot be reassigned, there is only the node's
    // architecture to consider.
    
    // we use the period here as the deadline is the same as the period
    // and we only calculate the clk cnt for the latter.
    
    int j = 0;
    
    for ( j = 0; j < NUM_PRGS; j++ )
    {
        // as we recorded the t_clk_cnt for all architectures we have
        // to find out the architecture of the node the prg has been
        // assigned to with:
        // nodes[ prgs[j].assigned_to ].arch
        
        prgs[ j ].next_release_clk_cnt = prgs[ j ].t_clk_cnt[ nodes[ prgs[j].assigned_to ].arch ];
        prgs[ j ].next_deadline_clk_cnt = prgs[ j ].t_clk_cnt[ nodes[ prgs[j].assigned_to ].arch ] * 2;
    }
}

#ifdef REP_INITIAL_DEADLINES
    
    void rep_prgs_set_initial_deadlines()
    {
        int j = 0;
        
        
        print_str( "\ninitial r and d\n" );
        
        for ( j = 0; j < NUM_PRGS; j++ )
        {
            // as we recorded the t_clk_cnt for all architectures we have
            // to find out the architecture of the node the prg has been
            // assigned to with:
            // nodes[ prgs[j].assigned_to ].arch
            
            
            print_str( "\np" );print_dec( j );
            print_str( "\nr: " );print_dec( prgs[ j ].next_release_clk_cnt );
            print_str( "\nd: " );print_dec( prgs[ j ].next_deadline_clk_cnt );
        }
    }
    
    
#endif

void prg_set_next_deadline( int prg_i )
{
    // here we set the next absolute deadline for a task.
    // the current deadline is used to define the next release time. as
    // the periods and the deadlines are always the same the deadlines
    // are always the next release times.
    
    unsigned int tmp = prgs[ prg_i ].next_deadline_clk_cnt;
    
    prgs[ prg_i ].next_release_clk_cnt = prgs[ prg_i ].next_deadline_clk_cnt;
    prgs[ prg_i ].next_release_overflows = prgs[ prg_i ].next_deadline_overflows;
    
    prgs[ prg_i ].next_deadline_clk_cnt += prgs[ prg_i ].t_clk_cnt[ nodes[ prgs[prg_i].assigned_to ].arch ];
    
    // check for overflows
    
    if ( tmp > prgs[ prg_i ].next_deadline_clk_cnt )
    {
        prgs[ prg_i ].next_deadline_overflows += 1;
        
        #ifdef DBG_SET_NEXT_DEADLINE
            
            print_str( "\nset_next_deadline overflow detected" ); 
            print_str( "\ntmp: " ); print_dec( tmp ); 
            print_str( "\nnext: " ); print_dec( prgs[ prg_i ].next_deadline_clk_cnt );
            print_str( "\nnew overflow: " ); print_dec( prgs[ prg_i ].next_deadline_overflows );
            
        #endif
    }
}

















//------------------------------------------------------------------------------
// 
// prgs_check_if_finished
// 
//------------------------------------------------------------------------------



void prgs_check_if_finished()
{
    unsigned int nodes_finished = get_finished_nodes_mask( nodes_busy );
    
    int nodes_finished_index = 0;
    
    int prg_finished;
    
    // we look at all the nodes that have finished executing to
    // see what prg they ran. we do this by shifting the variable
    // nodes_finished to the right and check which bits are 1.
    // this could be improved by a better search algorithm instead
    // of shifting the whole variable.
    
    // if there are only 0s left in the varaible we end the search.
    
    while ( 0 != nodes_finished )
    {
        // we mask out all the bits except the lsb and check if this
        // equlas 1.
        // if it is 1, then the node has finished as well as the
        // prg it ran.
        
        if ( 1 == ( 1 & nodes_finished ) )
        {
            // the nodes_finished_index now holds the index of the
            // node that finished. this varaible is incremented at
            // the end of the while loop.
            
            prg_finished = nodes[ nodes_finished_index ].prg;
            
            // we now know the index of the prg that finished and
            // use this to mask out the corresponding bit in the
            // prgs_active variable.
            
            prg_set_inactive( prg_finished );
            
            // in the node struct we do not change the variable
            // used to record which prg the node runs as this
            // variable is going to be set again anyway.
            // furthermore there is valid prg with the index 0.
            
            // don't do this!
            // nodes[ nodes_finished_index ].prg = 0;
        }
        
        // TODO
        // could be improved to save a variable
        
        nodes_finished >>= 1;
        nodes_finished_index += 1;
    }
    
	#ifdef DBG_PRGS_ACTIVE
		print_bin( task_set.prgs_active, 5 ); NL;
	#endif
}

//------------------------------------------------------------------------------
// 
// prg_set_inactive
// 
//------------------------------------------------------------------------------

// TODO - only works for 32 or less prgs. maybe not needed anymore.

void prg_set_inactive( int prg_i )
{
    unsigned int prg_mask = 0;
    
    // preparing the mask
    
    prg_mask = 1 << prg_i;
    prg_mask = ~prg_mask;
    
    task_set.prgs_active &= prg_mask;
}

//------------------------------------------------------------------------------
// 
// prg_set_active
// 
//------------------------------------------------------------------------------

void prg_set_active( int prg_i )
{
    task_set.prgs_active |= ( 1 << prg_i );
    
    
    
#ifdef DBG_PRGS_ACTIVE
    print_str( "prgs_active: " );
    print_bin( task_set.prgs_active, 5 );
    nl();
#endif
    
    
    
}

//------------------------------------------------------------------------------
// 
// prg_is_running
// 
//------------------------------------------------------------------------------

int prg_is_running( int prg_i )
{
    if ( 0 != ( task_set.prgs_active & (1<<prg_i) ) )
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

//------------------------------------------------------------------------------
// 
// prgs_summary
// 
//------------------------------------------------------------------------------

#ifdef REP_PRGS_SUMMERY
    
    void prgs_summary() // CHECKED
    {
        int i = 0;
        int j = 0;
        
        // here we first loop through the prgs and not the archs
        
        for ( j = 0; j < NUM_PRGS; j++ )
        {
            
            print_str( "\nprg " );
            print_dec( j );
            print_str( ": " );
            print_str( prgs[ j ].name );
            
            print_str( "\n===" );
            
            for ( i = 0; i < NUM_ARCHS; i++ )
            {
                print_str( "arch" );
                print_dec( i );
                
                print_str( "\nc: " ) ; print_fix( prgs[ j ].c[ i ], 8, 8 ) ; print_str( "ms\n" );
                print_str( "d: " ) ; print_fix( prgs[ j ].d[ i ], 8, 8 ) ; print_str( "ms\n" );
                print_str( "t: " ) ; print_fix( prgs[ j ].t[ i ], 8, 8 ) ; print_str( "ms\n" );
                print_str( "e: " ) ; print_fix( prgs[ j ].e[ i ], 8, 8 ) ; print_str( "mj\n" );
                print_str( "c_clk_cnt: " ); print_dec( prgs[ j ].c_clk_cnt[ i ] );
                print_str( "\nt_clk_cnt: " ); print_dec( prgs[ j ].t_clk_cnt[ i ] ); 
            }
        }
    }
    
#endif

void prgs_set_ready( int node_i ) // new
{
    #ifdef DBG_SET_READY
        print_str( "setting prgs ready for n" ); print_dec( node_i ); NL;
    #endif
    
    int i;
    int prg_i = 0;
    
    unsigned int end = ( LAST_NODE(node_i) ) ? NUM_PRGS : nodes[ node_i+1 ].prgs_start_i;
    
    //~ #ifdef DBG_SET_READY
        //~ print_str( "prgs list range:" ); NL;
        //~ print_dec( nodes[ node_i ].prgs_start_i ); print_str( " - " ); print_dec( end ); NL;
    //~ #endif
    
    // iterating all the prgs assigned to the node
    // -----------------------------------------------------------------
    
    for ( i = nodes[ node_i ].prgs_start_i; i < end; i++ )
    {
        prg_i = prgs_list[ i ];
        
        // figure out how many times the task can be executed during
        // the period defined by d.
        
        #ifdef DBG_SET_READY
            print_str( "p" ); print_dec( prg_i );
        #endif
        
        if ( TRUE == time_reached( prgs[ prg_i ].next_release_clk_cnt, prgs[ prg_i ].next_release_overflows ) )
        {
            #ifdef DBG_SET_READY
                print_str( "-> ready" );
            #endif
            
            ready_list[ i ] = 1;
        }
        else
        {
            #ifdef DBG_SET_READY
                
                print_str( " " );print_dec( prgs[ prg_i ].next_release_clk_cnt );
                
            #endif
            
            ready_list[ i ] = 0;
        }
        
        #ifdef DBG_SET_READY
            NL;
        #endif
    }
    
    #ifdef DBG_SET_READY
        print_str("-> done\n");
    #endif
}
