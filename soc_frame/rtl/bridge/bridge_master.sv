
/* ****************************************************************************
  This Source Code Form is subject to the terms of the
  Open Hardware Description License, v. 1.0. If a copy
  of the OHDL was not distributed with this file, You
  can obtain one at http://juliusbaxter.net/ohdl/ohdl.txt
  
  Copyright (C) 2019 Stefan Huemer <stefan@huemer.tech>
  
***************************************************************************** */

//`include "defines_axi.vh"
//`include "defines_noc.vh"

module bridge_master #()
(
     input clk
    ,input res_n
    
    ,if_axi_light.master  m_axi
    
    // communication with the flit_buffer
    
    ,input      data_to_bridge_avail
    ,output reg data_to_bridge_taken
    
    ,output reg data_from_bridge_avail
    ,input      data_from_bridge_taken
    
    ,input      [ `MERGED_REQUEST_WIDTH-1:0 ] merged_request_buffer_to_bridge
    ,output reg [ `MERGED_REQUEST_WIDTH-1:0 ] merged_request_bridge_to_buffer
);

enum
{
     IDLE
    ,AXI_EXTRACT
    ,AXI_WRITE
    ,AXI_READ
    ,AXI_WAIT
    ,AXI_MERGE
    ,SEND_DATA_TO_BUFFER
}state;

reg[ `MERGED_REQUEST_WIDTH-1:0 ] merged_request;

// AXI stuff

reg[ `AXI_ADDR_WIDTH-1:0 ] latched_awaddr;
reg[                 2:0 ] latched_awprot;

reg[ `AXI_DATA_WIDTH-1:0 ] latched_wdata;
reg[`AXI_WSTRB_WIDTH-1:0 ] latched_wstrb;

reg[ `AXI_ADDR_WIDTH-1:0 ] latched_araddr;
reg[                 2:0 ] latched_arprot;

reg[                 1:0 ] latched_bresp;

reg[                 1:0 ] latched_rresp;
reg[ `AXI_DATA_WIDTH-1:0 ] latched_rdata;

// extracted from flits

reg[ `AXI_ADDR_WIDTH-1:0 ] extracted_awaddr;
reg[                 2:0 ] extracted_awprot;

reg[ `AXI_DATA_WIDTH-1:0 ] extracted_wdata;
reg[                 3:0 ] extracted_wstrb;

reg[ `AXI_ADDR_WIDTH-1:0 ] extracted_araddr;
reg[                 2:0 ] extracted_arprot;

reg w_merge;
reg r_merge;

reg done;

always @ ( posedge clk )
begin : proc_bridge_master
    
    m_axi.m_default();
    
    data_from_bridge_avail = 1'b0;
    data_to_bridge_taken = 1'b0;
    
    if ( ! res_n )
    begin
        
        state = IDLE;
        
        merged_request = 0;
        
        // AXI stuff
        
        latched_awaddr = 0;
        latched_awprot = 0;
       
        latched_wdata = 0;
        latched_wstrb = 0;
       
        latched_araddr = 0;
        latched_arprot = 0;
       
        latched_bresp = 0;
       
        latched_rresp = 0;
        latched_rdata = 0;
        
        // extracted from flits
        
        extracted_awaddr = 0;
        extracted_awprot = 0;
       
        extracted_wdata = 0;
        extracted_wstrb = 0;
       
        extracted_araddr = 0;
        extracted_arprot = 0;
        
        w_merge = 0;
        r_merge = 0;
       
        done = 0;
        
        // flit buffer
        
        data_to_bridge_taken = 0;
        data_from_bridge_avail = 0;
        merged_request_bridge_to_buffer = 0;
    
    end
    else
    begin
    
    case(state)
        
        // ---------------------------------------------------------------------
        // IDLE
        // ---------------------------------------------------------------------
        
        IDLE :
        begin
            
            if ( data_to_bridge_avail == 1'b1 )
            begin
                
                data_to_bridge_taken = 1'b1;
                merged_request = merged_request_buffer_to_bridge;
                state = AXI_EXTRACT;
                
            end
            
        end
        
        // ---------------------------------------------------------------------
        // AXI_EXTRACT
        // ---------------------------------------------------------------------
        
        AXI_EXTRACT:
        begin
            
            if ( merged_request[0] == 1'b0 ) // write
            begin
                
                // how it looks in the default configuration using numbers:
                // extracted_awprot = merged_request[ 71 : 69 ];
                // extracted_wstrb  = merged_request[ 68 : 65 ];
                // extracted_awaddr = merged_request[ 64 : 33 ];
                // extracted_wdata  = merged_request[ 32 :  1 ];
                
                extracted_awprot = merged_request[ `RW_INDICATOR + `AXI_DATA_WIDTH + `AXI_ADDR_WIDTH + `AXI_WSTRB_WIDTH +:                3 ];
                extracted_wstrb  = merged_request[ `RW_INDICATOR + `AXI_DATA_WIDTH + `AXI_ADDR_WIDTH                    +: `AXI_WSTRB_WIDTH ];
                extracted_awaddr = merged_request[ `RW_INDICATOR + `AXI_DATA_WIDTH                                      +: `AXI_ADDR_WIDTH  ];
                extracted_wdata  = merged_request[ `RW_INDICATOR                                                        +: `AXI_DATA_WIDTH  ];
                
                state = AXI_WRITE;
                
            end
            else // read
            begin
                
                // how it looks in the default configuration using numbers:
                // extracted_arprot = merged_request[ 71 : 69 ];
                // extracted_araddr = merged_request[ 64 : 33 ];
                
                extracted_arprot = merged_request[ `RW_INDICATOR + `AXI_DATA_WIDTH + `AXI_ADDR_WIDTH + `AXI_WSTRB_WIDTH +:                3 ];
                extracted_araddr = merged_request[ `RW_INDICATOR + `AXI_DATA_WIDTH                                      +: `AXI_ADDR_WIDTH  ];
                
                state = AXI_READ;
                
            end
            
        end
        
        // ---------------------------------------------------------------------
        // AXI_WRITE
        // ---------------------------------------------------------------------
        
        AXI_WRITE:
        begin
            
            m_axi.write_req( extracted_awaddr, extracted_awprot, extracted_wdata, extracted_wstrb, done );
            if ( done == 1'b1 ) state = AXI_WAIT;
            
        end
        
        // ---------------------------------------------------------------------
        // AXI_READ
        // ---------------------------------------------------------------------
        
        AXI_READ:
        begin
            
            m_axi.read_req( extracted_araddr, extracted_arprot, done );
            if ( done == 1'b1 ) state = AXI_WAIT;
            
        end
        
        // ---------------------------------------------------------------------
        // AXI_WAIT
        // ---------------------------------------------------------------------
        
        AXI_WAIT:
        begin
            
            // i can reuse the done variable here. if the first one returns
            // done, w_merge will be set.
            // the m_axi.read_resp_wait task will set done to false and
            // r_merge will not be set.
            
            m_axi.write_resp_wait( latched_bresp, done );
            
            if ( done == 1'b1 )
            begin
                w_merge = 1'b1;
                state = AXI_MERGE;
            end
            
            m_axi.read_resp_wait( latched_rdata, latched_rresp, done );
            
            if ( done == 1'b1 )
            begin
                r_merge = 1'b1;
                state = AXI_MERGE;
            end
            
        end
        
        // ---------------------------------------------------------------------
        // AXI_MERGE
        // ---------------------------------------------------------------------
        
        AXI_MERGE :
        begin
            
            // TODO - replace constant values
            
            if ( w_merge == 1'b1 )
            begin
                
                merged_request =
                {
                     {                3 {1'b0} }
                    ,{                4 {1'b0} }
                    ,{`AXI_ADDR_WIDTH-2 {1'b0} } , latched_bresp
                    ,{`AXI_DATA_WIDTH   {1'b0} }
                    ,`AXI_WRITE
                };
                
                w_merge = 1'b0;
                
                state = SEND_DATA_TO_BUFFER;
                
            end
            else if ( r_merge == 1'b1 )
            begin
                
                merged_request =
                {
                     {                3 {1'b0} }
                    ,{                4 {1'b0} }
                    ,{`AXI_ADDR_WIDTH-2 {1'b0} } , latched_rresp
                    ,latched_rdata
                    ,`AXI_READ
                };
                
                r_merge = 1'b0;
                
                state = SEND_DATA_TO_BUFFER;
                
            end
            
        end
        
        // ---------------------------------------------------------------------
        // SEND_DATA_TO_BUFFER
        // ---------------------------------------------------------------------
        
        SEND_DATA_TO_BUFFER :
        begin
            
            merged_request_bridge_to_buffer = merged_request;
            data_from_bridge_avail = 1'b1;
            
            if ( data_from_bridge_taken == 1'b1 ) state = IDLE;
            
        end
        
        // ---------------------------------------------------------------------
        // DEFAULT
        // ---------------------------------------------------------------------
        
        default : state = IDLE;
        
        endcase
        
    end
    
end

endmodule
