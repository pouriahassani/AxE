#ifndef NODES_FUNC_H
#define NODES_FUNC_H

#include "globals.h"
#define LAST_NODE(i) ( (NUM_NODES-1) == i )               // check if a node is the last one in the node array
#define NODE_CNT(i) *( (volatile int*) nodes[ i ].cnt )   // TODO - should be deleted



//------------------------------------------------------------------------------
//
// keep track of busy nodes
//
//------------------------------------------------------------------------------



// get busy node mask
//------------------------------------------------------------------------------

unsigned int get_busy_node_mask();


// get idle node mask
//------------------------------------------------------------------------------

unsigned int get_idle_node_mask();


// get finished nodes mask
//------------------------------------------------------------------------------

unsigned int get_finished_nodes_mask( unsigned int nodes_busy_prev );


// node_set_busy
//------------------------------------------------------------------------------

// keep track of the nodes that are busy to find out which finish executing a
// prg

void node_set_busy( int node_i );


// node_set_busy
//------------------------------------------------------------------------------

void nodes_set_idle();

// node_is_busy
//------------------------------------------------------------------------------

int node_is_busy( int node_i );


//------------------------------------------------------------------------------
// 
// node_assign_prg
// 
//------------------------------------------------------------------------------



void node_assign_prg( int node_i, int prg_i );


//------------------------------------------------------------------------------
// 
// report charges
// 
//------------------------------------------------------------------------------



void nodes_report_charges();

#endif