// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef _VTOP__SYMS_H_
#define _VTOP__SYMS_H_  // guard

#include "verilated_heavy.h"

// INCLUDE MODULE CLASSES
#include "Vtop.h"
#include "Vtop_mkIQRouterCoreSimple.h"
#include "Vtop_if_axi_light.h"
#include "Vtop_if_axi_light__AC4.h"
#include "Vtop_if_connect.h"

// SYMS CLASS
class Vtop__Syms : public VerilatedSyms {
  public:
    
    // LOCAL STATE
    const char* __Vm_namep;
    bool __Vm_activity;  ///< Used by trace routines to determine change occurred
    bool __Vm_didInit;
    
    // SUBCELL STATE
    Vtop*                          TOPp;
    Vtop_if_axi_light__AC4         TOP__top__DOT__controller_inst__DOT__if_axi_light_cpu_to_debugger;
    Vtop_if_axi_light__AC4         TOP__top__DOT__controller_inst__DOT__if_axi_light_debugger_to_offset;
    Vtop_if_axi_light              TOP__top__DOT__if_axi_light_controller;
    Vtop_if_connect                TOP__top__DOT__if_connect_memory;
    Vtop_if_connect                TOP__top__DOT__if_connect_node_0;
    Vtop_if_connect                TOP__top__DOT__if_connect_node_1;
    Vtop_if_connect                TOP__top__DOT__if_connect_node_empty;
    Vtop_mkIQRouterCoreSimple      TOP__top__DOT__if_wrapper_noc_2x2_16_inst__DOT__mkNetworkSimple_inst__DOT__net_routers_router_core;
    Vtop_mkIQRouterCoreSimple      TOP__top__DOT__if_wrapper_noc_2x2_16_inst__DOT__mkNetworkSimple_inst__DOT__net_routers_router_core_1;
    Vtop_mkIQRouterCoreSimple      TOP__top__DOT__if_wrapper_noc_2x2_16_inst__DOT__mkNetworkSimple_inst__DOT__net_routers_router_core_2;
    Vtop_mkIQRouterCoreSimple      TOP__top__DOT__if_wrapper_noc_2x2_16_inst__DOT__mkNetworkSimple_inst__DOT__net_routers_router_core_3;
    Vtop_if_axi_light              TOP__top__DOT__memory_controller_inst__DOT__if_axi_light_arbiter_to_detect_demux;
    Vtop_if_axi_light              TOP__top__DOT__memory_controller_inst__DOT__if_axi_light_bridge_to_arbiter;
    Vtop_if_axi_light              TOP__top__DOT__memory_controller_inst__DOT__if_axi_light_control;
    Vtop_if_axi_light              TOP__top__DOT__memory_controller_inst__DOT__if_axi_light_demux;
    Vtop_if_axi_light              TOP__top__DOT__memory_controller_inst__DOT__if_axi_light_memory;
    Vtop_if_axi_light__AC4         TOP__top__DOT__node_0__DOT__if_axi_light_cpu_to_detector;
    Vtop_if_axi_light              TOP__top__DOT__node_0__DOT__if_axi_light_detector_to_offset;
    Vtop_if_axi_light              TOP__top__DOT__node_0__DOT__if_axi_light_mux_to_slave_bridge;
    Vtop_if_axi_light              TOP__top__DOT__node_0__DOT__if_axi_light_offset_to_mux;
    Vtop_if_axi_light              TOP__top__DOT__node_0__DOT__if_axi_light_self_awareness_to_mux;
    Vtop_if_axi_light__AC4         TOP__top__DOT__node_1__DOT__if_axi_light_cpu_to_detector;
    Vtop_if_axi_light              TOP__top__DOT__node_1__DOT__if_axi_light_detector_to_offset;
    Vtop_if_axi_light              TOP__top__DOT__node_1__DOT__if_axi_light_mux_to_slave_bridge;
    Vtop_if_axi_light              TOP__top__DOT__node_1__DOT__if_axi_light_offset_to_mux;
    Vtop_if_axi_light              TOP__top__DOT__node_1__DOT__if_axi_light_self_awareness_to_mux;
    
    // CREATORS
    Vtop__Syms(Vtop* topp, const char* namep);
    ~Vtop__Syms() {}
    
    // METHODS
    inline const char* name() { return __Vm_namep; }
    inline bool getClearActivity() { bool r=__Vm_activity; __Vm_activity=false; return r; }
    
} VL_ATTR_ALIGNED(VL_CACHE_LINE_BYTES);

#endif  // guard
