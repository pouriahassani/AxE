
/* ****************************************************************************
  This Source Code Form is subject to the terms of the
  Open Hardware Description License, v. 1.0. If a copy
  of the OHDL was not distributed with this file, You
  can obtain one at http://juliusbaxter.net/ohdl/ohdl.txt
  
  Copyright (C) 2019 Stefan Huemer <stefan@huemer.tech>
  
***************************************************************************** */

// this memory has an output that makes it possible to track to which addresses
// data has been written.

module memory
#()
(
     input clk
    ,input res_n
    
    ,if_axi_light.slave  s_axi
    
    // debug output
    
    ,output reg ill_awaddr_out_of_range
    ,output reg ill_araddr_out_of_range
    
    ,output reg w
    ,output reg [ `AXI_ADDR_WIDTH-1:0 ] w_index
);

enum
{
     IDLE
    ,WRITE
    ,WRITE_RESP
    ,READ
    ,READ_RESP
}state;

reg[ `AXI_ADDR_WIDTH-1:0 ] latched_awaddr = 'h0;
reg[                 2:0 ] latched_awprot = 'h0;

reg[ `AXI_DATA_WIDTH-1:0 ] latched_wdata = 'h0;
reg[`AXI_WSTRB_WIDTH-1:0 ] latched_wstrb = 'h0;

reg[ `AXI_ADDR_WIDTH-1:0 ] latched_araddr = 'h0;
reg[                 2:0 ] latched_arprot = 'h0;

reg[ `AXI_ADDR_WIDTH-1:0 ] index = 'h0;

reg[ 1:0 ] status = 2'b00;

reg[ `AXI_DATA_WIDTH-1:0 ] mem[ `MEM_SIZE-1:0 ];

reg[ `AXI_DATA_WIDTH-1:0 ] rdata_temp;

reg done = 1'b0;

initial begin
    
    // read the program to memory array.
    // $display("\nhere we read the program to memory array.: %d %d",`MEM_SIZE,`AXI_DATA_WIDTH);
    $readmemh( `MEM_PATH, mem,  0 );
    
    state = IDLE;
    
    ill_awaddr_out_of_range = 1'b0;
    ill_araddr_out_of_range = 1'b0;
    
    status = 2'b00;
    
end

always @ ( posedge clk )
begin : proc_memory
    
    // the default state is that we CANNOT receive anything
    // and that there is no response.
    
    s_axi.s_default();
    
    ill_awaddr_out_of_range = 1'b0;
    ill_araddr_out_of_range = 1'b0;
    
    w = 1'b0;
    
    case(state)
    
    // -------------------------------------------------------------------------
    // IDLE
    // -------------------------------------------------------------------------
    
    IDLE :
        begin
            
            status = `RESP_OKAY;
            //rdata_temp = 0;
            
            //---------------------
            // write
            //---------------------
            
            s_axi.write_req_wait( latched_awaddr, latched_awprot, latched_wdata, latched_wstrb, done );
            
            if ( done == 1'b1 )
            begin
                
                index = ( latched_awaddr>>2 );
                
                if ( ( latched_awaddr>>2 ) > `MEM_SIZE )
                    ill_awaddr_out_of_range = 1'b1;
                
                state = WRITE;
                
            end
            
            //---------------------
            // read
            //---------------------
            
            s_axi.read_req_wait( latched_araddr, latched_arprot, done );
            
            if ( done == 1'b1 )
            begin
                
                index = ( latched_araddr>>2 );
                
                if ( ( latched_araddr>>2 ) > `MEM_SIZE )
                    ill_araddr_out_of_range = 1'b1;
                
                state = READ;
                
            end
            
        end
    
    // -------------------------------------------------------------------------
    // WRITE
    // -------------------------------------------------------------------------
    
    WRITE :
        begin
            
            // latched data will not be resetted as it will be overwritten
            // anyway.
            // store data in the memory array.
            // return an error if the address is to big.
            
            if ( index < `MEM_SIZE )
            begin
                // strobe
                
                if ( latched_wstrb[0] == 1'b1 ) mem[ index ][  7: 0 ] = latched_wdata[  7: 0 ];
                if ( latched_wstrb[1] == 1'b1 ) mem[ index ][ 15: 8 ] = latched_wdata[ 15: 8 ];
                if ( latched_wstrb[2] == 1'b1 ) mem[ index ][ 23:16 ] = latched_wdata[ 23:16 ];
                if ( latched_wstrb[3] == 1'b1 ) mem[ index ][ 31:24 ] = latched_wdata[ 31:24 ];
                
                w = 1'b1;
                
                w_index = index;
                
                //~ mem[ index ] = latched_wdata;
            end
            else
                status = `RESP_SLVERR;
            
            state = WRITE_RESP;
            
        end
    
    // -------------------------------------------------------------------------
    // WRITE_RESP
    // -------------------------------------------------------------------------
    
    WRITE_RESP :
        begin
            
            s_axi.write_resp( status, done );
            
            if ( done == 1'b1 ) state = IDLE;
            
        end
    
    // -------------------------------------------------------------------------
    // READ
    // -------------------------------------------------------------------------
    
    READ :
        begin
            
            // save data from memory array to temp register.
            // this should allow a higher clk frequency as the memory is only
            // accessed once.
            
            if ( index < `MEM_SIZE )
                rdata_temp = mem[ index ];
            else
                status = `RESP_SLVERR;
            
            state = READ_RESP;
            
        end
    
    // -------------------------------------------------------------------------
    // READ_RESP
    // -------------------------------------------------------------------------
    
    READ_RESP :
        begin
            
            s_axi.read_resp( rdata_temp, status, done );
            if ( done == 1'b1 ) state = IDLE;
            
        end
    
    // -------------------------------------------------------------------------
    // DEFAULT
    // -------------------------------------------------------------------------
    
    default : state = IDLE;
    
    endcase
    
end

endmodule
