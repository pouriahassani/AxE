
/* ****************************************************************************
  This Source Code Form is subject to the terms of the
  Open Hardware Description License, v. 1.0. If a copy
  of the OHDL was not distributed with this file, You
  can obtain one at http://juliusbaxter.net/ohdl/ohdl.txt
  
  Copyright (C) 2019 Stefan Huemer <stefan@huemer.tech>
  
***************************************************************************** */

module controller #(
    
     parameter ID = 0
    
    ,parameter SEND_TO = 0
    
)
(
     input clk
    ,input res_n
    
    ,output trap
    
    ,if_axi_light.master   if_axi_controller_master
    
    //~ ,(* mark_debug = "true" *) output debugger_sig
    //~ ,(* mark_debug = "true" *) output [ `ASCII_WIDTH-1:0 ] debugger_ascii
    ,output debugger_sig
    ,output [ `ASCII_WIDTH-1:0 ] debugger_ascii
);
    
    if_axi_light #( .AXI_WSTRB_WIDTH(`AXI_WSTRB_WIDTH) ) if_axi_light_cpu_to_debugger();
    if_axi_light #( .AXI_WSTRB_WIDTH(`AXI_WSTRB_WIDTH) ) if_axi_light_debugger_to_offset();
    
    // -------------------------------------------------------------------------
    // P I C O
    // -------------------------------------------------------------------------
    
    picorv32_if_wrapper
    #(
         .ENABLE_MUL ( 1 )
        ,.ENABLE_DIV ( 1 )
    )
    picorv32_if_wrapper_inst
    (
         .clk( clk )
        ,.res_n( res_n )
        
        ,.trap( trap )
        
        ,.m_axi( if_axi_light_cpu_to_debugger.master )
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
        
        ,.s_axi( if_axi_light_cpu_to_debugger.slave )
        ,.m_axi( if_axi_controller_master )
        
        ,.sig( debugger_sig )
        ,.ascii( debugger_ascii )
    );
    
endmodule
