
/* ****************************************************************************
  This Source Code Form is subject to the terms of the
  Open Hardware Description License, v. 1.0. If a copy
  of the OHDL was not distributed with this file, You
  can obtain one at http://juliusbaxter.net/ohdl/ohdl.txt
  
  Copyright (C) 2019 Stefan Huemer <stefan@huemer.tech>
  
***************************************************************************** */

`include "defines_axi.vh"
`include "defines_mem.vh"
`include "defines_ascii.vh"

`include "../../rtl/interfaces/if_axi_light.sv"

`include "../../rtl/axi_detector/axi_detector.sv"

`include "../../rtl/pico/picorv32.v"

`ifdef INCISIVE
    
    `include "../../rtl/pico/picorv32_if_wrapper_cadence.sv"
    
    `include "../../rtl/memory_asic/memory_latch1.sv"
    `include "../../rtl/memory_asic/latch_register_file.sv"
    `include "../../rtl/memory_asic/latch_register_file_wrapper.sv"
    `include "../../rtl/memory_asic/cluster_clock_gating.sv"
    
`else
    
    `include "../../rtl/pico/picorv32_if_wrapper.sv"
    
    `include "../../rtl/memory/memory_mem_packer.sv"
    
`endif

`include "../../rtl/debugger/debugger.sv"

module top
(
     input clk
    ,input res_n
    
    `ifdef INCISIVE
        ,input res_n_pico
    `endif
    
    ,output fin
    
    // debugging
    
    ,output debugger_sig
    ,output [ `ASCII_WIDTH-1:0 ] debugger_ascii
    
    ,output w
    ,output [ `AXI_ADDR_WIDTH-1:0 ] w_index
    
    // pico
    
    ,output trap
    
    // memory
    
    ,output ill_awaddr_out_of_range
    ,output ill_araddr_out_of_range
    
    // load memory
    
    `ifdef INCISIVE
        ,input we_ext // write enable (active high)
        ,input [ `AXI_DATA_WIDTH-1 : 0 ] dload_data
        ,input [ `AXI_ADDR_WIDTH-1 : 0 ] dload_addr
    `endif
);
    
    // -------------------------------------------------------------------------
    // INTERFACES
    // -------------------------------------------------------------------------
    
    if_axi_light #() if_axi_light_axi_detector();
    if_axi_light #() if_axi_light_debugger();
    if_axi_light #() if_axi_light_memory();
    
    // -------------------------------------------------------------------------
    // P I C O
    // -------------------------------------------------------------------------
    
    picorv32_if_wrapper
    #(
         .ENABLE_MUL ( 0 )
        ,.ENABLE_DIV ( 0 )
        
        //~ ,.STACKADDR( 32'h ffff_fff0 )
        ,.STACKADDR( 32'h 0001_0000 )
        //~ ,.STACKADDR( 32'h FFFF_FFFF )
    )
    picorv32_if_wrapper_inst
    (
         .clk( clk )
        
        `ifdef INCISIVE ,.res_n( res_n_pico )
        `else           ,.res_n( res_n )
        `endif
        
        //~ ,.m_axi( if_axi_light_debugger.master )
        ,.m_axi( if_axi_light_axi_detector.master )
        
        ,.trap( trap )
    );
    
    // -------------------------------------------------------------------------
    // A X I _ D E T E C T O R
    // -------------------------------------------------------------------------
    
    axi_detector
    #(
         .ADDR_DETECT ( 32'h 00FF_FFFC )
        
        ,.DETECT_READ( 0 )
        ,.DETECT_WRITE( 1 )
        
        ,.GREATER_THAN( 0 )
        
        ,.SIGNAL_PULSE( 1 )
        ,.FORWARD( 0 )
    )
    axi_detector_inst
    (
         .clk( clk )
        ,.res_n( res_n )
        
        ,.s_axi( if_axi_light_axi_detector.slave )
        ,.m_axi( if_axi_light_debugger.master )
        
        ,.sig( fin )
    );
    
    // -------------------------------------------------------------------------
    // D E B U G G E R
    // -------------------------------------------------------------------------
    
    debugger
    #(
         .ACTIVE( 1 )
    )
    debugger_inst
    (
         .clk( clk )
        ,.res_n( res_n )
        
        ,.s_axi( if_axi_light_debugger.slave )
        ,.m_axi( if_axi_light_memory.master )
        
        ,.sig( debugger_sig )
        ,.ascii( debugger_ascii )
    );
    
    // -------------------------------------------------------------------------
    // M E M O R Y
    // -------------------------------------------------------------------------
    
    memory
    #(
        `ifdef INCISIVE 
            .ADDR_DETECT( 0 )
        `endif
    )
    memory_inst
    (
         .clk( clk )
        ,.res_n( res_n )
        
        ,.s_axi( if_axi_light_memory.slave )
        
        ,.w( w )
        ,.w_index( w_index )
        
        ,.ill_awaddr_out_of_range( ill_awaddr_out_of_range )
        ,.ill_araddr_out_of_range( ill_araddr_out_of_range )
        
        `ifdef INCISIVE
            
            // added ports
            ,.we_ext(we_ext)
            ,.dload_data(dload_data)
            ,.dload_addr(dload_addr)
            
        `endif
        
        // degub signals
        //~ ,.sig( debugger_sig_c )
        //~ ,.ascii( debugger_ascii_c )
    );
    
endmodule
