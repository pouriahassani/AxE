
module uart_tx
#()
(
     input clk
    ,input res_n
    
    ,(* mark_debug = "true" *) input clk_baud_rising
    
    ,(* mark_debug = "true" *) input [6:0] data
    ,(* mark_debug = "true" *) input wr
    
    ,(* mark_debug = "true" *) output reg tx
    ,(* mark_debug = "true" *) output reg busy
);

(* mark_debug = "true" *) enum
{
     IDLE
    ,SEND_START
    ,SEND_DATA
    ,SEND_STOP
}state;

(* mark_debug = "true" *) reg [ 7:0 ] latched_data;
(* mark_debug = "true" *) integer cnt_bit;

always @ ( posedge clk )
begin : uart_tx_proc
    
    if ( ! res_n )
    begin
        
        state = IDLE;
        
        latched_data = 8'b00000000;
        cnt_bit = 0;
        //~ cnt_bit = 7;
        
        tx = 1'b1;
        
    end
    else
    begin
        
        busy = 1'b1;
        
        case(state)
        
        // -------------------------------------------------------------------------
        // IDLE
        // -------------------------------------------------------------------------
        
        IDLE:
        begin
            
            busy = 1'b0;
            
            tx = 1'b1;
            
            if ( wr == 1'b1 )
            begin
                
                cnt_bit = 0;
                //~ cnt_bit = 7;
                
                latched_data[ 6:0 ] = data;
                
                state = SEND_START;
                
                busy = 1'b1;
                
            end
            
        end
        
        // -------------------------------------------------------------------------
        // SEND_START
        // -------------------------------------------------------------------------
        
        // we set tx to 0 and jump to the next state. there we will wait for
        // the next occurance of clk_baud_rising.
        // therefore the transmission of the start bit is actually done during
        // the SEND_DATA state.
        
        SEND_START:
        begin
            
            if ( clk_baud_rising == 1'b1 )
            begin
                
                tx = 1'b0;
                
                state = SEND_DATA;
                
            end
            
        end
        
        // -------------------------------------------------------------------------
        // SEND_DATA
        // -------------------------------------------------------------------------
        
        SEND_DATA:
        begin
            
            if ( clk_baud_rising == 1'b1 )
            begin
                
                tx = latched_data[ cnt_bit ];
                cnt_bit = cnt_bit + 1;
                //~ cnt_bit = cnt_bit - 1;
                
                if ( cnt_bit == 8 ) state = SEND_STOP;
                //~ if ( cnt_bit == 0 ) state = SEND_STOP;
                
            end
            
        end
        
        // -------------------------------------------------------------------------
        // SEND_STOP
        // -------------------------------------------------------------------------
        
        SEND_STOP:
        begin
            
            if ( clk_baud_rising == 1'b1 )
            begin
                
                tx = 1'b1;
                
                state = IDLE;
                
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
