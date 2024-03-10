
module uart
#(
     parameter BAUD = 115200
)
(
     input      clk
    ,input      res_n
    ,input[6:0] data
    ,input      wr
    ,output reg tx
    ,output reg busy
);
    
    //~ wire clk_baud;
    
    wire rx_clk_en_w;
    wire tx_clk_en_w;
    
    wire clk_baud_rising_w;
    
    uart_clk
    #(
         .BAUD( BAUD )
    )
    uart_clk_inst
    (
         .clk( clk )
        ,.res_n( res_n )
        ,.clk_baud_rising( clk_baud_rising_w )
    );
    
    uart_tx #() uart_tx_inst
    (
         .clk( clk )
        ,.res_n( res_n )
        ,.clk_baud_rising( clk_baud_rising_w )
        ,.data( data )
        ,.wr( wr )
        ,.tx( tx )
        ,.busy( busy )
    );
    
endmodule
