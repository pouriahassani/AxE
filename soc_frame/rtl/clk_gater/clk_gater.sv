
/* ****************************************************************************
  This Source Code Form is subject to the terms of the
  Open Hardware Description License, v. 1.0. If a copy
  of the OHDL was not distributed with this file, You
  can obtain one at http://juliusbaxter.net/ohdl/ohdl.txt
  
  Copyright (C) 2019 Stefan Huemer <stefan@huemer.tech>
  
***************************************************************************** */

// this module is also responsible for the reset.

module clk_gater
#()
(
     input clk
    ,input res_n
    
    ,output clk_gated
    ,output reg res_n_gated
    
);

`ifdef SYNTHESIS
    
    // this is for Xilinx
    
    BUFGCE bufgce_i0
    (
        .I( clk )
       ,.CE( clk_en )
       ,.O( clk_gated )
    );
    
    wire clk_en;
    
    assign clk_en = ( state == IDLE ) ? 1'b0 : 1'b1;
    
`else
    
    assign clk_gated = ( state == IDLE ) ? 1'b0 : clk;
    
`endif

enum
{
     IDLE
    ,CLK
    ,RES_N
}state;

integer i;

initial
begin
    
    state = IDLE;
    
end

always @ ( posedge clk )
begin : clk_gater_proc
    
    res_n_gated = 1'b0;
    
    case(state)
    
    // ---------------------------------------------------------------------
    // IDLE
    // ---------------------------------------------------------------------
    
    IDLE :
    begin
        
        // when the reset is deasserted, the state will change.
        
        i = 0;
        
        if ( res_n == 1'b1 ) state = CLK;
        
    end
    
    // ---------------------------------------------------------------------
    // CLK
    // ---------------------------------------------------------------------
    
    // TODO - rename state to res_n_delay
    
    CLK :
    begin
        
        // the reset is deasserted after a delay. without this, the PicoRV32
        // does not start.
        // 10 is just an arbitrary number and a lower one might also work.
        
        i = i + 1;
        
        if ( i == 10 ) state = RES_N;
        
    end
    
    // ---------------------------------------------------------------------
    // RES_N
    // ---------------------------------------------------------------------
    
    RES_N :
    begin
        
        res_n_gated = 1'b1;
        
        if ( res_n == 1'b0 ) state = IDLE;
        
    end
    
    // ---------------------------------------------------------------------
    // DEFAULT
    // ---------------------------------------------------------------------
    
    default : state = IDLE;
    
    endcase

    
end

endmodule
 
