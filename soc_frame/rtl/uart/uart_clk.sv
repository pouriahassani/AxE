
module uart_clk
#(
     parameter BAUD = 115200
)
(
     input      clk
    ,input      res_n
    ,(* mark_debug = "true" *) output reg clk_baud_rising
);

(* mark_debug = "true" *) parameter CNT_TO = `CLK / BAUD;

(* mark_debug = "true" *) integer cnt = 0;

(* mark_debug = "true" *) reg clk_baud;
(* mark_debug = "true" *) reg clk_baud_old;

assign clk_baud_rising = ( clk_baud == 1'b1 ) && ( clk_baud_old == 1'b0 );

always @( posedge clk )
begin : uart_clk_proc
    
    if ( ! res_n )
    begin
        
        cnt = 0;
        clk_baud = 1'b0;
        clk_baud_old = 1'b0;
        
    end
    else
    begin
        
        clk_baud_old = clk_baud;
        
        if ( cnt == CNT_TO )
        begin
            
            cnt = 0;
            clk_baud = ~clk_baud;
            
        end
        else
        begin
            
            cnt = cnt + 1;
            
        end
        
    end
    
end

endmodule
