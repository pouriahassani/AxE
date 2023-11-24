
/* ****************************************************************************
  This Source Code Form is subject to the terms of the
  Open Hardware Description License, v. 1.0. If a copy
  of the OHDL was not distributed with this file, You
  can obtain one at http://juliusbaxter.net/ohdl/ohdl.txt
  
  Copyright (C) 2019 Stefan Huemer <stefan@huemer.tech>
  
***************************************************************************** */

module flit_buffer_missing #()
(
     input clk
    ,input res_n
    
    ,if_connect.bridge    noc
    
    // bridge master
    
    ,output reg data_to_bridge_avail
    ,input      data_to_bridge_taken
    
    ,input      data_from_bridge_avail
    ,output reg data_from_bridge_taken
    
    ,output reg [ `MERGED_REQUEST_WIDTH-1:0 ] merged_request_buffer_to_bridge
    ,input      [ `MERGED_REQUEST_WIDTH-1:0 ] merged_request_bridge_to_buffer
);

enum
{
     IDLE
    ,MERGE_FLIT
    ,SEND_DATA_TO_BRIDGE
    ,WAIT
    ,SPLIT
    ,SEND
}state;

integer flit_index;

reg[ `FLIT_BODY_WIDTH-1:0 ] flit_array[ `FLITS_TO_SEND-1:0 ];

reg[ `MERGED_REQUEST_WIDTH-1:0 ] merged_request;

// buffer

// the buffer holds elements that are [USEFUL_DATA_WIDTH-1:0] wide.
// it needs [FLITS_TO_SEND-1:0] of these elements to get a full request.
// it receives requests from [NUM_NODES-1:0] nodes.

reg[ `USEFUL_DATA_WIDTH-1:0 ] buffer_array[ `NUM_NODES-1:0 ][ `FLITS_TO_SEND-1:0 ];

integer flit_index_array[ `NUM_NODES-1:0 ];

integer curr_flit_index;

reg[ `NUM_NODES-1:0 ] flits_collected;

integer flits_collected_select;

reg[ `NOC_NODE_WIDTH-1:0 ] recv_id;
reg[ `NOC_NODE_WIDTH-1:0 ] recv_id_curr;

integer i;

//~ integer fuck_me_verilog;

always @ ( posedge clk )
begin : flit_buffer_missing_proc
    
    if ( ! res_n )
    begin
        
        //~ fuck_me_verilog = `MISSING;
        
        state = IDLE;
        
        flit_index = 0;
        
        //~ reg[ `FLIT_BODY_WIDTH-1:0 ] flit_array[ `FLITS_TO_SEND-1:0 ];
        
        merged_request = 0;
        
        //~ reg[ `USEFUL_DATA_WIDTH-1:0 ] buffer_array[ `NUM_NODES-1:0 ][ `FLITS_TO_SEND-1:0 ];
        
        //~ integer flit_index_array[ `NUM_NODES-1:0 ];
        
        curr_flit_index = 0;
        
        flits_collected = 0;
        
        flits_collected_select = 0;
        
        recv_id = 0;
        recv_id_curr = 0;
        
        // bridge master
        
        data_to_bridge_avail = 0;
        data_from_bridge_taken = 0;
        merged_request_buffer_to_bridge = 0;
        
        for ( i = 0; i < `NUM_NODES; i = i +1 ) begin
            flit_index_array[ i ] = 0;
        end
        
    end
    else
    begin
        
        noc.en_put = 1'b0;
        noc.en_get = 1'b0;
        
        noc.en_get_non_full_VCs = 1'b1;
        
        noc.en_put_non_full_VCs = 1'b1;
        noc.put_non_full_VCs = 2'b11;
        
        data_to_bridge_avail = 1'b0;
        data_from_bridge_taken = 1'b0;
        
        // ----------------------
        // get flits
        // ----------------------
        
        noc.en_get = 1'b1;
        
        if ( noc.get_flit[ `FLIT_WIDTH-1 ] == 1'b1 )
        begin
            
            //~ recv_id_curr = noc.get_flit[ `USEFUL_DATA_WIDTH + 1 : `USEFUL_DATA_WIDTH ];
            recv_id_curr = noc.get_flit[ (`USEFUL_DATA_WIDTH + `NOC_NODE_WIDTH)-1 : `USEFUL_DATA_WIDTH ];
            
            // this does not work
            //~ if ( ( state == IDLE ) || ( recv_id_curr != recv_id ) )
            
            curr_flit_index = flit_index_array[ recv_id_curr ];
            
            buffer_array[ recv_id_curr ][ curr_flit_index ] = noc.get_flit[ `USEFUL_DATA_WIDTH-1 : 0 ];
            
            if ( curr_flit_index == `FLITS_TO_SEND-1 )
            begin
                
                flits_collected[ recv_id_curr ] = 1'b1;
                flit_index_array[ recv_id_curr ] = 0;
                
            end
            else
            begin
                
                flit_index_array[ recv_id_curr ] = curr_flit_index + 1;
                
                `ifdef DEB_FLIT_BUFFER
                    $display( "FLIT_BUFFER: got flit for: %u - index: %u", recv_id_curr, (curr_flit_index + 1) );
                `endif
                
            end
            
            
        end
        
        case(state)
        
        // ---------------------------------------------------------------------
        // IDLE
        // ---------------------------------------------------------------------
        
        IDLE :
        begin
            
            if ( flits_collected[ flits_collected_select ] == 1'b1 )
            begin
                
                recv_id = flits_collected_select[ `NOC_NODE_WIDTH-1:0 ];
                flits_collected[ flits_collected_select ] = 1'b0;
                
                state = MERGE_FLIT;
                
            end
            
            
            if ( flits_collected_select == `NUM_NODES-1 )
                flits_collected_select = 0;
            else
                flits_collected_select = flits_collected_select + 1;
            
        end
        
        // ---------------------------------------------------------------------
        // MERGE_FLIT
        // ---------------------------------------------------------------------
        
        MERGE_FLIT:
        begin
            
            if ( flit_index == `FLITS_TO_SEND-1 )
            begin
                
                // hier ist der unterschied zwischen dem missing und dem ohne missing
                
                merged_request[ ( `MERGED_REQUEST_WIDTH-1 ) -: `MISSING ] = buffer_array[ recv_id ][ flit_index ][ `MISSING-1:0 ];
                
                // if `MISSING is 0, than the access to the buffer_array looks like this:
                // buffer_array[ recv_id ][ flit_index ][ 0-1:0 ]
                // this should (???) not be possible and was only cought once the
                // number of nodes was increased.
                // therefore this line is skipped if `MISSING equals 0.
                
                //~ merged_request[ ( 72-1 ) -: 0 ] = buffer_array[ recv_id ][ flit_index ][ 0-1:0 ];
                
                //~ merged_request[ ( `MERGED_REQUEST_WIDTH-1 ) -: `MISSING ] = buffer_array[ recv_id ][ flit_index ][ `MISSING-1:0 ];
                
                //~ if ( fuck_me_verilog != 0 )
                //~ begin
                    
                    //~ merged_request[ ( `MERGED_REQUEST_WIDTH-1 ) -: `MISSING ] = buffer_array[ recv_id ][ flit_index ][ fuck_me_verilog-1+:0 ];
                    
                //~ end
                
                flit_index = 0;
                state = SEND_DATA_TO_BRIDGE;
                
            end
            else
            begin
                
                merged_request[ ( `USEFUL_DATA_WIDTH * (flit_index+1) - 1 ) -: `USEFUL_DATA_WIDTH ] = buffer_array[ recv_id ][ flit_index ];
                
                flit_index = flit_index + 1;
                
            end
            
        end
        
        // ---------------------------------------------------------------------
        // SEND_DATA_TO_BRIDGE
        // ---------------------------------------------------------------------
        
        SEND_DATA_TO_BRIDGE:
        begin
            
            data_to_bridge_avail = 1'b1;
            
            merged_request_buffer_to_bridge = merged_request;
            
            if ( data_to_bridge_taken == 1'b1 ) state = WAIT;
            
        end
        
        // ---------------------------------------------------------------------
        // WAIT
        // ---------------------------------------------------------------------
        
        WAIT:
        begin
            
            if ( data_from_bridge_avail == 1'b1 )
            begin
                
                data_from_bridge_taken = 1'b1;
                merged_request = merged_request_bridge_to_buffer;
                
                flit_index = 0;
                
                state = SPLIT;
                
            end
            
        end
        
        // ---------------------------------------------------------------------
        // SPLIT
        // ---------------------------------------------------------------------
        
        SPLIT :
        begin
            
            if ( flit_index == `FLITS_TO_SEND-1 )
            begin
                
                flit_array[ flit_index ] =
                {
                     noc.this_id
                    ,{ `PADDING { 1'b1 } }
                    ,merged_request[ ( `MERGED_REQUEST_WIDTH-1 ) -: `MISSING ]
                };
                
                // reset flit index to be used for sending
                
                flit_index = 0;
                state = SEND;
                
            end
            else
            begin
                
                flit_array[ flit_index ] =
                {
                     noc.this_id
                    ,merged_request[ ( `USEFUL_DATA_WIDTH * (flit_index+1) - 1 ) -: `USEFUL_DATA_WIDTH ]
                };
                
                flit_index = flit_index + 1;
                
            end
            
        end
        
        // ---------------------------------------------------------------------
        // SEND
        // ---------------------------------------------------------------------
        
        SEND :
        begin
            
            if ( flit_index == `FLITS_TO_SEND )
            begin
                
                flit_index = 0;
                state = IDLE;
                
            end
            else
            begin
                
                noc.put_flit =
                {
                     1'b1    // valid
                    ,1'b0    // tail
                    ,recv_id // receiver
                    ,1'b0    // always 0
                    ,flit_array[ flit_index ]
                };
                
                noc.en_put = 1'b1;
                
                flit_index = flit_index + 1;
                
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
