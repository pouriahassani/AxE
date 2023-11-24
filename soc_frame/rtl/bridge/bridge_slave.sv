
module bridge_slave
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
    
    generate
        
        if ( `MISSING == 0 )
        begin
            
            bridge_slave_none_missing
            #(
                 .ID( ID )
                
                ,.SEND_TO( SEND_TO )
            )
            bridge_slave_none_missing_inst
            (
                 .clk( clk )
                ,.res_n( res_n )
                
                ,.s_axi( s_axi )
                ,.noc( noc )
            );
            
        end
        else
        begin
            
            bridge_slave_missing
            #(
                 .ID( ID )
                
                ,.SEND_TO( SEND_TO )
            )
            bridge_slave_missing_inst
            (
                 .clk( clk )
                ,.res_n( res_n )
                
                ,.s_axi( s_axi )
                ,.noc( noc )
            );
            
        end
        
    endgenerate
    
endmodule
