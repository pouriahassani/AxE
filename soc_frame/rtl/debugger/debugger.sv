
/* ****************************************************************************
  This Source Code Form is subject to the terms of the
  Open Hardware Description License, v. 1.0. If a copy
  of the OHDL was not distributed with this file, You
  can obtain one at http://juliusbaxter.net/ohdl/ohdl.txt
  
  Copyright (C) 2019 Stefan Huemer <stefan@huemer.tech>
  
***************************************************************************** */

// once a certain WDATA and AWADDR combination is detected the output signal is
// asserted for 1 clk cycle.

module debugger #(
    
     parameter ACTIVE = 0
    
)
(
     input clk
    ,input res_n
    
    ,input busy
    
    ,if_axi_light.slave  s_axi
    ,if_axi_light.master m_axi
    
    ,output reg sig
    ,output reg [ `ASCII_WIDTH-1:0 ] ascii
);
    
    axi_detector
    #(
         .ADDR_DETECT ( 32'h 0000_0000 )
        
        ,.DETECT_READ( 0 )
        ,.DETECT_WRITE( ACTIVE )
        
        ,.GREATER_THAN( 0 )
        
        ,.SIGNAL_PULSE( 1 )
        ,.FORWARD( 0 )
    )
    axi_detector_debugger_inst
    (
         .clk( clk )
        ,.res_n( res_n )
        
        ,.s_axi( s_axi )
        ,.m_axi( m_axi )
        
        ,.sig( sig )
        ,.data( ascii )
    );
    
endmodule
