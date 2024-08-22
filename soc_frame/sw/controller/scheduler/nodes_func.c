#include "nodes_func.h"
//------------------------------------------------------------------------------
//
// keep track of busy nodes
//
//------------------------------------------------------------------------------



// get busy node mask
//------------------------------------------------------------------------------

unsigned int get_busy_node_mask()
{
    return GET_BUSY;
}



// get idle node mask
//------------------------------------------------------------------------------

unsigned int get_idle_node_mask()
{
    // find out which are ready and which actually exist
    // all possible nodes not connected appear as ready
    // the busy nodes are inverted so only the ones that are
    // idle are 1.
    // the nodes mask holds all the nodes that are available in
    // the system. a system with 2 nodes has a node mask of 11.
    // as we inverted the active nodes before, all node indices
    // of nodes not even active in the system are set to 1 and by
    // using the NODES_MASK we get rid of those nodes.
    
    unsigned int state_nodes = GET_BUSY;
    
    state_nodes = ~state_nodes;
    state_nodes &= NODES_MASK;
    
    return state_nodes;
}



// get finished nodes mask
//------------------------------------------------------------------------------

unsigned int get_finished_nodes_mask( unsigned int nodes_busy_prev )
{
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
		print_bin( nodes_busy_prev ,  5 ); NL;
		print_bin( nodes_busy_curr ,  5 ); NL;
		print_bin( nodes_finished  , 16 ); NL;
	#endif
    
    return nodes_finished;
}



// node_set_busy
//------------------------------------------------------------------------------

// keep track of the nodes that are busy to find out which finish executing a
// prg

void node_set_busy( int node_i )
{
    nodes_busy |= ( 1 << node_i );
    
	#ifdef DBG_NODES_BUSY
		print_str( "\nnodes_busy: " ); print_bin( nodes_busy, 5 ); NL;
	#endif
}



// node_set_busy
//------------------------------------------------------------------------------

void nodes_set_idle()
{
    unsigned int nodes_finished = get_finished_nodes_mask( nodes_busy );
    
    int nodes_finished_index = 0;
    
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
			nodes[ nodes_finished_index ].prg = -1;
        }
        
        nodes_finished >>= 1;
        nodes_finished_index += 1;
    }
    
	#ifdef DBG_PRGS_ACTIVE
		print_bin( task_set.prgs_active, 5 ); NL;
	#endif
}

// node_is_busy
//------------------------------------------------------------------------------

int node_is_busy( int node_i )
{
	if ( nodes[ node_i ].prg == -1 )
	{
		return TRUE;
	}

	return FALSE;
}



//------------------------------------------------------------------------------
// 
// node_assign_prg
// 
//------------------------------------------------------------------------------



void node_assign_prg( int node_i, int prg_i )
{
    print_str( "In node_assign_prg func" );
        print_dec(node_i);
        print_dec(nodes[node_i].addr_assign);
        print_str( "In node_assign_prg func" );
    print_str_m("node_assign_prg");
    ASSIGN( nodes[node_i], prgs[prg_i] );
    print_str( "In node_assign_prg func" );
    
    // remember which prg the node is running and that the prg
    // as well as the node is active
    
    nodes[node_i].prg = prg_i;
	node_set_busy( node_i );
}



//------------------------------------------------------------------------------
// 
// report charges
// 
//------------------------------------------------------------------------------



void nodes_report_charges()
{
    int i = 0;
    
    for ( i = 0; i < NUM_NODES; i++ )
    {
        print_node( i ); print_dec( nodes[ i ].charge ); print_str( "\n;" );
    }
    
    
}

