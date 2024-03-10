// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vtop__Syms.h"


//======================

void Vtop::traceChg(VerilatedVcd* vcdp, void* userthis, uint32_t code) {
    // Callback from vcd->dump()
    Vtop* t = (Vtop*)userthis;
    Vtop__Syms* __restrict vlSymsp = t->__VlSymsp;  // Setup global symbol table
    if (vlSymsp->getClearActivity()) {
        t->traceChgThis(vlSymsp, vcdp, code);
    }
}

//======================


void Vtop::traceChgThis(Vtop__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) {
    Vtop* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    int c = code;
    if (0 && vcdp && c) {}  // Prevent unused
    // Body
    {
        if (VL_UNLIKELY((1U & (vlTOPp->__Vm_traceActivity 
                               | (vlTOPp->__Vm_traceActivity 
                                  >> 1U))))) {
            vlTOPp->traceChgThis__2(vlSymsp, vcdp, code);
        }
        if (VL_UNLIKELY((1U & (vlTOPp->__Vm_traceActivity 
                               | (vlTOPp->__Vm_traceActivity 
                                  >> 2U))))) {
            vlTOPp->traceChgThis__3(vlSymsp, vcdp, code);
        }
        if (VL_UNLIKELY((2U & vlTOPp->__Vm_traceActivity))) {
            vlTOPp->traceChgThis__4(vlSymsp, vcdp, code);
        }
        vlTOPp->traceChgThis__5(vlSymsp, vcdp, code);
    }
    // Final
    vlTOPp->__Vm_traceActivity = 0U;
}

void Vtop::traceChgThis__2(Vtop__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) {
    Vtop* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    int c = code;
    if (0 && vcdp && c) {}  // Prevent unused
    // Body
    {
        vcdp->chgBit(c+1,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT____Vcellout__picorv32_axi_inst__mem_axi_awvalid));
        vcdp->chgBit(c+9,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT____Vcellout__picorv32_axi_inst__mem_axi_wvalid));
        vcdp->chgBit(c+17,(vlSymsp->TOP__top__DOT__if_axi_light_axi_detector.bvalid));
        vcdp->chgBit(c+25,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT____Vcellout__picorv32_axi_inst__mem_axi_arvalid));
        vcdp->chgBit(c+33,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__mem_ready));
        vcdp->chgBus(c+41,((((IData)(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__mem_do_prefetch) 
                             | (IData)(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__mem_do_rinst))
                             ? (0xfffffffcU & vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__next_pc)
                             : (0xfffffffcU & vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__reg_op1))),32);
        vcdp->chgBus(c+49,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__mem_la_wdata),32);
        vcdp->chgBus(c+57,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__mem_la_wstrb),4);
        vcdp->chgBus(c+65,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__dbg_insn_opcode),32);
        vcdp->chgBus(c+73,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__next_pc),32);
        vcdp->chgBit(c+81,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__pcpi_int_wr));
        vcdp->chgBus(c+89,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__pcpi_int_rd),32);
        vcdp->chgBit(c+97,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__pcpi_int_ready));
        vcdp->chgBus(c+105,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__mem_rdata_word),32);
        vcdp->chgBit(c+113,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__mem_xfer));
        vcdp->chgBus(c+121,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__mem_rdata_latched_noshuffle),32);
        vcdp->chgBit(c+129,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__instr_trap));
        vcdp->chgBit(c+137,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__is_rdcycle_rdcycleh_rdinstr_rdinstrh));
        vcdp->chgQuad(c+145,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__new_ascii_instr),64);
        vcdp->chgQuad(c+161,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__dbg_ascii_instr),64);
        vcdp->chgBus(c+177,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__dbg_insn_imm),32);
        vcdp->chgBus(c+185,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__dbg_insn_rs1),5);
        vcdp->chgBus(c+193,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__dbg_insn_rs2),5);
        vcdp->chgBus(c+201,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__dbg_insn_rd),5);
        vcdp->chgBit(c+209,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__launch_next_insn));
        vcdp->chgArray(c+217,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__dbg_ascii_state),128);
        vcdp->chgBus(c+249,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__alu_out),32);
        vcdp->chgBit(c+257,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__alu_out_0));
        vcdp->chgBit(c+265,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__alu_eq));
        vcdp->chgBit(c+273,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__alu_ltu));
        vcdp->chgBit(c+281,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__alu_lts));
        vcdp->chgBit(c+289,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__cpuregs_write));
        vcdp->chgBus(c+297,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__cpuregs_wrdata),32);
        vcdp->chgBus(c+305,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__cpuregs_rs1),32);
        vcdp->chgBus(c+313,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__cpuregs_rs2),32);
        vcdp->chgBit(c+321,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__genblk2__DOT__genblk1__DOT__pcpi_mul__DOT__instr_any_mulh));
        vcdp->chgQuad(c+329,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__genblk2__DOT__genblk1__DOT__pcpi_mul__DOT__next_rs1),64);
        vcdp->chgQuad(c+345,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__genblk2__DOT__genblk1__DOT__pcpi_mul__DOT__next_rs2),64);
        vcdp->chgQuad(c+361,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__genblk2__DOT__genblk1__DOT__pcpi_mul__DOT__this_rs2),64);
        vcdp->chgQuad(c+377,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__genblk2__DOT__genblk1__DOT__pcpi_mul__DOT__next_rd),64);
        vcdp->chgQuad(c+393,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__genblk2__DOT__genblk1__DOT__pcpi_mul__DOT__next_rdx),64);
        vcdp->chgQuad(c+409,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__genblk2__DOT__genblk1__DOT__pcpi_mul__DOT__next_rdt),64);
        vcdp->chgBit(c+425,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__genblk3__DOT__pcpi_div__DOT__start));
        vcdp->chgBus(c+433,(vlTOPp->top__DOT__memory_inst__DOT__state),32);
        vcdp->chgBus(c+441,(vlTOPp->top__DOT__memory_inst__DOT__latched_awaddr),32);
        vcdp->chgBus(c+449,(vlTOPp->top__DOT__memory_inst__DOT__latched_awprot),3);
        vcdp->chgBus(c+457,(vlTOPp->top__DOT__memory_inst__DOT__latched_wdata),32);
        vcdp->chgBus(c+465,(vlTOPp->top__DOT__memory_inst__DOT__latched_wstrb),4);
        vcdp->chgBus(c+473,(vlTOPp->top__DOT__memory_inst__DOT__latched_araddr),32);
        vcdp->chgBus(c+481,(vlTOPp->top__DOT__memory_inst__DOT__latched_arprot),3);
        vcdp->chgBus(c+489,(vlTOPp->top__DOT__memory_inst__DOT__index),32);
        vcdp->chgBus(c+497,(vlTOPp->top__DOT__memory_inst__DOT__status),2);
        vcdp->chgBit(c+505,(vlTOPp->top__DOT__memory_inst__DOT__done));
        vcdp->chgBus(c+513,(vlSymsp->TOP__top__DOT__if_axi_light_axi_detector.bresp),2);
        vcdp->chgBit(c+521,(vlSymsp->TOP__top__DOT__if_axi_light_axi_detector.w_addr_collected));
        vcdp->chgBit(c+529,(vlSymsp->TOP__top__DOT__if_axi_light_axi_detector.w_data_collected));
        vcdp->chgBit(c+537,(vlSymsp->TOP__top__DOT__if_axi_light_debugger.bvalid));
        vcdp->chgBit(c+545,(vlSymsp->TOP__top__DOT__if_axi_light_debugger.bready));
        vcdp->chgBus(c+553,(vlSymsp->TOP__top__DOT__if_axi_light_debugger.bresp),2);
        vcdp->chgBit(c+561,(vlSymsp->TOP__top__DOT__if_axi_light_debugger.w_addr_collected));
        vcdp->chgBit(c+569,(vlSymsp->TOP__top__DOT__if_axi_light_debugger.w_data_collected));
        vcdp->chgBit(c+577,(vlSymsp->TOP__top__DOT__if_axi_light_debugger.w_addr_sent));
        vcdp->chgBit(c+585,(vlSymsp->TOP__top__DOT__if_axi_light_debugger.w_data_sent));
        vcdp->chgBit(c+593,(vlSymsp->TOP__top__DOT__if_axi_light_memory.bready));
        vcdp->chgBit(c+601,(vlSymsp->TOP__top__DOT__if_axi_light_memory.w_addr_collected));
        vcdp->chgBit(c+609,(vlSymsp->TOP__top__DOT__if_axi_light_memory.w_data_collected));
        vcdp->chgBit(c+617,(vlSymsp->TOP__top__DOT__if_axi_light_memory.w_addr_sent));
        vcdp->chgBit(c+625,(vlSymsp->TOP__top__DOT__if_axi_light_memory.w_data_sent));
    }
}

void Vtop::traceChgThis__3(Vtop__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) {
    Vtop* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    int c = code;
    if (0 && vcdp && c) {}  // Prevent unused
    // Body
    {
        vcdp->chgBit(c+633,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__mem_la_read));
        vcdp->chgBit(c+641,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__mem_la_write));
        vcdp->chgBit(c+649,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__clear_prefetched_high_word));
        vcdp->chgBit(c+657,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__mem_done));
    }
}

void Vtop::traceChgThis__4(Vtop__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) {
    Vtop* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    int c = code;
    if (0 && vcdp && c) {}  // Prevent unused
    // Body
    {
        vcdp->chgBit(c+665,(vlSymsp->TOP__top__DOT__if_axi_light_axi_detector.awready));
        vcdp->chgBus(c+673,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__mem_addr),32);
        vcdp->chgBit(c+681,(vlSymsp->TOP__top__DOT__if_axi_light_axi_detector.wready));
        vcdp->chgBus(c+689,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__mem_wdata),32);
        vcdp->chgBus(c+697,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__mem_wstrb),4);
        vcdp->chgBit(c+705,(((IData)(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__mem_valid) 
                             & (0U != (IData)(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__mem_wstrb)))));
        vcdp->chgBit(c+713,(vlSymsp->TOP__top__DOT__if_axi_light_memory.arready));
        vcdp->chgBus(c+721,(((IData)(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__mem_instr)
                              ? 4U : 0U)),3);
        vcdp->chgBit(c+729,(vlSymsp->TOP__top__DOT__if_axi_light_memory.rvalid));
        vcdp->chgBit(c+737,(((IData)(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__mem_valid) 
                             & (~ (IData)((0U != (IData)(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__mem_wstrb)))))));
        vcdp->chgBus(c+745,(vlSymsp->TOP__top__DOT__if_axi_light_memory.rdata),32);
        vcdp->chgBit(c+753,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__pcpi_valid));
        vcdp->chgBus(c+761,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__pcpi_insn),32);
        vcdp->chgBus(c+769,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__reg_op1),32);
        vcdp->chgBus(c+777,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__reg_op2),32);
        vcdp->chgBus(c+785,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__eoi),32);
        vcdp->chgBit(c+793,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__trace_valid));
        vcdp->chgQuad(c+801,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__trace_data),36);
        vcdp->chgBit(c+817,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__mem_valid));
        vcdp->chgBit(c+825,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__mem_instr));
        vcdp->chgBit(c+833,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__axi_adapter__DOT__ack_awvalid));
        vcdp->chgBit(c+841,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__axi_adapter__DOT__ack_arvalid));
        vcdp->chgBit(c+849,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__axi_adapter__DOT__ack_wvalid));
        vcdp->chgBit(c+857,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__axi_adapter__DOT__xfer_done));
        vcdp->chgQuad(c+865,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__count_cycle),64);
        vcdp->chgQuad(c+881,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__count_instr),64);
        vcdp->chgBus(c+897,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__reg_pc),32);
        vcdp->chgBus(c+905,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__reg_next_pc),32);
        vcdp->chgBus(c+913,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__reg_out),32);
        vcdp->chgBus(c+921,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__reg_sh),5);
        vcdp->chgBus(c+929,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__next_insn_opcode),32);
        vcdp->chgBus(c+937,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__dbg_insn_addr),32);
        vcdp->chgBit(c+945,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__irq_delay));
        vcdp->chgBit(c+953,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__irq_active));
        vcdp->chgBus(c+961,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__irq_mask),32);
        vcdp->chgBus(c+969,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__irq_pending),32);
        vcdp->chgBus(c+977,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__timer),32);
        vcdp->chgBus(c+985,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__cpuregs[0]),32);
        vcdp->chgBus(c+986,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__cpuregs[1]),32);
        vcdp->chgBus(c+987,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__cpuregs[2]),32);
        vcdp->chgBus(c+988,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__cpuregs[3]),32);
        vcdp->chgBus(c+989,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__cpuregs[4]),32);
        vcdp->chgBus(c+990,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__cpuregs[5]),32);
        vcdp->chgBus(c+991,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__cpuregs[6]),32);
        vcdp->chgBus(c+992,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__cpuregs[7]),32);
        vcdp->chgBus(c+993,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__cpuregs[8]),32);
        vcdp->chgBus(c+994,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__cpuregs[9]),32);
        vcdp->chgBus(c+995,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__cpuregs[10]),32);
        vcdp->chgBus(c+996,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__cpuregs[11]),32);
        vcdp->chgBus(c+997,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__cpuregs[12]),32);
        vcdp->chgBus(c+998,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__cpuregs[13]),32);
        vcdp->chgBus(c+999,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__cpuregs[14]),32);
        vcdp->chgBus(c+1000,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__cpuregs[15]),32);
        vcdp->chgBus(c+1001,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__cpuregs[16]),32);
        vcdp->chgBus(c+1002,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__cpuregs[17]),32);
        vcdp->chgBus(c+1003,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__cpuregs[18]),32);
        vcdp->chgBus(c+1004,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__cpuregs[19]),32);
        vcdp->chgBus(c+1005,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__cpuregs[20]),32);
        vcdp->chgBus(c+1006,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__cpuregs[21]),32);
        vcdp->chgBus(c+1007,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__cpuregs[22]),32);
        vcdp->chgBus(c+1008,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__cpuregs[23]),32);
        vcdp->chgBus(c+1009,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__cpuregs[24]),32);
        vcdp->chgBus(c+1010,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__cpuregs[25]),32);
        vcdp->chgBus(c+1011,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__cpuregs[26]),32);
        vcdp->chgBus(c+1012,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__cpuregs[27]),32);
        vcdp->chgBus(c+1013,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__cpuregs[28]),32);
        vcdp->chgBus(c+1014,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__cpuregs[29]),32);
        vcdp->chgBus(c+1015,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__cpuregs[30]),32);
        vcdp->chgBus(c+1016,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__cpuregs[31]),32);
        vcdp->chgBit(c+1241,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__pcpi_mul_wr));
        vcdp->chgBus(c+1249,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__pcpi_mul_rd),32);
        vcdp->chgBit(c+1257,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__pcpi_mul_wait));
        vcdp->chgBit(c+1265,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__pcpi_mul_ready));
        vcdp->chgBit(c+1273,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__pcpi_div_wr));
        vcdp->chgBus(c+1281,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__pcpi_div_rd),32);
        vcdp->chgBit(c+1289,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__pcpi_div_wait));
        vcdp->chgBit(c+1297,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__pcpi_div_ready));
        vcdp->chgBit(c+1305,(((IData)(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__pcpi_mul_wait) 
                              | (IData)(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__pcpi_div_wait))));
        vcdp->chgBus(c+1313,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__mem_state),2);
        vcdp->chgBus(c+1321,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__mem_wordsize),2);
        vcdp->chgBus(c+1329,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__mem_rdata_q),32);
        vcdp->chgBit(c+1337,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__mem_do_prefetch));
        vcdp->chgBit(c+1345,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__mem_do_rinst));
        vcdp->chgBit(c+1353,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__mem_do_rdata));
        vcdp->chgBit(c+1361,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__mem_do_wdata));
        vcdp->chgBit(c+1369,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__mem_la_secondword));
        vcdp->chgBit(c+1377,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__mem_la_firstword_reg));
        vcdp->chgBit(c+1385,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__last_mem_valid));
        vcdp->chgBit(c+1393,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__prefetched_high_word));
        vcdp->chgBit(c+1401,(((IData)(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__mem_do_prefetch) 
                              | ((IData)(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__mem_do_rinst) 
                                 | ((IData)(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__mem_do_rdata) 
                                    | (IData)(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__mem_do_wdata))))));
        vcdp->chgBit(c+1409,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__instr_lui));
        vcdp->chgBit(c+1417,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__instr_auipc));
        vcdp->chgBit(c+1425,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__instr_jal));
        vcdp->chgBit(c+1433,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__instr_jalr));
        vcdp->chgBit(c+1441,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__instr_beq));
        vcdp->chgBit(c+1449,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__instr_bne));
        vcdp->chgBit(c+1457,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__instr_blt));
        vcdp->chgBit(c+1465,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__instr_bge));
        vcdp->chgBit(c+1473,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__instr_bltu));
        vcdp->chgBit(c+1481,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__instr_bgeu));
        vcdp->chgBit(c+1489,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__instr_lb));
        vcdp->chgBit(c+1497,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__instr_lh));
        vcdp->chgBit(c+1505,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__instr_lw));
        vcdp->chgBit(c+1513,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__instr_lbu));
        vcdp->chgBit(c+1521,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__instr_lhu));
        vcdp->chgBit(c+1529,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__instr_sb));
        vcdp->chgBit(c+1537,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__instr_sh));
        vcdp->chgBit(c+1545,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__instr_sw));
        vcdp->chgBit(c+1553,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__instr_addi));
        vcdp->chgBit(c+1561,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__instr_slti));
        vcdp->chgBit(c+1569,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__instr_sltiu));
        vcdp->chgBit(c+1577,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__instr_xori));
        vcdp->chgBit(c+1585,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__instr_ori));
        vcdp->chgBit(c+1593,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__instr_andi));
        vcdp->chgBit(c+1601,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__instr_slli));
        vcdp->chgBit(c+1609,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__instr_srli));
        vcdp->chgBit(c+1617,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__instr_srai));
        vcdp->chgBit(c+1625,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__instr_add));
        vcdp->chgBit(c+1633,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__instr_sub));
        vcdp->chgBit(c+1641,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__instr_sll));
        vcdp->chgBit(c+1649,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__instr_slt));
        vcdp->chgBit(c+1657,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__instr_sltu));
        vcdp->chgBit(c+1665,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__instr_xor));
        vcdp->chgBit(c+1673,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__instr_srl));
        vcdp->chgBit(c+1681,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__instr_sra));
        vcdp->chgBit(c+1689,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__instr_or));
        vcdp->chgBit(c+1697,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__instr_and));
        vcdp->chgBit(c+1705,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__instr_rdcycle));
        vcdp->chgBit(c+1713,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__instr_rdcycleh));
        vcdp->chgBit(c+1721,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__instr_rdinstr));
        vcdp->chgBit(c+1729,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__instr_rdinstrh));
        vcdp->chgBit(c+1737,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__instr_ecall_ebreak));
        vcdp->chgBit(c+1745,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__instr_getq));
        vcdp->chgBit(c+1753,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__instr_setq));
        vcdp->chgBit(c+1761,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__instr_retirq));
        vcdp->chgBit(c+1769,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__instr_maskirq));
        vcdp->chgBit(c+1777,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__instr_waitirq));
        vcdp->chgBit(c+1785,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__instr_timer));
        vcdp->chgBus(c+1793,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__decoded_rd),5);
        vcdp->chgBus(c+1801,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__decoded_rs1),5);
        vcdp->chgBus(c+1809,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__decoded_rs2),5);
        vcdp->chgBus(c+1817,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__decoded_imm),32);
        vcdp->chgBus(c+1825,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__decoded_imm_uj),32);
        vcdp->chgBit(c+1833,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__decoder_trigger));
        vcdp->chgBit(c+1841,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__decoder_trigger_q));
        vcdp->chgBit(c+1849,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__decoder_pseudo_trigger));
        vcdp->chgBit(c+1857,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__decoder_pseudo_trigger_q));
        vcdp->chgBit(c+1865,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__compressed_instr));
        vcdp->chgBit(c+1873,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__is_lui_auipc_jal));
        vcdp->chgBit(c+1881,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__is_lb_lh_lw_lbu_lhu));
        vcdp->chgBit(c+1889,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__is_slli_srli_srai));
        vcdp->chgBit(c+1897,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__is_jalr_addi_slti_sltiu_xori_ori_andi));
        vcdp->chgBit(c+1905,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__is_sb_sh_sw));
        vcdp->chgBit(c+1913,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__is_sll_srl_sra));
        vcdp->chgBit(c+1921,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__is_lui_auipc_jal_jalr_addi_add_sub));
        vcdp->chgBit(c+1929,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__is_slti_blt_slt));
        vcdp->chgBit(c+1937,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__is_sltiu_bltu_sltu));
        vcdp->chgBit(c+1945,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__is_beq_bne_blt_bge_bltu_bgeu));
        vcdp->chgBit(c+1953,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__is_lbu_lhu_lw));
        vcdp->chgBit(c+1961,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__is_alu_reg_imm));
        vcdp->chgBit(c+1969,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__is_alu_reg_reg));
        vcdp->chgBit(c+1977,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__is_compare));
        vcdp->chgBus(c+1985,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__dbg_rs1val),32);
        vcdp->chgBus(c+1993,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__dbg_rs2val),32);
        vcdp->chgBit(c+2001,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__dbg_rs1val_valid));
        vcdp->chgBit(c+2009,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__dbg_rs2val_valid));
        vcdp->chgQuad(c+2017,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__q_ascii_instr),64);
        vcdp->chgBus(c+2033,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__q_insn_imm),32);
        vcdp->chgBus(c+2041,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__q_insn_opcode),32);
        vcdp->chgBus(c+2049,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__q_insn_rs1),5);
        vcdp->chgBus(c+2057,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__q_insn_rs2),5);
        vcdp->chgBus(c+2065,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__q_insn_rd),5);
        vcdp->chgBit(c+2073,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__dbg_next));
        vcdp->chgBit(c+2081,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__dbg_valid_insn));
        vcdp->chgQuad(c+2089,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__cached_ascii_instr),64);
        vcdp->chgBus(c+2105,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__cached_insn_imm),32);
        vcdp->chgBus(c+2113,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__cached_insn_opcode),32);
        vcdp->chgBus(c+2121,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__cached_insn_rs1),5);
        vcdp->chgBus(c+2129,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__cached_insn_rs2),5);
        vcdp->chgBus(c+2137,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__cached_insn_rd),5);
        vcdp->chgBus(c+2145,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__cpu_state),8);
        vcdp->chgBus(c+2153,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__irq_state),2);
        vcdp->chgBit(c+2161,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__set_mem_do_rinst));
        vcdp->chgBit(c+2169,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__set_mem_do_rdata));
        vcdp->chgBit(c+2177,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__set_mem_do_wdata));
        vcdp->chgBit(c+2185,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__latched_store));
        vcdp->chgBit(c+2193,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__latched_stalu));
        vcdp->chgBit(c+2201,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__latched_branch));
        vcdp->chgBit(c+2209,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__latched_compr));
        vcdp->chgBit(c+2217,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__latched_trace));
        vcdp->chgBit(c+2225,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__latched_is_lu));
        vcdp->chgBit(c+2233,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__latched_is_lh));
        vcdp->chgBit(c+2241,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__latched_is_lb));
        vcdp->chgBus(c+2249,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__latched_rd),5);
        vcdp->chgBus(c+2257,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__current_pc),32);
        vcdp->chgBus(c+2265,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__pcpi_timeout_counter),4);
        vcdp->chgBit(c+2273,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__pcpi_timeout));
        vcdp->chgBus(c+2281,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__next_irq_pending),32);
        vcdp->chgBit(c+2289,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__do_waitirq));
        vcdp->chgBus(c+2297,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__alu_out_q),32);
        vcdp->chgBit(c+2305,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__alu_out_0_q));
        vcdp->chgBit(c+2313,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__alu_wait));
        vcdp->chgBit(c+2321,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__alu_wait_2));
        vcdp->chgBus(c+2329,(((IData)(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__instr_sub)
                               ? (vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__reg_op1 
                                  - vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__reg_op2)
                               : (vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__reg_op1 
                                  + vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__reg_op2))),32);
        vcdp->chgBus(c+2337,((vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__reg_op1 
                              << (0x1fU & vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__reg_op2))),32);
        vcdp->chgBus(c+2345,((IData)((VL_ULL(0x1ffffffff) 
                                      & VL_SHIFTRS_QQI(33,33,5, 
                                                       (((QData)((IData)(
                                                                         (((IData)(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__instr_sra) 
                                                                           | (IData)(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__instr_srai)) 
                                                                          & (vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__reg_op1 
                                                                             >> 0x1fU)))) 
                                                         << 0x20U) 
                                                        | (QData)((IData)(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__reg_op1))), 
                                                       (0x1fU 
                                                        & vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__reg_op2))))),32);
        vcdp->chgBit(c+2353,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__clear_prefetched_high_word_q));
        vcdp->chgBit(c+2361,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__genblk2__DOT__genblk1__DOT__pcpi_mul__DOT__instr_mul));
        vcdp->chgBit(c+2369,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__genblk2__DOT__genblk1__DOT__pcpi_mul__DOT__instr_mulh));
        vcdp->chgBit(c+2377,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__genblk2__DOT__genblk1__DOT__pcpi_mul__DOT__instr_mulhsu));
        vcdp->chgBit(c+2385,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__genblk2__DOT__genblk1__DOT__pcpi_mul__DOT__instr_mulhu));
        vcdp->chgBit(c+2393,(((IData)(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__genblk2__DOT__genblk1__DOT__pcpi_mul__DOT__instr_mul) 
                              | ((IData)(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__genblk2__DOT__genblk1__DOT__pcpi_mul__DOT__instr_mulh) 
                                 | ((IData)(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__genblk2__DOT__genblk1__DOT__pcpi_mul__DOT__instr_mulhsu) 
                                    | (IData)(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__genblk2__DOT__genblk1__DOT__pcpi_mul__DOT__instr_mulhu))))));
        vcdp->chgBit(c+2401,(((IData)(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__genblk2__DOT__genblk1__DOT__pcpi_mul__DOT__instr_mulh) 
                              | (IData)(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__genblk2__DOT__genblk1__DOT__pcpi_mul__DOT__instr_mulhsu))));
        vcdp->chgBit(c+2409,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__genblk2__DOT__genblk1__DOT__pcpi_mul__DOT__pcpi_wait_q));
        vcdp->chgBit(c+2417,(((IData)(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__pcpi_mul_wait) 
                              & (~ (IData)(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__genblk2__DOT__genblk1__DOT__pcpi_mul__DOT__pcpi_wait_q)))));
        vcdp->chgQuad(c+2425,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__genblk2__DOT__genblk1__DOT__pcpi_mul__DOT__rs1),64);
        vcdp->chgQuad(c+2441,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__genblk2__DOT__genblk1__DOT__pcpi_mul__DOT__rs2),64);
        vcdp->chgQuad(c+2457,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__genblk2__DOT__genblk1__DOT__pcpi_mul__DOT__rd),64);
        vcdp->chgQuad(c+2473,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__genblk2__DOT__genblk1__DOT__pcpi_mul__DOT__rdx),64);
        vcdp->chgBus(c+2489,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__genblk2__DOT__genblk1__DOT__pcpi_mul__DOT__mul_counter),7);
        vcdp->chgBit(c+2497,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__genblk2__DOT__genblk1__DOT__pcpi_mul__DOT__mul_waiting));
        vcdp->chgBit(c+2505,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__genblk2__DOT__genblk1__DOT__pcpi_mul__DOT__mul_finish));
        vcdp->chgBit(c+2513,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__genblk3__DOT__pcpi_div__DOT__instr_div));
        vcdp->chgBit(c+2521,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__genblk3__DOT__pcpi_div__DOT__instr_divu));
        vcdp->chgBit(c+2529,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__genblk3__DOT__pcpi_div__DOT__instr_rem));
        vcdp->chgBit(c+2537,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__genblk3__DOT__pcpi_div__DOT__instr_remu));
        vcdp->chgBit(c+2545,(((IData)(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__genblk3__DOT__pcpi_div__DOT__instr_div) 
                              | ((IData)(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__genblk3__DOT__pcpi_div__DOT__instr_divu) 
                                 | ((IData)(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__genblk3__DOT__pcpi_div__DOT__instr_rem) 
                                    | (IData)(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__genblk3__DOT__pcpi_div__DOT__instr_remu))))));
        vcdp->chgBit(c+2553,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__genblk3__DOT__pcpi_div__DOT__pcpi_wait_q));
        vcdp->chgBus(c+2561,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__genblk3__DOT__pcpi_div__DOT__dividend),32);
        vcdp->chgQuad(c+2569,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__genblk3__DOT__pcpi_div__DOT__divisor),63);
        vcdp->chgBus(c+2585,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__genblk3__DOT__pcpi_div__DOT__quotient),32);
        vcdp->chgBus(c+2593,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__genblk3__DOT__pcpi_div__DOT__quotient_msk),32);
        vcdp->chgBit(c+2601,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__genblk3__DOT__pcpi_div__DOT__running));
        vcdp->chgBit(c+2609,(vlTOPp->top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__genblk3__DOT__pcpi_div__DOT__outsign));
        vcdp->chgBus(c+2617,(vlTOPp->top__DOT__axi_detector_inst__DOT__data),32);
        vcdp->chgBus(c+2625,(vlTOPp->top__DOT__axi_detector_inst__DOT__state),32);
        vcdp->chgBus(c+2633,(vlTOPp->top__DOT__axi_detector_inst__DOT__latched_awaddr),32);
        vcdp->chgBus(c+2641,(vlTOPp->top__DOT__axi_detector_inst__DOT__latched_awprot),3);
        vcdp->chgBus(c+2649,(vlTOPp->top__DOT__axi_detector_inst__DOT__latched_wdata),32);
        vcdp->chgBus(c+2657,(vlTOPp->top__DOT__axi_detector_inst__DOT__latched_wstrb),4);
        vcdp->chgBus(c+2665,(vlTOPp->top__DOT__axi_detector_inst__DOT__latched_araddr),32);
        vcdp->chgBus(c+2673,(vlTOPp->top__DOT__axi_detector_inst__DOT__addr_to_check),32);
        vcdp->chgBit(c+2681,(vlTOPp->top__DOT__axi_detector_inst__DOT__done));
        vcdp->chgBit(c+2689,(vlTOPp->top__DOT__axi_detector_inst__DOT__resp_from));
        vcdp->chgBit(c+2697,(vlTOPp->top__DOT__axi_detector_inst__DOT__r_bvalid));
        vcdp->chgBit(c+2705,(vlTOPp->top__DOT__axi_detector_inst__DOT__r_rvalid));
        vcdp->chgBit(c+2713,(vlTOPp->top__DOT__axi_detector_inst__DOT__detected));
        vcdp->chgBit(c+2721,(vlTOPp->top__DOT__axi_detector_inst__DOT__write));
        vcdp->chgBus(c+2729,(vlTOPp->top__DOT__debugger_inst__DOT____Vcellout__axi_detector_debugger_inst__data),32);
        vcdp->chgBus(c+2737,(vlTOPp->top__DOT__debugger_inst__DOT__axi_detector_debugger_inst__DOT__state),32);
        vcdp->chgBus(c+2745,(vlTOPp->top__DOT__debugger_inst__DOT__axi_detector_debugger_inst__DOT__latched_awaddr),32);
        vcdp->chgBus(c+2753,(vlTOPp->top__DOT__debugger_inst__DOT__axi_detector_debugger_inst__DOT__latched_awprot),3);
        vcdp->chgBus(c+2761,(vlTOPp->top__DOT__debugger_inst__DOT__axi_detector_debugger_inst__DOT__latched_wdata),32);
        vcdp->chgBus(c+2769,(vlTOPp->top__DOT__debugger_inst__DOT__axi_detector_debugger_inst__DOT__latched_wstrb),4);
        vcdp->chgBus(c+2777,(vlTOPp->top__DOT__debugger_inst__DOT__axi_detector_debugger_inst__DOT__latched_araddr),32);
        vcdp->chgBus(c+2785,(vlTOPp->top__DOT__debugger_inst__DOT__axi_detector_debugger_inst__DOT__addr_to_check),32);
        vcdp->chgBit(c+2793,(vlTOPp->top__DOT__debugger_inst__DOT__axi_detector_debugger_inst__DOT__done));
        vcdp->chgBit(c+2801,(vlTOPp->top__DOT__debugger_inst__DOT__axi_detector_debugger_inst__DOT__resp_from));
        vcdp->chgBit(c+2809,(vlTOPp->top__DOT__debugger_inst__DOT__axi_detector_debugger_inst__DOT__r_bvalid));
        vcdp->chgBit(c+2817,(vlTOPp->top__DOT__debugger_inst__DOT__axi_detector_debugger_inst__DOT__r_rvalid));
        vcdp->chgBit(c+2825,(vlTOPp->top__DOT__debugger_inst__DOT__axi_detector_debugger_inst__DOT__detected));
        vcdp->chgBit(c+2833,(vlTOPp->top__DOT__debugger_inst__DOT__axi_detector_debugger_inst__DOT__write));
        vcdp->chgBus(c+2841,(vlTOPp->top__DOT__memory_inst__DOT__rdata_temp),32);
        vcdp->chgBus(c+2849,(vlSymsp->TOP__top__DOT__if_axi_light_memory.rresp),2);
        vcdp->chgBit(c+2857,(vlSymsp->TOP__top__DOT__if_axi_light_debugger.awvalid));
        vcdp->chgBit(c+2865,(vlSymsp->TOP__top__DOT__if_axi_light_debugger.awready));
        vcdp->chgBus(c+2873,(vlSymsp->TOP__top__DOT__if_axi_light_debugger.awaddr),32);
        vcdp->chgBus(c+2881,(vlSymsp->TOP__top__DOT__if_axi_light_debugger.awprot),3);
        vcdp->chgBit(c+2889,(vlSymsp->TOP__top__DOT__if_axi_light_debugger.wvalid));
        vcdp->chgBit(c+2897,(vlSymsp->TOP__top__DOT__if_axi_light_debugger.wready));
        vcdp->chgBus(c+2905,(vlSymsp->TOP__top__DOT__if_axi_light_debugger.wdata),32);
        vcdp->chgBus(c+2913,(vlSymsp->TOP__top__DOT__if_axi_light_debugger.wstrb),4);
        vcdp->chgBit(c+2921,(vlSymsp->TOP__top__DOT__if_axi_light_memory.awvalid));
        vcdp->chgBit(c+2929,(vlSymsp->TOP__top__DOT__if_axi_light_memory.awready));
        vcdp->chgBus(c+2937,(vlSymsp->TOP__top__DOT__if_axi_light_memory.awaddr),32);
        vcdp->chgBus(c+2945,(vlSymsp->TOP__top__DOT__if_axi_light_memory.awprot),3);
        vcdp->chgBit(c+2953,(vlSymsp->TOP__top__DOT__if_axi_light_memory.wvalid));
        vcdp->chgBit(c+2961,(vlSymsp->TOP__top__DOT__if_axi_light_memory.wready));
        vcdp->chgBus(c+2969,(vlSymsp->TOP__top__DOT__if_axi_light_memory.wdata),32);
        vcdp->chgBus(c+2977,(vlSymsp->TOP__top__DOT__if_axi_light_memory.wstrb),4);
        vcdp->chgBit(c+2985,(vlSymsp->TOP__top__DOT__if_axi_light_memory.bvalid));
        vcdp->chgBus(c+2993,(vlSymsp->TOP__top__DOT__if_axi_light_memory.bresp),2);
    }
}

void Vtop::traceChgThis__5(Vtop__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) {
    Vtop* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    int c = code;
    if (0 && vcdp && c) {}  // Prevent unused
    // Body
    {
        vcdp->chgBit(c+3001,(vlTOPp->clk));
        vcdp->chgBit(c+3009,(vlTOPp->res_n));
        vcdp->chgBit(c+3017,(vlTOPp->fin));
        vcdp->chgBit(c+3025,(vlTOPp->debugger_sig));
        vcdp->chgBus(c+3033,(vlTOPp->debugger_ascii),7);
        vcdp->chgBit(c+3041,(vlTOPp->w));
        vcdp->chgBus(c+3049,(vlTOPp->w_index),32);
        vcdp->chgBit(c+3057,(vlTOPp->trap));
        vcdp->chgBit(c+3065,(vlTOPp->ill_awaddr_out_of_range));
        vcdp->chgBit(c+3073,(vlTOPp->ill_araddr_out_of_range));
    }
}
