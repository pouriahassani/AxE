
//------------------------------------------------------------------------------
// 
// node_get
// 
//------------------------------------------------------------------------------

// masks[ 0 ] -> preferred
// masks[ 1 ] -> if preferred not available

// ich bekomme einen array von archs indicis wo der erste die preferred arch
// ist. den geh ich dann durch.

int node_get( int *preferred_archs, int prg_i )
{
    
    
    
#ifdef DBG_GET_NODE
    print_str( "get node\n" );
#endif
    
    
    
    int state_nodes = GET_BUSY;
    
    // find out which are ready and which actually exist
    // all possible nodes not connected appear as ready
    // the busy nodes are inverted so only the ones that are
    // idle are 1.
    // the nodes mask holds all the nodes that are available in
    // the system. a system with 2 nodes has a node mask of 11.
    // as we inverted the active nodes before, all node indices
    // of nodes not even active in the system are set to 1.
    
    state_nodes = ~state_nodes;
    state_nodes &= NODES_MASK;
    
    // state_nodes &= NODES_MASK_RV32IM;
    // state_nodes &= NODES_MASK_RV32I ;
    
    int nodes_state_curr = 0;
    int nodes_i_curr = 0;
    
    int arch_i = 0;
    int preferred_arch_i = 0;
    
    for ( preferred_arch_i = 0; preferred_arch_i < NUM_ARCHS; preferred_arch_i++ )
    {
        // ich hole mir den arch index mit masks[ arch_i ] aus dem array von den
        // preferred archs. damit schau ich dann bei archs nach wie die
        // node_mask aussieht.
        
        arch_i = preferred_archs[ preferred_arch_i ];
        
        
        
#ifdef DBG_GET_NODE
        //~ print_str( "arch: " );
        //~ print_dec( arch_i );
        
        //~ print_str( " - mask: " );
        //~ print_bin( archs[ arch_i ].node_mask, 8 );
        //~ nl();
#endif
        
        
        
        nodes_state_curr = state_nodes & archs[ arch_i ].node_mask;
        nodes_i_curr = 0;
        
        // while nodes_state_curr is not 0 there are some idle nodes that can
        // be used
        
        while ( 0 != nodes_state_curr )
        {
            // if we find a that is idle
            
            if ( 1 == ( 1 & nodes_state_curr ) )
            {
                // check the charge of the node's battery
                
                // energy required by the prg
                // prgs[ i ].exec_e[ARCH_RV32I]
                // prgs[ i ].exec_e[ARCH_RV32IM]
                // 
                // charge of the node's battery
                // node[ i ].charge
                
                if ( nodes[ nodes_i_curr ].charge > prgs[ prg_i ].exec_e[ arch_i ] )
                {
                    
                    
                    
#ifdef DBG_GET_NODE
                    print_str( "found node_i: " );
                    print_dec( nodes_i_curr );
                    nl();
#endif
                    
                    
                    
                    return nodes_i_curr;
                }
                else
                {
                    
                    
                    
#ifdef DBG_GET_NODE
                    print_str( "not enough charge node_i: " );
                    print_dec( nodes_i_curr );
                    nl();
#endif
                    
                    
                    
                }
            }
            
            nodes_i_curr += 1;
            nodes_state_curr >>= 1;
            
            // if there are no idle nodes left, the while loop will end
        }
    }
    
    // if we reach this return, there are no nodes that can be used.
    
    return -1;
}

//------------------------------------------------------------------------------
// 
// nodes_charge
// 
//------------------------------------------------------------------------------

void nodes_charge( unsigned int charge )
{
    
    
    
#ifdef DBG_CHARGING
    print_str( "charging\n" );
    print_dec( charge );
    nl();
#endif
    
    
    
    int i = 0;
    
    for ( i = 0; i < NUM_NODES; i++ )
    {
        
        
        
#ifdef DBG_CHARGING
        print_dec( i );
        print_str( ": " );
        print_dec( nodes[ i ].charge );
        print_str( " -> \n" );
#endif
        
        
        
        nodes[ i ].charge += charge;
        
        
        
#ifdef DBG_CHARGING
        print_dec( nodes[ i ].charge );
        nl();
#endif
        
        
        
    }
    
    
    
#ifdef REP_CHARGING
    nodes_report_charges( "charging", charge );
#endif
    
    
    
}

//------------------------------------------------------------------------------
// 
// node_discharge
// 
//------------------------------------------------------------------------------

void node_discharge( int node_i, int prg_i )
{
    int to_discharge = prgs[ prg_i ].exec_e[ nodes[ node_i ].arch ];
    
    
    
#ifdef DBG_DISCHARGING
    print_str( "discharging\n" );
    print_dec( to_discharge );
    nl();
    
    print_dec( node_i );
    print_str( ": " );
    print_dec( nodes[ node_i ].charge );
    print_str( " -> \n" );
#endif
    
    
    
    nodes[ node_i ].charge -= to_discharge;
    
    
    
#ifdef DBG_DISCHARGING
    print_dec( nodes[ node_i ].charge );
    nl();
#endif
    
    
    
#ifdef REP_DISCHARGING
    nodes_report_charges( "discharging", to_discharge );
#endif
    
}

//------------------------------------------------------------------------------
// 
// report charges
// 
//------------------------------------------------------------------------------

void nodes_report_charges( char* event, int charge )
{
    int i = 0;
    
    print_str( event );
    print_str( ";" );
    print_dec( charge );
    print_str( ";" );
    
    for ( i = 0; i < NUM_NODES; i++ )
    {
        print_dec( i );
        print_str( ";" );
        print_dec( nodes[ i ].charge );
        print_str( ";" );
    }
    
    nl();
}

//------------------------------------------------------------------------------
// 
// get finished nodes
// 
//------------------------------------------------------------------------------

unsigned int get_finished_nodes( unsigned int nodes_busy_prev )
{
    // TODO (maybe)
    // this could be done in the control (hw), but is done in the sw
    // for now.
    
    // to check which prgs have finished we look at which nodes
    // are not busy anymore and which prg they executed
    
    unsigned int nodes_busy_curr = GET_BUSY;
    
    // xor shows the changes in the varaibals. a 1 means, that a
    // node, that was previoulsy busy is not busy anymore.
    // -> the node has finished.
    // this change would be also true for nodes that are activated
    // (changed from not busy to busy), but newly activated nodes
    // are saved at the end of the loop.
    
    unsigned int nodes_finished = nodes_busy_curr ^ nodes_busy_prev;
    
    
    
#ifdef DBG_NODES_FINISHED
    print_bin( nodes_busy_prev ,  5 ); nl();
    print_bin( nodes_busy_curr ,  5 ); nl();
    print_bin( nodes_finished  , 16 ); nl();
#endif
    
    
    
    return nodes_finished;
}

//------------------------------------------------------------------------------
// 
// node_set_busy
// 
//------------------------------------------------------------------------------

// keep track of the nodes that are busy to find out which finish executing a
// prg

void node_set_busy( int node_i )
{
    nodes_busy |= ( 1 << node_i );
    
    
    
#ifdef DBG_NODES_BUSY
    print_str( "nodes_busy: " );
    print_bin( nodes_busy, 5 );
    nl();
#endif
    
    
    
}

void node_assign_prg( int node_i, int prg_i )
{
    ASSIGN( nodes[node_i], prgs[prg_i] );
    
    // remember which prg the node is running and that the prg
    // as well as the node is active
    
    nodes[node_i].prg = prg_i;
}
