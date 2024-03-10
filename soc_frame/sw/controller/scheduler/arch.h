
void init_archs( arch_t *archs )
{
    archs[ ARCH_RV32I  ].node_mask = NODES_MASK_RV32I;
    archs[ ARCH_RV32I  ].power = 1125;
    
    archs[ ARCH_RV32IM ].node_mask = NODES_MASK_RV32IM;
    archs[ ARCH_RV32IM ].power = 1126;
}
