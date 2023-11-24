
/* ****************************************************************************
  This Source Code Form is subject to the terms of the
  Open Hardware Description License, v. 1.0. If a copy
  of the OHDL was not distributed with this file, You
  can obtain one at http://juliusbaxter.net/ohdl/ohdl.txt
  
  Copyright (C) 2019 Stefan Huemer <stefan@huemer.tech>
  
***************************************************************************** */

module memory_controller
#()
(
     input clk
    ,input res_n
    
    ,if_axi_light.slave   if_axi_priority_input_slave
    
    ,if_connect.bridge    noc
    
    ,output reg [7:0] leds_status
    ,output reg [7:0] triggers
);
    
    if_axi_light #() if_axi_light_bridge_to_arbiter();
    if_axi_light #() if_axi_light_arbiter_to_detect_demux();
    if_axi_light #() if_axi_light_demux();
    if_axi_light #() if_axi_light_memory();
    if_axi_light #() if_axi_light_control();
    
    // wires
    
    wire w_data_to_bridge_avail;
    wire w_data_to_bridge_taken;
    
    wire w_data_from_bridge_avail;
    wire w_data_from_bridge_taken;
    
    wire [ `MERGED_REQUEST_WIDTH-1:0 ] w_merged_request_buffer_to_bridge;
    wire [ `MERGED_REQUEST_WIDTH-1:0 ] w_merged_request_bridge_to_buffer;
    
    // arbiter
    
    wire selector;
    
    // detector_demux
    
    wire sig_demux;
    
    // bram
    
    wire [31:0] w_bram_addr;
    
    wire [31:0] w_bram_wdata;
    wire [31:0] w_bram_rdata;
    
    wire        w_bram_read;
    wire        w_bram_write;
    
    wire        w_bram_done;
    
    // -------------------------------------------------------------------------
    // F L I T _ B U F F E R
    // -------------------------------------------------------------------------
    
    flit_buffer #() flit_buffer_inst
    (
         .clk( clk )
        ,.res_n( res_n )
        
        ,.noc( noc )
        
        ,.data_to_bridge_avail( w_data_to_bridge_avail )
        ,.data_to_bridge_taken( w_data_to_bridge_taken )
        
        ,.data_from_bridge_avail( w_data_from_bridge_avail )
        ,.data_from_bridge_taken( w_data_from_bridge_taken )
        
        ,.merged_request_buffer_to_bridge( w_merged_request_buffer_to_bridge )
        ,.merged_request_bridge_to_buffer( w_merged_request_bridge_to_buffer )
    );
    
    // -------------------------------------------------------------------------
    // M A S T E R _ B R I D G E
    // -------------------------------------------------------------------------
    
    bridge_master #() bridge_master_inst
    (
         .clk( clk )
        ,.res_n( res_n )
        
        ,.m_axi( if_axi_light_bridge_to_arbiter.master )
        
        ,.data_to_bridge_avail( w_data_to_bridge_avail )
        ,.data_to_bridge_taken( w_data_to_bridge_taken )
        
        ,.data_from_bridge_avail( w_data_from_bridge_avail )
        ,.data_from_bridge_taken( w_data_from_bridge_taken )
        
        ,.merged_request_buffer_to_bridge( w_merged_request_buffer_to_bridge )
        ,.merged_request_bridge_to_buffer( w_merged_request_bridge_to_buffer )
    );
    
    // -------------------------------------------------------------------------
    // A X I _ A R B I T E R
    // -------------------------------------------------------------------------
    
    axi_arbiter #() axi_arbiter_inst
    (
         .clk( clk )
        ,.res_n( res_n )
        
        ,.s_axi_0( if_axi_light_bridge_to_arbiter.slave )
        ,.s_axi_1( if_axi_priority_input_slave )
        
        ,.m_axi( if_axi_light_arbiter_to_detect_demux.master )
    );
    
    // -------------------------------------------------------------------------
    // A X I _ D E M U X
    // -------------------------------------------------------------------------
    
    // everything above CUT_OFF is reserved for the control.
    
    axi_detector
    #(
         .ADDR_DETECT ( 32'h 7FFF_FFFF - 1 )
        
        ,.DETECT_READ( 1 )
        ,.DETECT_WRITE( 1 )
        
        ,.GREATER_THAN( 1 )
        
        ,.SIGNAL_PULSE( 0 )
        ,.FORWARD( 1 )
    )
    axi_detector_demux_inst
    (
         .clk( clk )
        ,.res_n( res_n )
        
        ,.sig( sig_demux )
        
        ,.s_axi( if_axi_light_arbiter_to_detect_demux.slave )
        ,.m_axi( if_axi_light_demux.master )
        
    );
    
    axi_demux #() axi_demux_inst
    (
         .selector( sig_demux )
        
        ,.s_axi_0( if_axi_light_demux.slave )
        
        ,.m_axi_0( if_axi_light_memory.master )
        ,.m_axi_1( if_axi_light_control.master )
    );
    
    // -------------------------------------------------------------------------
    // M E M O R Y
    // -------------------------------------------------------------------------
    
    bram_controller #() bram_controller_inst
    (
         .clk( clk )
        ,.res_n( res_n )
        
        ,.s_axi( if_axi_light_memory.slave )
        
        ,.bram_addr  ( w_bram_addr  )
        ,.bram_wdata ( w_bram_wdata )
        ,.bram_rdata ( w_bram_rdata )
        ,.bram_read  ( w_bram_read  )
        ,.bram_write ( w_bram_write )
        ,.bram_done  ( w_bram_done  )
        
    );
    
    bram #() bram_inst
    (
         .clk( clk )
        ,.res_n( res_n )
        
        ,.addr  ( w_bram_addr  )
        ,.wdata ( w_bram_wdata )
        ,.rdata ( w_bram_rdata )
        ,.read  ( w_bram_read  )
        ,.write ( w_bram_write )
        ,.done  ( w_bram_done  )
    );
    
    // -------------------------------------------------------------------------
    // C O N T R O L
    // -------------------------------------------------------------------------
    
    control #() control_inst
    (
         .clk( clk )
        ,.res_n( res_n )
        
        ,.s_axi( if_axi_light_control.slave )
        
        ,.leds_status( leds_status )
        ,.triggers( triggers )
    );
    
endmodule
