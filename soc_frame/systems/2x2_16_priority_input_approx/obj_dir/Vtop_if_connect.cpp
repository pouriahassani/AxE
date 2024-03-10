// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtop.h for the primary calling header

#include "Vtop_if_connect.h"
#include "Vtop__Syms.h"

//==========

VL_CTOR_IMP(Vtop_if_connect) {
    // Reset internal values
    // Reset structure values
    _ctor_var_reset();
}

void Vtop_if_connect::__Vconfigure(Vtop__Syms* vlSymsp, bool first) {
    if (0 && first) {}  // Prevent unused
    this->__VlSymsp = vlSymsp;
}

Vtop_if_connect::~Vtop_if_connect() {
}

void Vtop_if_connect::_ctor_var_reset() {
    VL_DEBUG_IF(VL_DBG_MSGF("+              Vtop_if_connect::_ctor_var_reset\n"); );
    // Body
    put_flit = VL_RAND_RESET_I(21);
    en_put = VL_RAND_RESET_I(1);
    en_get_non_full_VCs = VL_RAND_RESET_I(1);
    en_get = VL_RAND_RESET_I(1);
    put_non_full_VCs = VL_RAND_RESET_I(2);
    en_put_non_full_VCs = VL_RAND_RESET_I(1);
}
