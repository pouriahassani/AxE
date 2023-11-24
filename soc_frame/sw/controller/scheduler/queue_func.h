
void queue_build_event_queue()
{
    int i = 0;
    int j = 0;
    
    // 1.1. add charging events
    // ------------------------
    
    // 25,000,000 clk cnts
    // 171.7986918 charging events are possible until an overflow
    
    // for testing we use 5,000,000
    // 10 charging events
    
    // we don't charge at t0 so we start the loop at 1
    
    queue_index = 0;
    
    for ( i = 1; i < 11; i++ )
    {
        queue[ queue_index ].cnt   = 5000000 * i;
        queue[ queue_index ].event = QUEUE_CHARGING_EVENT;
        
        queue_index += 1;
    }
    
    // 1.2. add prgs
    // -------------
    
    // add each prg 10 times to the event queue
    
    for ( i = 0; i < NUM_PRGS; i++ )
    {
        // we don't start a prg at t0 so we start the loop at 1
        
        for ( j = 1; j < 11; j++ )
        {
            queue[ queue_index ].cnt   = prgs[i].exec_inv[ ARCH_RV32I ] * j;
            queue[ queue_index ].event = i;
            
            queue_index += 1;
        }
    }
    
#ifdef DBG_EVENT_QUEUE
    
    print_str( "queue: \n" );
    
    for ( i = 0; i < queue_index; i++ )
    {
        print_dec( queue[ i ].cnt );
        print_str( ": " );
        print_dec( queue[ i ].event );
        nl();
    }
    
#endif
    
    // sort the queue
    
    int tmp1;
    int tmp2;
    
    for ( i = 0; i < queue_index; i++ )
    {
        tmp1 = i;
        
        for ( j = i; j < queue_index; j++ )
        {
            if ( queue[ j ].cnt < queue[ tmp1 ].cnt )
            {
                tmp1 = j;
            }
        }
        
        tmp2 = queue[ i ].cnt;
        queue[ i ].cnt = queue[ tmp1 ].cnt;
        queue[ tmp1 ].cnt = tmp2;
        
        tmp2 = queue[ i ].event;
        queue[ i ].event = queue[ tmp1 ].event;
        queue[ tmp1 ].event = tmp2;
    }
    
#ifdef DBG_EVENT_QUEUE
    
    print_str( "queue: \n" );
    
    for ( i = 0; i < queue_index; i++ )
    {
        print_dec( queue[ i ].cnt );
        print_str( ": " );
        print_dec( queue[ i ].event );
        nl();
    }
    
#endif
}
