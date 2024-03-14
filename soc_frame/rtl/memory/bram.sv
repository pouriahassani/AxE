
/* ****************************************************************************
  This Source Code Form is subject to the terms of the
  Open Hardware Description License, v. 1.0. If a copy
  of the OHDL was not distributed with this file, You
  can obtain one at http://juliusbaxter.net/ohdl/ohdl.txt

  Copyright (C) 2019 Stefan Huemer <stefan@huemer.tech>

***************************************************************************** */

module bram
#()
(
     input clk
    ,input res_n
    
    ,input      [31:0] addr
    
    ,input      [31:0] wdata
    ,output reg [31:0] rdata
    
    ,input             write
    ,input             read
    
    ,output reg        done
);

// in the log vivado will comment, that it saw the ram_style stuff, but not if
// this has been achieved or not.

(* ram_style = "block" *) reg[ `AXI_DATA_WIDTH-1:0 ] mem[ `MEM_SIZE-1:0 ];

reg [ 31:0 ] index;

assign index = addr >> 2;

initial begin
    
    // read the program to a memory array.
    
    $readmemh( "/home/user/soc_frame/mem.hex", mem,  0 );
    //~ $readmemh( "../../mem.hex", mem,  0 );
    
end

always @ ( posedge clk )
begin : proc_bram
    
    // the default state is that we CANNOT receive anything
    // and that there is no response.
    
    if ( ! res_n )
    begin
        
        done = 1'b0;
        
        rdata = 32'h 0000_0000;
        
    end
    else
    begin
        
        done = 1'b0;
        
        if ( read == 1'b1 )
        begin
            
            rdata = mem[ index ];
            done = 1'b1;
            
        end
        else if ( write == 1'b1 )
        begin
            
            mem[ index ] = wdata;
            done = 1'b1;
            
        end
        
    end
    
end

endmodule
