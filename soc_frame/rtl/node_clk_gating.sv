
/* ****************************************************************************
  This Source Code Form is subject to the terms of the
  Open Hardware Description License, v. 1.0. If a copy
  of the OHDL was not distributed with this file, You
  can obtain one at http://juliusbaxter.net/ohdl/ohdl.txt
  
  Copyright (C) 2019 Stefan Huemer <stefan@huemer.tech>
  
***************************************************************************** */

module node #(
    
     parameter ID = 0
    
    ,parameter SEND_TO = 0
    ,parameter BIG = 0
)
(
     input clk
    ,input res_n
    
    ,output trap
    
    ,if_connect.bridge    noc
);
    
    if_axi_light #(.AXI_WSTRB_WIDTH(`AXI_WSTRB_WIDTH)) if_axi_light_cpu_to_detector();
    if_axi_light #() if_axi_light_detector_to_offset();
    
    if_axi_light #() if_axi_light_offset_to_mux();
    if_axi_light #() if_axi_light_self_awareness_to_mux();
    
    if_axi_light #() if_axi_light_mux_to_slave_bridge();
    
    wire w_activate;
    wire [ `AXI_ADDR_WIDTH-1:0 ] w_axi_offset;
    
    wire w_fin;
    
    //~ wire w_clk = clk && w_activate;
    
    wire w_clk_gated;
    wire w_res_n_gated;
    
    // -------------------------------------------------------------------------
    // C L K _ G A T E R
    // -------------------------------------------------------------------------
    
    clk_gater #() clk_gater_inst
    (
         .clk( clk )
        ,.res_n( w_activate )
        
        ,.clk_gated( w_clk_gated )
        ,.res_n_gated( w_res_n_gated )
    );
    
    // -------------------------------------------------------------------------
    // P I C O
    // -------------------------------------------------------------------------
    
    picorv32_if_wrapper
    #(
         .ENABLE_MUL ( BIG )
        ,.ENABLE_DIV ( BIG )
    )
    picorv32_if_wrapper_inst
    (
         .clk( w_clk_gated )
        ,.res_n( w_res_n_gated )
        
        ,.trap( trap )
        
        ,.m_axi( if_axi_light_cpu_to_detector.master )
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
         .clk( w_clk_gated )
        ,.res_n( w_res_n_gated )
        
        ,.s_axi( if_axi_light_cpu_to_detector.slave )
        ,.m_axi( if_axi_light_detector_to_offset.master )
        
        ,.sig( w_fin )
        ,.data(  )
    );
    
    // -------------------------------------------------------------------------
    // A X I _ O F F S E T
    // -------------------------------------------------------------------------
    
    axi_offset
    #(
         .OFFSET( 0 )
        ,.USE_PARAMETER( 0 )
    )
    axi_offset_inst
    (
         .s_axi( if_axi_light_detector_to_offset.slave )
        ,.m_axi( if_axi_light_offset_to_mux.master )
        
        ,.offset( w_axi_offset )
    );
    
    // -------------------------------------------------------------------------
    // S E L F _ A W A R E N E S S
    // -------------------------------------------------------------------------
    
    self_awareness
    #(
         .ID( ID )
    )
    self_awareness_inst
    (
         .clk( clk )
        ,.res_n( res_n )
        
        ,.activate( w_activate )
        ,.axi_offset( w_axi_offset )
        
        ,.fin( w_fin )
        
        ,.m_axi( if_axi_light_self_awareness_to_mux.master )
    );
    
    // -------------------------------------------------------------------------
    // A X I _ M U X
    // -------------------------------------------------------------------------
    
    axi_mux #() axi_mux_inst
    (
         .selector( w_activate )
        
        ,.s_axi_0( if_axi_light_self_awareness_to_mux.slave )
        ,.s_axi_1( if_axi_light_offset_to_mux.slave )
        
        ,.m_axi_0( if_axi_light_mux_to_slave_bridge.master )
    );
    
    // -------------------------------------------------------------------------
    // S L A V E _ B R I D G E
    // -------------------------------------------------------------------------
    
    bridge_slave
    #(
         .ID( ID )
        
        ,.SEND_TO( SEND_TO )
    )
    bridge_slave_inst
    (
         .clk( clk )
        ,.res_n( res_n )
        
        ,.s_axi( if_axi_light_mux_to_slave_bridge.slave )
        ,.noc( noc )
    );

endmodule
