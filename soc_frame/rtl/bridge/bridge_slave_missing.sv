
/* ****************************************************************************
  This Source Code Form is subject to the terms of the
  Open Hardware Description License, v. 1.0. If a copy
  of the OHDL was not distributed with this file, You
  can obtain one at http://juliusbaxter.net/ohdl/ohdl.txt
  
  Copyright (C) 2019 Stefan Huemer <stefan@huemer.tech>
  
***************************************************************************** */

module bridge_slave_missing
#(
     parameter ID = 0
    
    ,parameter SEND_TO = 0
)
(
     input clk
    ,input res_n
    
    ,if_axi_light.slave  s_axi
    ,if_connect.bridge   noc
);

//~ (* mark_debug = "true" *) enum
enum
{
     IDLE
    ,MERGE_AXI
    ,SEND
    ,WAIT
    ,AXI_EXTRACT
    ,AXI_WRITE
    ,AXI_READ
}state;

//---------------------
// NOC
//---------------------

//~ (* mark_debug = "true" *) integer flit_index;
integer flit_index;

// the whole request / response is merged into one reg

//~ (* mark_debug = "true" *) reg[ `MERGED_REQUEST_WIDTH-1:0 ] merged_request;
reg[ `MERGED_REQUEST_WIDTH-1:0 ] merged_request;

//---------------------
// AXI
//---------------------

// AXI request latched from the AXI input

reg[ `AXI_ADDR_WIDTH-1:0 ] latched_awaddr;
reg[                 2:0 ] latched_awprot;

reg[ `AXI_DATA_WIDTH-1:0 ] latched_wdata;
reg[`AXI_WSTRB_WIDTH-1:0 ] latched_wstrb;

reg[ `AXI_ADDR_WIDTH-1:0 ] latched_araddr;
reg[                 2:0 ] latched_arprot;

// AXI response extracted from the merged flits

//~ (* mark_debug = "true" *) reg[                 1:0 ] extracted_bresp;

//~ (* mark_debug = "true" *) reg[                 1:0 ] extracted_rresp;
//~ (* mark_debug = "true" *) reg[ `AXI_DATA_WIDTH-1:0 ] extracted_rdata;
reg[                 1:0 ] extracted_bresp;

reg[                 1:0 ] extracted_rresp;
reg[ `AXI_DATA_WIDTH-1:0 ] extracted_rdata;

reg w_merge;
reg r_merge;

reg done;

// -----------------------------------------------------------------------------
// always
// -----------------------------------------------------------------------------

always @ ( posedge clk )
begin : bridge_slave_missing_proc
    
    s_axi.s_default();
    
    // default values
    
    noc.en_put = 1'b0;
    noc.en_get = 1'b0;
    
    noc.en_get_non_full_VCs = 1'b0;
    
    noc.en_put_non_full_VCs = 1'b1;
    noc.put_non_full_VCs = 2'b11;
    
    if ( ! res_n )
    begin
        
        state = IDLE;
        
        flit_index = 0;
        
        merged_request = 0;
        
        // AXI request latched from the AXI input
        
        latched_awaddr = 0;
        latched_awprot = 0;
        
        latched_wdata = 0;
        latched_wstrb = 0;
        
        latched_araddr = 0;
        latched_arprot = 0;
        
        // AXI response extracted from the merged flits
        
        extracted_bresp = 0;
        
        extracted_rresp = 0;
        extracted_rdata = 0;
        
        // other stuff
        
        w_merge = 0;
        r_merge = 0;
        
        done = 0;
        
    end
    else
    begin
        
        case(state)
        
        // ---------------------------------------------------------------------
        // IDLE
        // ---------------------------------------------------------------------
        
        // the bridge waits for AXI request that should be sent over the NoC.
        
        IDLE :
        begin
            
            s_axi.write_req_wait( latched_awaddr, latched_awprot, latched_wdata, latched_wstrb, done );
            
            if ( done == 1'b1 )
            begin
                w_merge = 1'b1;
                state = MERGE_AXI;
                
                `ifdef DEB_BRIDGE_SLAVE
                    $display( "BRIDGE_SLAVE: IDLE -> MERGE_AXI (write)" );
                `endif
                
            end
            
            s_axi.read_req_wait( latched_araddr, latched_arprot, done );
            
            if ( done == 1'b1 )
            begin
                r_merge = 1'b1;
                state = MERGE_AXI;
                
                //~ $display( "BRIDGE_SLAVE: ID: %d, read from %x", ID, latched_araddr );
                
                `ifdef DEB_BRIDGE_SLAVE
                    $display( "BRIDGE_SLAVE: IDLE -> MERGE_AXI (read)" );
                `endif
                
            end
            
        end
        
        // ---------------------------------------------------------------------
        // MERGE_AXI
        // ---------------------------------------------------------------------
        
        // the AXI request is merged into one big reg. the lsb is used to record
        // if the request is a write or a read.
        
        MERGE_AXI :
        begin
            
            if ( w_merge == 1'b1 ) // write
            begin
                
                merged_request =
                {
                     latched_awprot
                    ,latched_wstrb
                    ,latched_awaddr
                    ,latched_wdata
                    ,`AXI_WRITE
                };
                
                flit_index = 0;
                w_merge = 1'b0;
                
                state = SEND;
                
            end
            else if ( r_merge == 1'b1 ) // read
            begin
                
                merged_request =
                {
                     latched_arprot
                    ,{ 4 { 1'b0 } }
                    ,latched_araddr
                    ,{ `AXI_DATA_WIDTH { 1'b0 } }
                    ,`AXI_READ
                };
                
                flit_index = 0;
                r_merge = 1'b0;
                
                state = SEND;
                
            end
            
            `ifdef DEB_BRIDGE_SLAVE
                $display( "BRIDGE_SLAVE: MERGE_AXI -> SEND" );
            `endif
            
        end
        
        // ---------------------------------------------------------------------
        // SEND
        // ---------------------------------------------------------------------
        
        // the flits are sent to the NoC. this is also the moment the flit header
        // is added.
        
        // the merged request is split into flits.
        
        // although this is called flit_array, the "flits" still miss the
        // header and are therefore not real flits yet.
        
        SEND :
        begin
            
            if ( flit_index == `FLITS_TO_SEND )
            begin
                
                flit_index = 0;
                state = WAIT;
                
                `ifdef DEB_BRIDGE_SLAVE
                    $display( "BRIDGE_SLAVE: SEND -> WAIT" );
                `endif
                
            end
            else if ( flit_index == `FLITS_TO_SEND-1 )
            begin
                
                noc.put_flit =
                {
                     1'b1                           // valid
                    ,1'b0                           // tail
                    ,SEND_TO[ `NOC_NODE_WIDTH-1:0 ] // receiver
                    ,1'b0                           // always 0
                    ,noc.this_id
                    ,{ `PADDING { 1'b1 } }
                    ,merged_request[ ( `MERGED_REQUEST_WIDTH-1 ) -: `MISSING ]
                };
                noc.put_flit[ `FLIT_WIDTH-1 ] = 1'b1; // needed by vivado
                
                noc.en_put = 1'b1;
                
                flit_index = flit_index + 1;
                
            end
            else
            begin
                
                // the second bit, the tail, is used to specify the flit.
                // as the bridge is aware how may flits are in a request this
                // is always set to 0 and never looked at.
                
                noc.put_flit =
                {
                     1'b1                           // valid
                    ,1'b0                           // tail
                    ,SEND_TO[ `NOC_NODE_WIDTH-1:0 ] // receiver
                    ,1'b0                           // always 0
                    ,noc.this_id
                    ,merged_request[ ( `USEFUL_DATA_WIDTH * (flit_index+1) - 1 ) -: `USEFUL_DATA_WIDTH ]
                };
                noc.put_flit[ `FLIT_WIDTH-1 ] = 1'b1; // needed by vivado
                
                noc.en_put = 1'b1;
                
                flit_index = flit_index + 1;
            end
            
            
        end
        
        // ---------------------------------------------------------------------
        // WAIT
        // ---------------------------------------------------------------------
        
        // after the flits have been sent the bridge waits for a response.
        
        // the flits are merged into one reg again.
        // although this is the merged_response, the reg form before is reused.
        
        WAIT :
        begin
            
            if ( flit_index == `FLITS_TO_SEND )
            begin
                
                flit_index = 0;
                state = AXI_EXTRACT;
                
                `ifdef DEB_BRIDGE_SLAVE
                    $display( "BRIDGE_SLAVE: WAIT -> AXI_EXTRACT" );
                `endif
                
            end
            else
            begin
                
                noc.en_get = 1'b1;
                
                // check the msb if the flit is valid and store the collected flit.
                // please note, that the header and sender is discarded and only
                // the actual data is stored.
                
                if ( noc.get_flit[ `FLIT_WIDTH-1 ] == 1'b1 )
                begin
                    
                    if ( flit_index == `FLITS_TO_SEND-1 )
                    begin
                        
                        // hier ist der unterschied
                        
                        merged_request[ ( `MERGED_REQUEST_WIDTH-1 )                 -: `MISSING           ] = noc.get_flit[ `MISSING-1:0 ];
                        
                        // wenn missing = 0 ist:
                        
                        // missing wird -1 -> dass passt verilator nicht.
                        
                        //~ merged_request[ ( `MERGED_REQUEST_WIDTH-1 )                 -: `MISSING           ] = noc.get_flit[ 0 +: `MISSING ];
                        
                        // warum geht der scheiss nicht. LHS sollte merged_request-1 -: 0 sein. also von 71 auf 0 hinunter. wird aber laut:
                        // %Error: ../../rtl/bridge/bridge_slave.sv:343: Unsupported: MSB < LSB of bit extract: -1<0
                        // das RHS kann ja nur 0:0 sein, oder?
                        
                        //~ if ( `MISSING == 0 )
                            //~ low_index = ( `MERGED_REQUEST_WIDTH-1 );
                        //~ else
                            //~ low_index = ( `MERGED_REQUEST_WIDTH-`MISSING );
                        
                        //~ merged_request[ ( `MERGED_REQUEST_WIDTH-1 )                 : low_index           ] = noc.get_flit[ 0 +: `MISSING ];
                        
                        // das mit dem low index passt verilator auch nicht:
                        // %Error: ../../rtl/bridge/bridge_slave.sv:359: Expecting expression to be constant, but variable isn't const: low_index
                        // %Error: ../../rtl/bridge/bridge_slave.sv:359: First value of [a:b] isn't a constant, maybe you want +: or -:
                        // %Error: ../../rtl/bridge/bridge_slave.sv:359: Unsupported: MSB < LSB of bit extract: -1<0
                    end
                    else
                        merged_request[ ( `USEFUL_DATA_WIDTH * (flit_index+1) - 1 ) -: `USEFUL_DATA_WIDTH ] = noc.get_flit[ `USEFUL_DATA_WIDTH-1 : 0 ];
                        
                    
                    
                    flit_index = flit_index + 1;
                    
                end
                
            end
            
        end
        
        // ---------------------------------------------------------------------
        // AXI_EXTRACT
        // ---------------------------------------------------------------------
        
        // the AXI signals are extracted from the merged flits.
        
        AXI_EXTRACT:
        begin
            
            if ( merged_request[0] == `AXI_WRITE ) // write
            begin
                
                extracted_bresp  = merged_request[ `RW_INDICATOR+`AXI_DATA_WIDTH +:               2 ];
                
                state = AXI_WRITE;
                
                `ifdef DEB_BRIDGE_SLAVE
                    $display( "BRIDGE_SLAVE: AXI_EXTRACT -> AXI_WRITE" );
                `endif
                
            end
            else
            begin
                
                extracted_rresp  = merged_request[ `RW_INDICATOR+`AXI_DATA_WIDTH +:               2 ];
                extracted_rdata  = merged_request[ `RW_INDICATOR                 +: `AXI_DATA_WIDTH ];
                
                state = AXI_READ;
                
                `ifdef DEB_BRIDGE_SLAVE
                    $display( "BRIDGE_SLAVE: AXI_EXTRACT -> AXI_READ" );
                `endif
                
            end
            
        end
        
        // ---------------------------------------------------------------------
        // AXI_WRITE
        // ---------------------------------------------------------------------
        
        AXI_WRITE:
        begin
            
            // TODO ?
            // it would be possible to save some regs but omitting the
            // extracted_* variables like this:
            // s_axi.write_resp( merged_request[ `RW_INDICATOR+`AXI_DATA_WIDTH +:               2 ], done );
            // this was not done as the code is more readable this way.
            
            s_axi.write_resp( extracted_bresp, done );
            
            if ( done == 1'b1 )
            begin
                
                state = IDLE;
                
                `ifdef DEB_BRIDGE_SLAVE
                    $display( "BRIDGE_SLAVE: AXI_WRITE -> IDLE" );
                `endif
                
            end
            
        end
        
        // ---------------------------------------------------------------------
        // AXI_READ
        // ---------------------------------------------------------------------
        
        AXI_READ:
        begin
            
            s_axi.read_resp( extracted_rdata, extracted_rresp, done );
            
            if ( done == 1'b1 )
            begin
                
                state = IDLE;
                
                `ifdef DEB_BRIDGE_SLAVE
                    $display( "BRIDGE_SLAVE: AXI_READ -> IDLE" );
                `endif
                
            end
            
        end
        
        // ---------------------------------------------------------------------
        // DEFAULT
        // ---------------------------------------------------------------------
        
        default : state = IDLE;
        
        endcase
    
    end
    
end

endmodule
