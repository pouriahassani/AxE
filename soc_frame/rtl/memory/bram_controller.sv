
`timescale 1ns / 1ps

/* ****************************************************************************
  This Source Code Form is subject to the terms of the
  Open Hardware Description License, v. 1.0. If a copy
  of the OHDL was not distributed with this file, You
  can obtain one at http://juliusbaxter.net/ohdl/ohdl.txt
  
  Copyright (C) 2019 Stefan Huemer <stefan@huemer.tech>
  
***************************************************************************** */

module bram_controller
#()
(
     input clk
    ,input res_n
    
    ,if_axi_light.slave  s_axi
    
    // bram
    
    ,output reg [31:0] bram_addr
    
    ,output reg [31:0] bram_wdata
    ,input      [31:0] bram_rdata
    
    ,output reg        bram_read
    ,output reg        bram_write
    
    ,input             bram_done
);

enum
{
     IDLE
    ,WRITE_READ
    ,WRITE_STRB
    ,WRITE
    ,WRITE_RESP
    ,READ
    ,READ_RESP
}state;

reg[ `AXI_ADDR_WIDTH-1:0 ] latched_awaddr;
reg[                 2:0 ] latched_awprot;

reg[ `AXI_DATA_WIDTH-1:0 ] latched_wdata;
reg[`AXI_WSTRB_WIDTH-1:0 ] latched_wstrb;

reg[ `AXI_ADDR_WIDTH-1:0 ] latched_araddr;
reg[                 2:0 ] latched_arprot;

reg[ `AXI_ADDR_WIDTH-1:0 ] index;

reg[ 1:0 ] status;

reg[ `AXI_DATA_WIDTH-1:0 ] wdata_temp;
reg[ `AXI_DATA_WIDTH-1:0 ] rdata_temp;

reg done = 1'b0;

always @ ( posedge clk )
begin : proc_bram_controller
    
    if ( ! res_n )
    begin
        
        state = IDLE;
        
        latched_awaddr = 0;
        latched_awprot = 0;
        
        latched_wdata = 0;
        latched_wstrb = 0;
        
        latched_araddr = 0;
        latched_arprot = 0;
        
        index = 0;
        
        status = 2'b00;
        
        wdata_temp = 0;
        rdata_temp = 0;
        
        done = 1'b0;
        
    end
    else
    begin
    
    // the default state is that we CANNOT receive anything
    // and that there is no response.
    
    s_axi.s_default();
    
    bram_read = 1'b0;
    bram_write = 1'b0;
    
    //~ bram_wdata = 32'h 0000_0000;
    
    case(state)
    
    // -------------------------------------------------------------------------
    // IDLE
    // -------------------------------------------------------------------------
    
    IDLE :
        begin
            
            status = `RESP_OKAY;
            
            //---------------------
            // write
            //---------------------
            
            s_axi.write_req_wait( latched_awaddr, latched_awprot, latched_wdata, latched_wstrb, done );
            if ( done == 1'b1 ) state = WRITE_READ;
            
            //---------------------
            // read
            //---------------------
            
            s_axi.read_req_wait( latched_araddr, latched_arprot, done );
            if ( done == 1'b1 ) state = READ;
            
        end
    
    // -------------------------------------------------------------------------
    // WRITE_READ
    // -------------------------------------------------------------------------
    
    WRITE_READ :
        begin
            
            bram_read = 1'b1;
            bram_addr = latched_awaddr;
            
            if ( bram_done == 1'b1 )
            begin
                
                wdata_temp = bram_rdata;
                
                state = WRITE_STRB;
                
            end
            
        end
    
    // -------------------------------------------------------------------------
    // WRITE_STRB
    // -------------------------------------------------------------------------
    
    WRITE_STRB :
        begin
            
            if ( latched_wstrb[0] == 1'b1 ) wdata_temp[  7: 0 ] = latched_wdata[  7: 0 ];
            if ( latched_wstrb[1] == 1'b1 ) wdata_temp[ 15: 8 ] = latched_wdata[ 15: 8 ];
            if ( latched_wstrb[2] == 1'b1 ) wdata_temp[ 23:16 ] = latched_wdata[ 23:16 ];
            if ( latched_wstrb[3] == 1'b1 ) wdata_temp[ 31:24 ] = latched_wdata[ 31:24 ];
            
            state = WRITE;
            
        end
    
    // -------------------------------------------------------------------------
    // WRITE
    // -------------------------------------------------------------------------
    
    WRITE :
        begin
            
            bram_write = 1'b1;
            bram_addr = latched_awaddr;
            
            bram_wdata = wdata_temp;
            
            if ( bram_done == 1'b1 ) state = WRITE_RESP;
            
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
            
            bram_read = 1'b1;
            bram_addr = latched_araddr;
            
            if ( bram_done == 1'b1 )
            begin
                
                rdata_temp = bram_rdata;
                
                state = READ_RESP;
                
            end
            
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
    
end

endmodule
