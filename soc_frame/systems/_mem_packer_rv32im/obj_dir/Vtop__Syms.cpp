// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table implementation internals

#include "Vtop__Syms.h"
#include "Vtop.h"
#include "Vtop_if_axi_light.h"



// FUNCTIONS
Vtop__Syms::Vtop__Syms(Vtop* topp, const char* namep)
    // Setup locals
    : __Vm_namep(namep)
    , __Vm_activity(false)
    , __Vm_didInit(false)
    // Setup submodule names
    , TOP__top__DOT__if_axi_light_axi_detector(Verilated::catName(topp->name(), "top.if_axi_light_axi_detector"))
    , TOP__top__DOT__if_axi_light_debugger(Verilated::catName(topp->name(), "top.if_axi_light_debugger"))
    , TOP__top__DOT__if_axi_light_memory(Verilated::catName(topp->name(), "top.if_axi_light_memory"))
{
    // Pointer to top level
    TOPp = topp;
    // Setup each module's pointers to their submodules
    TOPp->__PVT__top__DOT__if_axi_light_axi_detector = &TOP__top__DOT__if_axi_light_axi_detector;
    TOPp->__PVT__top__DOT__if_axi_light_debugger = &TOP__top__DOT__if_axi_light_debugger;
    TOPp->__PVT__top__DOT__if_axi_light_memory = &TOP__top__DOT__if_axi_light_memory;
    // Setup each module's pointer back to symbol table (for public functions)
    TOPp->__Vconfigure(this, true);
    TOP__top__DOT__if_axi_light_axi_detector.__Vconfigure(this, true);
    TOP__top__DOT__if_axi_light_debugger.__Vconfigure(this, false);
    TOP__top__DOT__if_axi_light_memory.__Vconfigure(this, false);
}
