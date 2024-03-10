// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vtop.h for the primary calling header

#ifndef _VTOP_IF_CONNECT_H_
#define _VTOP_IF_CONNECT_H_  // guard

#include "verilated_heavy.h"

//==========

class Vtop__Syms;
class Vtop_VerilatedVcd;


//----------

VL_MODULE(Vtop_if_connect) {
  public:
    
    // LOCAL SIGNALS
    CData/*0:0*/ en_put;
    CData/*0:0*/ en_get_non_full_VCs;
    CData/*0:0*/ en_get;
    CData/*1:0*/ put_non_full_VCs;
    CData/*0:0*/ en_put_non_full_VCs;
    IData/*20:0*/ put_flit;
    
    // INTERNAL VARIABLES
  private:
    Vtop__Syms* __VlSymsp;  // Symbol table
  public:
    
    // CONSTRUCTORS
  private:
    VL_UNCOPYABLE(Vtop_if_connect);  ///< Copying not allowed
  public:
    Vtop_if_connect(const char* name = "TOP");
    ~Vtop_if_connect();
    
    // INTERNAL METHODS
    void __Vconfigure(Vtop__Syms* symsp, bool first);
  private:
    void _ctor_var_reset() VL_ATTR_COLD;
  public:
    static void traceInit(VerilatedVcd* vcdp, void* userthis, uint32_t code);
    static void traceFull(VerilatedVcd* vcdp, void* userthis, uint32_t code);
    static void traceChg(VerilatedVcd* vcdp, void* userthis, uint32_t code);
} VL_ATTR_ALIGNED(VL_CACHE_LINE_BYTES);

//----------


#endif  // guard
