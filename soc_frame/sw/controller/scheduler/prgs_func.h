
//------------------------------------------------------------------------------
// 
// estimate execution time
// 
//------------------------------------------------------------------------------

void prgs_estimate_execution_times()
{
    int i = 0;
    int j = 0;
    
    int node_to_use = 0;
    
    for ( i = 0; i < NUM_ARCHS; i++ )
    {
        preferred_archs[ 0 ] = i;
        
        node_to_use = node_get( preferred_archs, i );
        
        for ( j = 0; j < NUM_PRGS; j++ )
        {
            prg_estimate_execution_time( node_to_use, j );
        }
    }
    
    
    
#ifdef DBG_ESTIMATE_EXECUTION_TIME
    prgs_execution_time_debug();
#endif
    
    
    
}

void prg_estimate_execution_time( int node_i, int prg_i )
{
    
    
    
#ifdef DBG_ESTIMATE_EXECUTION_TIME
    print_str( "exec time of: " );
    print_str( prgs[ prg_i ].name );
    nl();
#endif
    
    int cnt_start = 0;
    int cnt_end = 0;
    
    int cnt_diff = 0;
    
    // we reset the timer just in case all these inits overflow the timer
    
    cnt = GET_COUNTER_GLOBAL_RESET;
    
    // assign a prg and wait for it to finish
    
    ASSIGN( nodes[node_i], prgs[ prg_i ] );
    
    cnt_start = GET_COUNTER_GLOBAL;
    
    while ( IS_BUSY( nodes[node_i].id_flag ) ) {}
    
    cnt_end = GET_COUNTER_GLOBAL;
    
    // calculate the diff
    
    cnt_diff = cnt_end - cnt_start;
    
    // use the node index to get the node and it's arch.
    // this is used to save the cnt_diff in the correct array index of exec_t.
    
    prgs[ prg_i ].exec_t[ nodes[ node_i].arch ] = cnt_diff;
    
    // exec interval
    
    prgs[ prg_i ].exec_inv[ nodes[ node_i].arch ] = cnt_diff * 2;
}

void prgs_execution_time_debug()
{
    nl();
    print_str( "execution time estimations:\n" );
    
    int i = 0;
    int j = 0;
    
    for ( i = 0; i < NUM_ARCHS; i++ )
    {
        nl();
        
        print_str( "arch " );
        print_dec( i );
        nl();
        
        for ( j = 0; j < NUM_PRGS; j++ )
        {
            print_str( "p" );
            print_dec( j );
            print_str( " - " );
            print_str( prgs[ j ].name );
            print_str( ": " );
            
            print_dec( prgs[ j ].exec_t[ i ] );
            print_str( " - " );
            print_dec( prgs[ j ].exec_inv[ i ] );
            nl();
        }
    }
}

//------------------------------------------------------------------------------
// 
// estimate energy requirements
// 
//------------------------------------------------------------------------------

void prgs_estimate_energy_requirements()
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

void estimate_energy_requirement( int arch_i, int prg_i )
{
    // big:   1126 milliwatts
    // small: 1125 milliwatts
    
    // 3687889 * 4 = 100000x
    // -> 100000x / 100000 = x
    
    // 147 milliseconds * 1,126 milliwatts = 165,522 millijouls
    
    int milli_sec = 0;
    
    print_str( "p" );
    print_dec( prg_i );
    
    // calc time
    // ( exec_t * 4 ) / 100000 = milliseconds
    
    milli_sec = prgs[ prg_i ].exec_t[ arch_i ] * 4;
    milli_sec /= 100000;
    
    print_str( " t: " );
    print_dec( milli_sec );
    
    // calc energy
    // milli_sec * power = millijouls
    
    prgs[ prg_i ].exec_e[ arch_i ] = milli_sec * archs[ arch_i ].power;
    
    print_str( " - e: " );
    print_dec( prgs[ prg_i ].exec_e[ arch_i ] );
    
    nl();
}

//------------------------------------------------------------------------------
// 
// prgs_check_if_finished
// 
//------------------------------------------------------------------------------

void prgs_check_if_finished()
{
    unsigned int nodes_finished = get_finished_nodes( nodes_busy );
    
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
    print_bin( prgs_active, 5 ); nl();
#endif
    
    
    
}

//------------------------------------------------------------------------------
// 
// prg_set_inactive
// 
//------------------------------------------------------------------------------

void prg_set_inactive( int prg_i )
{
    unsigned int prg_mask = 0;
    
    // preparing the mask
    
    prg_mask = 1 << prg_i;
    prg_mask = ~prg_mask;
    
    prgs_active &= prg_mask;
}

//------------------------------------------------------------------------------
// 
// prg_set_active
// 
//------------------------------------------------------------------------------

void prg_set_active( int prg_i )
{
    prgs_active |= ( 1 << prg_i );
    
    
    
#ifdef DBG_PRGS_ACTIVE
    print_str( "prgs_active: " );
    print_bin( prgs_active, 5 );
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
    if ( 0 != ( prgs_active & (1<<prg_i) ) )
    {
        // if the prg is still running we just skip it's execution.
        // as the exec again variable has already been set the next
        // time the execution of the prog is attemted is already
        // set.
        
        return 1;
    }
    else
    {
        return 0;
    }
}
