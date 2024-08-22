
/* ****************************************************************************
  This Source Code Form is subject to the terms of the
  Open Hardware Description License, v. 1.0. If a copy
  of the OHDL was not distributed with this file, You
  can obtain one at http://juliusbaxter.net/ohdl/ohdl.txt
  
  Copyright (C) 2019 Stefan Huemer <stefan@huemer.tech>
  
***************************************************************************** */

// this module can activate the nodes and set the AXI address offsets.
// `define DEBUG_CONTROL
module control #()
(
     input clk
    ,input res_n
    
    ,if_axi_light.slave  s_axi
    
    ,output reg [7:0] leds_status
    ,output reg [7:0] triggers
);

//~ (* mark_debug = "true" *) enum
enum
{
     IDLE
    ,WRITE
    ,READ
    ,SEND_WRITE_RESP
    ,SEND_READ_RESP
}state;

parameter ACTIVATE_INDEX = `AXI_ADDR_WIDTH-1;

// the range which holds the node id.

parameter NODE_LSB = 2;

parameter INDEX_PROG           =  7;
parameter INDEX_BUSY           =  8;
parameter INDEX_COUNT          =  9;
parameter INDEX_COUNT_GLOBAL   = 10;

// not used

// parameter INDEX_ = 11;
// parameter INDEX_ = 12;
// parameter INDEX_ = 13;
// parameter INDEX_ = 14;

parameter INDEX_COUNT_GLOBAL_RESET = 15;

// not used

// parameter INDEX_  = 16;
// parameter INDEX_  = 17;

parameter INDEX_LEDS_STATUS = 18;
parameter INDEX_TRIGGERS = 19;

// req

reg[ `AXI_ADDR_WIDTH-1:0 ] latched_awaddr;
reg[                 2:0 ] latched_awprot;

reg[ `AXI_DATA_WIDTH-1:0 ] latched_wdata;
reg[`AXI_WSTRB_WIDTH-1:0 ] latched_wstrb;

reg[ `AXI_ADDR_WIDTH-1:0 ] latched_araddr;
reg[                 2:0 ] latched_arprot;

// resp

reg[                 1:0 ] latched_bresp;

reg[                 1:0 ] latched_rresp;
reg[ `AXI_DATA_WIDTH-1:0 ] latched_rdata;

reg done;

reg[ `NUM_NODES_PROCESSING_WIDTH-1:0 ] node_sel;

// the width of the active reg does not need to be so wide, but it is easier
// this way. the actual width is determined by the active nodes.

reg[ `AXI_DATA_WIDTH-1:0 ] active;

reg[ `AXI_DATA_WIDTH-1:0 ] axi_offsets[ `NUM_NODES_PROCESSING-1:0 ];

reg trigger_a_reg;
reg trigger_b_reg;

// counters are used to count the clk cycles that a program/task is running.
// counter_global holds the count beginning from the start of the system.

integer unsigned counter_global;

`ifdef DEBUG_CONTROL

integer unsigned counter_global_prev;

`endif


integer counters[ `NUM_NODES_PROCESSING-1:0 ];

integer i;

integer num_active;

always @ ( posedge clk )
begin : control_proc
    
    s_axi.s_default();
    
    if ( ! res_n )
    begin
        
        for ( i = 0; i < `NUM_NODES_PROCESSING; i = i +1 ) begin
            axi_offsets[ i ] = 32'h 0000_0000;
            counters[ i ] = 0;
        end
        
        done = 0;
        
        node_sel = 0;
        active = 0;
        
        num_active = 0;
        
        // the values commented out can be used to test overflows.
        
        counter_global = 1;
        //~ counter_global = 4294967295;
        //~ counter_global = 4293967295;
        
`ifdef DEBUG_CONTROL
        
        counter_global_prev = 0;
        //~ counter_global = 4263506011;
        //~ counter_global = 4183506011;
        
`endif
        
        // req
        
        latched_awaddr = 0;
        latched_awprot = 0;
        
        latched_wdata = 0;
        latched_wstrb = 0;
        
        latched_araddr = 0;
        latched_arprot = 0;
        
        // resp
        
        latched_bresp = 0;
        
        latched_rresp = 0;
        latched_rdata = 0;
        
    end
    else
    begin
        
        // inc counters
        
        // the counters are just incremented without any care for overflows
        
        counter_global = counter_global + 1;
        
        // if a node is active, it's counter is incremented
        
        for ( i = 0; i < `NUM_NODES_PROCESSING; i = i +1 ) begin
            if ( active[ i ] == 1'b1 ) counters[ i ] = counters[ i ] + 1;
        end
        
        case(state)
        
        // ---------------------------------------------------------------------
        // IDLE
        // ---------------------------------------------------------------------
        
        // during the IDLE state the module waits for AXI write requests.
        // once a request has been received, the next state SET_CONTROL is entered.
        
        IDLE :
        begin
            
            s_axi.write_req_wait( latched_awaddr, latched_awprot, latched_wdata, latched_wstrb, done );
            if ( done == 1'b1 ) state = WRITE;
            
            s_axi.read_req_wait( latched_araddr, latched_arprot, done );
            if ( done == 1'b1 ) state = READ;
            
        end
        
        // ---------------------------------------------------------------------
        // WRITE
        // ---------------------------------------------------------------------
        
        // in this state the msb is checked to make sure it is a valid control
        // request.
        
        // the node id is extracted from the AXI address and the corresponding
        // controls set.
        
        WRITE :
        begin
            
            // if you add the width of the processing nodes to the lsb of the
            // index where the node id is recorded in the address, you get the
            // range between the lsb and the msb of node id.
            // it could alos be written as:
            // node_sel = latched_awaddr[ NODE_MSB:NODE_LSB ];
            
            node_sel = latched_awaddr[ NODE_LSB +: `NUM_NODES_PROCESSING_WIDTH ];
            
`ifdef DEBUG_CONTROL
            
            // $display( "pico_sel: %d", pico_sel );
            $display( "awaddr: %b", latched_awaddr );
            
`endif
            
            if ( latched_awaddr[ INDEX_PROG ] == 1'b1 )
            begin
                
                // set offset
                
                axi_offsets[ node_sel ] = latched_wdata;
                
                // turned on or off
                
                if ( latched_wdata == 0 )
                begin
                    
                    active[ node_sel ] = 1'b0;
                    num_active -= 1;
                    
                end
                else
                begin
                    
                    counters[ node_sel ] = 0;
                    active[ node_sel ] = 1'b1;
                    num_active += 1;
                    
                end
                
`ifdef DEBUG_CONTROL
                
                if ( latched_wdata == 0 )
                    $display( ";%d,%d,fin;", counter_global, node_sel );
                else
                    $display( "Contro set prg:;%d,p%h,%d;", counter_global, latched_wdata, node_sel );
                
                // check for overflow
                
                if ( counter_global_prev > counter_global )
                begin
                    
                    $display( "uut: detected overflow" );
                    $display( "uut: prev: %d", counter_global_prev );
                    $display( "uut: curr: %d", counter_global );
                    
                end
                
                $display( "uut: %d,%d,%d,%h", counter_global, num_active, node_sel, latched_wdata );
                
                counter_global_prev = counter_global;
                
`endif
                
            end
            else if ( latched_awaddr[ INDEX_LEDS_STATUS  ] == 1'b1 ) leds_status = latched_wdata[ 7:0 ];
            else if ( latched_awaddr[ INDEX_TRIGGERS     ] == 1'b1 ) triggers    = latched_wdata[ 7:0 ];
            
            state = SEND_WRITE_RESP;
            
        end
        
        // ---------------------------------------------------------------------
        // READ
        // ---------------------------------------------------------------------
        
        READ :
        begin
            
            node_sel = latched_araddr[ NODE_LSB +: `NUM_NODES_PROCESSING_WIDTH ];
            
                 if ( latched_araddr[ INDEX_PROG         ] == 1'b1 ) latched_rdata = axi_offsets[ node_sel ];
            else if ( latched_araddr[ INDEX_BUSY         ] == 1'b1 ) latched_rdata = active;
            else if ( latched_araddr[ INDEX_COUNT        ] == 1'b1 ) latched_rdata = counters[ node_sel ];
            else if ( latched_araddr[ INDEX_COUNT_GLOBAL ] == 1'b1 ) latched_rdata = counter_global;
            
            else if ( latched_araddr[ INDEX_COUNT_GLOBAL_RESET ] == 1'b1 ) begin latched_rdata = counter_global; counter_global = 0; end
            
`ifdef DEBUG_CONTROL
            
            if ( latched_araddr[ INDEX_PROG         ] == 1'b1 )
            begin
                
                $display( "got read at control: %h", node_sel );
                $display( "got read at control: %h", axi_offsets[ node_sel ] );
                
            end
            
            // $display( "get prg for pico %d", pico_sel );
            
            //~ if (
                //~ ( latched_araddr[ INDEX_PROG ] == 1'b1 ) &&
                //~ ( latched_araddr[ INDEX_TIME ] == 1'b1 ) &&
                //~ ( axi_offsets[ pico_sel ] != 0 )
            //~ )
            
            if ( latched_araddr[ INDEX_COUNT_GLOBAL ] == 1'b1 )
            begin
                
                // $display( "get prg for pico %d", pico_sel );
                $display( "global time" );
                
            end
            
`endif
            
            state = SEND_READ_RESP;
            
        end
        
        // ---------------------------------------------------------------------
        // SEND_WRITE_RESP
        // ---------------------------------------------------------------------
        
        SEND_WRITE_RESP :
        begin
            
            s_axi.write_resp( `RESP_OKAY, done );
            if ( done == 1'b1 ) state = IDLE;
            
        end
        
        // ---------------------------------------------------------------------
        // SEND_READ_RESP
        // ---------------------------------------------------------------------
        
        SEND_READ_RESP :
        begin
            
            s_axi.read_resp( latched_rdata, `RESP_OKAY, done );
            if ( done == 1'b1 ) state = IDLE;
            
        end
        
        // ---------------------------------------------------------------------
        // DEFAULT
        // ---------------------------------------------------------------------
        
        default : state = IDLE;
        
        endcase
        
    end
    
end

endmodule
