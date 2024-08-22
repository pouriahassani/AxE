/* This file has been automatically generated */

#define NUM_NODES ( 2 )

void init_nodes( node_t *nodes )
{
	nodes[0].id          = 0;
	nodes[0].arch        = ARCH_RV32IM;
	nodes[0].id_flag     = NODE_0_ID;
	nodes[0].addr_assign = NODE_0_ADDR_ASSIGN;
	nodes[0].prg         = 0;
	
	nodes[1].id          = 1;
	nodes[1].arch        = ARCH_RV32I;
	nodes[1].id_flag     = NODE_1_ID;
	nodes[1].addr_assign = NODE_1_ADDR_ASSIGN;
	nodes[1].prg         = 0;
	
}

#define NODES_MASK        ( 0b0000000000000000000000000000011 )
#define NODES_MASK_RV32I  ( 0b0000000000000000000000000000010 )
#define NODES_MASK_RV32IM ( 0b0000000000000000000000000000001 )
