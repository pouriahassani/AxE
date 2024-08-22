
// these are the supported archs.

// this files is not automatically generated and could be used to
// get a more clear overview of the arches. like some kind of list
// of all the arches that are available.
// generally the whole support of multiple arches is lacking.

// the power values are from actual measurements from a board.

void init_archs( arch_t *archs )
{
    archs[ ARCH_RV32I  ].node_mask = NODES_MASK_RV32I;
    archs[ ARCH_RV32I  ].power = 1125;
    
    archs[ ARCH_RV32IM ].node_mask = NODES_MASK_RV32IM;
    archs[ ARCH_RV32IM ].power = 1126;
}