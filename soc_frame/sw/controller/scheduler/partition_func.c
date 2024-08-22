#include "partition_func.h"
//----------------------------------------------------------------------
// 
// partition_eh_ra
// 
//----------------------------------------------------------------------

// returns -1 if partition is not successful


int partition_eh_ra()
{
    #ifdef DBG_PARTITION_EH_RA
        print_str( "\nstarting partition eh ra" ); 
    #endif
    
    unsigned int wccr = 42000;
    
    int i = 0;
    int j = 0;
    
    unsigned int upi = 0;
    unsigned int uei = 0;
    
    int tmp = 0;
    
    for( i = 0; i < NUM_PRGS; i++ )
    {
        #ifdef DBG_PARTITION_EH_RA
            print_str( "\np" );
            print_dec( i ); 
        #endif
        
        // calc ci / ti
        
        upi = fixed_div_8q8( prgs[ i ].c[ 0 ], prgs[ i ].t[ 0 ] );
        uei = fixed_div_8q8( prgs[ i ].e[ 0 ], prgs[ i ].t[ 0 ] );
        
        #ifdef DBG_PARTITION_EH_RA
            print_fixed_div( prgs[ i ].c[ 0 ], prgs[ i ].t[ 0 ], upi );
            print_fixed_div( prgs[ i ].e[ 0 ], prgs[ i ].t[ 0 ], uei );
        #endif
        
        // loop over nodes to find a fitting one
        
        // first we reset all the recorded values of Prj - Uej
        
        for( j = 0; j < NUM_NODES; j++ )
        {
            nodes[ j ].addr_assign = MAX_HALF;
        }
        
        for( j = 0; j < NUM_NODES; j++ )
        {
            #ifdef DBG_PARTITION_EH_RA
                print_str( "\nn" );
                print_dec( j ); 
            #endif
            
            // we add the load of the prg to the node to see if the
            // accumulated load with the current one is smaller than 1
            
            // prg is used to keep track of the accumulated load
            
            tmp = nodes[ j ].prg + upi;
            
            #ifdef DBG_PARTITION_EH_RA
                print_fixed_add( nodes[ j ].prg, upi, tmp );
            #endif
            
            // we still deal with a 8q8 number here, so we shift the
            // number to the right by 8 bits making the comparison
            // easier
            
            tmp = tmp >> 8;
            
            if ( tmp < 1 )
            {
                // timing utilization is ok -> only looking at timing
                // this means, that we can allocate the current prg
                
                #ifdef DBG_PARTITION_EH_RA
                    print_str( "\nload check has passed" ); 
                #endif
                
                // next we check the energy utilization
                
                // charge is used to keep track of the accumulated
                // energy demand
                
                tmp = nodes[ j ].charge + uei;
                
                #ifdef DBG_PARTITION_EH_RA
                    print_fixed_add( nodes[ j ].charge, uei, tmp );
                #endif
                
                tmp = tmp >> 8;
                
                if ( tmp < wccr )
                {
                    // charging utilization ok -> timing and energy is
                    // covered
                    
                    #ifdef DBG_PARTITION_EH_RA
                        print_str( "\nenergy check has passed" );
                    #endif
                    
                    // remember node as possible choice and record
                    // Prj - Uej. later we will search all the nodes
                    // to find the smallest result.
                    
                    // addr_assign is used to keep track of Prj - Uej
                    
                    nodes[ j ].addr_assign = wccr - tmp;
                    
                    #ifdef DBG_PARTITION_EH_RA
                        print_sub( wccr, tmp, nodes[ j ].addr_assign );
                    #endif
                }
            }
        }
        
        // walk through all the nodes to find the one with the smalles
        // Prj - Uej
        
        // tmp is used to hold the node with the currently smallest
        // Prj - Uej
        
        tmp = 0;
        
        for( j = 0; j < NUM_NODES; j++ )
        {
            if ( nodes[ j ].addr_assign < nodes[ tmp ].addr_assign )
            {
                tmp = j;
            }
        }
        
        // if all the nodes have MAX_HALF in the addr_assign, than
        // there was no node for which the timing as well as the energy
        // checks passed. if the previous loop resulted in finding a
        // node with an addr_assign of MAX_HALF, then the task could
        // not be assigned.
        
        if ( nodes[ tmp ].addr_assign == MAX_HALF )
        {
            #ifdef DBG_PARTITION_EH_RA
                print_str( "\npartition was not possible" );
            #endif
            return -1;
        }
        
        // the found node is recorded in the prg
        
        #ifdef DBG_PARTITION_EH_RA
            print_str( "\nassigned to n" );
            print_dec( tmp );
            
        #endif
        
        prgs[ i ].assigned_to = tmp;
        
        nodes[ tmp ].prg    += upi;
        nodes[ tmp ].charge += uei;
        
        #ifdef DBG_PARTITION_EH_RA
            NL;
        #endif
    }
    
    return 1;
}

// report partition
//----------------------------------------------------------------------

#ifdef REP_PARTITION_EH_RA
    
    void rep_partition()
    {
        int i = 0;
        
        
        print_str( "\n\npartition summary" );
        
        
        for( i = 0; i < NUM_PRGS; i++ )
        {
            print_str( "\np" );
            print_dec( i );
            print_str( " -> n" );
            print_dec( prgs[i].assigned_to );
            
        }
        
        
    }
    
#endif

//----------------------------------------------------------------------
// 
// create task array
// 
//----------------------------------------------------------------------

void create_task_array()
{
    // we have recorded in each task the node it belongs to. however,
    // always iterating over all tasks is very time consuming, so we
    // build an array where to tasks are orderd depending on the index
    // of the node they are assigned to. in the nodes, an index will
    // be recorded that corresponds to the starting index of their
    // assigned tasks. to getting the prgs for node 1 means iterating
    // over this array starting at nodes[ 1 ].prgs_start_i up until not
    // including nodes[ +1 ].prgs_start_i. each entry in this array
    // is an index for the prgs array.
    
    int i = 0;
    int j = 0;
    
    // we are going to keep track of the current index in the
    // prgs_start_i variable of the next node.
    
    // make sure that the value is set to 0 for every node.
    
    for ( i = 0; i < NUM_NODES; i++ ) { nodes[ i ].prgs_start_i = 0; }
    
    #ifdef DBG_PRGS_LIST_CREATION
        
        print_str( "\ncreating task list/array" ); 
    #endif
    
    for ( i = 0; i < NUM_NODES; i++ )
    {
        #ifdef DBG_PRGS_LIST_CREATION
            
            
            print_str( "\nfinding prgs belonging to n" );
            print_dec( i );
            
            
        #endif
        
        // we don't need to set the start index of the node we are going
        // to do next as this is already recorded in the index.
        // recall, that we record the current index of the prgs_list in
        // the next node. so when we move on to the next node node, we
        // already have the current index recorded in it. as we are
        // going to keep track of the current index in the next node,
        // we need to copy that value there.
        // it would have been smarter to keep track of the number in the
        // previous node as the first node always starts at 0.
        
        // if we are not at the last node
        
        if ( LAST_NODE(i) )
        {
            #ifdef DBG_PRGS_LIST_CREATION
                print_str( "\nlast node" ); 
            #endif
            
            nodes[ 0 ].prgs_start_i = nodes[ i ].prgs_start_i;
        }
        else
        {
            nodes[ i+1 ].prgs_start_i = nodes[ i ].prgs_start_i;
        }
        
        #ifdef DBG_PRGS_LIST_CREATION
            print_str( "\nprgs_start_i set to: " );print_dec( nodes[ i ].prgs_start_i );
        #endif
        
        for ( j = 0; j < NUM_PRGS; j++ )
        {
            #ifdef DBG_PRGS_LIST_CREATION
                print_str( "\nlooking at p" );print_dec( j ); 
            #endif
            
            if ( prgs[ j ].assigned_to == i )
            {
                #ifdef DBG_PRGS_LIST_CREATION
                    print_str( "\nfound p" );print_dec( j );
                    print_str( " for -> n" );print_dec( i );
                   
                #endif
                
                // if we are at the last node we use node 0 to keep
                // track of the index as we know that this is going to
                // be 0.
                
                #ifdef DBG_PRGS_LIST_CREATION
                    print_str( "\nset p" );print_dec( j );
                    print_str( " at index: " );
                #endif
                
                if ( LAST_NODE(i) )
                {
                    #ifdef DBG_PRGS_LIST_CREATION
                        print_dec( nodes[0].prgs_start_i );
                        
                    #endif
                    
                    prgs_list[ nodes[0].prgs_start_i ] = j;
                    nodes[0].prgs_start_i += 1;
                    
                    #ifdef DBG_PRGS_LIST_CREATION
                        print_str( "\nnext index is: " );
                        print_dec( nodes[0].prgs_start_i );
                        
                    #endif
                }
                else
                {
                    #ifdef DBG_PRGS_LIST_CREATION
                        print_dec( nodes[i+1].prgs_start_i );
                        
                    #endif
                    
                    prgs_list[ nodes[i+1].prgs_start_i ] = j;
                    nodes[i+1].prgs_start_i += 1;
                    
                    #ifdef DBG_PRGS_LIST_CREATION
                        print_str( "\nnext index is: " );
                        print_dec( nodes[i+1].prgs_start_i );
                        
                    #endif
                }
            }
        }
    }
    
    // as we used the variable for node 0 to keep track of the index
    // while processing the last node we set it again to 0 here.
    
    nodes[0].prgs_start_i = 0;
    
    #ifdef DBG_PRGS_LIST_CREATION
        
        print_str( "\nall prgs_starts: " ); 
        
        for ( i = 0; i < NUM_NODES; i++ )
        {
            print_str( "\nn" );
            print_dec( i );
            print_str( " : " );
            print_dec( nodes[ i ].prgs_start_i );
            
        }
        
    #endif
}

// report prgs list
//----------------------------------------------------------------------

#ifdef REP_PRGS_LIST
    
    void rep_prgs_list()
    {
        int i = 0;
        int j = 0;
        
        
        
        print_str( "\nreport prgs list:\n" );
        
        for ( i = 0; i < NUM_PRGS; i++ )
        {
            print_dec( i );
            print_str( " | p" );
            print_dec( prgs_list[ i ] );
            
            if ( i == nodes[ j ].prgs_start_i )
            {
                print_str( " <- n" );
                print_dec( j );
                
                j += 1;
            }
            
           print_str( ";\n ");
        }
        
        
    }
    
#endif
