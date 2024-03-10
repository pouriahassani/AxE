
//------------------------------------------------------------------------------
// 
// archs_get_preferred
// 
//------------------------------------------------------------------------------

void archs_get_preferred( int *preferred_archs )
{
    // in save mode try to pick an i node, pick im otherwise
    // only pick the other node if none is available.
    
    if ( 1 == save_mode )
    {
        preferred_archs[0] = ARCH_RV32I;
        preferred_archs[1] = ARCH_RV32IM;
    }
    else
    {
        preferred_archs[0] = ARCH_RV32IM;
        preferred_archs[1] = ARCH_RV32I;
    }
}
