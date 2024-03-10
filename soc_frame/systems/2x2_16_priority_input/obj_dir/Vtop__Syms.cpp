// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table implementation internals

#include "Vtop__Syms.h"
#include "Vtop.h"
#include "Vtop_mkIQRouterCoreSimple.h"
#include "Vtop_if_axi_light.h"
#include "Vtop_if_axi_light__AC4.h"
#include "Vtop_if_connect.h"



// FUNCTIONS
Vtop__Syms::Vtop__Syms(Vtop* topp, const char* namep)
    // Setup locals
    : __Vm_namep(namep)
    , __Vm_activity(false)
    , __Vm_didInit(false)
    // Setup submodule names
    , TOP__top__DOT__controller_inst__DOT__if_axi_light_cpu_to_debugger(Verilated::catName(topp->name(), "top.controller_inst.if_axi_light_cpu_to_debugger"))
    , TOP__top__DOT__controller_inst__DOT__if_axi_light_debugger_to_offset(Verilated::catName(topp->name(), "top.controller_inst.if_axi_light_debugger_to_offset"))
    , TOP__top__DOT__if_axi_light_controller(Verilated::catName(topp->name(), "top.if_axi_light_controller"))
    , TOP__top__DOT__if_connect_memory(Verilated::catName(topp->name(), "top.if_connect_memory"))
    , TOP__top__DOT__if_connect_node_0(Verilated::catName(topp->name(), "top.if_connect_node_0"))
    , TOP__top__DOT__if_connect_node_1(Verilated::catName(topp->name(), "top.if_connect_node_1"))
    , TOP__top__DOT__if_connect_node_empty(Verilated::catName(topp->name(), "top.if_connect_node_empty"))
    , TOP__top__DOT__if_wrapper_noc_2x2_16_inst__DOT__mkNetworkSimple_inst__DOT__net_routers_router_core(Verilated::catName(topp->name(), "top.if_wrapper_noc_2x2_16_inst.mkNetworkSimple_inst.net_routers_router_core"))
    , TOP__top__DOT__if_wrapper_noc_2x2_16_inst__DOT__mkNetworkSimple_inst__DOT__net_routers_router_core_1(Verilated::catName(topp->name(), "top.if_wrapper_noc_2x2_16_inst.mkNetworkSimple_inst.net_routers_router_core_1"))
    , TOP__top__DOT__if_wrapper_noc_2x2_16_inst__DOT__mkNetworkSimple_inst__DOT__net_routers_router_core_2(Verilated::catName(topp->name(), "top.if_wrapper_noc_2x2_16_inst.mkNetworkSimple_inst.net_routers_router_core_2"))
    , TOP__top__DOT__if_wrapper_noc_2x2_16_inst__DOT__mkNetworkSimple_inst__DOT__net_routers_router_core_3(Verilated::catName(topp->name(), "top.if_wrapper_noc_2x2_16_inst.mkNetworkSimple_inst.net_routers_router_core_3"))
    , TOP__top__DOT__memory_controller_inst__DOT__if_axi_light_arbiter_to_detect_demux(Verilated::catName(topp->name(), "top.memory_controller_inst.if_axi_light_arbiter_to_detect_demux"))
    , TOP__top__DOT__memory_controller_inst__DOT__if_axi_light_bridge_to_arbiter(Verilated::catName(topp->name(), "top.memory_controller_inst.if_axi_light_bridge_to_arbiter"))
    , TOP__top__DOT__memory_controller_inst__DOT__if_axi_light_control(Verilated::catName(topp->name(), "top.memory_controller_inst.if_axi_light_control"))
    , TOP__top__DOT__memory_controller_inst__DOT__if_axi_light_demux(Verilated::catName(topp->name(), "top.memory_controller_inst.if_axi_light_demux"))
    , TOP__top__DOT__memory_controller_inst__DOT__if_axi_light_memory(Verilated::catName(topp->name(), "top.memory_controller_inst.if_axi_light_memory"))
    , TOP__top__DOT__node_0__DOT__if_axi_light_cpu_to_detector(Verilated::catName(topp->name(), "top.node_0.if_axi_light_cpu_to_detector"))
    , TOP__top__DOT__node_0__DOT__if_axi_light_detector_to_offset(Verilated::catName(topp->name(), "top.node_0.if_axi_light_detector_to_offset"))
    , TOP__top__DOT__node_0__DOT__if_axi_light_mux_to_slave_bridge(Verilated::catName(topp->name(), "top.node_0.if_axi_light_mux_to_slave_bridge"))
    , TOP__top__DOT__node_0__DOT__if_axi_light_offset_to_mux(Verilated::catName(topp->name(), "top.node_0.if_axi_light_offset_to_mux"))
    , TOP__top__DOT__node_0__DOT__if_axi_light_self_awareness_to_mux(Verilated::catName(topp->name(), "top.node_0.if_axi_light_self_awareness_to_mux"))
    , TOP__top__DOT__node_1__DOT__if_axi_light_cpu_to_detector(Verilated::catName(topp->name(), "top.node_1.if_axi_light_cpu_to_detector"))
    , TOP__top__DOT__node_1__DOT__if_axi_light_detector_to_offset(Verilated::catName(topp->name(), "top.node_1.if_axi_light_detector_to_offset"))
    , TOP__top__DOT__node_1__DOT__if_axi_light_mux_to_slave_bridge(Verilated::catName(topp->name(), "top.node_1.if_axi_light_mux_to_slave_bridge"))
    , TOP__top__DOT__node_1__DOT__if_axi_light_offset_to_mux(Verilated::catName(topp->name(), "top.node_1.if_axi_light_offset_to_mux"))
    , TOP__top__DOT__node_1__DOT__if_axi_light_self_awareness_to_mux(Verilated::catName(topp->name(), "top.node_1.if_axi_light_self_awareness_to_mux"))
{
    // Pointer to top level
    TOPp = topp;
    // Setup each module's pointers to their submodules
    TOPp->__PVT__top__DOT__controller_inst__DOT__if_axi_light_cpu_to_debugger = &TOP__top__DOT__controller_inst__DOT__if_axi_light_cpu_to_debugger;
    TOPp->__PVT__top__DOT__controller_inst__DOT__if_axi_light_debugger_to_offset = &TOP__top__DOT__controller_inst__DOT__if_axi_light_debugger_to_offset;
    TOPp->__PVT__top__DOT__if_axi_light_controller = &TOP__top__DOT__if_axi_light_controller;
    TOPp->__PVT__top__DOT__if_connect_memory = &TOP__top__DOT__if_connect_memory;
    TOPp->__PVT__top__DOT__if_connect_node_0 = &TOP__top__DOT__if_connect_node_0;
    TOPp->__PVT__top__DOT__if_connect_node_1 = &TOP__top__DOT__if_connect_node_1;
    TOPp->__PVT__top__DOT__if_connect_node_empty = &TOP__top__DOT__if_connect_node_empty;
    TOPp->__PVT__top__DOT__if_wrapper_noc_2x2_16_inst__DOT__mkNetworkSimple_inst__DOT__net_routers_router_core = &TOP__top__DOT__if_wrapper_noc_2x2_16_inst__DOT__mkNetworkSimple_inst__DOT__net_routers_router_core;
    TOPp->__PVT__top__DOT__if_wrapper_noc_2x2_16_inst__DOT__mkNetworkSimple_inst__DOT__net_routers_router_core_1 = &TOP__top__DOT__if_wrapper_noc_2x2_16_inst__DOT__mkNetworkSimple_inst__DOT__net_routers_router_core_1;
    TOPp->__PVT__top__DOT__if_wrapper_noc_2x2_16_inst__DOT__mkNetworkSimple_inst__DOT__net_routers_router_core_2 = &TOP__top__DOT__if_wrapper_noc_2x2_16_inst__DOT__mkNetworkSimple_inst__DOT__net_routers_router_core_2;
    TOPp->__PVT__top__DOT__if_wrapper_noc_2x2_16_inst__DOT__mkNetworkSimple_inst__DOT__net_routers_router_core_3 = &TOP__top__DOT__if_wrapper_noc_2x2_16_inst__DOT__mkNetworkSimple_inst__DOT__net_routers_router_core_3;
    TOPp->__PVT__top__DOT__memory_controller_inst__DOT__if_axi_light_arbiter_to_detect_demux = &TOP__top__DOT__memory_controller_inst__DOT__if_axi_light_arbiter_to_detect_demux;
    TOPp->__PVT__top__DOT__memory_controller_inst__DOT__if_axi_light_bridge_to_arbiter = &TOP__top__DOT__memory_controller_inst__DOT__if_axi_light_bridge_to_arbiter;
    TOPp->__PVT__top__DOT__memory_controller_inst__DOT__if_axi_light_control = &TOP__top__DOT__memory_controller_inst__DOT__if_axi_light_control;
    TOPp->__PVT__top__DOT__memory_controller_inst__DOT__if_axi_light_demux = &TOP__top__DOT__memory_controller_inst__DOT__if_axi_light_demux;
    TOPp->__PVT__top__DOT__memory_controller_inst__DOT__if_axi_light_memory = &TOP__top__DOT__memory_controller_inst__DOT__if_axi_light_memory;
    TOPp->__PVT__top__DOT__node_0__DOT__if_axi_light_cpu_to_detector = &TOP__top__DOT__node_0__DOT__if_axi_light_cpu_to_detector;
    TOPp->__PVT__top__DOT__node_0__DOT__if_axi_light_detector_to_offset = &TOP__top__DOT__node_0__DOT__if_axi_light_detector_to_offset;
    TOPp->__PVT__top__DOT__node_0__DOT__if_axi_light_mux_to_slave_bridge = &TOP__top__DOT__node_0__DOT__if_axi_light_mux_to_slave_bridge;
    TOPp->__PVT__top__DOT__node_0__DOT__if_axi_light_offset_to_mux = &TOP__top__DOT__node_0__DOT__if_axi_light_offset_to_mux;
    TOPp->__PVT__top__DOT__node_0__DOT__if_axi_light_self_awareness_to_mux = &TOP__top__DOT__node_0__DOT__if_axi_light_self_awareness_to_mux;
    TOPp->__PVT__top__DOT__node_1__DOT__if_axi_light_cpu_to_detector = &TOP__top__DOT__node_1__DOT__if_axi_light_cpu_to_detector;
    TOPp->__PVT__top__DOT__node_1__DOT__if_axi_light_detector_to_offset = &TOP__top__DOT__node_1__DOT__if_axi_light_detector_to_offset;
    TOPp->__PVT__top__DOT__node_1__DOT__if_axi_light_mux_to_slave_bridge = &TOP__top__DOT__node_1__DOT__if_axi_light_mux_to_slave_bridge;
    TOPp->__PVT__top__DOT__node_1__DOT__if_axi_light_offset_to_mux = &TOP__top__DOT__node_1__DOT__if_axi_light_offset_to_mux;
    TOPp->__PVT__top__DOT__node_1__DOT__if_axi_light_self_awareness_to_mux = &TOP__top__DOT__node_1__DOT__if_axi_light_self_awareness_to_mux;
    // Setup each module's pointer back to symbol table (for public functions)
    TOPp->__Vconfigure(this, true);
    TOP__top__DOT__controller_inst__DOT__if_axi_light_cpu_to_debugger.__Vconfigure(this, true);
    TOP__top__DOT__controller_inst__DOT__if_axi_light_debugger_to_offset.__Vconfigure(this, false);
    TOP__top__DOT__if_axi_light_controller.__Vconfigure(this, true);
    TOP__top__DOT__if_connect_memory.__Vconfigure(this, true);
    TOP__top__DOT__if_connect_node_0.__Vconfigure(this, false);
    TOP__top__DOT__if_connect_node_1.__Vconfigure(this, false);
    TOP__top__DOT__if_connect_node_empty.__Vconfigure(this, false);
    TOP__top__DOT__if_wrapper_noc_2x2_16_inst__DOT__mkNetworkSimple_inst__DOT__net_routers_router_core.__Vconfigure(this, true);
    TOP__top__DOT__if_wrapper_noc_2x2_16_inst__DOT__mkNetworkSimple_inst__DOT__net_routers_router_core_1.__Vconfigure(this, false);
    TOP__top__DOT__if_wrapper_noc_2x2_16_inst__DOT__mkNetworkSimple_inst__DOT__net_routers_router_core_2.__Vconfigure(this, false);
    TOP__top__DOT__if_wrapper_noc_2x2_16_inst__DOT__mkNetworkSimple_inst__DOT__net_routers_router_core_3.__Vconfigure(this, false);
    TOP__top__DOT__memory_controller_inst__DOT__if_axi_light_arbiter_to_detect_demux.__Vconfigure(this, false);
    TOP__top__DOT__memory_controller_inst__DOT__if_axi_light_bridge_to_arbiter.__Vconfigure(this, false);
    TOP__top__DOT__memory_controller_inst__DOT__if_axi_light_control.__Vconfigure(this, false);
    TOP__top__DOT__memory_controller_inst__DOT__if_axi_light_demux.__Vconfigure(this, false);
    TOP__top__DOT__memory_controller_inst__DOT__if_axi_light_memory.__Vconfigure(this, false);
    TOP__top__DOT__node_0__DOT__if_axi_light_cpu_to_detector.__Vconfigure(this, false);
    TOP__top__DOT__node_0__DOT__if_axi_light_detector_to_offset.__Vconfigure(this, false);
    TOP__top__DOT__node_0__DOT__if_axi_light_mux_to_slave_bridge.__Vconfigure(this, false);
    TOP__top__DOT__node_0__DOT__if_axi_light_offset_to_mux.__Vconfigure(this, false);
    TOP__top__DOT__node_0__DOT__if_axi_light_self_awareness_to_mux.__Vconfigure(this, false);
    TOP__top__DOT__node_1__DOT__if_axi_light_cpu_to_detector.__Vconfigure(this, false);
    TOP__top__DOT__node_1__DOT__if_axi_light_detector_to_offset.__Vconfigure(this, false);
    TOP__top__DOT__node_1__DOT__if_axi_light_mux_to_slave_bridge.__Vconfigure(this, false);
    TOP__top__DOT__node_1__DOT__if_axi_light_offset_to_mux.__Vconfigure(this, false);
    TOP__top__DOT__node_1__DOT__if_axi_light_self_awareness_to_mux.__Vconfigure(this, false);
}
