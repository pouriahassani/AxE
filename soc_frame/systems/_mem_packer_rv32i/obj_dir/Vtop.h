// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Primary design header
//
// This header should be included by all source files instantiating the design.
// The class here is then constructed to instantiate the design.
// See the Verilator manual for examples.

#ifndef _VTOP_H_
#define _VTOP_H_  // guard

#include "verilated_heavy.h"

//==========

class Vtop__Syms;
class Vtop_VerilatedVcd;
class Vtop_if_axi_light;


//----------

VL_MODULE(Vtop) {
  public:
    // CELLS
    // Public to allow access to /*verilator_public*/ items;
    // otherwise the application code can consider these internals.
    Vtop_if_axi_light* __PVT__top__DOT__if_axi_light_axi_detector;
    Vtop_if_axi_light* __PVT__top__DOT__if_axi_light_debugger;
    Vtop_if_axi_light* __PVT__top__DOT__if_axi_light_memory;
    
    // PORTS
    // The application code writes and reads these signals to
    // propagate new values into/out from the Verilated model.
    VL_IN8(clk,0,0);
    VL_IN8(res_n,0,0);
    VL_OUT8(fin,0,0);
    VL_OUT8(debugger_sig,0,0);
    VL_OUT8(debugger_ascii,6,0);
    VL_OUT8(w,0,0);
    VL_OUT8(trap,0,0);
    VL_OUT8(ill_awaddr_out_of_range,0,0);
    VL_OUT8(ill_araddr_out_of_range,0,0);
    VL_OUT(w_index,31,0);
    
    // LOCAL SIGNALS
    // Internals; generally not touched by application code
    // Anonymous structures to workaround compiler member-count bugs
    struct {
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__pcpi_valid;
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__pcpi_wr;
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__pcpi_wait;
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__pcpi_ready;
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__trace_valid;
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__mem_valid;
        CData/*3:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__mem_wstrb;
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__mem_instr;
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__mem_ready;
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__axi_adapter__DOT__ack_awvalid;
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__axi_adapter__DOT__ack_arvalid;
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__axi_adapter__DOT__ack_wvalid;
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__axi_adapter__DOT__xfer_done;
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__mem_la_read;
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__mem_la_write;
        CData/*3:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__mem_la_wstrb;
        CData/*4:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__reg_sh;
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__irq_delay;
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__irq_active;
        CData/*1:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__mem_state;
        CData/*1:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__mem_wordsize;
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__mem_do_prefetch;
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__mem_do_rinst;
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__mem_do_rdata;
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__mem_do_wdata;
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__mem_xfer;
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__mem_la_secondword;
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__mem_la_firstword_reg;
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__last_mem_valid;
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__prefetched_high_word;
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__clear_prefetched_high_word;
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__mem_done;
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__instr_lui;
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__instr_auipc;
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__instr_jal;
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__instr_jalr;
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__instr_beq;
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__instr_bne;
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__instr_blt;
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__instr_bge;
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__instr_bltu;
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__instr_bgeu;
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__instr_lb;
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__instr_lh;
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__instr_lw;
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__instr_lbu;
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__instr_lhu;
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__instr_sb;
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__instr_sh;
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__instr_sw;
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__instr_addi;
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__instr_slti;
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__instr_sltiu;
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__instr_xori;
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__instr_ori;
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__instr_andi;
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__instr_slli;
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__instr_srli;
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__instr_srai;
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__instr_add;
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__instr_sub;
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__instr_sll;
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__instr_slt;
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__instr_sltu;
    };
    struct {
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__instr_xor;
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__instr_srl;
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__instr_sra;
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__instr_or;
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__instr_and;
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__instr_rdcycle;
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__instr_rdcycleh;
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__instr_rdinstr;
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__instr_rdinstrh;
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__instr_ecall_ebreak;
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__instr_getq;
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__instr_setq;
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__instr_retirq;
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__instr_maskirq;
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__instr_waitirq;
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__instr_timer;
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__instr_trap;
        CData/*4:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__decoded_rd;
        CData/*4:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__decoded_rs1;
        CData/*4:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__decoded_rs2;
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__decoder_trigger;
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__decoder_trigger_q;
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__decoder_pseudo_trigger;
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__decoder_pseudo_trigger_q;
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__compressed_instr;
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__is_lui_auipc_jal;
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__is_lb_lh_lw_lbu_lhu;
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__is_slli_srli_srai;
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__is_jalr_addi_slti_sltiu_xori_ori_andi;
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__is_sb_sh_sw;
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__is_sll_srl_sra;
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__is_lui_auipc_jal_jalr_addi_add_sub;
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__is_slti_blt_slt;
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__is_sltiu_bltu_sltu;
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__is_beq_bne_blt_bge_bltu_bgeu;
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__is_lbu_lhu_lw;
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__is_alu_reg_imm;
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__is_alu_reg_reg;
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__is_compare;
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__is_rdcycle_rdcycleh_rdinstr_rdinstrh;
        CData/*4:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__dbg_insn_rs1;
        CData/*4:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__dbg_insn_rs2;
        CData/*4:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__dbg_insn_rd;
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__dbg_rs1val_valid;
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__dbg_rs2val_valid;
        CData/*4:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__q_insn_rs1;
        CData/*4:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__q_insn_rs2;
        CData/*4:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__q_insn_rd;
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__dbg_next;
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__launch_next_insn;
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__dbg_valid_insn;
        CData/*4:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__cached_insn_rs1;
        CData/*4:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__cached_insn_rs2;
        CData/*4:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__cached_insn_rd;
        CData/*7:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__cpu_state;
        CData/*1:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__irq_state;
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__set_mem_do_rinst;
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__set_mem_do_rdata;
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__set_mem_do_wdata;
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__latched_store;
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__latched_stalu;
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__latched_branch;
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__latched_compr;
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__latched_trace;
    };
    struct {
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__latched_is_lu;
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__latched_is_lh;
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__latched_is_lb;
        CData/*4:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__latched_rd;
        CData/*3:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__pcpi_timeout_counter;
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__pcpi_timeout;
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__do_waitirq;
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__alu_out_0;
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__alu_out_0_q;
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__alu_wait;
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__alu_wait_2;
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__alu_eq;
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__alu_ltu;
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__alu_lts;
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__clear_prefetched_high_word_q;
        CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__cpuregs_write;
        CData/*2:0*/ top__DOT__axi_detector_inst__DOT__latched_awprot;
        CData/*3:0*/ top__DOT__axi_detector_inst__DOT__latched_wstrb;
        CData/*2:0*/ top__DOT__axi_detector_inst__DOT__latched_arprot;
        CData/*0:0*/ top__DOT__axi_detector_inst__DOT__done;
        CData/*0:0*/ top__DOT__axi_detector_inst__DOT__resp_from;
        CData/*0:0*/ top__DOT__axi_detector_inst__DOT__r_bvalid;
        CData/*0:0*/ top__DOT__axi_detector_inst__DOT__r_rvalid;
        CData/*0:0*/ top__DOT__axi_detector_inst__DOT__detected;
        CData/*0:0*/ top__DOT__axi_detector_inst__DOT__write;
        CData/*0:0*/ top__DOT__debugger_inst__DOT__busy;
        CData/*2:0*/ top__DOT__debugger_inst__DOT__axi_detector_debugger_inst__DOT__latched_awprot;
        CData/*3:0*/ top__DOT__debugger_inst__DOT__axi_detector_debugger_inst__DOT__latched_wstrb;
        CData/*2:0*/ top__DOT__debugger_inst__DOT__axi_detector_debugger_inst__DOT__latched_arprot;
        CData/*0:0*/ top__DOT__debugger_inst__DOT__axi_detector_debugger_inst__DOT__done;
        CData/*0:0*/ top__DOT__debugger_inst__DOT__axi_detector_debugger_inst__DOT__resp_from;
        CData/*0:0*/ top__DOT__debugger_inst__DOT__axi_detector_debugger_inst__DOT__r_bvalid;
        CData/*0:0*/ top__DOT__debugger_inst__DOT__axi_detector_debugger_inst__DOT__r_rvalid;
        CData/*0:0*/ top__DOT__debugger_inst__DOT__axi_detector_debugger_inst__DOT__detected;
        CData/*0:0*/ top__DOT__debugger_inst__DOT__axi_detector_debugger_inst__DOT__write;
        CData/*2:0*/ top__DOT__memory_inst__DOT__latched_awprot;
        CData/*3:0*/ top__DOT__memory_inst__DOT__latched_wstrb;
        CData/*2:0*/ top__DOT__memory_inst__DOT__latched_arprot;
        CData/*1:0*/ top__DOT__memory_inst__DOT__status;
        CData/*0:0*/ top__DOT__memory_inst__DOT__done;
        SData/*15:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__mem_16bit_buffer;
        IData/*31:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__pcpi_insn;
        IData/*31:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__pcpi_rd;
        IData/*31:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__irq;
        IData/*31:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__eoi;
        IData/*31:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__mem_addr;
        IData/*31:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__mem_wdata;
        IData/*31:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__mem_la_wdata;
        IData/*31:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__reg_pc;
        IData/*31:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__reg_next_pc;
        IData/*31:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__reg_op1;
        IData/*31:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__reg_op2;
        IData/*31:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__reg_out;
        IData/*31:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__next_insn_opcode;
        IData/*31:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__dbg_insn_opcode;
        IData/*31:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__dbg_insn_addr;
        IData/*31:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__next_pc;
        IData/*31:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__irq_mask;
        IData/*31:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__irq_pending;
        IData/*31:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__timer;
        IData/*31:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__i;
        IData/*31:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__mem_rdata_word;
        IData/*31:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__mem_rdata_q;
        IData/*31:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__mem_rdata_latched_noshuffle;
    };
    struct {
        IData/*31:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__decoded_imm;
        IData/*31:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__decoded_imm_uj;
        IData/*31:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__dbg_insn_imm;
        IData/*31:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__dbg_rs1val;
        IData/*31:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__dbg_rs2val;
        IData/*31:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__q_insn_imm;
        IData/*31:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__q_insn_opcode;
        IData/*31:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__cached_insn_imm;
        IData/*31:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__cached_insn_opcode;
        WData/*127:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__dbg_ascii_state[4];
        IData/*31:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__current_pc;
        IData/*31:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__next_irq_pending;
        IData/*31:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__alu_out;
        IData/*31:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__alu_out_q;
        IData/*31:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__cpuregs_wrdata;
        IData/*31:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__cpuregs_rs1;
        IData/*31:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__cpuregs_rs2;
        IData/*31:0*/ top__DOT__axi_detector_inst__DOT__data;
        IData/*31:0*/ top__DOT__axi_detector_inst__DOT__state;
        IData/*31:0*/ top__DOT__axi_detector_inst__DOT__latched_awaddr;
        IData/*31:0*/ top__DOT__axi_detector_inst__DOT__latched_wdata;
        IData/*31:0*/ top__DOT__axi_detector_inst__DOT__latched_araddr;
        IData/*31:0*/ top__DOT__axi_detector_inst__DOT__addr_to_check;
        IData/*31:0*/ top__DOT__debugger_inst__DOT__axi_detector_debugger_inst__DOT__state;
        IData/*31:0*/ top__DOT__debugger_inst__DOT__axi_detector_debugger_inst__DOT__latched_awaddr;
        IData/*31:0*/ top__DOT__debugger_inst__DOT__axi_detector_debugger_inst__DOT__latched_wdata;
        IData/*31:0*/ top__DOT__debugger_inst__DOT__axi_detector_debugger_inst__DOT__latched_araddr;
        IData/*31:0*/ top__DOT__debugger_inst__DOT__axi_detector_debugger_inst__DOT__addr_to_check;
        IData/*31:0*/ top__DOT__memory_inst__DOT__state;
        IData/*31:0*/ top__DOT__memory_inst__DOT__latched_awaddr;
        IData/*31:0*/ top__DOT__memory_inst__DOT__latched_wdata;
        IData/*31:0*/ top__DOT__memory_inst__DOT__latched_araddr;
        IData/*31:0*/ top__DOT__memory_inst__DOT__index;
        IData/*31:0*/ top__DOT__memory_inst__DOT__rdata_temp;
        QData/*35:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__trace_data;
        QData/*63:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__count_cycle;
        QData/*63:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__count_instr;
        QData/*63:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__new_ascii_instr;
        QData/*63:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__dbg_ascii_instr;
        QData/*63:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__q_ascii_instr;
        QData/*63:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__cached_ascii_instr;
        IData/*31:0*/ top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__cpuregs[32];
        IData/*31:0*/ top__DOT__memory_inst__DOT__mem[120192];
    };
    
    // LOCAL VARIABLES
    // Internals; generally not touched by application code
    CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT____Vcellout__picorv32_axi_inst__mem_axi_arvalid;
    CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT____Vcellout__picorv32_axi_inst__mem_axi_wvalid;
    CData/*0:0*/ top__DOT__picorv32_if_wrapper_inst__DOT____Vcellout__picorv32_axi_inst__mem_axi_awvalid;
    CData/*7:0*/ top__DOT__memory_inst__DOT____Vlvbound1;
    CData/*7:0*/ top__DOT__memory_inst__DOT____Vlvbound2;
    CData/*7:0*/ top__DOT__memory_inst__DOT____Vlvbound3;
    CData/*7:0*/ top__DOT__memory_inst__DOT____Vlvbound4;
    CData/*7:0*/ __Vtableidx1;
    CData/*0:0*/ __Vclklast__TOP__clk;
    IData/*31:0*/ top__DOT__debugger_inst__DOT____Vcellout__axi_detector_debugger_inst__data;
    IData/*31:0*/ __Vm_traceActivity;
    static WData/*127:0*/ __Vtable1_top__DOT__picorv32_if_wrapper_inst__DOT__picorv32_axi_inst__DOT__picorv32_core__DOT__dbg_ascii_state[256][4];
    
    // INTERNAL VARIABLES
    // Internals; generally not touched by application code
    Vtop__Syms* __VlSymsp;  // Symbol table
    
    // CONSTRUCTORS
  private:
    VL_UNCOPYABLE(Vtop);  ///< Copying not allowed
  public:
    /// Construct the model; called by application code
    /// The special name  may be used to make a wrapper with a
    /// single model invisible with respect to DPI scope names.
    Vtop(const char* name = "TOP");
    /// Destroy the model; called (often implicitly) by application code
    ~Vtop();
    /// Trace signals in the model; called by application code
    void trace(VerilatedVcdC* tfp, int levels, int options = 0);
    
    // API METHODS
    /// Evaluate the model.  Application must call when inputs change.
    void eval();
    /// Simulation complete, run final blocks.  Application must call on completion.
    void final();
    
    // INTERNAL METHODS
  private:
    static void _eval_initial_loop(Vtop__Syms* __restrict vlSymsp);
  public:
    void __Vconfigure(Vtop__Syms* symsp, bool first);
  private:
    static QData _change_request(Vtop__Syms* __restrict vlSymsp);
  public:
    static void _combo__TOP__4(Vtop__Syms* __restrict vlSymsp);
  private:
    void _ctor_var_reset() VL_ATTR_COLD;
  public:
    static void _eval(Vtop__Syms* __restrict vlSymsp);
  private:
#ifdef VL_DEBUG
    void _eval_debug_assertions();
#endif  // VL_DEBUG
  public:
    static void _eval_initial(Vtop__Syms* __restrict vlSymsp) VL_ATTR_COLD;
    static void _eval_settle(Vtop__Syms* __restrict vlSymsp) VL_ATTR_COLD;
    static void _initial__TOP__1(Vtop__Syms* __restrict vlSymsp) VL_ATTR_COLD;
    static void _sequent__TOP__2(Vtop__Syms* __restrict vlSymsp);
    static void _settle__TOP__3(Vtop__Syms* __restrict vlSymsp) VL_ATTR_COLD;
    static void traceChgThis(Vtop__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code);
    static void traceChgThis__2(Vtop__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code);
    static void traceChgThis__3(Vtop__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code);
    static void traceChgThis__4(Vtop__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code);
    static void traceChgThis__5(Vtop__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code);
    static void traceFullThis(Vtop__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) VL_ATTR_COLD;
    static void traceFullThis__1(Vtop__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) VL_ATTR_COLD;
    static void traceInitThis(Vtop__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) VL_ATTR_COLD;
    static void traceInitThis__1(Vtop__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) VL_ATTR_COLD;
    static void traceInitThis__1__2(Vtop__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code, const char* scopep) VL_ATTR_COLD;
    static void traceInitThis__1__3(Vtop__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code, const char* scopep) VL_ATTR_COLD;
    static void traceInitThis__1__4(Vtop__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code, const char* scopep) VL_ATTR_COLD;
    static void traceInit(VerilatedVcd* vcdp, void* userthis, uint32_t code);
    static void traceFull(VerilatedVcd* vcdp, void* userthis, uint32_t code);
    static void traceChg(VerilatedVcd* vcdp, void* userthis, uint32_t code);
} VL_ATTR_ALIGNED(VL_CACHE_LINE_BYTES);

//----------


#endif  // guard
