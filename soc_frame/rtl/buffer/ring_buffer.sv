
/* ****************************************************************************
  This Source Code Form is subject to the terms of the
  Open Hardware Description License, v. 1.0. If a copy
  of the OHDL was not distributed with this file, You
  can obtain one at http://juliusbaxter.net/ohdl/ohdl.txt
  
  Copyright (C) 2019 Stefan Huemer <stefan@huemer.tech>
  
***************************************************************************** */

module ring_buffer #(
    
     parameter DATA_WIDTH = 32
    ,parameter BUFFER_DEPTH = 10
    
    ,parameter ALLOW_OVERWRITE_ON_FULL = 0
)
(
     input clk
    ,input res_n
    
    ,input      [ DATA_WIDTH-1:0 ] data_in
    ,output reg [ DATA_WIDTH-1:0 ] data_out
    
    ,input      data_in_valid
    ,output reg data_out_valid
    
    ,output reg full
    ,input recv_busy
    
);

// regs

(* mark_debug = "true" *) reg[ DATA_WIDTH-1:0 ] buffer[ BUFFER_DEPTH-1:0 ];

(* mark_debug = "true" *) integer p_in;
(* mark_debug = "true" *) integer p_out;

integer i;

(* mark_debug = "true" *) reg cooldown;

(* mark_debug = "true" *) reg empty;

(* mark_debug = "true" *) reg full_r;

// TODO - explain

//~ assign full = ( (p_in==(p_out-1)) || ( (p_in==(BUFFER_DEPTH-1)) && (p_out==0) ) );
assign full = full_r;

// wenn out, in einholt ist es leer
// wenn in, out einholt ist es voll


// der sender wartet immer

always @ ( posedge clk )
begin : ring_buffer_proc
    
    data_out_valid = 1'b0;
    
    if ( ! res_n )
    begin
        
        for ( i = 0; i < BUFFER_DEPTH; i = i + 1 )
            buffer[ i ] = 0;
        
        p_in = 0;
        p_out = 0;
        
        empty = 1'b1;
        full_r = 1'b0;
        cooldown = 1'b0;
        
    end
    else
    begin
        
        //~ empty = ( p_out == p_in );
        
        // TODO - kann das alles in einem process sein?
        
        if ( data_in_valid == 1'b1 )
        begin
            
            buffer[ p_in ] = data_in;
            
            if ( BUFFER_DEPTH-1 == p_in )
                p_in = 0;
            else
                p_in = p_in + 1;
            
            // wenn wir den out pointer erreicht haben sind wir full
            
            if ( p_in == p_out )
                full_r = 1'b1;
            
            // wenn der buffer empty war, dann ist er das jetzt nicht mehr
            
            if ( empty == 1'b1 )
                empty = 1'b0;
            
        end
        
        // wenn der buffer nicht empty ist, dann koennen wir was raus schreiben
        
        if ( empty == 1'b0 )
        begin
            
            // through trial and error if figured out, that a delay is needed
            // here. I don't really know why.
            
            if ( cooldown == 1'b0 )
            begin
                
                if ( recv_busy == 1'b0 )
                begin
                    
                    cooldown = 1'b1;
                    
                    data_out = buffer[ p_out ];
                    data_out_valid = 1'b1;
                    
                    if ( BUFFER_DEPTH-1 == p_out )
                        p_out = 0;
                    else
                        p_out = p_out + 1;
                    
                    // wenn wir den in buffer erreicht habe, dann sind wir empty
                    
                    if ( p_out == p_in )
                        empty = 1'b1;
                    
                    // wenn der buffer full war, dann ist er das jetzt nicht mehr
                    
                    if ( full_r == 1'b1 )
                        full_r = 1'b0;
                    
                end
                
            end
            else
            begin
                
                cooldown = 1'b0;
                
            end
            
            
        end
        
    end
    
end

endmodule
