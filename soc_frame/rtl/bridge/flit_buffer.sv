
module flit_buffer #()
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
    
    generate
        
        if ( `MISSING == 0 )
        begin
            
            flit_buffer_none_missing #() flit_buffer_none_missing_inst
            (
                 .clk( clk )
                ,.res_n( res_n )
                
                ,.noc( noc )
                
                ,.data_to_bridge_avail( data_to_bridge_avail )
                ,.data_to_bridge_taken( data_to_bridge_taken )
                
                ,.data_from_bridge_avail( data_from_bridge_avail )
                ,.data_from_bridge_taken( data_from_bridge_taken )
                
                ,.merged_request_buffer_to_bridge( merged_request_buffer_to_bridge )
                ,.merged_request_bridge_to_buffer( merged_request_bridge_to_buffer )
            );
            
        end
        else
        begin
            
            flit_buffer_missing #() flit_buffer_missing_inst
            (
                 .clk( clk )
                ,.res_n( res_n )
                
                ,.noc( noc )
                
                ,.data_to_bridge_avail( data_to_bridge_avail )
                ,.data_to_bridge_taken( data_to_bridge_taken )
                
                ,.data_from_bridge_avail( data_from_bridge_avail )
                ,.data_from_bridge_taken( data_from_bridge_taken )
                
                ,.merged_request_buffer_to_bridge( merged_request_buffer_to_bridge )
                ,.merged_request_bridge_to_buffer( merged_request_bridge_to_buffer )
            );
            
        end
        
    endgenerate
    
endmodule
