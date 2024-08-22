/* This file has been automatically generated */

#include "globals.h"

#include "Node_arch_prgs.h"

void init_nodes( node_t *nodes )
{
	nodes[0].id          = 0;
	nodes[0].arch        = ARCH_RV32IM;
	nodes[0].id_flag     = NODE_0_ID;
	nodes[0].addr_assign = NODE_0_ADDR_ASSIGN;
	nodes[0].mem_address_assigned = NODE_0_ADDR_ASSIGN;
	nodes[0].cnt         = NODE_0_COUNTER;
	nodes[0].prg         = -1;
	nodes[0].charge      = CHARGE_INITIAL;
	nodes[0].prgs_start_i = 0;
	
	nodes[1].id          = 1;
	nodes[1].arch        = ARCH_RV32IM;
	nodes[1].id_flag     = NODE_1_ID;
	nodes[1].addr_assign = NODE_1_ADDR_ASSIGN;
	nodes[1].mem_address_assigned = NODE_1_ADDR_ASSIGN;
	nodes[1].cnt         = NODE_1_COUNTER;
	nodes[1].prg         = -1;
	nodes[1].charge      = CHARGE_INITIAL;
	nodes[1].prgs_start_i = 0;
	
}

