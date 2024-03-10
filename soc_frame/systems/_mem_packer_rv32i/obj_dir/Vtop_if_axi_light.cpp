// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtop.h for the primary calling header

#include "Vtop_if_axi_light.h"
#include "Vtop__Syms.h"

//==========

VL_CTOR_IMP(Vtop_if_axi_light) {
    // Reset internal values
    // Reset structure values
    _ctor_var_reset();
}

void Vtop_if_axi_light::__Vconfigure(Vtop__Syms* vlSymsp, bool first) {
    if (0 && first) {}  // Prevent unused
    this->__VlSymsp = vlSymsp;
}

Vtop_if_axi_light::~Vtop_if_axi_light() {
}

void Vtop_if_axi_light::_initial__TOP__top__DOT__if_axi_light_axi_detector__1(Vtop__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+            Vtop_if_axi_light::_initial__TOP__top__DOT__if_axi_light_axi_detector__1\n"); );
    Vtop* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    this->w_addr_collected = 0U;
    this->w_data_collected = 0U;
}

void Vtop_if_axi_light::_initial__TOP__top__DOT__if_axi_light_debugger__2(Vtop__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+            Vtop_if_axi_light::_initial__TOP__top__DOT__if_axi_light_debugger__2\n"); );
    Vtop* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    this->w_addr_collected = 0U;
    this->w_data_collected = 0U;
    this->w_addr_sent = 0U;
    this->w_data_sent = 0U;
}

void Vtop_if_axi_light::_ctor_var_reset() {
    VL_DEBUG_IF(VL_DBG_MSGF("+            Vtop_if_axi_light::_ctor_var_reset\n"); );
    // Body
    awvalid = VL_RAND_RESET_I(1);
    awready = VL_RAND_RESET_I(1);
    awaddr = VL_RAND_RESET_I(32);
    awprot = VL_RAND_RESET_I(3);
    wvalid = VL_RAND_RESET_I(1);
    wready = VL_RAND_RESET_I(1);
    wdata = VL_RAND_RESET_I(32);
    wstrb = VL_RAND_RESET_I(4);
    bvalid = VL_RAND_RESET_I(1);
    bready = VL_RAND_RESET_I(1);
    bresp = VL_RAND_RESET_I(2);
    arready = VL_RAND_RESET_I(1);
    rvalid = VL_RAND_RESET_I(1);
    rdata = VL_RAND_RESET_I(32);
    rresp = VL_RAND_RESET_I(2);
    w_addr_collected = VL_RAND_RESET_I(1);
    w_data_collected = VL_RAND_RESET_I(1);
    w_addr_sent = VL_RAND_RESET_I(1);
    w_data_sent = VL_RAND_RESET_I(1);
}
