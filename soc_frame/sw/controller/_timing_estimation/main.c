
// This is free and unencumbered software released into the public domain.

// A simple test program to run on the controller.

#include "mpsoc.h"

#include "typedefs.h"
#include "defines.h"

#include "nodes.h"
#include "prgs.h"

#include "util.h"

node_t nodes[ NUM_NODES ];

prg_t prgs[ NUM_PRGS ];

int prg_to_run = PRG_TO_RUN;
int node_to_use = NODE_TO_USE;

void my_main()
{
    // init
    
    init_nodes( nodes );
    init_prgs( prgs );
    
    int cnt_start = 0;
    int cnt_end = 0;
    
    int cnt_diff = 0;
    print_str( prgs[prg_to_run].name );
    nl();
    
    ASSIGN( nodes[node_to_use], prgs[prg_to_run] );
    
    cnt_start = GET_COUNTER_GLOBAL;
    
    while ( IS_BUSY( nodes[node_to_use].id_flag ) ) {}
    
    cnt_end = GET_COUNTER_GLOBAL;
    
    // diff
    
    cnt_diff = cnt_end - cnt_start;
    
    nl();
    print_dec( cnt_diff );
    nl();
    
    print_char( 0x04 );
    
    while ( 1 == 1 ) {}
}
